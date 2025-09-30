from langchain_core.prompts import ChatPromptTemplate, FewShotChatMessagePromptTemplate
from langchain_core.messages import HumanMessage, SystemMessage, AIMessage, BaseMessage
from langchain_openai import ChatOpenAI
from langchain.callbacks.base import BaseCallbackHandler
from pydantic import BaseModel, Field

import logging, httpx, os, json
from datetime import datetime
from tqdm import tqdm

BabelTower_dir = os.getenv("BABELTOWER_DIR", "./BabelTower/test/mono_cases.jsonl")

def readdata(filename):
    data_list = []
    with open(filename, 'r', encoding='utf-8') as f:
        data_list = [json.loads(line) for line in f]
    return data_list

try:
    C_CUDA_Data = readdata(BabelTower_dir)
except Exception as err:
    print(f"Cannot read the few-shots examples - BabelTower_dir({BabelTower_dir}): {err}")
    exit()

def few_shots_prompt(nums: int = 3) -> FewShotChatMessagePromptTemplate:
    example_messages = []
    for i in range(min(nums, len(C_CUDA_Data))):
        example = {
            "src_code": C_CUDA_Data[i]["cuda_code"],
            "trans_code": C_CUDA_Data[i]["cpp_code"]
        }
        example_messages.append(example)

    example_prompt = ChatPromptTemplate.from_messages(
        [("human", "{src_code}"), 
         ("ai", "{trans_code}")]
    )

    few_shots_prompt = FewShotChatMessagePromptTemplate(
        example_prompt=example_prompt,
        examples=example_messages,
    )

    return few_shots_prompt


def get_LLM_gen_prompt() -> ChatPromptTemplate:
    few_shots = few_shots_prompt()
    system_message = """
You are an expert in translating CUDA kernels into serial C++ code.  
Please follow these steps:
1. Study the provided GPU CUDA function to C++ function on CPU few-shots examples to infer translation patterns.  
2. Analyze the given CUDA kernel for grid, block and thread parallel semantics.
3. Generate semantically-equivalent, syntax-correct serial C++ code.  
4. Review the generated C++ and self-correct if necessary.
5. keep the generated C++ code able to be compiled separately by adding necessary headers.
6. keep the function input variables consistent for the two codes(CUDA and C++).

Output **only** a valid JSON object with the following fields:
{{
  "trans_code": "<pure C++ function code, no main, no markdown fences>",
  "analysis": "<brief summary of translation highlights>"
}}
"""
    
    human_message = """
    CUDA Kernel: {src_code}
    """
    return ChatPromptTemplate.from_messages([
        ("system", system_message),
        #few_shots,
        ("human", human_message),
    ])

def get_LLM_UT_gen_prompt() -> ChatPromptTemplate:
    system_template = """
    You are a CUDA kernel development expert. You need to generate an unit test code or repair the existing given wrong unit test code with the error message from compiler feedback to verify whether the output results are identical with each other for a given **CUDA** kernel code on GPU and a given reference **C++** code on CPU. The requirements for the generated unit test cases include:
    1. the generated unit test code include main function, multiple unit test functions, **CUDA** kernel and the reference **C++** code.
    2. the generated unit test code shold be both correct in syntax and semantics.
    3. if the unit test code and the error message from compiler feedback have been given, try to repair the given unit test code instead of re-generation. 
    4. when executing the compiled unit test code, if the output results of the **CUDA** kernel function and reference **C++** function are identical, the print message must contain **UT_Verify: Pass**, on the other hand, if they are not identical, the print message must contain "UT_Verify: Fail".
    5. if the output results of the **CUDA** and reference **C++** functions are related to floating-point numbers, use the threshold of **1e-2** to measure the relative error of outputs like **err = abs(Y_cuda - Y_Cpp) / abs(Y_cpp)** in the main function of the unit test code.
    
    Output **only** a valid JSON object with the following fields:
    {{
      "UT_code": "<the complete unit test code>",
      "analysis": "<brief summary of unit test code generation or fixing>"
    }}
    """
    
    human_template = """
    CUDA Kernel: {src_code}
    C++ Code: {trans_code}
    Unit Test Code: {UT_code}
    Error feedback of previous unit test code: {feedback_UT}
    """
    
    return ChatPromptTemplate.from_messages([
        ("system", system_template),
        ("human", human_template),
    ])

def get_semantic_LLM_verify_prompt() -> ChatPromptTemplate:
    system_template = """
    You are an expert in CUDA and C++ programming. Your task is to roughly Compare the functional equivalence between a CUDA kernel implementation and its corresponding C++ CPU implementation, ensuring they produce identical results (ignoring floating-point precision differences and parallel execution timing).

    **Input Requirements:**
    - Provide two code segments:
    1. Original CUDA kernel code
    2. Equivalent C++ CPU implementation code

    **Analysis Guidelines:**

    **1. Memory Operations Analysis:**
    - Check that memory access patterns match in terms of indexing and stride

    **2. Computational Logic Verification:**
    - Map CUDA thread/block indexing (threadIdx, blockIdx) to equivalent loop structures in C++
    - Ensure mathematical operations and algorithms are identical
    - Verify that reduction operations (atomic operations, warps) are correctly serialized
    - Confirm boundary conditions and edge cases are handled equivalently

    **3. Control Flow Consistency:**
    - Check that conditional statements (if/else, switch) maintain identical branching logic
    - Verify loop structures match in iteration ranges and termination conditions
    - Ensure synchronization points (__syncthreads()) are properly handled in sequential code

    **4. Data Structure Alignment:**
    - Confirm equivalent data types and structures are used
    - Verify memory layout and padding are consistent where relevant

    **Key Comparison Points:**
    - Input/output parameters and their handling
    - Global/local memory access patterns
    - Mathematical computations and operator precedence
    - Error handling and boundary checks
    - Algorithmic steps and computational workflow

    **Output Format:**
    - Output must be a JSON object with two fields: "feedback_LLM" (brief summary for the comparison) and "LLM_Verify_Result"("Yes" or "No"):
        - LLM_Verify_Result = "Yes": if the final conclusion is that the two codes are functionally equivalent
        - LLM_Verify_Result = "No": if the final conclusion is that the two codes are not functionally equivalent

    **Important Notes:**
    - Focus on logical functionalities equivalence rather than performance characteristics
    - Focus on the main functionalities comparison, and neglect some corner cases
    - Account for sequential execution model differences
    - Ignore CUDA-specific optimizations that don't affect final results
    - Consider grid-stride loops versus sequential loops as functionally equivalent
    - do not consider the discrepancies caused by pointer alias problems of input variables for the comparison

    **Example Comparison Pattern:**
    CUDA: `array[threadIdx.x + blockIdx.x * blockDim.x] = ...`
    C++: `for(int i = 0; i < total_elements; i++) array[i] = ...`
    Considered functionally equivalent when iteration ranges match
    """

    human_template = """
    The two codes to be compared are:
    ------------------------------------
    Original CUDA Kernel Function:
    ```{src_code}```

    ------------------------------------
    Translated C++ code:
    ```{trans_code}```
    """
    return ChatPromptTemplate.from_messages([
        ("system", system_template),
        ("human", human_template),
    ])

def get_syntax_fix_prompt() -> ChatPromptTemplate:
    system_message = SystemMessage(content="""
    You are an advanced programming expert. Fix syntax errors in the C++ code based on compiler feedback to generate new correct C++ code able to be separately compiled. It means that necessary headers should be added.
    Output must be a JSON object with two fields: "trans_code" (the fixed C++ code) and "analysis" (brief summary).
    """)
    human_message = """
    CUDA Kernel: {src_code}
    C++ Code: {trans_code}
    Compiler Error: {feedback_compile}
    """
    return ChatPromptTemplate.from_messages([
        system_message,
        ("human", human_message),
    ])

def get_semantic_LLM_fix_prompt() -> ChatPromptTemplate:
    system_message = SystemMessage(content="""
    You are an advanced programming expert. Fix semantic errors in the C++ code based on feedback to generate new correct C++ code able to be separately compiled. It means that necessary headers should be added.
    Output must be a JSON object with two fields: "trans_code" (the fixed C++ code) and "analysis" (brief summary).
    """)
    human_message = """
    CUDA Kernel: {src_code}
    C++ Code: {trans_code}
    Feedback of LLM: {feedback_LLM}
    """
    return ChatPromptTemplate.from_messages([
        system_message,
        ("human", human_message),
    ])


class generation_output_format(BaseModel):
    trans_code: str = Field(description="translated **pure C++** function code without any explanary messages and main functions")
    analysis: str = Field(description="brief summary for the translation")

class generation_UT_format(BaseModel):
    UT_code: str = Field(description="generated complete Unit test code")
    analysis: str = Field(description="brief summary for the generated unit test code or the fixing of the given unit test code")

class LLM_verify_format(BaseModel):
    feedback_LLM: str = Field(description="brief summary if the codes have any discrepancies")
    LLM_Verify_Result: str = Field(description="Yes(if the codes are functionally equivalent); No(if the codes are not functionally equivalent)")

class fix_syntax_format(BaseModel):
    trans_code: str = Field(description="repaired **pure C++** function code without any explanary messages and main functions")
    analysis: str = Field(description="brief summary for the code syntax error and fixed methods")

class fix_semantic_format(BaseModel):
    trans_code: str = Field(description="repaired **pure C++** function code without any explanary messages and main functions")
    analysis: str = Field(description="brief summary for the code semantic error and fixed methods")

def log_request_size(request: httpx.Request):
    cl = request.headers.get("content-length")
    if cl is not None:
        size = int(cl)
    else:
        body = request.content or b""
        size = len(body)
    logging.info(
        "[%s] body_bytes=%d %s %s\n",
        datetime.now().isoformat(),
        size,
        request.method,
        request.url
    )

class tqdm_token_progress(BaseCallbackHandler):
    def __init__(self, expected_tokens = None, desc = "LLM generating ..."):
        self.expected_tokens = expected_tokens
        self.desc = desc
        self.pbar = None
        self._n = 0
        self.acc = ""

    def on_llm_start(self, *args, **kwargs):
        self.pbar = tqdm(total = self.expected_tokens, desc = self.desc, dynamic_ncols = True)

    def on_llm_new_token(self, token: str, **kwargs):
        dt = len(token)
        self._n += dt
        self.acc += token
        self.pbar.update(dt)

    def on_llm_end(self, *args, **kwargs):
        print(f"total_generated_tokens: {self._n}")
        if self.pbar:
            self.pbar.close()


expected_tokens = 8192
http_client = httpx.Client(verify = False, event_hooks = {"request": [log_request_size]})
http_client2 = httpx.Client(verify = False, event_hooks = {"request": [log_request_size]})
#
token_visual_handler1 = tqdm_token_progress(expected_tokens = expected_tokens, desc = "LLM Streaming ...")
token_visual_handler2 = tqdm_token_progress(expected_tokens = expected_tokens, desc = "LLM Streaming ...")
token_visual_handler3 = tqdm_token_progress(expected_tokens = expected_tokens, desc = "LLM Streaming ...")
token_visual_handler4 = tqdm_token_progress(expected_tokens = expected_tokens, desc = "LLM Streaming ...")
token_visual_handler5 = tqdm_token_progress(expected_tokens = expected_tokens, desc = "LLM Streaming ...")
#
ENGINE_GEN = os.getenv("ENGINE_GEN", "Pro/deepseek-ai/DeepSeek-R1")
ENGINE_ANALYSIS = os.getenv("ENGINE_ANALYSIS", "Pro/deepseek-ai/DeepSeek-R1")
ENGINE_REPAIR = os.getenv("ENGINE_REPAIR", "Pro/deepseek-ai/DeepSeek-R1")
API_URL = os.getenv("OPENAI_API_URL", "http://api.siliconflow.cn/v1")
API_KEY = os.getenv("OPENAI_API_KEY")

if API_KEY is None:
    raise ValueError(f"please set the API_KEY environment variables!")

max_tokens = 16384
llm_gen = ChatOpenAI(
    openai_api_base = API_URL,
    openai_api_key = API_KEY,
    model = ENGINE_GEN,
    http_client = http_client,
    streaming = True,
    max_tokens = 16384,
    temperature = 0.3,
    callbacks = [token_visual_handler1]
)
llm_UT_gen = ChatOpenAI(
    openai_api_base = API_URL,
    openai_api_key = API_KEY,
    model = ENGINE_GEN,
    http_client = http_client,
    streaming = True,
    max_tokens = 16384,
    temperature = 0.3,
    callbacks = [token_visual_handler2]
)
llm_syntax_fix = ChatOpenAI(
    openai_api_base = API_URL,
    openai_api_key = API_KEY,
    model = ENGINE_REPAIR,
    http_client = http_client,
    streaming = True,
    max_tokens = 16384,
    temperature = 0.1,
    callbacks = [token_visual_handler3]
)
llm_semantic_verify = ChatOpenAI(
    openai_api_base = API_URL,
    openai_api_key = API_KEY,
    model = ENGINE_ANALYSIS,
    http_client = http_client,
    streaming = True,
    max_tokens = 16384,
    temperature = 0.1,
    callbacks = [token_visual_handler4],
)
llm_semantic_fix = ChatOpenAI(
    openai_api_base = API_URL,
    openai_api_key = API_KEY,
    model = ENGINE_REPAIR,
    http_client = http_client,
    streaming = True,
    max_tokens = 16384,
    temperature = 0.3,
    callbacks = [token_visual_handler5]
)
#
Chain_LLM_Gen = get_LLM_gen_prompt() | llm_gen.with_structured_output(generation_output_format, method = 'json_mode')
Chain_LLM_UT_Gen = get_LLM_UT_gen_prompt() | llm_UT_gen.with_structured_output(generation_UT_format, method = 'json_mode')
Chain_LLM_verify = get_semantic_LLM_verify_prompt() | llm_semantic_verify.with_structured_output(LLM_verify_format, method = 'json_mode')
Chain_LLM_syntax_fix = get_syntax_fix_prompt() | llm_syntax_fix.with_structured_output(fix_syntax_format, method = 'json_mode')
Chain_LLM_semantic_fix = get_semantic_LLM_fix_prompt() | llm_semantic_fix.with_structured_output(fix_semantic_format, method = 'json_mode')

