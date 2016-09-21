Shunting yard algorithm and equation tokenizer. 

Written in 2016 as part of a group project in a course on testing and software maintenance. 

The purpose of the tokenizer is to take literal strings of equations, e.g. 1+[2,3] and turn them into a tokenized set of operations and numbers or intervals. The shunting yard algorithm takes this list of tokens and constructs a reverse polish notation list of the algorithm, to be used in an interval based solver.

Unittests for the shunting yard algorithm as well as the tokenizer included.
