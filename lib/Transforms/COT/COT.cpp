#include "llvm/Transforms/COT.h"
#include "llvm-c/Initialization.h"
#include "llvm-c/Transforms/Scalar.h"
#include "llvm/Analysis/BasicAliasAnalysis.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/Analysis/ScopedNoAliasAA.h"
#include "llvm/Analysis/TypeBasedAliasAnalysis.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Verifier.h"
#include "llvm/InitializePasses.h"
#include "llvm/IR/LegacyPassManager.h"

using namespace llvm;

/// initializeScalarOptsPasses - Initialize all passes linked into the
/// COT library.
void llvm::initializeCOT(PassRegistry &Registry) {
  initializeCOT1Pass(Registry);
}

void LLVMInitializeCOT1Pass(LLVMPassRegistryRef R) {
  initializeCOT1Pass(*unwrap(R));
}

void LLVMAddCOT1Pass(LLVMPassManagerRef PM) {
  unwrap(PM)->add(createCOT1Pass());
}
