#include "llvm/Transforms/COT.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "COT1"

namespace {
  struct COT1 : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    COT1() : FunctionPass(ID) {
      initializeCOT1Pass(*PassRegistry::getPassRegistry());
    }

    bool runOnFunction(Function &F) override {
      F.dump();
      for (Function::iterator FI = F.begin(), FE = F.end(); FI!= FE; ++FI) {
        TerminatorInst *Term = FI->getTerminator();
        BranchInst *BrI = dyn_cast<BranchInst>(Term);
        LLVMContext &Context = FI->getContext();

        if (!BrI || !BrI->isConditional())
          continue;

        BasicBlock *BBT = BrI->getSuccessor(0);
        BasicBlock *BBF;
        BasicBlock *BBM = BrI->getSuccessor(1);
        if (BrI->getNumSuccessors() == 2 && BBT->getUniqueSuccessor() == BBM) {
          ValueToValueMapTy VMap;
          BBF = CloneBasicBlock(BBT, VMap, ".us", &F);
          F.getBasicBlockList().splice(BBM->getIterator(),
                                       F.getBasicBlockList(),
                                       BBF);
          VMap[BBM] = BBF;
          RemapInstruction(BrI, VMap, RF_NoModuleLevelChanges | RF_IgnoreMissingLocals);
          for (BasicBlock::iterator BBI = BBF->begin(), BBE = --BBF->end(); BBI != BBE; BBI++) {
            RemapInstruction(&*BBI, VMap, RF_NoModuleLevelChanges | RF_IgnoreMissingLocals);
          }
        }
      }
      errs() << "##COT: ";
      F.dump();
      return false;
    }
  };
}

char COT1::ID = 0;
INITIALIZE_PASS_BEGIN(COT1, "cot1", "Promote Memory to Register",
            false, false)
INITIALIZE_PASS_END(COT1, "cot1", "Promote Memory to Register",
            false, false)

FunctionPass *llvm::createCOT1Pass() {
  return new COT1();
}
