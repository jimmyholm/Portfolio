## v.1
from pyinterval.Tokenizer import tokenize
from pyinterval.Token import Token
# Returns reverse polish notation stack of a mathematical expression (String).
def shunt(expr) :
    """shunt(expr)
    Performs the Shunting Yard algorithm on a list of tokens, producing a
    Reverse Polishg Notation representation of expr.

    expr -- List of tokens, produced by the tokenizer engine and representing a mathematical expression with at most two unknowns.
    
    returns: The same list of tokens as in expr, but transformed to reverse polish notation.
             The returned list has had all parentheses removes, as these are not necessary in RPN.
    Example: shunt([(Token.num, 2), (Token.op, "*"), (Token.func, "log"), 
                    (Token.openParen, None), (Token.num, 5, ), 
                    (Token.closeParen, None)]) -> 
                   [(Token.op, "*"), (Token.func, "log"),  (Token.num, 5), (Token.num, 2)]
    """
    
    # Operator definitions; dictionary of tuples containing
    # Associativity (0 = left, 1 = right) and priority (higher value takes precedence).
    _ops = (
        {
            "^":  (1, 4),
            "*":  (0, 3),
            "/":  (0, 3),
            "//": (0, 3),
            "+":  (0, 2),
            "-":  (0, 2)
        }
    )
    _input = tokenize(expr)
    output = []
    opstack = []
    for token in _input:         # Loop through the input tokens.
        if(token[0] == Token.num or         # Number or
           token[0] == Token.var):          # variable
            output.append(token)
        elif(token[0] == Token.func):       # Function
            opstack.append(token)
        elif(token[0] == Token.op):         # Operand
            while(len(opstack) > 0):
                o2 = opstack[-1]
                if(o2[0] == Token.op):
                    if(_ops[token[1]][0] == 0): # o1 is left associative.
                        if(_ops[token[1]][1] <= _ops[o2[1]][1]): # Pop the operator to output
                            output.append(opstack.pop())
                        else:
                            break
                    else:
                        if(_ops[token[1]][1] < _ops[o2[1]][1]):
                            output.append(opstack.pop())
                        else:
                            break
                else:
                    break
            opstack.append(token)
        elif(token[0] == Token.openParen):  # Open parenthesis
            opstack.append(token)
        elif(token[0] == Token.closeParen): # Close parenthesis
            while(True):
                if(len(opstack) == 0):
                    raise ValueError("Mismatched parentheses.")
                elif(opstack[-1][0] == Token.openParen): # Matching parenthesis
                    opstack.pop()
                    if(len(opstack) > 0 and opstack[-1][0] == Token.func): # top of stack after paren is a function.
                        output.append(opstack.pop())
                    break
                else:
                    output.append(opstack.pop())
        else: #(token[0] == Token.sep)        Separator
            while(True):
                if(len(opstack) == 0):
                    raise ValueError("Mismatched parentheses or misplaced separator.")
                if(opstack[-1][0] == Token.openParen):
                    break
                output.append(opstack.pop()) # Pop operators onto the output.
        # No more tokens; clear the opstack.
    while(len(opstack) != 0):
        if(opstack[-1][0] == Token.openParen or opstack[-1][0] == Token.closeParen):
            raise ValueError("Mismatched parentheses.")
        output.append(opstack.pop())
    return output[::-1]
