//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/COT.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "COT1"

STATISTIC(COT1Count, "Counts number of functions greeted");

namespace {
  struct COT1 : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    COT1() : FunctionPass(ID) {
      initializeCOT1Pass(*PassRegistry::getPassRegistry());
    }

    bool runOnFunction(Function &F) override {
      ++COT1Count;
      errs() << "COT: ";
      errs().write_escaped(F.getName()) << '\n';
      return false;
    }

    // We don't modify the program, so we preserve all analyses.
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
    }
  };
}

char COT1::ID = 0;
INITIALIZE_PASS_BEGIN(COT1, "cot1", "Promote Memory to Register",
            false, false)
INITIALIZE_PASS_DEPENDENCY(AssumptionCacheTracker)
INITIALIZE_PASS_DEPENDENCY(DominatorTreeWrapperPass)
INITIALIZE_PASS_END(COT1, "cot1", "Promote Memory to Register",
            false, false)

// createCTO - Provide an entry point to create this pass.
//
FunctionPass *llvm::createCOT1Pass() {
  return new COT1();
}

