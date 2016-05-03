//===-- Scalar.h - Scalar Transformations -----------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This header file defines prototypes for accessor functions that expose passes
// in the Scalar transformations library.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_CTO_H
#define LLVM_TRANSFORMS_CTO_H

#include <functional>

namespace llvm {

class BasicBlockPass;
class Function;
class FunctionPass;
class ModulePass;
class Pass;
class GetElementPtrInst;
class PassInfo;
class TerminatorInst;
class TargetLowering;
class TargetMachine;

//===----------------------------------------------------------------------===//
//
// COT1 - A worklist driven constant propagation pass
//
FunctionPass *createCOT1Pass();

} // End llvm namespace

#endif
