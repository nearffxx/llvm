add_llvm_library(LLVMCOT
  COT1.cpp
  COT.cpp
)

add_dependencies(LLVMCOT intrinsics_gen)
