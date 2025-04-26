# Expression Tree Evaluator

## Overview
This application implements an **Expression Tree** in C to evaluate binary arithmetic expressions given in **infix notation**. It supports basic arithmetic operations and converts infix expressions into postfix notation using a custom array-based stack.


## Features

- Read multiple infix expressions from a file
- Print original infix expressions
- Build expression trees and evaluate their results
- Convert and print postfix expressions
- Save postfix expressions and evaluation results to an output file
- Interactive menu-based interface


## Technologies Used

- C programming language
- Array-based Stack implementation
- Expression Tree for parsing and evaluation


## Supported Operators

- Addition (`+`)
- Subtraction (`-`)
- Multiplication (`*`)
- Division (`/`)
- Modulus (`%`)
- Parentheses (`(` and `)`)


## File Structure
```
expression_tree_evaluator/
├── main.c      # Main source code for building and evaluating expression trees
├── input.txt   # Sample input file containing infix expressions
├── output.txt  # Output file containing postfix expressions and results 
├── README.md   # Project documentation
```

## How to Run

1. Ensure you have a C compiler installed (e.g., CodeBlocks).
2. Clone or download the repository.
3. Compile the C file
