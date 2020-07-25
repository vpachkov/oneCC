#pragma once

#include <cstdint>
#include <vector>
#include "Regs.h"

typedef float real32_t;
typedef double real64_t;
typedef long double real80_t; // Platform dependent

typedef real32_t* real32_ptr;
typedef real64_t* real64_ptr;
typedef real80_t* real80_ptr;

typedef real80_t* dec80_ptr; // FIXME

typedef uint8_t* uint8_ptr;
typedef uint16_t* uint16_ptr;
typedef uint32_t* uint32_ptr;
typedef uint64_t* uint64_ptr;

typedef std::vector<oneCC::CodeGenerator::Aarch32::Register> RegisterList;