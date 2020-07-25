#pragma once

#include "../Common/ModRM.h"
#include "../Common/Regs.h"
#include "../Common/TypesX86_32.h"

namespace oneCC::CodeGenerator::X86_32 {

class AbstractX86_32Translator {
public:
    AbstractX86_32Translator() = default;

    // Generated (No float opcodes)
    virtual void AAA() {}
    virtual void AAD() {}
    virtual void AAM() {}
    virtual void AAS() {}
    virtual void ADC_AL_imm8(uint8_t op2) {}
    virtual void ADC_EAX_imm32(uint32_t op2) {}
    virtual void ADC_reg32_rm32(Register op1, RM op2) {}
    virtual void ADC_reg8_rm8(Register op1, RM op2) {}
    virtual void ADC_rm32_imm32(RM op1, uint32_t op2) {}
    virtual void ADC_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void ADC_rm32_reg32(RM op1, Register op2) {}
    virtual void ADC_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void ADC_rm8_reg8(RM op1, Register op2) {}
    virtual void ADD_AL_imm8(uint8_t op2) {}
    virtual void ADD_EAX_imm32(uint32_t op2) {}
    virtual void ADD_reg32_rm32(Register op1, RM op2) {}
    virtual void ADD_reg8_rm8(Register op1, RM op2) {}
    virtual void ADD_rm32_imm32(RM op1, uint32_t op2) {}
    virtual void ADD_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void ADD_rm32_reg32(RM op1, Register op2) {}
    virtual void ADD_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void ADD_rm8_reg8(RM op1, Register op2) {}
    virtual void ADX_imm8(uint8_t op3) {}
    virtual void AMX_imm8(uint8_t op3) {}
    virtual void AND_AL_imm8(uint8_t op2) {}
    virtual void AND_EAX_imm32(uint32_t op2) {}
    virtual void AND_reg32_rm32(Register op1, RM op2) {}
    virtual void AND_reg8_rm8(Register op1, RM op2) {}
    virtual void AND_rm32_imm32(RM op1, uint32_t op2) {}
    virtual void AND_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void AND_rm32_reg32(RM op1, Register op2) {}
    virtual void AND_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void AND_rm8_reg8(RM op1, Register op2) {}
    virtual void ARPL_rm16_reg16(RM op1, Register op2) {}
    virtual void CALLF_m16_32(uint32_ptr op1) {}
    virtual void CALLF_ptr16_32(uint32_ptr op1) {}
    virtual void CALL_rel32(uint32_t op1) {}
    virtual void CALL_rm32(RM op1) {}
    virtual void CBW() {}
    virtual void CDQ() {}
    virtual void CLC() {}
    virtual void CLD() {}
    virtual void CLI() {}
    virtual void CMC() {}
    virtual void CMPS_m16_m16(uint16_ptr op1, uint16_ptr op2) {}
    virtual void CMPS_m32_m32(uint32_ptr op1, uint32_ptr op2) {}
    virtual void CMPS_m8_m8(uint8_ptr op1, uint8_ptr op2) {}
    virtual void CMP_AL_imm8(uint8_t op2) {}
    virtual void CMP_EAX_imm32(uint32_t op2) {}
    virtual void CMP_reg32_rm32(Register op1, RM op2) {}
    virtual void CMP_reg8_rm8(Register op1, RM op2) {}
    virtual void CMP_rm32_imm32(RM op1, uint32_t op2) {}
    virtual void CMP_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void CMP_rm32_reg32(RM op1, Register op2) {}
    virtual void CMP_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void CMP_rm8_reg8(RM op1, Register op2) {}
    virtual void CS() {}
    virtual void CWD() {}
    virtual void CWDE() {}
    virtual void DAA() {}
    virtual void DAS() {}
    virtual void DEC_reg32(Register op1) {}
    virtual void DEC_rm32(RM op1) {}
    virtual void DEC_rm8(RM op1) {}
    virtual void DIV_rm32(RM op3) {}
    virtual void DIV_rm8(RM op4) {}
    virtual void DS() {}
    virtual void ENTER_imm16_imm8(uint16_t op2, uint8_t op3) {}
    virtual void ES() {}
    virtual void FCOM2_STi() {}
    virtual void FCOMP3_STi() {}
    virtual void FCOMP5_STi() {}
    virtual void FFREEP_STi() {}
    virtual void FSTP1_STi() {}
    virtual void FSTP8_STi() {}
    virtual void FSTP9_STi() {}
    virtual void FXCH4_STi() {}
    virtual void FXCH7_STi() {}
    virtual void GS() {}
    virtual void HLT() {}
    virtual void IDIV_rm32(RM op3) {}
    virtual void IDIV_rm8(RM op4) {}
    virtual void IMUL_reg32_rm32_imm32(Register op1, RM op2, uint32_t op3) {}
    virtual void IMUL_reg32_rm32_imm8(Register op1, RM op2, uint8_t op3) {}
    virtual void IMUL_rm32(RM op3) {}
    virtual void IMUL_rm8(RM op3) {}
    virtual void INC_reg32(Register op1) {}
    virtual void INC_rm32(RM op1) {}
    virtual void INC_rm8(RM op1) {}
    virtual void INS_m16_DX(uint16_ptr op1) {}
    virtual void INS_m32_DX(uint32_ptr op1) {}
    virtual void INS_m8_DX(uint8_ptr op1) {}
    virtual void INT1() {}
    virtual void INTO() {}
    virtual void INT_3() {}
    virtual void INT_imm8(uint8_t op1) {}
    virtual void IN_AL_DX() {}
    virtual void IN_AL_imm8(uint8_t op2) {}
    virtual void IN_EAX_DX() {}
    virtual void IN_EAX_imm8(uint8_t op2) {}
    virtual void IRET() {}
    virtual void IRETD() {}
    virtual void JBE_rel8(uint8_t op1) {}
    virtual void JB_rel8(uint8_t op1) {}
    virtual void JCXZ_rel8(uint8_t op1) {}
    virtual void JLE_rel8(uint8_t op1) {}
    virtual void JL_rel8(uint8_t op1) {}
    virtual void JMPF_m16_32(uint32_ptr op1) {}
    virtual void JMPF_ptr16_32(uint32_ptr op1) {}
    virtual void JMP_rel32(uint32_t op1) {}
    virtual void JMP_rel8(uint8_t op1) {}
    virtual void JMP_rm32(RM op1) {}
    virtual void JNBE_rel8(uint8_t op1) {}
    virtual void JNB_rel8(uint8_t op1) {}
    virtual void JNLE_rel8(uint8_t op1) {}
    virtual void JNL_rel8(uint8_t op1) {}
    virtual void JNO_rel8(uint8_t op1) {}
    virtual void JNP_rel8(uint8_t op1) {}
    virtual void JNS_rel8(uint8_t op1) {}
    virtual void JNZ_rel8(uint8_t op1) {}
    virtual void JO_rel8(uint8_t op1) {}
    virtual void JP_rel8(uint8_t op1) {}
    virtual void JS_rel8(uint8_t op1) {}
    virtual void JZ_rel8(uint8_t op1) {}
    virtual void LAHF() {}
    virtual void LDS_reg32_m16_32(Register op2, uint32_ptr op3) {}
    virtual void LEAVE() {}
    virtual void LEA_reg32_m(Register op1) {}
    virtual void LES_reg32_m16_32(Register op2, uint32_ptr op3) {}
    virtual void LOCK() {}
    virtual void LODS_m16(uint16_ptr op2) {}
    virtual void LODS_m32(uint32_ptr op2) {}
    virtual void LODS_m8(uint8_ptr op2) {}
    virtual void LOOPNZ_rel8(uint8_t op2) {}
    virtual void LOOPZ_rel8(uint8_t op2) {}
    virtual void LOOP_rel8(uint8_t op2) {}
    virtual void MOVS_m16_m16(uint16_ptr op1, uint16_ptr op2) {}
    virtual void MOVS_m32_m32(uint32_ptr op1, uint32_ptr op2) {}
    virtual void MOVS_m8_m8(uint8_ptr op1, uint8_ptr op2) {}
    virtual void MOV_AL_moffs8() {}
    virtual void MOV_EAX_moffs32() {}
    virtual void MOV_Sreg_rm16(RM op2) {}
    virtual void MOV_m16_Sreg(uint16_ptr op1) {}
    virtual void MOV_moffs32_EAX() {}
    virtual void MOV_moffs8_AL() {}
    virtual void MOV_reg32_imm32(Register op1, uint32_t op2) {}
    virtual void MOV_reg32_rm32(Register op1, RM op2) {}
    virtual void MOV_reg8_imm8(Register op1, uint8_t op2) {}
    virtual void MOV_reg8_rm8(Register op1, RM op2) {}
    virtual void MOV_rm32_imm32(RM op1, uint32_t op2) {}
    virtual void MOV_rm32_reg32(RM op1, Register op2) {}
    virtual void MOV_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void MOV_rm8_reg8(RM op1, Register op2) {}
    virtual void MUL_rm32(RM op3) {}
    virtual void MUL_rm8(RM op3) {}
    virtual void NEG_rm32(RM op1) {}
    virtual void NEG_rm8(RM op1) {}
    virtual void NOP() {}
    virtual void NOT_rm32(RM op1) {}
    virtual void NOT_rm8(RM op1) {}
    virtual void OR_AL_imm8(uint8_t op2) {}
    virtual void OR_EAX_imm32(uint32_t op2) {}
    virtual void OR_reg32_rm32(Register op1, RM op2) {}
    virtual void OR_reg8_rm8(Register op1, RM op2) {}
    virtual void OR_rm32_imm32(RM op1, uint32_t op2) {}
    virtual void OR_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void OR_rm32_reg32(RM op1, Register op2) {}
    virtual void OR_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void OR_rm8_reg8(RM op1, Register op2) {}
    virtual void OUTS_DX_m16(uint16_ptr op2) {}
    virtual void OUTS_DX_m32(uint32_ptr op2) {}
    virtual void OUTS_DX_m8(uint8_ptr op2) {}
    virtual void OUT_DX_AL() {}
    virtual void OUT_DX_EAX() {}
    virtual void OUT_imm8_AL(uint8_t op1) {}
    virtual void OUT_imm8_EAX(uint8_t op1) {}
    virtual void PAUSE() {}
    virtual void POPA() {}
    virtual void POPAD() {}
    virtual void POPF() {}
    virtual void POPFD() {}
    virtual void POP_DS() {}
    virtual void POP_ES() {}
    virtual void POP_SS() {}
    virtual void POP_reg32(Register op1) {}
    virtual void POP_rm32(RM op1) {}
    virtual void PUSHA() {}
    virtual void PUSHAD() {}
    virtual void PUSHF() {}
    virtual void PUSHFD() {}
    virtual void PUSH_CS() {}
    virtual void PUSH_DS() {}
    virtual void PUSH_ES() {}
    virtual void PUSH_SS() {}
    virtual void PUSH_imm32(uint32_t op1) {}
    virtual void PUSH_imm8(uint8_t op1) {}
    virtual void PUSH_reg32(Register op1) {}
    virtual void PUSH_rm32(RM op1) {}
    virtual void RCL_rm32_1(RM op1) {}
    virtual void RCL_rm32_CL(RM op1) {}
    virtual void RCL_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void RCL_rm8_1(RM op1) {}
    virtual void RCL_rm8_CL(RM op1) {}
    virtual void RCL_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void RCR_rm32_1(RM op1) {}
    virtual void RCR_rm32_CL(RM op1) {}
    virtual void RCR_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void RCR_rm8_1(RM op1) {}
    virtual void RCR_rm8_CL(RM op1) {}
    virtual void RCR_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void REP() {}
    virtual void REPNZ() {}
    virtual void REPZ() {}
    virtual void RETF() {}
    virtual void RETF_imm16(uint16_t op1) {}
    virtual void RETN() {}
    virtual void RETN_imm16(uint16_t op1) {}
    virtual void ROL_rm32_1(RM op1) {}
    virtual void ROL_rm32_CL(RM op1) {}
    virtual void ROL_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void ROL_rm8_1(RM op1) {}
    virtual void ROL_rm8_CL(RM op1) {}
    virtual void ROL_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void ROR_rm32_1(RM op1) {}
    virtual void ROR_rm32_CL(RM op1) {}
    virtual void ROR_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void ROR_rm8_1(RM op1) {}
    virtual void ROR_rm8_CL(RM op1) {}
    virtual void ROR_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void SAHF() {}
    virtual void SALC() {}
    virtual void SAL_rm32_1(RM op1) {}
    virtual void SAL_rm32_CL(RM op1) {}
    virtual void SAL_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void SAL_rm8_1(RM op1) {}
    virtual void SAL_rm8_CL(RM op1) {}
    virtual void SAL_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void SAR_rm32_1(RM op1) {}
    virtual void SAR_rm32_CL(RM op1) {}
    virtual void SAR_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void SAR_rm8_1(RM op1) {}
    virtual void SAR_rm8_CL(RM op1) {}
    virtual void SAR_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void SBB_AL_imm8(uint8_t op2) {}
    virtual void SBB_EAX_imm32(uint32_t op2) {}
    virtual void SBB_reg32_rm32(Register op1, RM op2) {}
    virtual void SBB_reg8_rm8(Register op1, RM op2) {}
    virtual void SBB_rm32_imm32(RM op1, uint32_t op2) {}
    virtual void SBB_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void SBB_rm32_reg32(RM op1, Register op2) {}
    virtual void SBB_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void SBB_rm8_reg8(RM op1, Register op2) {}
    virtual void SCAS_m16(uint16_ptr op1) {}
    virtual void SCAS_m32(uint32_ptr op1) {}
    virtual void SCAS_m8(uint8_ptr op1) {}
    virtual void SHL_rm32_1(RM op1) {}
    virtual void SHL_rm32_CL(RM op1) {}
    virtual void SHL_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void SHL_rm8_1(RM op1) {}
    virtual void SHL_rm8_CL(RM op1) {}
    virtual void SHL_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void SHR_rm32_1(RM op1) {}
    virtual void SHR_rm32_CL(RM op1) {}
    virtual void SHR_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void SHR_rm8_1(RM op1) {}
    virtual void SHR_rm8_CL(RM op1) {}
    virtual void SHR_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void SS() {}
    virtual void STC() {}
    virtual void STD() {}
    virtual void STI() {}
    virtual void STOS_m16(uint16_ptr op1) {}
    virtual void STOS_m32(uint32_ptr op1) {}
    virtual void STOS_m8(uint8_ptr op1) {}
    virtual void SUB_AL_imm8(uint8_t op2) {}
    virtual void SUB_EAX_imm32(uint32_t op2) {}
    virtual void SUB_reg32_rm32(Register op1, RM op2) {}
    virtual void SUB_reg8_rm8(Register op1, RM op2) {}
    virtual void SUB_rm32_imm32(RM op1, uint32_t op2) {}
    virtual void SUB_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void SUB_rm32_reg32(RM op1, Register op2) {}
    virtual void SUB_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void SUB_rm8_reg8(RM op1, Register op2) {}
    virtual void TEST_AL_imm8(uint8_t op2) {}
    virtual void TEST_EAX_imm32(uint32_t op2) {}
    virtual void TEST_rm32_imm32(RM op1, uint32_t op2) {}
    virtual void TEST_rm32_reg32(RM op1, Register op2) {}
    virtual void TEST_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void TEST_rm8_reg8(RM op1, Register op2) {}
    virtual void XCHG_reg32_EAX(Register op1) {}
    virtual void XCHG_reg32_rm32(Register op1, RM op2) {}
    virtual void XCHG_reg8_rm8(Register op1, RM op2) {}
    virtual void XLAT_m8(uint8_ptr op2) {}
    virtual void XOR_AL_imm8(uint8_t op2) {}
    virtual void XOR_EAX_imm32(uint32_t op2) {}
    virtual void XOR_reg32_rm32(Register op1, RM op2) {}
    virtual void XOR_reg8_rm8(Register op1, RM op2) {}
    virtual void XOR_rm32_imm32(RM op1, uint32_t op2) {}
    virtual void XOR_rm32_imm8(RM op1, uint8_t op2) {}
    virtual void XOR_rm32_reg32(RM op1, Register op2) {}
    virtual void XOR_rm8_imm8(RM op1, uint8_t op2) {}
    virtual void XOR_rm8_reg8(RM op1, Register op2) {}
};

}