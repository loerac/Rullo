# Rullo
Finds all the possible combinations of a set from a rullo puzzle using combinatorics. Combination function was given from http://rosettacode.org/wiki/Combinations#C.2B.2B

# Getting Started
Use the GNU g++ compiler for main.cpp

g++ main.c -o rullo

# Instructions
There are two arguments you need to give the program;

Rullo number: the number outside of the row/column

Set row/column: all the numbers given in the row/column

# Example
./rullo [rullo_number] [set_row_columns]

### Input
./rullo 10 1 3 5 7 9 10

### Output
Found Combination: [ 10 ]

Found Combination: [ 1 9 ]

Found Combination: [ 3 7 ]
