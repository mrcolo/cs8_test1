//
// Created by Arman Mansourian on 10/10/18.
//
#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Queue.h"
#include "Stack.h"

enum EXPRESSION_ERRORS {EMPTY_EXP, BAD_EXP};

class Parser {
public:
    // Union for managing data types in token queue.
    union data { double d; char c; };

    // Constructors.
    Parser();
    ~Parser();
    Parser(const Parser &other);
    Parser& operator=(const Parser &other);

    // Class functions.
    void tokenize(std::string input);
    void infixToPostfix();
    double evaluatePostfix();
    double performOperation(char operation, double operand1, double operand2);
    bool isValid(std::string input);
    bool isOperand(char C);
    bool isOperator(char C);
    bool isParens(char C);
    bool isDigit(char C);
    bool isLetter(char C);
    int prec(char C);

    // Friend functions.
    friend std::ostream& operator<<(std::ostream &out, const Parser &p);
    friend std::istream& operator>>(std::istream &in, Parser &p);

private:
    // Private objects.
    double result{};
    std::string expression{};
    std::string postfix{};

    // Private containers.
    Queue<data> tokens;
    Stack<double> operands;
    Stack<char> operators;
    std::vector<double> memories;

    // Private functions.
    void nuke();
    void copy(const Parser &other);
};

#endif //PARSER_H