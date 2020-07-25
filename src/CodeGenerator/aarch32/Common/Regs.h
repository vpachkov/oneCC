#pragma once

#include <string>

namespace oneCC::CodeGenerator::Aarch32 {

enum Register {
    r0,
    r1,
    r2,
    r3,
    r4,
    r5,
    r6,
    r7,
    r8,
    r9,
    r10,
    fp,
    ip,
    sp,
    lr,
    pc,
};

std::string toString(Register a);

}