"""
This program will be used to convert python code into C source code
The C source code can then be compiled using a C compiler (with heavy optimization for speed)
You will be able to choose the level of memory safety (static or dynamic)
Static means that all memory safety checks are made at compile time, while dynamic is done at runtime
Static also means the generated C code will not be very human readable
"""

def tokenize(filename):
    """Breaks a python file up into tokens"""
    with open(filename, "r") as f:
        lines = f.readlines()

    for i in range(len(lines)):
        lines[i] = " ".split(lines[i])


class Main:

    def __init__(self, safety:bool=False):
        # if safety is false, use static memory safety, else use dynamic
        print("Initializing the Python Compiler")


if __name__ == "__main__":
    main = Main()


