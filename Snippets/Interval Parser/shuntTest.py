import unittest, math
from pyinterval.shunt import shunt
from pyinterval.Token import Token
import coverage
cov = coverage.Coverage()
class shuntTest(unittest.TestCase):
    def testShunt(self):
        cov.start()
        # Test some operator precedents
        str = "x^y^x"
        res = ([(Token.op, "^"), (Token.op, "^"), (Token.var, "x"), (Token.var, "y"), (Token.var, "x")])
        self.assertEqual(shunt(str), res)
        str = "x^(y^x)"
        res = ([(Token.op, "^"), (Token.op, "^"), (Token.var, "x"),(Token.var, "y"),(Token.var, "x")])
        self.assertEqual(shunt(str), res)
        str = "(x^y)^x"
        res = ([(Token.op, "^"), (Token.var, "x"),(Token.op, "^"), (Token.var, "y"), (Token.var, "x") ])
        self.assertEqual(shunt(str), res)
        str = "3-3*6+2"
        res = (
            [
                (Token.op, "+"),(Token.num, 2),(Token.op, "-"),(Token.op, "*"),(Token.num, 6), (Token.num, 3), (Token.num, 3) 
            ]
        )
        self.assertEqual(shunt(str), res)
        str = "sin(x*2)+y"
        res = (
            [
                (Token.op, "+"), (Token.var, "y"),(Token.func, "sin"), (Token.op, "*"), (Token.num, 2), (Token.var, "x")
            ]
        )
        self.assertRaises(ValueError, shunt, "(100+19")

       
        str = "2*cos(x/y)"
        res = (
            [
                (Token.op, "*"), (Token.func, "cos"), (Token.op, "/"), (Token.var, "y"), (Token.var, "x"), (Token.num, 2)
            ]
        )
        self.assertEqual(shunt(str), res) 


        str = "2*log(5)" 
        res = (
            [
                (Token.op, "*"), (Token.func, "log"),  (Token.num, 5), (Token.num, 2)
            ]
        )
        self.assertEqual(shunt(str), res)


        str = "4*e^3"
        res = (
            [
                (Token.op, "*"), (Token.op, "^"), (Token.num, 3), (Token.var, 2.718281828459045), (Token.num, 4)
            ]
        )
        self.assertEqual(shunt(str), res)

        str = "1*inf"
        res = (
            [
                (Token.op, "*"), (Token.num, float("inf")), (Token.num, 1)
            ]
        )
        self.assertEqual(shunt(str), res)

        str = "1/-inf"
        res = (
            [
                (Token.op, "/"), (Token.num, float("-inf")), (Token.num, 1)
            ]
        )
        self.assertEqual(shunt(str), res)
        

if __name__ == '__main__':
    cov.start()
    unittest.main()
    cov.stop()
    cov.save()
    cov.html_report()
