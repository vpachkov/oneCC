#include "AsmTranslator.h"
#include <cassert>
#include <iostream>

#define NOT_IMPL(x) do { \
    std::cout << "\033[1;31mNOT IMPLEMENTED\033[0m in \033[1;31m" << __FILE__ << "\033[0m\n"; \
    assert(0); \
} while (0)

namespace oneCC::CodeGenerator::Aarch32 {


}