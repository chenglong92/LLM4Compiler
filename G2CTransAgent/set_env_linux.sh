#!/bin/bash

# LLM API
export OPENAI_API_BASE="https://api.siliconflow.cn/v1"
export OPENAI_API_KEY=""   # to be filled
export ENGINE1="Pro/deepseek-ai/DeepSeek-V3.1"
export ENGINE2="Pro/deepseek-ai/DeepSeek-R1"
export ENGINE3="Qwen/Qwen3-Coder-480B-A35B-Instruct"

export ENGINE_GEN=$ENGINE2
export ENGINE_ANALYSIS=$ENGINE3
export ENGINE_REPAIR=$ENGINE1

# few_shots examples
export BABELTOWER_DIR="./BabelTower/test/mono_cases.jsonl"


# For LLVM & Clang configuration
#export LLVM_HOME=~/install_llvm20    # /usr/local/cuda-12.4
#export PATH=$LLVM_HOME/bin:$PATH
#export LD_LIBRARY_PATH=$LLVM_HOME/lib:$LD_LIBRARY_PATH
#export LIBCLANG=$LLVM_HOME/lib
#export CC=$LLVM_HOME/bin/clang
#export CXX=$LLVM_HOME/bin/clang++

# for nvcc on GPU
export LLVM_HOME=/usr/local/cuda-12.4
export PATH=$LLVM_HOME/bin:$PATH
export LD_LIBRARY_PATH=$LLVM_HOME/lib64:$LD_LIBRARY_PATH
export LIBCLANG=$LLVM_HOME/lib
export CC=$LLVM_HOME/bin/nvcc
export CXX=$LLVM_HOME/bin/nvcc

export CLANG_PATH=$CXX

#export Z3_HOME=~/install_new
#export LD_LIBRARY_PATH=$Z3_HOME/lib:$LD_LIBRARY_PATH

#export ALIVE2_HOME=~/build
#export PATH=$ALIVE2_HOME:$PATH

