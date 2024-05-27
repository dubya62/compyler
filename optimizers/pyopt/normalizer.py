
class FunDef:
    def __init__(self, name:str = "anon", params:list = [], indention:int=0):
        self.name = name
        self.params = params
        self.indention = indention
        self.content = []

    def __str__(self):
        return f"def {self.name}({self.params}): {[str(x) for x in self.content]}"

class ClassDef:
    def __init__(self, name:str = "anon", params:list = [], indention:int=0):
        self.name = name
        self.params = params # superclasses
        self.indention = indention
        self.content = []
        
    def __str__(self):
        return f"class {self.name}({self.params}): {[str(x) for x in self.content]}"


class Normalizer:

    def __init__(self, lines:list[str]):
        self.lines = lines

    def tokenize(self, lines):
        """
        Tokenize a python file.
        Classes, functions, and the main part of the program
        are all put into blocks
        """
        tokens = []
        
        n = len(lines)
        continues = 0

        for line in range(len(lines)):
            if continues > 0:
                continues -= 1
                continue
            else:
                continues = 0
            # get the indention level of the code (tabs are just converted to 4 spaces)
            indents = 0
            for i in lines[line]:
                if i == ' ':
                    indents += 1
                elif i == "\t":
                    indents += 4
                else:
                    break
            
            # get what the line looks like without leading whitespace
            stripped = lines[line].lstrip()

            # if the line was empty, move on
            if stripped == "":
                continue

            # if this line starts with class or def,
            # recursively call this function on the
            # lines until the code block unindents
            if stripped[:3] == "def":
                # find next line that has the same number of indents or less
                iterator = line+1
                block = []
                while iterator < n:
                    # get number of indents of current line
                    indents2 = 0
                    for i in lines[iterator]:
                        if i == ' ':
                            indents2 += 1
                        elif i == "\t":
                            indents2 += 4
                        else:
                            break

                    if indents2 <= indents:
                        stripped2 = lines[iterator].strip()
                        if stripped2 == "" or stripped2[0] == "#":
                            pass
                        else:
                            break
                    
                    block.append(lines[iterator])
                    iterator += 1

                # get the function name and parameters from the current line
                continues = iterator - line - 1

                splitted = stripped[4:].split("(")
                name = splitted[0].strip()
                params = splitted[1].split(")")[0].split(",")

                if len(params) == 1 and params[0] == "":
                    params = []
                
                func = FunDef(name=name, params=params, indention=indents)
                print(f"Block: {block}")
                func.content = self.tokenize(block)

                tokens.append(func)
                
            elif stripped[:5] == "class":
                # find next line that has the same number of indents or less
                iterator = line+1
                block = []
                while iterator < n:
                    # get number of indents of current line
                    indents2 = 0
                    for i in lines[iterator]:
                        if i == ' ':
                            indents2 += 1
                        elif i == "\t":
                            indents2 += 4
                        else:
                            break

                    if indents2 <= indents:
                        stripped2 = lines[iterator].strip()
                        if stripped2 == "" or stripped2[0] == "#":
                            pass
                        else:
                            break
                    
                    block.append(lines[iterator])
                    iterator += 1

                # get the function name and parameters from the current line
                continues = iterator - line - 1

                splitted = stripped[6:].split("(")
                if len(splitted) == 1:
                    name = splitted[0].strip().strip(":")
                    params = []
                else:
                    name = splitted[0].strip()
                    params = splitted[1].split(")")[0].split(",")
                    if len(params) == 1 and params[0] == "":
                        params = []
                
                func = ClassDef(name=name, params=params, indention=indents)
                func.content = self.tokenize(block)

                tokens.append(func)
                
            else:
                tokens.append(lines[line])

        return tokens


    def normalize(self):
        """
        Go through the python program,
        making sure there is only one function call per line
        (making the code less pythonic)
        """
        tokens = self.tokenize(self.lines)

        


    def result(self):
        return self.lines


