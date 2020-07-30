#include "AsmTranslator.h"
#include <cassert>
#include <iostream>

#define NOT_IMPL(x) do { \
    std::cout << "\033[1;31mNOT IMPLEMENTED\033[0m in \033[1;31m" << __FILE__ << "\033[0m\n"; \
    assert(0); \
} while (0)

namespace oneCC::CodeGenerator::X86_32 {
    void AsmTranslator::AAA() {
        std::cout << "aaa ";
        std::cout << "\n";
    }
    void AsmTranslator::AAD() {
        std::cout << "aad ";
        std::cout << "\n";
    }
    void AsmTranslator::AAM() {
        std::cout << "aam ";
        std::cout << "\n";
    }
    void AsmTranslator::AAS() {
        std::cout << "aas ";
        std::cout << "\n";
    }
    void AsmTranslator::ADC_AL_imm8(uint8_t op2) {
        std::cout << "adc ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::ADC_EAX_imm32(uint32_t op2) {
        std::cout << "adc ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::ADC_reg32_rm32(Register op1, RM op2) {
        std::cout << "adc ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::ADC_reg8_rm8(Register op1, RM op2) {
        std::cout << "adc ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::ADC_rm32_imm32(RM op1, uint32_t op2) {
        std::cout << "adc ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::ADC_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "adc ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::ADC_rm32_reg32(RM op1, Register op2) {
        std::cout << "adc ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::ADC_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "adc ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::ADC_rm8_reg8(RM op1, Register op2) {
        std::cout << "adc ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::ADD_AL_imm8(uint8_t op2) {
        std::cout << "add ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::ADD_EAX_imm32(uint32_t op2) {
        std::cout << "add ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::ADD_reg32_rm32(Register op1, RM op2) {
        std::cout << "add ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::ADD_reg8_rm8(Register op1, RM op2) {
        std::cout << "add ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::ADD_rm32_imm32(RM op1, uint32_t op2) {
        std::cout << "add ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::ADD_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "add ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::ADD_rm32_reg32(RM op1, Register op2) {
        std::cout << "add ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::ADD_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "add ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::ADD_rm8_reg8(RM op1, Register op2) {
        std::cout << "add ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::ADX_imm8(uint8_t op3) {
        std::cout << "adx ";
        std::cout << ", ";
        std::cout << op3;
        std::cout << "\n";
    }
    void AsmTranslator::AMX_imm8(uint8_t op3) {
        std::cout << "amx ";
        std::cout << ", ";
        std::cout << op3;
        std::cout << "\n";
    }
    void AsmTranslator::AND_AL_imm8(uint8_t op2) {
        std::cout << "and ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::AND_EAX_imm32(uint32_t op2) {
        std::cout << "and ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::AND_reg32_rm32(Register op1, RM op2) {
        std::cout << "and ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::AND_reg8_rm8(Register op1, RM op2) {
        std::cout << "and ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::AND_rm32_imm32(RM op1, uint32_t op2) {
        std::cout << "and ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::AND_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "and ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::AND_rm32_reg32(RM op1, Register op2) {
        std::cout << "and ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::AND_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "and ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::AND_rm8_reg8(RM op1, Register op2) {
        std::cout << "and ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::ARPL_rm16_reg16(RM op1, Register op2) {
        std::cout << "arpl ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::CALLF_m16_32(uint32_ptr op1) {
        std::cout << "callf ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::CALLF_ptr16_32(uint32_ptr op1) {
        std::cout << "callf ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::CALL_rel32(uint32_t op1) {
        std::cout << "call ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::CALL_rm32(RM op1) {
        std::cout << "call ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::CBW() {
        std::cout << "cbw ";
        std::cout << "\n";
    }
    void AsmTranslator::CDQ() {
        std::cout << "cdq ";
        std::cout << "\n";
    }
    void AsmTranslator::CLC() {
        std::cout << "clc ";
        std::cout << "\n";
    }
    void AsmTranslator::CLD() {
        std::cout << "cld ";
        std::cout << "\n";
    }
    void AsmTranslator::CLI() {
        std::cout << "cli ";
        std::cout << "\n";
    }
    void AsmTranslator::CMC() {
        std::cout << "cmc ";
        std::cout << "\n";
    }
    void AsmTranslator::CMPS_m16_m16(uint16_ptr op1, uint16_ptr op2) {
        std::cout << "cmps ";
        std::cout << op1;
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::CMPS_m32_m32(uint32_ptr op1, uint32_ptr op2) {
        std::cout << "cmps ";
        std::cout << op1;
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::CMPS_m8_m8(uint8_ptr op1, uint8_ptr op2) {
        std::cout << "cmps ";
        std::cout << op1;
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::CMP_AL_imm8(uint8_t op2) {
        std::cout << "cmp ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::CMP_EAX_imm32(uint32_t op2) {
        std::cout << "cmp ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::CMP_reg32_rm32(Register op1, RM op2) {
        std::cout << "cmp ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::CMP_reg8_rm8(Register op1, RM op2) {
        std::cout << "cmp ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::CMP_rm32_imm32(RM op1, uint32_t op2) {
        std::cout << "cmp ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::CMP_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "cmp ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::CMP_rm32_reg32(RM op1, Register op2) {
        std::cout << "cmp ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::CMP_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "cmp ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::CMP_rm8_reg8(RM op1, Register op2) {
        std::cout << "cmp ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::CS() {
        std::cout << "cs ";
        std::cout << "\n";
    }
    void AsmTranslator::CWD() {
        std::cout << "cwd ";
        std::cout << "\n";
    }
    void AsmTranslator::CWDE() {
        std::cout << "cwde ";
        std::cout << "\n";
    }
    void AsmTranslator::DAA() {
        std::cout << "daa ";
        std::cout << "\n";
    }
    void AsmTranslator::DAS() {
        std::cout << "das ";
        std::cout << "\n";
    }
    void AsmTranslator::DEC_reg32(Register op1) {
        std::cout << "dec ";
        std::cout << registerToString(op1);
        std::cout << "\n";
    }
    void AsmTranslator::DEC_rm32(RM op1) {
        std::cout << "dec ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::DEC_rm8(RM op1) {
        std::cout << "dec ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::DIV_rm32(RM op3) {
        std::cout << "div ";
        std::cout << ", ";
        if (op3.isReg()) { std::cout << registerToString(op3.reg()); }
        else { std::cout << "DWORD PTR " << -op3.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::DIV_rm8(RM op4) {
        std::cout << "div ";
        std::cout << ", ";
        if (op4.isReg()) { std::cout << registerToString(op4.reg()); }
        else { std::cout << "DWORD PTR " << -op4.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::DS() {
        std::cout << "ds ";
        std::cout << "\n";
    }
    void AsmTranslator::ENTER_imm16_imm8(uint16_t op2, uint8_t op3) {
        std::cout << "enter ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << ", ";
        std::cout << op3;
        std::cout << "\n";
    }
    void AsmTranslator::ES() {
        std::cout << "es ";
        std::cout << "\n";
    }
    void AsmTranslator::FCOM2_STi() {
        std::cout << "fcom2 ";
        std::cout << "\n";
    }
    void AsmTranslator::FCOMP3_STi() {
        std::cout << "fcomp3 ";
        std::cout << "\n";
    }
    void AsmTranslator::FCOMP5_STi() {
        std::cout << "fcomp5 ";
        std::cout << "\n";
    }
    void AsmTranslator::FFREEP_STi() {
        std::cout << "ffreep ";
        std::cout << "\n";
    }
    void AsmTranslator::FSTP1_STi() {
        std::cout << "fstp1 ";
        std::cout << "\n";
    }
    void AsmTranslator::FSTP8_STi() {
        std::cout << "fstp8 ";
        std::cout << "\n";
    }
    void AsmTranslator::FSTP9_STi() {
        std::cout << "fstp9 ";
        std::cout << "\n";
    }
    void AsmTranslator::FXCH4_STi() {
        std::cout << "fxch4 ";
        std::cout << "\n";
    }
    void AsmTranslator::FXCH7_STi() {
        std::cout << "fxch7 ";
        std::cout << "\n";
    }
    void AsmTranslator::GS() {
        std::cout << "gs ";
        std::cout << "\n";
    }
    void AsmTranslator::HLT() {
        std::cout << "hlt ";
        std::cout << "\n";
    }
    void AsmTranslator::IDIV_rm32(RM op3) {
        std::cout << "idiv ";
        std::cout << ", ";
        if (op3.isReg()) { std::cout << registerToString(op3.reg()); }
        else { std::cout << "DWORD PTR " << -op3.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::IDIV_rm8(RM op4) {
        std::cout << "idiv ";
        std::cout << ", ";
        if (op4.isReg()) { std::cout << registerToString(op4.reg()); }
        else { std::cout << "DWORD PTR " << -op4.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::IMUL_reg32_rm32_imm32(Register op1, RM op2, uint32_t op3) {
        std::cout << "imul ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op3;
        std::cout << "\n";
    }
    void AsmTranslator::IMUL_reg32_rm32_imm8(Register op1, RM op2, uint8_t op3) {
        std::cout << "imul ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op3;
        std::cout << "\n";
    }
    void AsmTranslator::IMUL_rm32(RM op3) {
        std::cout << "imul ";
        std::cout << ", ";
        if (op3.isReg()) { std::cout << registerToString(op3.reg()); }
        else { std::cout << "DWORD PTR " << -op3.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::IMUL_rm8(RM op3) {
        std::cout << "imul ";
        std::cout << ", ";
        if (op3.isReg()) { std::cout << registerToString(op3.reg()); }
        else { std::cout << "DWORD PTR " << -op3.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::INC_reg32(Register op1) {
        std::cout << "inc ";
        std::cout << registerToString(op1);
        std::cout << "\n";
    }
    void AsmTranslator::INC_rm32(RM op1) {
        std::cout << "inc ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::INC_rm8(RM op1) {
        std::cout << "inc ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::INS_m16_DX(uint16_ptr op1) {
        std::cout << "ins ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::INS_m32_DX(uint32_ptr op1) {
        std::cout << "ins ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::INS_m8_DX(uint8_ptr op1) {
        std::cout << "ins ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::INT1() {
        std::cout << "int1 ";
        std::cout << "\n";
    }
    void AsmTranslator::INTO() {
        std::cout << "into ";
        std::cout << "\n";
    }
    void AsmTranslator::INT_3() {
        std::cout << "int ";
        std::cout << "\n";
    }
    void AsmTranslator::INT_imm8(uint8_t op1) {
        std::cout << "int ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::IN_AL_DX() {
        std::cout << "in ";
        std::cout << "\n";
    }
    void AsmTranslator::IN_AL_imm8(uint8_t op2) {
        std::cout << "in ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::IN_EAX_DX() {
        std::cout << "in ";
        std::cout << "\n";
    }
    void AsmTranslator::IN_EAX_imm8(uint8_t op2) {
        std::cout << "in ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::IRET() {
        std::cout << "iret ";
        std::cout << "\n";
    }
    void AsmTranslator::IRETD() {
        std::cout << "iretd ";
        std::cout << "\n";
    }
    void AsmTranslator::JBE_rel8(uint8_t op1) {
        std::cout << "jbe ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JB_rel8(uint8_t op1) {
        std::cout << "jb ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JCXZ_rel8(uint8_t op1) {
        std::cout << "jcxz ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JLE_rel8(uint8_t op1) {
        std::cout << "jle ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JL_rel8(uint8_t op1) {
        std::cout << "jl ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JMPF_m16_32(uint32_ptr op1) {
        std::cout << "jmpf ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JMPF_ptr16_32(uint32_ptr op1) {
        std::cout << "jmpf ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JMP_rel32(uint32_t op1) {
        std::cout << "jmp ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JMP_rel8(uint8_t op1) {
        std::cout << "jmp ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JMP_rm32(RM op1) {
        std::cout << "jmp ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::JNBE_rel8(uint8_t op1) {
        std::cout << "jnbe ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JNB_rel8(uint8_t op1) {
        std::cout << "jnb ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JNLE_rel8(uint8_t op1) {
        std::cout << "jnle ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JNL_rel8(uint8_t op1) {
        std::cout << "jnl ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JNO_rel8(uint8_t op1) {
        std::cout << "jno ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JNP_rel8(uint8_t op1) {
        std::cout << "jnp ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JNS_rel8(uint8_t op1) {
        std::cout << "jns ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JNZ_rel8(uint8_t op1) {
        std::cout << "jnz ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JO_rel8(uint8_t op1) {
        std::cout << "jo ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JP_rel8(uint8_t op1) {
        std::cout << "jp ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JS_rel8(uint8_t op1) {
        std::cout << "js ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::JZ_rel8(uint8_t op1) {
        std::cout << "jz ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::LAHF() {
        std::cout << "lahf ";
        std::cout << "\n";
    }
    void AsmTranslator::LDS_reg32_m16_32(Register op2, uint32_ptr op3) {
        std::cout << "lds ";
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << ", ";
        std::cout << op3;
        std::cout << "\n";
    }
    void AsmTranslator::LEAVE() {
        std::cout << "leave ";
        std::cout << "\n";
    }
    void AsmTranslator::LEA_reg32_m(Register op1) {
        std::cout << "lea ";
        std::cout << registerToString(op1);
        std::cout << "\n";
    }
    void AsmTranslator::LES_reg32_m16_32(Register op2, uint32_ptr op3) {
        std::cout << "les ";
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << ", ";
        std::cout << op3;
        std::cout << "\n";
    }
    void AsmTranslator::LOCK() {
        std::cout << "lock ";
        std::cout << "\n";
    }
    void AsmTranslator::LODS_m16(uint16_ptr op2) {
        std::cout << "lods ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::LODS_m32(uint32_ptr op2) {
        std::cout << "lods ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::LODS_m8(uint8_ptr op2) {
        std::cout << "lods ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::LOOPNZ_rel8(uint8_t op2) {
        std::cout << "loopnz ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::LOOPZ_rel8(uint8_t op2) {
        std::cout << "loopz ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::LOOP_rel8(uint8_t op2) {
        std::cout << "loop ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::MOVS_m16_m16(uint16_ptr op1, uint16_ptr op2) {
        std::cout << "movs ";
        std::cout << op1;
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::MOVS_m32_m32(uint32_ptr op1, uint32_ptr op2) {
        std::cout << "movs ";
        std::cout << op1;
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::MOVS_m8_m8(uint8_ptr op1, uint8_ptr op2) {
        std::cout << "movs ";
        std::cout << op1;
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::MOV_AL_moffs8() {
        std::cout << "mov ";
        std::cout << "\n";
    }
    void AsmTranslator::MOV_EAX_moffs32() {
        std::cout << "mov ";
        std::cout << "\n";
    }
    void AsmTranslator::MOV_Sreg_rm16(RM op2) {
        std::cout << "mov ";
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::MOV_m16_Sreg(uint16_ptr op1) {
        std::cout << "mov ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::MOV_moffs32_EAX() {
        std::cout << "mov ";
        std::cout << "\n";
    }
    void AsmTranslator::MOV_moffs8_AL() {
        std::cout << "mov ";
        std::cout << "\n";
    }
    void AsmTranslator::MOV_reg32_imm32(Register op1, uint32_t op2) {
        std::cout << "mov ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::MOV_reg32_rm32(Register op1, RM op2) {
        std::cout << "mov ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::MOV_reg8_imm8(Register op1, uint8_t op2) {
        std::cout << "mov ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::MOV_reg8_rm8(Register op1, RM op2) {
        std::cout << "mov ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::MOV_rm32_imm32(RM op1, uint32_t op2) {
        std::cout << "mov ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::MOV_rm32_reg32(RM op1, Register op2) {
        std::cout << "mov ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::MOV_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "mov ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::MOV_rm8_reg8(RM op1, Register op2) {
        std::cout << "mov ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::MUL_rm32(RM op3) {
        std::cout << "mul ";
        std::cout << ", ";
        if (op3.isReg()) { std::cout << registerToString(op3.reg()); }
        else { std::cout << "DWORD PTR " << -op3.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::MUL_rm8(RM op3) {
        std::cout << "mul ";
        std::cout << ", ";
        if (op3.isReg()) { std::cout << registerToString(op3.reg()); }
        else { std::cout << "DWORD PTR " << -op3.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::NEG_rm32(RM op1) {
        std::cout << "neg ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::NEG_rm8(RM op1) {
        std::cout << "neg ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::NOP() {
        std::cout << "nop ";
        std::cout << "\n";
    }
    void AsmTranslator::NOT_rm32(RM op1) {
        std::cout << "not ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::NOT_rm8(RM op1) {
        std::cout << "not ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::OR_AL_imm8(uint8_t op2) {
        std::cout << "or ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::OR_EAX_imm32(uint32_t op2) {
        std::cout << "or ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::OR_reg32_rm32(Register op1, RM op2) {
        std::cout << "or ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::OR_reg8_rm8(Register op1, RM op2) {
        std::cout << "or ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::OR_rm32_imm32(RM op1, uint32_t op2) {
        std::cout << "or ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::OR_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "or ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::OR_rm32_reg32(RM op1, Register op2) {
        std::cout << "or ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::OR_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "or ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::OR_rm8_reg8(RM op1, Register op2) {
        std::cout << "or ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::OUTS_DX_m16(uint16_ptr op2) {
        std::cout << "outs ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::OUTS_DX_m32(uint32_ptr op2) {
        std::cout << "outs ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::OUTS_DX_m8(uint8_ptr op2) {
        std::cout << "outs ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::OUT_DX_AL() {
        std::cout << "out ";
        std::cout << "\n";
    }
    void AsmTranslator::OUT_DX_EAX() {
        std::cout << "out ";
        std::cout << "\n";
    }
    void AsmTranslator::OUT_imm8_AL(uint8_t op1) {
        std::cout << "out ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::OUT_imm8_EAX(uint8_t op1) {
        std::cout << "out ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::PAUSE() {
        std::cout << "pause ";
        std::cout << "\n";
    }
    void AsmTranslator::POPA() {
        std::cout << "popa ";
        std::cout << "\n";
    }
    void AsmTranslator::POPAD() {
        std::cout << "popad ";
        std::cout << "\n";
    }
    void AsmTranslator::POPF() {
        std::cout << "popf ";
        std::cout << "\n";
    }
    void AsmTranslator::POPFD() {
        std::cout << "popfd ";
        std::cout << "\n";
    }
    void AsmTranslator::POP_DS() {
        std::cout << "pop ";
        std::cout << "\n";
    }
    void AsmTranslator::POP_ES() {
        std::cout << "pop ";
        std::cout << "\n";
    }
    void AsmTranslator::POP_SS() {
        std::cout << "pop ";
        std::cout << "\n";
    }
    void AsmTranslator::POP_reg32(Register op1) {
        std::cout << "pop ";
        std::cout << registerToString(op1);
        std::cout << "\n";
    }
    void AsmTranslator::POP_rm32(RM op1) {
        std::cout << "pop ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::PUSHA() {
        std::cout << "pusha ";
        std::cout << "\n";
    }
    void AsmTranslator::PUSHAD() {
        std::cout << "pushad ";
        std::cout << "\n";
    }
    void AsmTranslator::PUSHF() {
        std::cout << "pushf ";
        std::cout << "\n";
    }
    void AsmTranslator::PUSHFD() {
        std::cout << "pushfd ";
        std::cout << "\n";
    }
    void AsmTranslator::PUSH_CS() {
        std::cout << "push ";
        std::cout << "\n";
    }
    void AsmTranslator::PUSH_DS() {
        std::cout << "push ";
        std::cout << "\n";
    }
    void AsmTranslator::PUSH_ES() {
        std::cout << "push ";
        std::cout << "\n";
    }
    void AsmTranslator::PUSH_SS() {
        std::cout << "push ";
        std::cout << "\n";
    }
    void AsmTranslator::PUSH_imm32(uint32_t op1) {
        std::cout << "push ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::PUSH_imm8(uint8_t op1) {
        std::cout << "push ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::PUSH_reg32(Register op1) {
        std::cout << "push ";
        std::cout << registerToString(op1);
        std::cout << "\n";
    }
    void AsmTranslator::PUSH_rm32(RM op1) {
        std::cout << "push ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::RCL_rm32_1(RM op1) {
        std::cout << "rcl ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::RCL_rm32_CL(RM op1) {
        std::cout << "rcl ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::RCL_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "rcl ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::RCL_rm8_1(RM op1) {
        std::cout << "rcl ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::RCL_rm8_CL(RM op1) {
        std::cout << "rcl ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::RCL_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "rcl ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::RCR_rm32_1(RM op1) {
        std::cout << "rcr ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::RCR_rm32_CL(RM op1) {
        std::cout << "rcr ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::RCR_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "rcr ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::RCR_rm8_1(RM op1) {
        std::cout << "rcr ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::RCR_rm8_CL(RM op1) {
        std::cout << "rcr ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::RCR_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "rcr ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::REP() {
        std::cout << "rep ";
        std::cout << "\n";
    }
    void AsmTranslator::REPNZ() {
        std::cout << "repnz ";
        std::cout << "\n";
    }
    void AsmTranslator::REPZ() {
        std::cout << "repz ";
        std::cout << "\n";
    }
    void AsmTranslator::RETF() {
        std::cout << "retf ";
        std::cout << "\n";
    }
    void AsmTranslator::RETF_imm16(uint16_t op1) {
        std::cout << "retf ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::RETN() {
        std::cout << "retn ";
        std::cout << "\n";
    }
    void AsmTranslator::RETN_imm16(uint16_t op1) {
        std::cout << "retn ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::ROL_rm32_1(RM op1) {
        std::cout << "rol ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::ROL_rm32_CL(RM op1) {
        std::cout << "rol ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::ROL_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "rol ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::ROL_rm8_1(RM op1) {
        std::cout << "rol ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::ROL_rm8_CL(RM op1) {
        std::cout << "rol ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::ROL_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "rol ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::ROR_rm32_1(RM op1) {
        std::cout << "ror ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::ROR_rm32_CL(RM op1) {
        std::cout << "ror ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::ROR_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "ror ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::ROR_rm8_1(RM op1) {
        std::cout << "ror ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::ROR_rm8_CL(RM op1) {
        std::cout << "ror ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::ROR_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "ror ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SAHF() {
        std::cout << "sahf ";
        std::cout << "\n";
    }
    void AsmTranslator::SALC() {
        std::cout << "salc ";
        std::cout << "\n";
    }
    void AsmTranslator::SAL_rm32_1(RM op1) {
        std::cout << "sal ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SAL_rm32_CL(RM op1) {
        std::cout << "sal ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SAL_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "sal ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SAL_rm8_1(RM op1) {
        std::cout << "sal ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SAL_rm8_CL(RM op1) {
        std::cout << "sal ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SAL_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "sal ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SAR_rm32_1(RM op1) {
        std::cout << "sar ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SAR_rm32_CL(RM op1) {
        std::cout << "sar ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SAR_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "sar ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SAR_rm8_1(RM op1) {
        std::cout << "sar ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SAR_rm8_CL(RM op1) {
        std::cout << "sar ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SAR_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "sar ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SBB_AL_imm8(uint8_t op2) {
        std::cout << "sbb ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SBB_EAX_imm32(uint32_t op2) {
        std::cout << "sbb ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SBB_reg32_rm32(Register op1, RM op2) {
        std::cout << "sbb ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SBB_reg8_rm8(Register op1, RM op2) {
        std::cout << "sbb ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SBB_rm32_imm32(RM op1, uint32_t op2) {
        std::cout << "sbb ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SBB_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "sbb ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SBB_rm32_reg32(RM op1, Register op2) {
        std::cout << "sbb ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::SBB_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "sbb ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SBB_rm8_reg8(RM op1, Register op2) {
        std::cout << "sbb ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::SCAS_m16(uint16_ptr op1) {
        std::cout << "scas ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::SCAS_m32(uint32_ptr op1) {
        std::cout << "scas ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::SCAS_m8(uint8_ptr op1) {
        std::cout << "scas ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::SHL_rm32_1(RM op1) {
        std::cout << "shl ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SHL_rm32_CL(RM op1) {
        std::cout << "shl ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SHL_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "shl ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SHL_rm8_1(RM op1) {
        std::cout << "shl ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SHL_rm8_CL(RM op1) {
        std::cout << "shl ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SHL_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "shl ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SHR_rm32_1(RM op1) {
        std::cout << "shr ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SHR_rm32_CL(RM op1) {
        std::cout << "shr ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SHR_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "shr ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SHR_rm8_1(RM op1) {
        std::cout << "shr ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SHR_rm8_CL(RM op1) {
        std::cout << "shr ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SHR_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "shr ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SS() {
        std::cout << "ss ";
        std::cout << "\n";
    }
    void AsmTranslator::STC() {
        std::cout << "stc ";
        std::cout << "\n";
    }
    void AsmTranslator::STD() {
        std::cout << "std ";
        std::cout << "\n";
    }
    void AsmTranslator::STI() {
        std::cout << "sti ";
        std::cout << "\n";
    }
    void AsmTranslator::STOS_m16(uint16_ptr op1) {
        std::cout << "stos ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::STOS_m32(uint32_ptr op1) {
        std::cout << "stos ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::STOS_m8(uint8_ptr op1) {
        std::cout << "stos ";
        std::cout << op1;
        std::cout << "\n";
    }
    void AsmTranslator::SUB_AL_imm8(uint8_t op2) {
        std::cout << "sub ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SUB_EAX_imm32(uint32_t op2) {
        std::cout << "sub ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SUB_reg32_rm32(Register op1, RM op2) {
        std::cout << "sub ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SUB_reg8_rm8(Register op1, RM op2) {
        std::cout << "sub ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::SUB_rm32_imm32(RM op1, uint32_t op2) {
        std::cout << "sub ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SUB_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "sub ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SUB_rm32_reg32(RM op1, Register op2) {
        std::cout << "sub ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::SUB_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "sub ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::SUB_rm8_reg8(RM op1, Register op2) {
        std::cout << "sub ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::TEST_AL_imm8(uint8_t op2) {
        std::cout << "test ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::TEST_EAX_imm32(uint32_t op2) {
        std::cout << "test ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::TEST_rm32_imm32(RM op1, uint32_t op2) {
        std::cout << "test ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::TEST_rm32_reg32(RM op1, Register op2) {
        std::cout << "test ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::TEST_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "test ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::TEST_rm8_reg8(RM op1, Register op2) {
        std::cout << "test ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::XCHG_reg32_EAX(Register op1) {
        std::cout << "xchg ";
        std::cout << registerToString(op1);
        std::cout << "\n";
    }
    void AsmTranslator::XCHG_reg32_rm32(Register op1, RM op2) {
        std::cout << "xchg ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::XCHG_reg8_rm8(Register op1, RM op2) {
        std::cout << "xchg ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::XLAT_m8(uint8_ptr op2) {
        std::cout << "xlat ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::XOR_AL_imm8(uint8_t op2) {
        std::cout << "xor ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::XOR_EAX_imm32(uint32_t op2) {
        std::cout << "xor ";
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::XOR_reg32_rm32(Register op1, RM op2) {
        std::cout << "xor ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::XOR_reg8_rm8(Register op1, RM op2) {
        std::cout << "xor ";
        std::cout << registerToString(op1);
        std::cout << ", ";
        if (op2.isReg()) { std::cout << registerToString(op2.reg()); }
        else { std::cout << "DWORD PTR " << -op2.mem() << "[ebp]"; }
        std::cout << "\n";
    }
    void AsmTranslator::XOR_rm32_imm32(RM op1, uint32_t op2) {
        std::cout << "xor ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::XOR_rm32_imm8(RM op1, uint8_t op2) {
        std::cout << "xor ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::XOR_rm32_reg32(RM op1, Register op2) {
        std::cout << "xor ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }
    void AsmTranslator::XOR_rm8_imm8(RM op1, uint8_t op2) {
        std::cout << "xor ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << op2;
        std::cout << "\n";
    }
    void AsmTranslator::XOR_rm8_reg8(RM op1, Register op2) {
        std::cout << "xor ";
        if (op1.isReg()) { std::cout << registerToString(op1.reg()); }
        else { std::cout << "DWORD PTR " << -op1.mem() << "[ebp]"; }
        std::cout << ", ";
        std::cout << registerToString(op2);
        std::cout << "\n";
    }


}