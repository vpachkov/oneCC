#pragma once

namespace oneCC::CodeGenerator::X86_32 {

enum Register {
    EAX,AX,AH,AL,
    EBX,BX,BH,BL,
    ECX,CX,CH,CL,
    EDX,DX,DH,DL,

    ESP, EBP,
};

static const char* registerToString(Register reg) {
    static const char* regs[] = {
        "EAX", "AX", "AH", "AL",
        "EBX", "BX", "BH", "BL",
        "ECX", "CX", "CH", "CL",
        "EDX", "DX", "DH", "DL",

        "ESP", "EBP",
    };

    return regs[reg];
}

}