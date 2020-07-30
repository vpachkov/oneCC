from bs4 import BeautifulSoup

import requests

url = "http://ref.x86asm.net/coder32.html"
r = requests.get(url)
data = r.text

soup = BeautifulSoup(data)

class Opcode:
    def __init__(self):
        self.pf = None
        self.pref0x = None
        self.po = None
        self.so = None
        self.o = None
        self.proc = None
        self.st = None
        self.m = None
        self.rl = None
        self.x = None
        self.mnemonic = None
        self.op1 = None
        self.op2 = None
        self.op3 = None
        self.op4 = None

class CppFunc:
    def __init__(self):
        self.name = None
        self.oper = None
        self.op1  = None
        self.op2  = None
        self.op3  = None
        self.op4  = None

    def __init__(self, name, op1, op2, op3, op4):
        self.name = self.gen_name(name, op1, op2, op3, op4)
        self.oper = self.norm_name(name)

        self.op1  = self.to_cpp_type(op1)
        self.op2  = self.to_cpp_type(op2)
        self.op3  = self.to_cpp_type(op3)
        self.op4  = self.to_cpp_type(op4)

    def norm_operand(self, op):
        op = str(op)
        op = op.replace("<b>", "")
        op = op.replace("</b>", "")
        op = op.replace("16/32", "32")
        op = op.replace("r/m", "rm")
        op = op.replace("r8", "reg8")
        op = op.replace("r16", "reg16")
        op = op.replace("r32", "reg32")
        op = op.replace("ptreg", "ptr") # if we broke it in prev lines
        op = op.replace("16:32", "16_32") # if we broke it in prev lines
        op = op.replace("eAX", "EAX")
        op = op.replace("eCX", "ECX")
        op = op.replace("eDX", "EDX")
        op = op.replace("eBP", "EBP")
        op = op.replace("m94/108", "m94_108")
        return op

    def norm_name(self, op):
        op = str(op)
        op = op.replace("<i>", "")
        op = op.replace("</i>", "")
        return op

    def to_cpp_type(self, op):
        op = self.norm_operand(op)
        if op[:3] == "<i>":
            return ""
        if op[:3] == "...":
            return ""

        if op == "imm8":
            return "uint8_t"
        if op == "imm16":
            return "uint16_t"
        if op == "imm32":
            return "uint32_t"

        if op == "reg8":
            return "Register"
        if op == "reg16":
            return "Register"
        if op == "reg32":
            return "Register"

        if op == "rm8":
            return "RM"
        if op == "rm16":
            return "RM"
        if op == "rm32":
            return "RM"

        if op == "m8int":
            return "uint8_ptr"
        if op == "m16int":
            return "uint16_ptr"
        if op == "m32int":
            return "uint32_ptr"
        if op == "m64int":
            return "uint64_ptr"
        if op == "m32real":
            return "real32_ptr"
        if op == "m64real":
            return "real64_ptr"
        if op == "m80real":
            return "real80_ptr"
        if op == "m8":
            return "uint8_ptr"
        if op == "m16":
            return "uint16_ptr"
        if op == "m32":
            return "uint32_ptr"
        if op == "m64":
            return "uint64_ptr"

        if op == "rel8":
            return "uint8_t"
        if op == "rel16":
            return "uint16_t"
        if op == "rel32":
            return "uint32_t"

        if op == "ptr16_32":
            return "uint32_ptr"

        if op == "m16_32":
            return "uint32_ptr"

        return ""

    def use_as_name(self, op):
        if op == "":
            return False

        if op.find("<i>") != -1:
            return False

        if op.find("<span") != -1:
            return False

        if op[:3] == "...":
            return False

        return True

    def gen_name(self, name, op1, op2, op3, op4):
        res = self.norm_name(name)
        if self.use_as_name(op1) == True:
            res += "_" + self.norm_operand(op1)

        if self.use_as_name(op2) == True:
            res += "_" + self.norm_operand(op2)

        if self.use_as_name(op3) == True:
            res += "_" + self.norm_operand(op3)

        if self.use_as_name(op4) == True:
            res += "_" + self.norm_operand(op4)

        return res

    def get_init_cpp(self):
        res = "void "
        res += self.name
        res += "("

        fst = True
        if self.op1 != "":
            if not fst:
                res += ', '
            fst = False
            res += self.op1 + " op1"

        if self.op2 != "":
            if not fst:
                res += ', '
            fst = False
            res += self.op2 + " op2"

        if self.op3 != "":
            if not fst:
                res += ', '
            fst = False
            res += self.op3 + " op3"

        if self.op4 != "":
            if not fst:
                res += ', '
            fst = False
            res += self.op4 + " op4"

        res += ") override ;"
        return res

    def get_impl_cpp(self, module):
        res = "void "
        res += module
        res += "::"
        res += self.name
        res += "("

        fst = True
        if self.op1 != "":
            if not fst:
                res += ', '
            fst = False
            res += self.op1 + " op1"

        if self.op2 != "":
            if not fst:
                res += ', '
            fst = False
            res += self.op2 + " op2"

        if self.op3 != "":
            if not fst:
                res += ', '
            fst = False
            res += self.op3 + " op3"

        if self.op4 != "":
            if not fst:
                res += ', '
            fst = False
            res += self.op4 + " op4"

        buf = ''
        buf += (
            f'\tstd::cout << "{self.oper.lower()} ";\n'
        )
        for index, op in enumerate((self.op1, self.op2, self.op3, self.op4)):
            if op:
                if index != 0:
                    buf += f'\tstd::cout << ", ";\n'
                if op == 'Register':
                    buf += f'\tstd::cout << registerToString(op{index + 1});\n'
                elif op == 'RM':
                    buf += f'\tif (op{index + 1}.isReg()) ' + '{ std::cout << ' + f'registerToString(op{index + 1}.reg());' + ' }\n'
                    buf += '\telse { std::cout << "DWORD PTR " << ' + f'-op{index + 1}.mem() << "[ebp]";' + ' }\n'
                else:
                    buf += f'\tstd::cout << op{index + 1};\n'

        buf += '\tstd::cout << "\\n";\n'

        res += ") { \n" + buf + "}"
        return res

    def get_virt_impl_cpp(self):
        res = "virtual void "
        res += self.name
        res += "("

        fst = True
        if self.op1 != "":
            if not fst:
                res += ', '
            fst = False
            res += self.op1 + " op1"

        if self.op2 != "":
            if not fst:
                res += ', '
            fst = False
            res += self.op2 + " op2"

        if self.op3 != "":
            if not fst:
                res += ', '
            fst = False
            res += self.op3 + " op3"

        if self.op4 != "":
            if not fst:
                res += ', '
            fst = False
            res += self.op4 + " op4"

        res += ") { }"
        return res

# Defines for more comfortable access to table cells
pf = 0
pref0x = 1
po = 2
so = 3
o = 4
proc = 5
st = 6
m = 7
rl = 8
x = 9
mnemonic = 10
op1 = 11
op2 = 12
op3 = 13
op4 = 14

cpp_generated_funcs = []

def should_add(data):
    if data[mnemonic] == "" or data[mnemonic].find("no mnemonic") != -1 or data[mnemonic].find("undefined") != -1:
        return False

    if data[mnemonic].find("BOUND") != -1: # we don't support BOUND instruction now
        return False

    if data[mnemonic][0] == "F":
        # Now we don't have support for float instrction and operands
        # Let's drop it for now
        return False

    return True


for table in soup.find_all('table'):
    for entry in table.find_all('tbody'):
        data_tagged = entry.find_all('td')
        data = []
        for d in data_tagged:
            if d.contents == []:
                data.append("")
            else:
                data.append(str(d.contents[0]))

            if (len(data) == 3):
                # Means we are in PO cell
                if (data[-1].endswith('+r')):
                    # Align cells in such a row
                    data.append("")
        if should_add(data):
            cpp_generated_funcs.append(CppFunc(data[mnemonic], data[op1], data[op2], data[op3], data[op4]))

    break


def main():
    GET_FIRST = len(cpp_generated_funcs)

    file_init = open("init_cpp_funcs.tmp", "w")
    file_impl = open("impl_cpp_funcs.tmp", "w")
    file_virt_impl = open("virt_impl_cpp_funcs.tmp", "w")

    init_cpp_funcs = []
    for i in range(GET_FIRST):
        init_cpp_funcs.append(cpp_generated_funcs[i].get_init_cpp())
    init_cpp_funcs = sorted(set(init_cpp_funcs))

    for entry in init_cpp_funcs:
        file_init.write(entry + "\n")

    impl_cpp_funcs = []
    for i in range(GET_FIRST):
        impl_cpp_funcs.append(cpp_generated_funcs[i].get_impl_cpp("AsmTranslator"))
    impl_cpp_funcs = sorted(set(impl_cpp_funcs))

    for entry in impl_cpp_funcs:
        file_impl.write(entry + "\n")

    virt_impl_cpp_funcs = []
    for i in range(GET_FIRST):
        virt_impl_cpp_funcs.append(cpp_generated_funcs[i].get_virt_impl_cpp())
    virt_impl_cpp_funcs = list(set(virt_impl_cpp_funcs))
    virt_impl_cpp_funcs.sort()

    for entry in virt_impl_cpp_funcs:
        file_virt_impl.write(entry + "\n")

    file_init.close()
    file_impl.close()
    file_virt_impl.close()


if __name__ == '__main__':
    main()