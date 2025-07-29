from langchain.prompts import PromptTemplate
from langchain_openai import OpenAI
from langchain_core.runnables import RunnableLambda, RunnablePassthrough
from langchain_core.output_parsers import StrOutputParser
import re
import os
import httpx

http_client = httpx.Client(verify=False)

# 1. input processer
class PythonInputProcessor:
    def transform(self, input_data: dict) -> dict:
        code = input_data.get("code", "")
        text = input_data.get("text", "")
        code = "\n".join([line for line in code.splitlines() if line.strip()])
        print(f"code: {code}")
        print(f"text: {text}")
        return {"code": code, "text": text}

# 2. output parser
class CodeExtractor:
    def extract(self, text: str) -> str:
        """abstract pure CPP code from LLM output"""
        print("=============================")
        print(f"text: {text}")
        pattern = r"```cpp\n(.*?)```"
        match = re.search(pattern, text, re.DOTALL)
        print("=============================")
        print(f"Intermediate Code: {match.group(1).strip()}")
        return match.group(1).strip() if match else text

class printIR:
    def prints(self, input_data):
        print(input_data)
        return input_data

# 3. build complete chain-workflow
def build_format_agent(sys_prompt: str = None):
    # prompt tempalte
    if sys_prompt != None:
        OPTIMIZATION_PROMPT = PromptTemplate.from_template(sys_prompt)
    else:
        sys_prompt = """
        you are a software engineer. you are assigned a simple task: replace the function name of the given cpp program with a new function name - {text}. the requirements include:
        1. just replace the function name, do not change other code samples;
        2. the final optimized llm output must be fully c++ code without any other explanatory samples.
        The original function/program:
        ```cpp
        {code}
        ```
        Final output program format:
        ```cpp
        
        ```
        """
        OPTIMIZATION_PROMPT = PromptTemplate.from_template(sys_prompt)

    ENGINE = os.getenv("ENGINE")
    # model configurations
    llm = OpenAI(
        model=ENGINE,
        temperature=0.1,
        max_tokens=8192,
        http_client=http_client
    )

    # build processing components
    input_processor = RunnableLambda(PythonInputProcessor().transform)
    output_extractor = RunnableLambda(CodeExtractor().extract)
    print_pr = RunnableLambda(printIR().prints)
    
    # build processing chains
    chain = (
        RunnablePassthrough()
        | input_processor
        | OPTIMIZATION_PROMPT
        | print_pr
        | llm
        | StrOutputParser()
        | output_extractor
    )

    return chain

# 4. Agent encapsulation
class FormatAgent:
    def __init__(self, sys_prompt: str = None):
        self.chain = build_format_agent(sys_prompt)

    def run(self, input_data) -> str:
        return self.chain.invoke(input_data)

# 5. usecases
if __name__ == "__main__":
    # CUDA-C: system prompt
    sys_prompt = """ 
    you are a software engineer. you are assigned a simple task: replace the function name of the given cpp program with a new function name - {text}. the requirements include:
        1. just replace the function name, do not change other code samples;
        2. the final optimized llm output must be fully c++ code without any other explanatory samples.

        the original function/program:
        ```cpp
        {code}
        ```

        final output program format:
        ```cpp

        ```
    """
    #sys_prompt = "hello, introduce yourself."
    #agent = FormatAgent(sys_prompt)
    agent = FormatAgent()

    test_code = """
    void add_sources_d(const float* const model, float* wfp, const float* const source_amplitude, const int* const sources_z, const int* const sources_x, const int nz, const int nx, const int nt, const int ns, const int it) {
            for (int b = 0; b < ns; ++b) {
                for (int x = 0; x < ns; ++x) {
                    int i = sources_z[b * ns + x] * nx + sources_x[b * ns + x];
                    int ib = b * nz * nx + i;
                    wfp[ib] += source_amplitude[b * ns * nt + x * nt + it] * model[i];
                }
            }
        }
    """
    test_text = "add_source_ll"
    input_data = {"code": test_code, "text": test_text}
    #
    optimized_code = agent.run(input_data)

    print(f"Original Code: \n{test_code} \n   \nOptimized Code：\n{optimized_code}")
    #
    filename = "revised_code.cpp"
    if os.path.exists(filename) and os.path.isfile(filename):
        os.remove(filename)
    with open(filename, "a") as f:
        f.write(f"// original code: \n /*\n{test_code}\n*/\n")
        f.write(optimized_code)
