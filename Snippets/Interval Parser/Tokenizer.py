import math
from pyinterval.Token import Token
from pyinterval.Interval import Interval

def tokenize(tokenString):
    """Tokenization function
Generates a list of token-value tuples for a given expression.
@Param: tokenString String - Expression using basic mathematical notation.
Returns: List containing tuples of cardinaltiy 2, containing a Token and when applicable
a value, or None when not.
Example: tokenize(\"1+2\") -> [(Token.num, 1), (Token.op, \"+\"), (Token.num, 2)]"""
    _num = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]
    _ops = ["+", "-", "*", "/", "^"]
    _var = ["x", "X", "y", "Y"]
    _accept = [0,1,3,12]
    ret = []
    state = 0
    openParen = 0
    ind = 0
    stop = len(tokenString)
    next = ""
    num = ""
    while(ind < stop):
        next = tokenString[ind]
        if(next == " "): # Discard white spaces.
            ind += 1
            continue
        if (state == 0 ): # Initial state. Allow unary operations, numbers, open parenthesis and variables.
            if(next in _var):
                state = 3
                ret.append((Token.var, next.lower()))
            elif(next in _num or next == "-"):
                state = 1
                num += next
            elif(next == "e" or next == "E"):
                state = 3
                ret.append((Token.num, math.e))
            elif(next == "i" or next == "I"):
                state = 19
            elif(next == "p" or next == "P"): # Pi, anyone?
                state = 15
            elif(next == "("):
                openParen += 1
                state = 4
                ret.append((Token.openParen, None))
            elif(next == "l" or next == "L"):
                state = 16
            elif(next == "s" or next == "S"):
                state = 6
            elif(next == "c" or next == "C"):
                state = 9
            elif(next == "["):
                ret.append((Token.func, "interval"))
                ret.append((Token.openParen, None))
                openParen += 1
                state = 13
            else:
                raise ValueError
        elif(state == 1 ): # Numerical parsing, allow digits, comma, variable, operation and open parenthesis
            if(next in _num):
                num += next
            elif(next == "e" or next == "E"):
                if(num == "-"):
                    ret.append((Token.num, -math.e))
                    num = ""
                    state = 3
                else:
                    ret.append((Token.num, float(num)))
                    ret.append((Token.op, "*"))
                    ret.append((Token.num, math.e))
                    num = ""
            elif(next == "i" or next == "I"):
                if(num != "-"):
                    ret.append((Token.num, float(num)))
                    ret.append((Token.op, "*"))
                    num = ""
                state = 19
            elif(next == "p" or next == "P"):
                if(num != "-"):
                    ret.append((Token.num, float(num)))
                    ret.append((Token.op, "*"))
                state = 15
            elif(next == "."):
                state = 2
                num += "."
            elif(next == ","):
                ret.append((Token.num, float(num)))
                ret.append((Token.sep, None))
                num = ""
                state = 14
            elif(next in _var): # Implicit multiplication with variable
                state = 3
                ret.append((Token.num, float(num)))
                num = ""
                ret.append((Token.op, "*"))
                ret.append((Token.var, next.lower()))
            elif(next == "("): # Implicit multiplication with parenthetical.
                if(num == "-"):
                    raise ValueError
                state = 4
                ret.append((Token.num, float(num)))
                num = ""
                ret.append((Token.op, "*"))
                ret.append((Token.openParen, None))
                openParen += 1
            elif(next == "["):
                if(num == "-"):
                    raise ValueError
                state = 13
                ret.append((Token.num, float(num)))
                num = ""
                ret.append((Token.op, "*"))
                ret.append((Token.func, "interval"))
                openParen += 1    
            elif(next in _ops): # Operand
                state = 5
                ret.append((Token.num, float(num)))
                num = ""
                ret.append((Token.op, next))
            elif(next == ")"): # End Parenthetical.
                if(openParen == 0):
                    raise ValueError
                openParen -= 1
                state = 12
                ret.append((Token.num, float(num)))
                num = ""
                ret.append((Token.closeParen, None))
            elif(next == "l" or next == "L"): #Implicit multiplication with sine
                if(num == "-"): #interpret "negative sine" as "-1 * sine"
                    ret.append((Token.num, -1.0))
                else:
                    ret.append((Token.num, float(num)))
                ret.append((Token.op, "*"))
                num = ""
                state = 16
            elif(next == "l" or next == "L"): #Implicit multiplication with sine
                if(num == "-"): #interpret "negative sine" as "-1 * sine"
                    ret.append((Token.num, -1.0))
                else:
                    ret.append((Token.num, float(num)))
                ret.append((Token.op, "*"))
                num = ""
                state = 16
            elif(next == "s" or next == "S"): #Implicit multiplication with sine
                if(num == "-"): #interpret "negative sine" as "-1 * sine"
                    ret.append((Token.num, -1.0))
                else:
                    ret.append((Token.num, float(num)))
                ret.append((Token.op, "*"))
                num = ""
                state = 6
            elif(next == "c" or next == "C"): # Implicit multiplication with cosinde
                if(num == "-"): #interpret "negative cosine" as "-1 * cosine"
                    ret.append((Token.num, -1.0))
                else:
                    ret.append((Token.num, float(num)))
                ret.append((Token.op, "*"))
                num = ""
                state = 9
            elif(next == "]"): # End Interval.
                if(openParen == 0):
                    raise ValueError
                openParen-=1
                state = 12
                ret.append((Token.num, float(num)))
                num = ""
                ret.append((Token.closeParen, None))
            else:
                raise ValueError
        elif(state == 2): # Fractional part of integer. Does not allow another fractional delimiter.
            if(next in _num):
                num += next
            elif(next == ","):
                ret.append((Token.num, float(num)))
                ret.append((Token.sep, None))
                num = ""
                state = 14
            elif(next == "e" or next == "E"):
                ret.append((Token.num, float(num)))
                ret.append((Token.op, "*"))
                ret.append((Token.num, math.e))
                state = 3
            elif(next == "i" or next == "I"):
                if(num != "-"):
                    ret.append((Token.num, float(num)))
                    ret.append((Token.op, "*"))
                    num = ""
                state = 19
            elif(next == "p" or next == "P"):
                ret.append((Token.num, float(num)))
                ret.append((Token.op, "*"))
                num = ""
                state = 15
            elif(next in _var): # Implicit multiplication with variable
                state = 3
                ret.append((Token.num, float(num)))
                num = ""
                ret.append((Token.op, "*"))
                ret.append((Token.var, next.lower()))
            elif(next == "("): # Implicit multiplication with parenthetical.
                state = 4
                ret.append((Token.num, float(num)))
                num = ""
                ret.append((Token.op, "*"))
                ret.append((Token.openParen, None))
                openParen += 1
            elif(next in _ops): # Operand
                if(num == "-"): # No operators allowed after negative sign.
                    raise ValueError
                state = 5
                ret.append((Token.num, float(num)))
                num = ""
                ret.append((Token.op, next.lower()))
            elif(next == "l" or next == "L"): #Implicit multiplication with sine
                if(num == "-"): #interpret "negative sine" as "-1 * sine"
                    ret.append((Token.num, -1.0))
                else:
                    ret.append((Token.num, float(num)))
                ret.append((Token.op, "*"))
                num = ""
                state = 16
            elif(next == "s" or next == "S"): #Implicit multiplication with sine
                if(num == "-"): #interpret "negative sine" as "-1 * sine"
                    ret.append((Token.num, -1.0))
                else:
                    ret.append((Token.num, float(num)))
                    ret.append((Token.op, "*"))
                    num = ""
                    state = 6
            elif(next == "c" or next == "C"): # Implicit multiplication with cosinde
                if(num == "-"): #interpret "negative cosine" as "-1 * cosine"
                    ret.append((Token.num, -1.0))
                else:
                    ret.append((Token.num, float(num)))
                    ret.append((Token.op, "*"))
                    num = ""
                    state = 9
            elif(next == ")"): # End Parenthetical.
                if(openParen == 0):
                    raise ValueError
                openParen -= 1
                state = 12
                ret.append((Token.num, float(num)))
                num = ""
                ret.append((Token.closeParen, None))
            elif(next == "["):
                state = 13
                ret.append((Token.num, float(num)))
                num = ""
                ret.append((Token.op, "*"))
                ret.append((Token.openParen, None))
                openParen += 1
            elif(next == "]"): # End Interval.
                if(openParen == 0):
                    raise ValueError
                openParen -= 1
                state = 12
                ret.append((Token.num, float(num)))
                num = ""
                ret.append((Token.closeParen, None))
            else:
                raise ValueError
        elif(state == 3 ): # Variable
            if(next in _var): # Implicit multiplication with variable.
                ret.append((Token.op, "*"))
                ret.append((Token.var, next.lower()))
            elif(next == "e" or next == "E"):
                ret.append((Token.op, "*"))
                ret.append((Token.num, math.e))
                state = 3
            elif(next == "i" or next == "I"):
                ret.append((Token.op, "*"))
                state = 19
            elif(next == "p" or next == "P"):
                ret.append((Token.op, "*"))
                state = 15
            elif(next == ","):
                ret.append((Token.var, next.lower()))
                ret.append((Token.sep, None))
                state = 14
            elif(next in _num): # Implicit multiplication with constant
                ret.append((Token.op, "*"))
                num += next
                state = 1
            elif(next == "("): # Implicit multiplication parenthetical
                ret.append((Token.op, "*"))
                ret.append((Token.openParen, None))
                state = 4
                openParen += 1
            elif(next == "["): # Implicit multiplication interval
                ret.append((Token.op, "*"))
                ret.append((Token.func, "interval"))
                ret.append((Token.openParen, None))
                openParen += 1
                state = 13
            elif(next in _ops):
                ret.append((Token.op, next))
                state = 5
            elif(next == "l" or next == "L"): #Implicit multiplication with sine
                ret.append((Token.op, "*"))
                num = ""
                state = 16
            elif(next == "s" or next == "S"): #Implicit multiplication with sine
                ret.append((Token.op, "*"))
                num = ""
                state = 6
            elif(next == "c" or next == "C"): # Implicit multiplication with cosinde
                ret.append((Token.op, "*"))
                num = ""
                state = 9
            elif(next == ")"): # End Parenthetical.
                if(openParen == 0):
                    raise ValueError
                openParen -= 1
                state = 12
                ret.append((Token.closeParen, None))
            elif(next == "]"): # End Parenthetical.
                if(openParen == 0):
                    raise ValueError
                openParen -= 1
                state = 12
                ret.append((Token.closeParen, None))
            else:
                raise ValueError            
        elif(state == 4 ): # Open parenthesis
            if(next in _var): #Variable
                state = 3
                ret.append((Token.var, next.lower()))
            elif(next in _num or next == "-"): # Number
                state = 1
                num += next
            elif(next == ")"): # Close paren
                if(openParen == 0):
                    raise ValueError
                openParen -= 1
                state = 12
                ret.append((Token.closeParen, None))
            elif(next == "("):
                openParen += 1
                ret.append((Token.openParen, None))
            elif(next == "["):
                openParen += 1
                ret.append((Token.func, "interval"))
                ret.append((Token.openParen, None))
                state = 13
            elif(next == "l" or next == "L"): # Logarithms
                state = 16
            elif(next == "s" or next == "S"):
                state = 6
            elif(next == "c" or next == "C"):
                state = 9
            elif(next == "e" or next == "E"):
                state = 3
                ret.append((Token.num, math.e))
            elif(next == "i" or next == "I"):
                state = 19
            elif(next == "p" or next == "P"): # Pi, anyone?
                state = 15
            else:
                raise ValueError            
        elif(state == 5 ): # Operand.
            if(next in _num or next == "-"):
                num += next
                state = 1
            elif(next == "e" or next == "E"):
                state = 3
                ret.append((Token.var, math.e))
            elif(next == "i" or next == "I"):
                state = 19
            elif(next == "p" or next == "P"): # Pi, anyone?
                state = 15
            elif(next in _var):
                ret.append((Token.var, next.lower()))
                state = 3
            elif(next == "l" or next == "L"): #Implicit multiplication with sine
                state = 16
            elif(next == "s" or next == "S"):
                state = 6
            elif(next == "c" or next == "C"):
                state = 9
            elif(next == "("):
                ret.append((Token.openParen, None))
                state = 4
                openParen += 1
            elif(next == "["): # Implicit multiplication interval
                ret.append((Token.func, "interval"))
                ret.append((Token.openParen, None))
                openParen += 1
                state = 13
            elif(len(ret) > 0 and next == "/" and ret[-1][1] == "/"): # Special case; allow floor division.
                if(len(ret) > 1):
                    if (ret[-2][1] == "/"): # Three division-symbols not allowed.
                        raise ValueError
                ret.pop()
                ret.append((Token.op, "//"))
            else:
                raise ValueError                
            
        elif(state == 6): # Read "s". (Sin)
            if(next == "i" or next == "I"):
                state = 7
            else:
                raise ValueError
        elif(state == 7): # Read "i".
            if(next == "n" or next == "N"):
                state = 8
            else:
                raise ValueError
        elif(state == 8): # Read "n".
            if(next == "("):
                state = 4
                ret.append((Token.func, "sin"))
                ret.append((Token.openParen, None))
                openParen += 1
            else:
                raise ValueError
            
        elif(state == 9): # Read "c".
            if(next == "o" or next == "O"):
                state = 10
            else:
                raise ValueError
            
        elif(state == 10): # Read "o".
            if(next == "s" or next == "S"):
                state = 11
            else:
                raise ValueError
            
        elif(state == 11): # Read "s". (cos)
            if(next == "("):
                state = 4
                ret.append((Token.func, "cos"))
                ret.append((Token.openParen, None))
                openParen += 1
            else:
                raise ValueError
        elif(state == 12): # Close paren/interval
            if(next in _num):
                ret.append((Token.op, "*"))
                state = 1
                num += next
            elif(next == "e" or next == "E"):
                state = 3
                ret.append((Token.op, "*"))
                ret.append((Token.num, math.e))
            elif(next == "i" or next == "I"):
                ret.append((Token.op, "*"))
                state = 19
            elif(next == "p" or next == "P"):
                state = 15
                ret.append((Token.op, "*"))
            elif(next in _var):
                ret.append((Token.op, "*"))
                state = 3
                ret.append((Token.var, next.lower()))
            elif(next in _ops):
                state = 5
                ret.append((Token.op, next))
            elif(next == "s" or next == "S"): # Implicit multiplication sin
                ret.append((Token.op, "*"))
                state = 6
            elif(next == "c" or next == "C"): #Implicit multiplcation cos
                ret.append((Token.op, "*"))
                state = 9
            elif(next == "("): #Implicit multiplication, other parenthesis
                state = 4
                openParen += 1
                ret.append((Token.op, "*"))
                ret.append((Token.openParen, None))
            elif(next == "["): #Implicit multiplication, interval
                state = 13
                openParen += 1
                ret.append((Token.op, "*"))
                ret.append((Token.openParen, None))
            elif(next == ")"): # Close paren
                if(openParen == 0):
                    raise ValueError # Too many paren closes
                openParen -= 1
                ret.append((Token.closeParen, None))
                state = 3 if openParen == 0 else 12
            elif(next == "]"): # Close interval
                if(openParen == 0):
                    raise ValueError # Too many interval closes or not enough arguments.
                openParen -= 1
                ret.append((Token.closeParen, None))
            elif(next == ","):
                ret.append((Token.sep, None))
                state = 14
            else:
                raise ValueError
        elif(state == 13): # Open Interval
            if(next in _var): #Variable
                state = 3
                ret.append((Token.var, next.lower()))
            elif(next in _num or next == "-"): # Number
                state = 1
                num += next
            elif(next == "]"): # Empty interval.
                openParen -= 1
                ret.append((Token.closeParen, None))
                state = 12
            elif(next == "("):
                openParen += 1
                ret.append((Token.openParen, None))
            elif(next == "s" or next == "S"):
                state = 6
            elif(next == "c" or next == "C"):
                state = 9
            elif(next == "p" or next == "P"):
                state = 15
            else:
                raise ValueError("Invalid token after [")
        elif(state == 14): # Comma found
            if(next in _num or next == "-"):
                num += next
                state = 1
            elif(next == "e" or next == "E"):
                state = 3
                ret.append((Token.num, math.e))
            elif(next == "i" or next == "I"):
                state = 19
            elif(next == "p" or next == "P"):
                state = 15
            elif(next in _var):
                ret.append((Token.var, next.lower()))
                state = 3
            elif(next == "("):
                openParen += 1
                ret.append((Token.openParen, None))
                state = 4
            elif(next == "["):
                openParen += 1
                ret.append((Token.func, "interval"))
                ret.append((Token.openParen, None))
                state = 13
            elif(next == "s" or next == "S"):
                state = 6
            elif(next == "c" or next == "C"):
                state = 9
            else:
                raise ValueError
        elif(state == 15): # P for Pi
            if(next == "i" or next == "I"):
                state = 3
                if(num == "-"):
                    ret.append((Token.num, -math.pi))
                num = ""
                ret.append((Token.num, math.pi))
            else:
                raise ValueError("P not a valid token.")
        elif(state == 16): #L for log
            if(next == "o" or next == "O"):
                state = 17
            else:
                raise ValueError
        elif(state == 17): # o for log!
            if(next == "g" or next == "G"):
                state = 18
            else:
                raise ValueError
        elif(state == 18): # and finally g.
            if(next == "("):
                ret.append((Token.func, "log"))
                ret.append((Token.openParen, None))
                openParen+=1
                state = 4
            else:
                raise ValueError
        elif(state == 19): #i for inf
            if(next == "n" or next == "N"):
                state = 20
            else:
                raise ValueError
        elif(state == 20): #n for inf!
            if(next == "f" or next == "F"):
                if(num == "-"):
                    ret.append((Token.num, float("-inf")))
                else:
                    ret.append((Token.num, float("inf")))
                state = 3
            else:
                raise ValueError
        else:
            raise RuntimeError # We ended up in a nonexistent state?        
        ind+=1
    if(state == 1 or state == 2): # Transcribing numbers
        ret.append((Token.num, float(num)))
    if(state not in _accept or openParen != 0 or openParen != 0):
        raise ValueError # The string is ill-formed.
    return ret
