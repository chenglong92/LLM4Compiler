from langgraph.graph import END, START, StateGraph
from langchain_core.runnables import RunnableConfig
from typing import List, Literal
from typing_extensions import TypedDict
import subprocess
import re, os
from PromptTemplates import Chain_LLM_UT_Gen, Chain_LLM_Gen, Chain_LLM_verify, Chain_LLM_syntax_fix, Chain_LLM_semantic_fix
from tools import extract_function_name, tool_compile, tool_compile_vectorization, tool_formal_verification, formal_verification, tool_gen_unit_test, tool_execute_test_code
from PromptTemplates import readdata
from tools import save_array_to_excel
import numpy as np
import pandas as pd

class State(TypedDict):
    # the state of G2CTrans Agent
    kernel_name: str                          # kernel_name
    path_name: str                            # the path name for the src_code

    LLM_gen_max_iter: int                     # LLM generation maximum iteration times.
    LLM_syntax_fix_iter: int                  # LLM syntax fixing iteration step.
    LLM_syntax_fix_max_iter: int              # LLM syntax fixing maximum iteration times.
    LLM_verify_semantic_fix_iter: int         # LLM verify semantic fixing iteration times.
    LLM_verify_semantic_fix_max_iter: int     # LLM verify semantic fixing maximum iteration times
    LLM_UT_semantic_fix_iter: int             # LLM UT semantic fixing iteration times.
    LLM_UT_semantic_fix_max_iter: int         # LLM UT semantic fixing maximum iteration times

    promptmessage: List[str]           # used prompt messages
    # Annotated[list, add_messages]
    memory: List[str]                  # record the agent memory
    src_code: str                      # original CUDA source code(kernel code)
    trans_code: str                    # translated C++ code from src_code(CUDA code)
    ref_code: str                      # reference code for formal verification (optional)
    UT_code: str                       # Unit test code
    analysis: str                      # translation analysis for src_code to trans_code

    eval_LLM_gen: bool                 # evaluation status for llm generation for code(False: generation failed).
    eval_syntax_compile: bool          # evaluation status for syntax check using compiler(True - pass compilation)
    eval_semantic_LLM: bool            # evaluation status for semantic check using LLM verifier(True - pass LLM comparison)
    eval_semantic_FV: bool             # evaluation status for semantic check using formal verification(optional)
    eval_semantic_UT: bool             # evaluation status for semantic check using LLM synthesized unit test
    eval_semantic_final: bool          # overall evaluation status for semantic check(LLM + UT/LLM + FV + UT)

    feedback_compile: str              # feedback information from compilation evaluation
    feedback_LLM: str                  # feedback from LLM verifier evaluation
    feedback_FV: str                   # feedback from formal verification evaluation
    feedback_UT: str                   # feedback from unit test evaluation

    debug_LLM_generation: bool         # debug for node-LLM_generation(print state)
    debug_Enode_syntax_compile: bool   # debug for node-Enode_syntax_compile(print state)
    debug_Enode_semantic_LLM: bool     # debug for node-Enode_semantic_LLM(print state)
    debug_Enode_semantic_UT: bool      # debug for node-Enode_semantic_UT(print state)
    debug_Fnode_syntax_compile: bool   # debug for node-Fnode_syntax_compile(print state)
    debug_Fnode_semantic_LLM: bool     # debug
    debug_Fnode_semantic_UT: bool

class G2CTrans:
    def __init__(self, 
                 LLM_gen_max_iter: int = 5,
                 LLM_syntax_fix_max_iter: int = 5,
                 LLM_verify_semantic_fix_max_iter: int = 5,
                 LLM_UT_semantic_fix_max_iter: int = 4,
                 is_perf_feedback: bool = False):
        #
        self.app = self.workflow()
        self.kernel_name: str = None
        self.is_perf_feedback = is_perf_feedback
        self.LLM_gen_max_iter = LLM_gen_max_iter
        self.LLM_syntax_fix_max_iter = LLM_syntax_fix_max_iter
        self.LLM_verify_semantic_fix_max_iter = LLM_verify_semantic_fix_max_iter
        self.LLM_UT_semantic_fix_max_iter = LLM_UT_semantic_fix_max_iter

    def create_initial_state(self, src_code: str, **kwargs) -> State:
        state: State = {
            "src_code": src_code,
            "kernel_name": kwargs.get("kernel_name", "default_kernel"),
            "path_name": kwargs.get("path_name", "./"),
            "LLM_gen_max_iter": self.LLM_gen_max_iter,
            "LLM_syntax_fix_max_iter": self.LLM_syntax_fix_max_iter,
            "LLM_verify_semantic_fix_max_iter": self.LLM_verify_semantic_fix_max_iter,
            "LLM_UT_semantic_fix_max_iter": self.LLM_UT_semantic_fix_max_iter,
            "promptmessage": [],
            "memory": [],
            "trans_code": "",
            "UT_code": "",
            "analysis": "",
            "eval_LLM_gen": True,
            "eval_syntax_compile": False,
            "eval_semantic_LLM": False,
            "eval_semantic_FV": False,
            "eval_semantic_UT": False,
            "eval_semantic_final": False,
            "feedback_compile": "",
            "feedback_LLM": "",
            "feedback_FV": "",
            "feedback_UT": "",
            "LLM_syntax_fix_iter": 0,
            "LLM_verify_semantic_fix_iter": 0,
            "LLM_UT_semantic_fix_iter": 0,
            "debug_LLM_generation": False,
            "debug_Enode_syntax_compile": False,
            "debug_Enode_semantic_LLM": False,
            "debug_Enode_semantic_UT": False,
            "debug_Fnode_syntax_compile":False,
            "debug_Fnode_semantic_LLM": False,
            "debug_Fnode_semantic_UT": False,
        }
        
        if "ref_code" in kwargs:
            state["ref_code"] = kwargs["ref_code"]
        return state
    
    def input_preprocessing(self, state: State, config: RunnableConfig):
        #
        """standardize input code"""
        # add preprocessing module(like remove annotation/blank）
        #print(f"code: {code}")
        #print("===========================")
        code = state["src_code"]
        clean_code = "\n".join([line for line in code.splitlines() if line.strip()])
        #print(f"# Input Type: CUDA\n{clean_code}")
        #print("===========================")
        #print(f"input_processing: {clean_code}")
        return {"src_code": clean_code}
    
    def LLM_generation(self, state: State, config: RunnableConfig):
        if state["debug_LLM_generation"]:
            print(f"=====================LLM_generation - \n state: {state}")
        n_attempt = 0
        src_code = state["src_code"]
        while n_attempt < state["LLM_gen_max_iter"]:
            try:
                result = Chain_LLM_Gen.invoke({"src_code": state["src_code"]})
                if state["debug_LLM_generation"]:
                    print(f"LLM_generation: \n trans_code: \n{result.trans_code}, \n analysis: \n {result.analysis}")
                return {"trans_code": result.trans_code, "analysis": result.analysis}
            except Exception as err:
                if state["debug_LLM_generation"]:
                    print(f"For {n_attempt}-th try, LLM launching failed: {err}")
                n_attempt += 1
        raise Exception("Reach the Maximum Try to Launch LLM Generation!")
    
    def Enode_syntax_compile(self, state: State, config: RunnableConfig):
        if state["debug_Enode_syntax_compile"]:
            print(f"=====================Enode_syntax_compile - \n state: {state}")
        #pdb.set_trace()
        trans_code = state["trans_code"]
        filename = "test_code.cpp"
        with open(filename, "w") as f:
            f.write(trans_code)
        res = tool_compile(filename)
        if res.returncode == 0:
            return {"eval_syntax_compile": True, "eval_semantic_LLM": False, "eval_semantic_UT": False}
        else:
            return {"eval_syntax_compile": False, "feedback_compile": res.stderr}
    
    def Enode_syntax_compile_branch(self, state: State) -> Literal["Enode_semantic_LLM", "Fnode_syntax_compile"]:
        if state["eval_syntax_compile"]:
            # pass the syntax check
            trans_code = state["trans_code"]
            if state["debug_Enode_syntax_compile"]:
                print(f"============Enode_syntax_compile -> Enode_semantic_LLM: Pass Syntax Check =========\n trans_code: {trans_code}")
            return "Enode_semantic_LLM"
        else:
            trans_code = state["trans_code"]
            if state["debug_Enode_syntax_compile"]:
                print(f"============Enode_syntax_compile -> Fnode_syntax_compile: Not Pass Syntax Check =========\n trans_code: {trans_code}")
            return "Fnode_syntax_compile"
    
    def Enode_semantic_LLM(self, state: State, config: RunnableConfig):
        if state["debug_Enode_semantic_LLM"]:
            print(f"=====================Enode_semantic_LLM - \n state: {state}")
        trans_code = state["trans_code"]
        src_code = state["src_code"]
        n_attempt = 0
        while n_attempt < state["LLM_gen_max_iter"]:
            response = Chain_LLM_verify.invoke({"src_code": src_code, "trans_code": trans_code})
            LLM_Verify_Result = response.LLM_Verify_Result
            feedback_LLM = response.feedback_LLM
            if LLM_Verify_Result == "Yes":
                if state["debug_Enode_semantic_LLM"]:
                    print(f"============Enode_semantic_LLM: LLM_Verify_Result (Pass): \n {LLM_Verify_Result}, \n feedback_LLM: {feedback_LLM}")
                return {"eval_semantic_LLM": True, "LLM_verify_semantic_fix_iter": 0}
            else:
                if state["debug_Enode_semantic_LLM"]:
                    print(f"============Enode_semantic_LLM: LLM_Verify_Result (Not Pass): \n {LLM_Verify_Result}, \n feedback_LLM: {feedback_LLM}")
                return {"eval_semantic_LLM": False, "feedback_LLM": feedback_LLM}
            n_attempt += 1
        raise Exception("Reach the Maximum Try to Launch LLM Verifier!")
    
    def Enode_semantic_LLM_branch(self, state: State) -> Literal["Enode_semantic_UT", "Fnode_semantic_LLM"]:
        if state["eval_semantic_LLM"]:
            trans_code = state["trans_code"]
            if state["debug_Enode_semantic_LLM"]:
                print(f"============Enode_semantic_LLM -> Enode_semantic_UT: Pass Semantic LLM Check =========\n trans_code: {trans_code}")
            return "Enode_semantic_UT"
        else:
            trans_code = state["trans_code"]
            if state["debug_Enode_semantic_LLM"]:
                print(f"============Enode_semantic_LLM -> Fnode_semantic_LLM: Not Pass Semantic LLM Check =========\n trans_code: {trans_code}")
            return "Fnode_semantic_LLM"
    
    def Enode_semantic_UT(self, state: State, config: RunnableConfig):
        if state["debug_Enode_semantic_UT"]:
            print(f"=====================Enode_semantic_UT - \n state: {state}")
        src_code = state["src_code"]
        trans_code = state["trans_code"]
        n_attempt = 0
        gen_feedback = ""
        test_code = ""
        ##### for temperary neglecting the UT test when GPU is unavaiable.
        #return {"UT_code": test_code, "eval_semantic_UT": True, "LLM_UT_semantic_fix_iter": 0}
        ####
        while n_attempt < state["LLM_UT_semantic_fix_max_iter"]:
            test_code = tool_gen_unit_test(src_code, trans_code, test_code, gen_feedback, max_iter = state["LLM_UT_semantic_fix_max_iter"])
            output = tool_execute_test_code(test_code)
            if state["debug_Enode_semantic_UT"]:
                print(f"Enode_semantic_UT: {output}")
            #output = "Pass"    # for temporary test purpose when the GPU is unavaiable.
            if "test execution failed" in output:
                gen_feedback = output
                n_attempt += 1
                if n_attempt >= state["LLM_UT_semantic_fix_max_iter"]:
                    raise Exception("Reach the Maximum Try to Launch UT!")
                continue
            if "Pass" in output:
                if state["debug_Enode_semantic_UT"]:
                    print(f"Enode_semantic_UT: Pass, {test_code}")
                return {"UT_code": test_code, "eval_semantic_UT": True, "LLM_UT_semantic_fix_iter": 0}
            elif "Fail" in output:
                gen_feedback = output
                if state["debug_Enode_semantic_UT"]:
                    print(f"Enode_semantic_UT: Fail, {test_code}")
                return {"UT_code": test_code, "eval_semantic_UT": False, "feedback_UT": output}
    
    def Enode_semantic_UT_branch(self, state: State) -> Literal[END, "Fnode_semantic_UT"]:
        if state["eval_semantic_UT"]:
            trans_code = state["trans_code"]
            print(f"============Enode_semantic_UT -> END: Pass Semantic UT Check =========\n trans_code: {trans_code}")
            return END
        else:
            trans_code = state["trans_code"]
            print(f"============Enode_semantic_UT -> Fnode_semantic_UT: Not Pass Semantic UT Check =========\n trans_code: {trans_code}")
            return "Fnode_semantic_UT"
    
    def Fnode_syntax_compile(self, state: State, config: RunnableConfig):
        if state["debug_Fnode_syntax_compile"]:
            print(f"=====================Fnode_syntax_compile - \n state: {state}")
        # fix the syntax error according to the compiler feedback
        results = Chain_LLM_syntax_fix.invoke({
            "src_code": state["src_code"],
            "trans_code": state["trans_code"],
            "feedback_compile": state["feedback_compile"]
        })
        if state["debug_Fnode_syntax_compile"]:
            print(f"Fnode_syntax_compile: \n trans_code: \n {results.trans_code}, \n analysis: {results.analysis}")
        trans_code = results.trans_code
        return {"trans_code": trans_code, "feedback_compile": results.analysis}
    
    def Fnode_syntax_compile_branch(self, state: State) -> Literal["Enode_syntax_compile", END]:
        if state["LLM_syntax_fix_iter"] < state["LLM_syntax_fix_max_iter"]:
            state["LLM_syntax_fix_iter"] += 1
            trans_code = state["trans_code"]
            LLM_syntax_fix_iter = state["LLM_syntax_fix_iter"]
            if state["debug_Fnode_syntax_compile"]:
                print(f"============the {LLM_syntax_fix_iter}-he fixing with Fnode_syntax_compile =========\n trans_code: {trans_code}")
            return "Enode_syntax_compile"
        else:
            raise Exception("Reach the maximum iteration times for syntax fixing from compiler feedback, cannot fix the syntax error")
            return END
    
    def Fnode_semantic_LLM(self, state: State, config: RunnableConfig):
        if state["debug_Fnode_semantic_LLM"]:
            print(f"=====================Fnode_semantic_LLM - \n state: {state}")
        # fix the semantic error according to the LLM itselves' feedback.
        results = Chain_LLM_semantic_fix.invoke({
            "src_code": state["src_code"],
            "trans_code": state["trans_code"],
            "feedback_LLM": state["feedback_LLM"]
        })
        if state["debug_Fnode_semantic_LLM"]:
            print(f"Fnode_semantic_compile: {results}")
        trans_code = results.trans_code
        return {"trans_code": trans_code}
    
    def Fnode_semantic_LLM_branch(self, state: State) -> Literal["Enode_syntax_compile", END]:
        if state["LLM_verify_semantic_fix_iter"] < state["LLM_verify_semantic_fix_max_iter"]:
            state["LLM_verify_semantic_fix_iter"] += 1
            trans_code = state["trans_code"]
            LLM_verify_semantic_fix_iter = state["LLM_verify_semantic_fix_iter"]
            if state["debug_Fnode_semantic_LLM"]:
                print(f"============the {LLM_verify_semantic_fix_iter}-th fixing with Fnode_semantic_LLM =========\n trans_code: {trans_code}")
        else:
            raise Exception("Reach the maximum iteration times for semantic fixing from LLM feedback, cannot fix the semantic error")
            return END
    
    def Fnode_semantic_UT(self, state: State, config: RunnableConfig):
        if state["debug_Fnode_semantic_UT"]:
            print(f"=====================Fnode_semantic_UT - \n state: {state}")
        # fix the semantic error according to the LLM synthesized Unit test
        results = Chain_LLM_semantic_fix.invoke({
            "src_code": state["src_code"],
            "trans_code": state["trans_code"],
            "feedback_LLM": state["feedback_UT"]  # 注意：这里使用 feedback_UT 作为反馈
        })
        if state["debug_Fnode_semantic_UT"]:
            print(f"Fnode_semantic_UT: {results}")
        trans_code = results.trans_code
        return {"trans_code": trans_code}
    
    def Fnode_semantic_UT_branch(self, state: State) -> Literal["Enode_syntax_compile", END]:
        if state["LLM_UT_semantic_fix_iter"] < state["LLM_UT_semantic_fix_max_iter"]:
            state["LLM_UT_semantic_fix_iter"] += 1
            trans_code = state["trans_code"]
            LLM_UT_semantic_fix_iter = state["LLM_UT_semantic_fix_iter"]
            if state["debug_Fnode_semantic_UT"]:
                print(f"============Fnode_semantic_UT -> Enode_syntax_compile: Pass Semantic UT Check =========\n trans_code: {trans_code}")
            return "Enode_syntax_compile"
        else:
            raise Exception("Reach the maximum iteration times for semantic fixing from UT feedback, cannot fix the semantic error")
            return END
    
    def workflow(self):
        graph = StateGraph(State)
        graph.add_node("input_preprocessing", self.input_preprocessing)
        graph.add_node("LLM_generation", self.LLM_generation)
        graph.add_node("Enode_syntax_compile", self.Enode_syntax_compile)
        graph.add_node("Enode_semantic_LLM", self.Enode_semantic_LLM)
        graph.add_node("Enode_semantic_UT", self.Enode_semantic_UT)
        graph.add_node("Fnode_syntax_compile", self.Fnode_syntax_compile)
        graph.add_node("Fnode_semantic_LLM", self.Fnode_semantic_LLM)
        graph.add_node("Fnode_semantic_UT", self.Fnode_semantic_UT)
        graph.add_edge(START, "input_preprocessing")
        graph.add_edge("input_preprocessing", "LLM_generation")
        graph.add_edge("LLM_generation", "Enode_syntax_compile")
        graph.add_conditional_edges("Enode_syntax_compile", self.Enode_syntax_compile_branch)
        graph.add_conditional_edges("Enode_semantic_LLM", self.Enode_semantic_LLM_branch)
        graph.add_conditional_edges("Enode_semantic_UT", self.Enode_semantic_UT_branch)
        graph.add_conditional_edges("Fnode_syntax_compile", self.Fnode_syntax_compile_branch)
        graph.add_conditional_edges("Fnode_semantic_LLM", self.Fnode_semantic_LLM_branch)
        graph.add_conditional_edges("Fnode_semantic_UT", self.Fnode_semantic_UT_branch)
        app = graph.compile()
        return app
    
    def process_code(self, src_code: str, **kwargs):
        initial_state = self.create_initial_state(src_code, **kwargs)
        #print(f"process_code: {initial_state}")
        solution = self.app.invoke(initial_state)
        from IPython.display import Image
        #Image(self.app.get_graph().draw_mermaid_png())
        mermaid_src = self.app.get_graph()
        trans_code = solution.get("trans_code")
        #print(f"Final Output: \n trans_code: \n {trans_code}")
        eval_semantic_UT = solution.get("eval_semantic_UT")
        '''
        if eval_semantic_UT:
            UT_code = solution.get("UT_code")
            print("===================Translation is Successful!!===================")
            print(f"src_code: \n {src_code}")
            print(f"trans_code: \n {trans_code}")
            print(f"UT_code: \n {UT_code}")
        '''
        return trans_code, mermaid_src, eval_semantic_UT

def test_BabelTower_datasets():
    agent = G2CTrans()
    BabelTower_dir = os.getenv("BABELTOWER_DIR", "./BabelTower/test/mono_cases.jsonl")
    try:
        C_CUDA_Data = readdata(BabelTower_dir)
    except Exception as Err:
        print(f"=======Cannot read the datasets - BabelTower for the err: {Err}")
        exit()
    num_rows = len(C_CUDA_Data)
    #
    cur_dir = os.getcwd()
    folder_name = "Results_G2C"
    folder_path = os.path.join(cur_dir, folder_name)
    if not os.path.exists(folder_path):
        os.makedirs(folder_path)
    else:
        print(f"{folder_path} has existed!")
    #
    verify_summary = np.zeros((num_rows, 2), dtype = int)
    verify_summary[:, 0] = np.arange(num_rows)
    verify_summary[:, 1] = -1
    #
    pass_count = 0
    for i in range(num_rows):
        cuda_code = C_CUDA_Data[i]["cuda_code"]
        ref_code = C_CUDA_Data[i]["cpp_code"]
        kernel_name = str(i)
        #
        try:
            print(f"==============Launch G2CTrans Agent Succeed for i = {i} ===========")
            translated_code, mermaid_src, eval_sematic_UT = agent.process_code(
                cuda_code,
                kernel_name = kernel_name,
                path_name = "./"
            )
            trans_filename = "trans_" + str(i) + ".cpp"
            ref_filename = "ref_" + str(i) + ".cpp"
            filepath_trans = os.path.join(folder_path, trans_filename)
            filepath_ref = os.path.join(folder_path, ref_filename)
            if not os.path.isfile(filepath_trans) or not os.path.isfile(filepath_ref):
                with open(filepath_trans, "w") as f:
                    f.write(translated_code)
                with open(filepath_ref, "w") as f:
                    f.write(ref_code)
            #
            verify_summary[i, 1] = formal_verification(translated_code, ref_code)
            if (verify_summary[i, 1] == 1):
                pass_count += 1
            print(f"eval_sematic_UT: {eval_sematic_UT} \n \n src_code: \n{cuda_code} \n \n trans_code: \n{translated_code} \n \n ref_code: {ref_code} \n \n verify_summary: {verify_summary[i, 1]} \n \n Total pass count: {pass_count} / {i+1}")
        except Exception as Err:
            print(f"==============Launch G2CTrans Agent Failed for: {Err}, jump to the next case: {i+1}")
            continue
        save_array_to_excel(verify_summary, "verificationsummary.xlsx")

if __name__ == "__main__":
    '''
    cuda_code = """
    __global__ void addKernel(int *c, const int *a, const int *b) {
        int i = threadIdx.x;
        c[i] = a[i] + b[i];
    }
    """
    '''

    '''
    agent = G2CTrans()
    translated_code, mermaid_src = agent.process_code(
        cuda_code,
        kernel_name="addKernel",
        path_name="./"
    )
    from IPython.display import Image
    # mermaid_src = self.app.get_graph().draw_mermaid()
    print(mermaid_src.draw_mermaid())
    '''
    test_BabelTower_datasets()

