; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -fast-isel -mtriple=x86_64-unknown-unknown -mattr=+sse | FileCheck %s --check-prefix=X64

; NOTE: This should use IR equivalent to what is generated by clang/test/CodeGen/sse-builtins.c

define <4 x float> @test_mm_cvtsi64_ss(<4 x float> %a0, i64 %a1) nounwind {
; X64-LABEL: test_mm_cvtsi64_ss:
; X64:       # BB#0:
; X64-NEXT:    cvtsi2ssq %rdi, %xmm1
; X64-NEXT:    movss {{.*#+}} xmm0 = xmm1[0],xmm0[1,2,3]
; X64-NEXT:    retq
  %cvt = sitofp i64 %a1 to float
  %res = insertelement <4 x float> %a0, float %cvt, i32 0
  ret <4 x float> %res
}

define i64 @test_mm_cvtss_si64(<4 x float> %a0) nounwind {
; X64-LABEL: test_mm_cvtss_si64:
; X64:       # BB#0:
; X64-NEXT:    cvtss2si %xmm0, %rax
; X64-NEXT:    retq
  %res = call i64 @llvm.x86.sse.cvtss2si64(<4 x float> %a0)
  ret i64 %res
}
declare i64 @llvm.x86.sse.cvtss2si64(<4 x float>) nounwind readnone

define i64 @test_mm_cvttss_si64(<4 x float> %a0) nounwind {
; X64-LABEL: test_mm_cvttss_si64:
; X64:       # BB#0:
; X64-NEXT:    cvttss2si %xmm0, %rax
; X64-NEXT:    retq
  %cvt = extractelement <4 x float> %a0, i32 0
  %res = fptosi float %cvt to i64
  ret i64 %res
}
