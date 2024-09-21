# Polynomial Class Project

This project implements a Polynomial class in C++ that represents a polynomial as a linked list of terms. Each term is 
represented by a Node object. The class provides methods to add, subtract, multiply, divide polynomials, evaluate the 
polynomial for a given value of x, and print the polynomial.

## Features

- **Addition**: Add two polynomials.
- **Subtraction**: Subtract one polynomial from another.
- **Multiplication**: Multiply two polynomials.
- **Exponentiation**: Raise a polynomial to a power.
- **Division**: Divide one polynomial by another and return the remainder.
- **Evaluation**: Evaluate the polynomial for a given value of x.
- **Parsing**: Parse a polynomial from input.
- **Printing**: Print the polynomial.

## Class Overview

### Node Class

The `Node` class represents a term in the polynomial.

```cpp
class Node {
public:
    double coeff; // Coefficient of the term
    int exp;      // Exponent of the term
    Node* next;   // Pointer to the next node

    Node(double c, int e) : coeff(c), exp(e), next(nullptr) {}
};


class Polynomial {
private:
    Node* head; // Head of the linked list representing the polynomial
    Node* tail;

    void addTerm(double coeff, int exp);

public:
    Polynomial();
    Polynomial(std::istream& input);

    Polynomial operator+(const Polynomial& right_hand_side_poly) const;
    Polynomial operator-(const Polynomial& right_hand_side_poly) const;
    Polynomial operator*(const Polynomial& right_hand_side_poly) const;
    Polynomial operator%(const Polynomial& denominator) const;
    Polynomial operator^(int exp) const;

    double evaluate(const Polynomial& poly, double x) const;
    void parseFromInput(int terms, std::istream& input);
    void print() const;
    Polynomial zero() const;
};
```

Usage
Compilation
To compile the project, use the following command:
g++ -o polynomial main.cpp

Running the Program
To run the program, use the following command:
./polynomial


Commands
The program supports the following commands:

ZERO: Prints the zero polynomial.
ARBITRARY <n>: Parses an arbitrary polynomial with n terms from the input stream and prints it.
PRINT <n>: Parses a polynomial with n terms from the input stream and prints it.
EVAL <n> <m>: Parses a polynomial with n terms from the input stream and evaluates it at m.
ADD <n> <m>: Parses two polynomials with n and m terms from the input stream, adds them, and prints the result.
SUB <n> <m>: Parses two polynomials with n and m terms from the input stream, subtracts them, and prints the result.
MUL <n> <m>: Parses two polynomials with n and m terms from the input stream, multiplies them, and prints the result.
EXP <n> <m>: Parses a polynomial with n terms from the input stream and raises it to the power of m.
MOD <n> <m>: Parses two polynomials with n and m terms from the input stream,divides the first polynomial by the second polynomial, and prints the remainder.
QUIT: Exits the command processor.

```cpp
Example Usage
Please enter any of the following commands:
ZERO
ARBITRARY  <int> ( <int>  <int> )*
PRINT <int> ( <int>  <int> )*
EVAL   <int> ( <int>  <int> )*  <int>
ADD   <int> ( <int>  <int> )*  <int> ( <int>  <int> )*
SUB    <int> ( <int>  <int> )*  <int> ( <int>  <int> )*
MUL    <int> ( <int>  <int> )*  <int> ( <int>  <int> )*
EXP    <int> ( <int>  <int> )*  <int>
MOD    <int> ( <int>  <int> )*  <int> ( <int>  <int> )*
QUIT
Please enter the command:
```

Acknowledgments
This project was developed as part of a computer science course.
Special thanks to the course instructors and teaching assistants for their support and guidance.
