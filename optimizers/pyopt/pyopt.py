# This program tries to optimize python programs using a few different methods
# note that the resulting code follows terrible programming practices

#####################################################################
# Optimization methods:
# 1. Algorithmic (dynamic programming/optimizing nested loops)
# 2. Caching (dont recompute values if you can help it)
# 3. Precompute literals
# 4. Remove unnecessary code (probably a bad idea that will lead to bugs)
#####################################################################

import sys
import normalizer

#####################################################################
# handling command line args
# usage: (optional args are enclosed in brackets)
# python pyopt [-o <output_filename>] <input_filename>
def get_clargs()->dict:
    """
    Gets the command line args.
    Returns a dictionary with the input clargs.
    Prints usage when not enough args are given.
    """
    argc = len(sys.argv)
    if argc < 2:
        print("usage: (optional args are enclosed in brackets)\npython pyopt [-o <output_filename>] <input_filename>")
        exit(0)

    possible_args = ["-o", "-h", "--help"]

    args = {
        "output":"out.py"
        "input":"in.py"
    }

    for i in range(1, argc):
        if argv[i][0] == '-':
            # get the index of this arg
            if argv[i] in possible_args:
                index = possible_args.index(argv[i])
            else:
                print(f"argument {argv[i]} not recognized")
                exit(0)
            if index == 0:
                if argc < i+2:
                    print()
                filename = argv[i+1]
                args["output"] = filename
            elif index == 2 or index == 3:
                print("usage: (optional args are enclosed in brackets)\npython pyopt [-o <output_filename>] <input_filename>")
                exit(0)
        else:
            args["input"] = argv[i]
    return args


#####################################################################

class Optimizer:

    def __init__(self, lines:list[str]):
        self.lines = lines
        self.normalize()

    def normalize(self):
        # normalize the python program so that only one function call happens per line
        norm = normalizer.Normalizer()
        norm.normalize()
        return norm.result()

    def algorithm(self):
        # 1. Algorithmic (dynamic programming/optimizing nested loops)

    def cache(self):
        # 2. Caching (dont recompute values if you can help it)

    def precompute(self):
        # 3. Precompute literals

    def remove(self):
        # 4. Remove unnecessary code

    def result(self):
        return self.lines



if __name__ == "__main__":
    args = get_clargs()

    inp = args["input"]
    out = args["output"]

    # get the input file's data
    with open(inp, "r") as f:
        lines = f.readlines()

    # pass the file data to the optimizer
    opt = Optimizer(lines)

    # use each of the optimizer's features
    opt.algorithm()
    opt.cache()
    opt.precompute()
    opt.remove()

    outlines = opt.result()

    # write the optimizer's output to the output file
    with open(out, "w") as f:
        f.truncate(0)
        f.writelines(outlines)



