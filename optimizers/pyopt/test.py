import normalizer

with open("test.py", "r") as f:
    lines = f.readlines()

print("raw data:\n", lines)
norm = normalizer.Normalizer(lines)
tokens = norm.tokenize(lines)

print()
print()
print()
print()

print("tokenized:\n")
[print(str(x).strip()) for x in tokens]

def test(var1, var2, var3):
    print("testing")
    print("testing again")
    def test2(var4):
        pass

class Testing:

    def __init__(self, test="test,ing"):
        pass

    def __str__(self):
        pass

try:
    print()
except:
    print()
print()
print()
print()

print("final tokens:\n", tokens)

print()
print()
print()


normalized = norm.normalize(tokens)
print("normalized:\n", normalized)



