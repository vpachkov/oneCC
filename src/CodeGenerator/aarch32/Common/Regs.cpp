#include "Regs.h"

namespace oneCC::CodeGenerator::Aarch32 {
std::string toString(Register a)
{
    const char* data[] = {
        "r0",
        "r1",
        "r2",
        "r3",
        "r4",
        "r5",
        "r6",
        "r7",
        "r8",
        "r9",
        "r10",
        "fp",
        "ip",
        "sp",
        "lr",
        "pc",
    };
    return std::string(data[(int)a]);
}
}