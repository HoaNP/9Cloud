Name: Nguyen Phuong Hoa
RollNo: SE03457
Class: CS0901

Hi there! Welcome to this Project!

Have a look at the files, and use the terminal to build them:

    $ make
    $ ./main

* Input to your parser generator should consist of: 
1, A list of token names and numbers, one per line.  Token names are strings of printable, non-whitespace characters.  Token numbers are small nonnegative integers, not necessarily contiguous or in any particular order.  (This will make it easier for you to use the same scanner for several different grammars.  You may assume that all token numbers are less than 128, that the value 0 is not used, and that the value 1 is reserved for end-of-file.) 
2, A blank line. 
3, A list of productions, one per line.  Each production should consist of a symbol name, the metasymbol “->”, and a sequence of zero or more symbol names.  We will test your code with only pure BNF:  no alternation, no Kleene closure.  You may assume that productions with the same left-hand side will be consecutive, and that the start symbol is the left-hand side of the first production. 

* Output consist of:
1, First Set:
i-th nonterminal : first set of this nonterminal


2, Follow Set
i-th nonterminal : follow set of this nonterminal


3, Predict Set
i-th production: predict set of this production


4, LL Table
