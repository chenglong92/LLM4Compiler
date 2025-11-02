from typing import List, Literal
import subprocess
import re
from PromptTemplates import Chain_LLM_UT_Gen
import os
import numpy as no
import pandas as pd
import openpyxl

def save_array_to_excel(array, filename):
    df = pd.DataFrame(array)
    df.to_excel(f"{filename}.xlsx", index = False, header = False)

def extract_function_name(code):
    pattern = r'''
        (?:[\w\s\*&const]+?\s+)
        (?:(?:\w+::)*)
        ([a-zA-Z_][a-zA-Z0-9_]*)
        \s*\([^)]*\)\s*
        \{
    '''
    match = re.search(pattern, code, re.VERBOSE)

    if match:
        return match.group(1)
    return None

def tool_compile(source_cpp: str):
    clang_path = os.getenv("CLANG_PATH", "clang++")
    if "clang" in clang_path:
        compile_cmd = [
            clang_path,
            "-O0",
            "-S", "-emit-llvm",
            source_cpp
        ]
    elif "nvcc" in clang_path:
        compile_cmd = [
            clang_path,
            "-c",
            "-x",
            "cu",
            source_cpp
        ]
    try:
        result = subprocess.run(compile_cmd, capture_output = True, text = True, check = True)
        return result
    except subprocess.CalledProcessError as err:
        # If clang compilation fails, return the error message
        return err

def tool_compile_vectorization(source_cpp: str):
    clang_path = os.getenv("CLANG_PATH", "clang++")
    compile_cmd = [
        clang_path,                        # Use BiShengCompiler
        "-O3",                             # Optimization level
        "-S", "-emit-llvm",
        "-Rpass-analysis=loop-vectorize",  # Add LLVM debug options
        "-Rpass=loop-vectorize",
        "-ffast-math",
        source_cpp,                        #
    ]
    try:
        result = subprocess.run(compile_cmd, capture_output = True, text = True, check = True)
        return result
    except subprocess.CalledProcessError as err:
        return err

def tool_formal_verification(src_name: str, tar_name: str):
    # e.g: src_name: A.cpp, tar_name: B.cpp
    alive_tv_cmd = ["alive-tv", src_name, tar_name]
    try:
        result = subprocess.run(alive_tv_cmd, capture_output = True, text = True, check = True)
        return result.stdout
    except subprocess.CalledProcessError as err:
        return err.stderr

def formal_verification(src_code: str, ref_code: str):
    filename_src = "src_code"
    filename_ref = "ref_code"
    src_name = extract_function_name(src_code)
    ref_name = extract_function_name(ref_code)
    #assert(not src_name or not ref_name), "Error: Failed to extract function name!"
    #
    new_src_code = src_code.replace(src_name, ref_name)
    #
    with open(filename_src + ".cpp", "w") as f:
        f.write(new_src_code)
    with open(filename_ref + ".cpp", "w") as f:
        f.write(ref_code)
    res1 = tool_compile(filename_src + ".cpp")
    res2 = tool_compile(filename_ref + ".cpp")
    res = tool_formal_verification(filename_src + ".ll", filename_ref + ".ll")
    if "1 correct transformations" in res:
        return True
    return False

def tool_gen_unit_test(src_code: str, trans_code: str, test_code: str, gen_feedback: str = None, max_iter: int = 5) -> str:
    n_attempt = 0
    err_message: str = None
    while n_attempt < max_iter:
        try:
            # call LLM
            results = Chain_LLM_UT_Gen.invoke({
                "src_code": src_code,
                "trans_code": trans_code,
                "UT_code": test_code,
                "feedback_UT": gen_feedback or "",
            })
            test_code = results.UT_code
            if test_code:
                print(f"tool_gen_unit_test: {results}")
                return test_code
            n_attempt += 1
        except Exception as err:
            print(f"Error generating test code: {err}")
            err_message = err
            n_attempt += 1
            continue
    raise Exception(f"LLM UT generation failed for {err_message}")

def tool_execute_test_code(test_code: str):
    test_code_name = "UT_test.cpp"
    clang_path = os.getenv("CLANG_PATH", "clang++")
    if "clang" in clang_path:
        compile_cmd = [
            clang_path,
            "-o",
            "test_program",
            test_code_name,
        ]
    elif "nvcc" in clang_path:
        compile_cmd = [
            clang_path,
            "-x",
            "cu",
            "-o",
            "test_program",
            test_code_name
        ]
    try:
        # write test code
        with open(test_code_name, "w") as f:
            f.write(test_code)
        
        result = subprocess.run(compile_cmd, capture_output = True, text = True, check = True)
        if result.stderr:
            return result.stderr
        
        # execute test code
        result = subprocess.run("./test_program", capture_output = True, text = True, check = True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        return f"test execution failed: {e.stderr}"

if __name__ == "__main__":
    filename = "test_code.cpp"
    res = tool_compile(filename)
    print(res)
