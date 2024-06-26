
def quote_split(string:str, delimitter:str):
    """
    function to split a string,
    but the delimitter is ingored when inside quotes
    """
    result = string.split(delimitter)
    result2 = []
    quotes = 0
    for x in range(len(result)):
        if quotes:
            result2[-1] += delimitter + result[x] 
        else:
            result2.append(result[x])
        for y in range(len(result[x])):
            if result[x][y] == '"':
                quotes ^= 1
                quotes &= 1

    return result2


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

class CodeBlock:
    def __init__(self, name:str = "while", params:str = "1==1", indention:int=0):
        self.name = name
        self.params = params
        self.indention = indention
        self.content = []
        
    def __str__(self):
        return f"{self.name} ({self.params}): {[str(x) for x in self.content]}"


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

            # function to cut down on repetition for code blocks
            def block_helper(name:str="while", params:str="1==1"):
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

                code = CodeBlock(name=name, params=params, indention=indents)
                code.content = self.tokenize(block)

                tokens.append(code)
                return continues

            # if this line starts with class or def,
            # recursively call this function on the
            # lines until the code block unindents
            if stripped[:4] == "def ":
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

                splitted = quote_split(stripped[4:], "(")
                name = splitted[0].strip()
                params = quote_split(quote_split(splitted[1], ")")[0], ",")

                if len(params) == 1 and params[0] == "":
                    params = []
                
                func = FunDef(name=name, params=params, indention=indents)
                func.content = self.tokenize(block)

                tokens.append(func)
                
            elif stripped[:6] == "class ":
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

                splitted = quote_split(stripped[6:], "(")
                if len(splitted) == 1:
                    name = splitted[0].strip().strip(":")
                    params = []
                else:
                    name = splitted[0].strip()
                    params = quote_split(quote_split(splitted[1], ")")[0], ",")
                    if len(params) == 1 and params[0] == "":
                        params = []
                
                func = ClassDef(name=name, params=params, indention=indents)
                func.content = self.tokenize(block)

                tokens.append(func)
                
            elif stripped[:6] == "while ":
                the_params = (" ".join(stripped.split(" ")[1:])).strip().strip(":")
                continues = block_helper(name="while", params=the_params)
            elif stripped[:4] == "for ":
                the_params = (" ".join(stripped.split(" ")[1:])).strip().strip(":")
                continues = block_helper(name="for", params=the_params)
            elif stripped[:4] == "try:":
                continues = block_helper(name="try", params=[])
            elif stripped[:7] == "except:":
                continues = block_helper(name="except", params=[])
            elif stripped[:7] == "except ":
                the_params = (" ".join(stripped.split(" ")[1:])).strip().strip(":")
                continues = block_helper(name="except", params=[])
            elif stripped[:8] == "finally:":
                continues = block_helper(name="finally", params=[])
            elif stripped[:6] == "match ":
                the_params = (" ".join(stripped.split(" ")[1:])).strip().strip(":")
                continues = block_helper(name="match", params=the_params)
            elif stripped[:6] == "match(":
                the_params = stripped[6:].strip().strip(":")
                continues = block_helper(name="match", params=the_params)
            elif stripped[:5] == "case ":
                the_params = (" ".join(stripped.split(" ")[1:])).strip().strip(":")
                continues = block_helper(name="case", params=the_params)
            elif stripped[:3] == "if ":
                the_params = (" ".join(stripped.split(" ")[1:])).strip().strip(":")
                continues = block_helper(name="if", params=the_params)
            elif stripped[:5] == "elif ":
                the_params = (" ".join(stripped.split(" ")[1:])).strip().strip(":")
                continues = block_helper(name="elif", params=the_params)
            elif stripped[:5] == "else:":
                continues = block_helper(name="else", params=[])
            elif stripped[:5] == "with ":
                the_params = (" ".join(stripped.split(" ")[1:])).strip().strip(":")
                continues = block_helper(name="with", params=the_params)
            else:
                tokens.append(lines[line])

        return tokens


    def normalize(self, content):
        """
        Go through the python program,
        making sure there is only one function call per line
        (making the code less pythonic)
        """
        # go through the contents of the main program, then recursively call on all functions/classes/code blocks
        result = []

        # each line of main content should either be a function call or an assignment (using a function call)
        for token in content:
            if type(token) != str:
                token.content = self.normalize(token.content)
                # TODO: need to deal with parameter normalization
                result.append(token)
            else:
                result2 = []
                def helper(content:str, result, setvar:int=0, varNum:int=0, top:int=1)->list[str]:
                    # replace inside of parentheses with a tempVar
                    quotes = 0
                    stack = []
                    inside = ""
                    before = ""
                    after = ""
                    for i in range(len(content)-1, -1, -1):
                        if content[i] == '"':
                            quotes ^= 1
                            quotes &= 1
                        elif content[i] == ")" and quotes == 0:
                            if len(stack) == 0:
                                after = content[i+1:]
                                stack.append("")
                                continue
                            stack.append("")
                        elif content[i] == "(" and quotes == 0:
                            stack.pop()
                            if len(stack) == 0:
                                before = content[:i]
                                break
                        if len(stack) != 0:
                            inside = content[i] + inside
                    
                    # recursively call on inside of parentheses
                    if inside != "":
                        inside_handled, varNum = helper(inside, result, 1, varNum, 0)
                        result = inside_handled
                        remaining = before + f"(tempVar{varNum})" + after
                        varNum += 1
                        content = remaining


                    # replace to the left of . with tempVar
                    dot_index = -1
                    quotes = 0
                    for i in range(len(content)-1, -1, -1):
                        if content[i] == '"':
                            quotes ^= 1
                            quotes &= 1
                        elif content[i] == '.':
                            dot_index = i 
                            break
                    if dot_index != -1:
                        left = content[:dot_index]
                        right = content[dot_index+1:]
                    else:
                        left = ""
                        right = ""

                    assignment = ""
                    if top:
                        splitted = quote_split(left, "=")
                        if len(splitted) > 1:
                            assignment = "=".join(splitted[:-1])
                            left = splitted[-1]

                    # recursively call on left of .
                    if left != "":
                        left_handled, varNum = helper(left, result, 1, varNum, top)
                        result = left_handled
                        remaining = ""
                        if assignment != "":
                            remaining = f"{assignment}= "
                        remaining += f"tempVar{varNum}." + right
                        varNum += 1
                        content = remaining

                    if setvar:
                        temp_result = ""
                        iterator = 0
                        for i in range(len(content)):
                            if not iterator:
                                if not content[i].isspace():
                                    iterator = 1
                                    temp_result += f"tempVar{varNum} = "
                            if iterator:
                                temp_result += content[i]

                        result.append(temp_result)
                    else:
                        result.append(content)


                    return result, varNum
                res, varNum = helper(token, result2)
                result += res

        return result


    def result(self):
        return self.lines



