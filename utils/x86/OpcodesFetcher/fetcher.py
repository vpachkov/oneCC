from bs4 import BeautifulSoup

import requests

url = "http://ref.x86asm.net/coder32.html"
r  = requests.get(url)
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
        self.op1  = None
        self.op2  = None
        self.op3  = None
        self.op4  = None
    
    def __init__(self, name, op1, op2, op3, op4):
        self.name = self.gen_name(name, op1, op2, op3, op4)
        self.op1  = self.to_cpp_type(op1)
        self.op2  = self.to_cpp_type(op2)
        self.op3  = self.to_cpp_type(op3)
        self.op4  = self.to_cpp_type(op4)

    def norm_operand(self, op):
        op = op.replace("<b>", "")
        op = op.replace("</b>", "")
        op = op.replace("16/32", "32")
        op = op.replace("r/m", "rm")
        op = op.replace("r8", "reg8")
        op = op.replace("r16", "reg16")
        op = op.replace("r32", "reg32")
        op = op.replace("eAX", "EAX")
        return op

    def to_cpp_type(self, op):
        op = self.norm_operand(op)
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

        return ""

    def gen_name(self, name, op1, op2, op3, op4):
        res = name
        if op1 != "":
            res += "_" + self.norm_operand(op1)
        
        if op2 != "":
            res += "_" + self.norm_operand(op2)
        
        if op3 != "":
            res += "_" + self.norm_operand(op3)

        if op4 != "":
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

        res += ");"
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

        res += ") {}"
        return res


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

for table in soup.find_all('table'):
    for entry in table.find_all('tbody'):
        data_tagged = entry.find_all('td')
        data = []
        for d in data_tagged:
            data.append(d.text)
            if (len(data) == 3):
                # Means we are in PO cell
                if (data[-1].endswith('+r')):
                    # Align cells in such a row
                    data.append("")
        # print(data[mnemonic])

        cpp_generated_funcs.append(CppFunc(data[mnemonic], data[op1], data[op2], data[op3], data[op4]))
    
    break

for i in range(10): 
    print(cpp_generated_funcs[i].get_init_cpp())

for i in range(10): 
    print(cpp_generated_funcs[i].get_impl_cpp("AsmGenerator"))