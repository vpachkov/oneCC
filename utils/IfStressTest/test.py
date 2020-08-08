#For aarch32

code = """
Expr77:
Expr89:
Expr33:
cmp
bl True33
cmp
bl True33
bl Fals33
True33:
ncmp
bl Fals89
True89:
bl True77
Fals33:
bl Fals89
Fals89:
cmp
bl True77
bl Fals77
True77:
ldr r0, [fp, #-4]
Fals77:
"""