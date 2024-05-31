"""
This file's purpose is to get the time complexity of each line
of a normalized python program.
Using this analysis,
the program should decide where time complexity improvements need to be made.
(The worse the complexity, the harder the program will focus on that part)
(The time complexity does not need to be lowered if constant already)

TODO: This will hopefully include runtime analysis at some point
since the worst case complexity is not always the best indicator of performance 
"""

import normalizer
import complexities


class Line:
    def __init__(self, content:str, the_type:str):
        self.content = content
        # holds the type of the result of the expression on the left
        self.type = the_type
        self.complexity = self.analyze_complexity()


    def analyze_complexity(self)->str:
        """
        Possible complexities: 1, logn, n, nlogn, n2, n3, 2n, n!
        """
        # strip away the assignment since it should be constant (unless assigning a list, which should be handled later)
        splitted = quote_split(self.content)
        interest = splitted[-1] # now we have the interesting part
        
        # we need to check against a dictionary of each function's complexity
        comps = complexities.complexities

        # handle built in functions
        

        # handle declared functions
        
        return result


class Complexity:

    def __init__(self, normalized:list):
        self.normalized = normalized

    




