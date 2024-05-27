import normalizer

with open("test.py", "r") as f:
    lines = f.readlines()

norm = normalizer.Normalizer(lines)

print(lines)

print()
print()
print()

tokens = norm.tokenize(lines)
print(tokens)

print()
print()
print()

print(tokens[-1])

def test(var1, var2, var3):
    print("testing")
    print("testing again")
    def test2(var4):
        pass

class Testing:

    def __init__(self):
        pass

    def __str__(self):
        pass
