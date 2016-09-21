#!/home/senilica/school/testing
import unittest, math
from pyinterval.Tokenizer import tokenize
from pyinterval.Token import Token


class tokenizeTests(unittest.TestCase):
    def testTokenize(self):
        str = "100+10"
        res = [(Token.num, 100), (Token.op,"+"), (Token.num,10)]
        self.assertEqual(tokenize(str), res)
        str = "x"
        res = [(Token.var, "x")]
        self.assertEqual(tokenize(str), res)
        self.assertRaises(ValueError, tokenize, "100+")
        self.assertRaises(ValueError, tokenize,"+100")
        self.assertRaises(ValueError, tokenize, "*")
        str = "10x"
        res = [(Token.num, 10), (Token.op,"*"), (Token.var, "x")]
        self.assertEqual(tokenize(str), res)
        str = "10X"
        res = [(Token.num, 10), (Token.op,"*"), (Token.var, "x")]
        self.assertEqual(tokenize(str), res)
        str = "x10"
        res = [(Token.var, "x"), (Token.op,"*"), (Token.num, 10)]
        self.assertEqual(tokenize(str), res)
        str = "X10"
        res = [(Token.var, "x"), (Token.op,"*"), (Token.num, 10)]
        self.assertEqual(tokenize(str), res)
        str = "10x+sin(x)"
        res = [(Token.num, 10), (Token.op, "*"), (Token.var, "x"), (Token.op, "+"), (Token.func,"sin"), (Token.openParen, None), (Token.var, "x"), (Token.closeParen, None)]
        self.assertEqual(tokenize(str), res)
        self.assertRaises(ValueError, tokenize, "(100+10")
        self.assertRaises(ValueError, tokenize, "(100+)")
        self.assertRaises(ValueError, tokenize, "(+100)")
        str = "(10 (sin(x) + -2(2*4)) / 2^(CoS(y-2.5)))"
        res = ([(Token.openParen,  None),
                (Token.num, 10.0),
                (Token.op, "*"),
                (Token.openParen,  None),
                (Token.func, "sin"),
                (Token.openParen,  None),
                (Token.var, "x"),
                (Token.closeParen, None),
                (Token.op, "+"),
                (Token.num, -2.0),
                (Token.op, "*"),
                (Token.openParen,  None),
                (Token.num, 2.0),
                (Token.op, "*"),
                (Token.num, 4.0),
                (Token.closeParen, None),
                (Token.closeParen, None),
                (Token.op, "/"),
                (Token.num, 2.0),
                (Token.op, "^"),
                (Token.openParen,  None),
                (Token.func, "cos"),
                (Token.openParen,  None),
                (Token.var, "y"),
                (Token.op, "-"),
                (Token.num, 2.5),
                (Token.closeParen, None),
                (Token.closeParen, None),
                (Token.closeParen, None)
        ])
        self.assertEqual(tokenize(str), res)
        
        str = "10+1.2-[10]sIn(2.4x*y)/([2.4,4]x^[3.14])"
        res = ([(Token.num, 10),
                (Token.op, "+"),
                (Token.num, 1.2),
                (Token.op, "-"),
                (Token.func, "interval"),
                (Token.openParen, None),
                (Token.num, 10),
                (Token.closeParen, None),
                (Token.op, "*"),
                (Token.func, "sin"),
                (Token.openParen, None),
                (Token.num, 2.4),
                (Token.op, "*"),
                (Token.var, "x"),
                (Token.op, "*"),
                (Token.var, "y"),
                (Token.closeParen, None),
                (Token.op, "/"),
                (Token.openParen, None),
                (Token.func, "interval"),
                (Token.openParen, None),
                (Token.num, 2.4),
                (Token.sep, None),
                (Token.num, 4),
                (Token.closeParen, None),
                (Token.op, "*"),
                (Token.var, "x"),
                (Token.op, "^"),
                (Token.func, "interval"),
                (Token.openParen, None),
                (Token.num, 3.14),
                (Token.closeParen, None),
                (Token.closeParen, None)
        ])
        self.assertEqual(tokenize(str), res)
        self.assertEqual(tokenize("[]"), ([(Token.func, "interval"), (Token.openParen, None), (Token.closeParen, None)]))

        str = "[1,4]"
        res = ([(Token.func, "interval"), 
                (Token.openParen, None), 
                (Token.num, 1.0), 
                (Token.sep, None), 
                (Token.num, 4.0), 
                (Token.closeParen, None)
        ])

        self.assertEqual(tokenize(str), res)


    
        str = "1+pi"
        res = ([(Token.num, 1), (Token.op, "+"), (Token.num, math.pi)])
        self.assertEqual(tokenize(str), res) 


if __name__ == '__main__':
	unittest.main()      
