//
// Created by Arman Mansourian on 10/10/18.
//
#include "Parser.h"

// NEED TO WRITE
Parser::Parser() = default;

Parser::~Parser() {
    nuke();
}

Parser::Parser(const Parser &other) {
    copy(other);
}

Parser& Parser::operator=(const Parser &other) {
    if (this != &other) {
        nuke();
        copy(other);
    }
    return *this;
}

// NEED TO TEST (PROBABLY BUGGY)
// Function to take input expression (string) and convert into tokens for queue.
void Parser::tokenize(const std::string input) {
    if (!isValid(input))
        throw BAD_EXP;
    expression = input;
    int j = 0;
    for (int i = 0; i < input.length(); ++i, ++j) {
        if (tokens.full())
            throw QFULL;
        // If character is a delimiter, move on.
        if (input[i] == ' ' || input[i] == ',')
            continue;
        // If character is an operator or parenthesis or letter (A-Z), add to token queue
        if (isOperator(input[i]) || isParens(input[i]) || isLetter(input[i]))
            tokens[j].c = input[i];
        // If character is a number, check for decimal and add to token queue
        else if (isDigit(input[i]) || i == '.') {
            std::string temp;
            while (isDigit(input[i]) || i == '.') {
                temp += input[i];
                ++i;
            }
            --i;
            tokens[j].d = std::stod(temp);
        }
    }
}

// NEED TO FIX MY OLD CODE (IMPLEMENT CLASS FEATURES AND OBJECTS)
// Function to convert queue of tokens into postfix (RPN) string.
void Parser::infixToPostfix() {

    Stack<char> s;
    s.push('?');
    std::string result;

    while (!tokens.empty()) {

        if ()

    }

    for (int i = 0; i < tokens.getSize(); ++i) {

        // If the scanned character is an operand, add it to output string.
        if (isOperand([i]))
        {
            while(i < input.length() && isOperand(input[i]))
            {
                result += input[i];
                i++;
            }
            i--;
            result += ' ';
        }

            // If the scanned character is an ‘(‘, push it to the stack.
        else if (input[i] == '(')
            s.push('(');

            // If the scanned character is an ‘)’, pop to output string from the stack until an ‘(‘ is encountered.
        else if (input[i] == ')')
        {
            while (s.top() != '?' && s.top() != '(')
            {
                char C = s.top();
                s.pop();
                result += C;
                result += ' ';
            }
            if (s.top() == '(')
                s.pop();
        }

            // If an operator is scanned
        else {

            // Special case for negative sign
            if (input[i] == '-' && input[i-1] == '(')
            {
                result += '0';
                result += ' ';
            }

            // precedence check
            while (s.top() != '?' && prec(input[i]) <= prec(s.top()))
            {
                char C = s.top();
                s.pop();
                result += C;
                result += ' ';
            }
            s.push(input[i]);
        }
    }

    //Pop all the remaining elements from the stack
    while (s.top() != '?')
    {
        char C = s.top();
        s.pop();
        result += C;
        result += ' ';
    }
    return result;
}

// NEED TO FIX MY OLD CODE (IMPLEMENT NEW CLASS FEATURES AND OBJECTS)
// Function to evaluate Postfix expression (string) and return output.
double Parser::evaluatePostfix() {
    // Declaring a Stack from Standard template library in C++.
    Stack<double> s;

    for (int i = 0; i < input.length(); i++)
    {
        // Scanning each character from left.
        // If character is a delimiter, move on.
        if (input[i] == ' ' || input[i] == ',')
            continue;

            // If character is operator, pop two elements from stack, perform operation and push the result back.
        else if (isOperator(input[i]))
        {
            // Pop two operands.
            double operand2 = s.pop();
            double operand1 = s.pop();

            // Perform operation
            double result = performOperation(input[i], operand1, operand2);

            //Push back result of operation on stack.
            s.push(result);
        }

            // If character is digit or variable, extract the numeric operand from the string.
        else if (isOperand(input[i]))
        {
            double operand = 0;

            // Keep incrementing i as long as you are getting a numeric digit.
            while(i < input.length() && isOperand(input[i]))
            {
                // Every time we get a digit towards right, we can multiply current total in operand by 10
                // and add the new digit.
                if (isDigit(input[i]))
                {
                    operand = (operand * 10) + (input[i] - '0');
                    i++;
                }
            }
            // We don't want to skip the non-numeric character by incrementing i twice.
            i--;

            // Push operand on stack.
            s.push(operand);
        }
    }
    // If input is in correct format, Stack will have one element. This will be the output.
    return s.top();
}

// NEED TO TEST
// Function to perform an operation and return output.
double Parser::performOperation(char operation, double operand1, double operand2) {
    switch (operation) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        case '^':
            return pow(operand1, operand2);
        default:
            std::cout << "Unexpected Error in performOperation()!";
            return -1;
    }
}

// NEED TO WRITE
// Function to check if input expression is valid.
bool Parser::isValid(const std::string input) {
    // check std::string expression and return true or false...
}

// Function to check if character is letter or digit.
bool Parser::isOperand(char C) {
    if (C >= 'A' && C <= 'Z')
        return true;
    if (C >= 'a' && C <= 'z')
        return true;
    return (C >= '0' && C <= '9');
}

// Function to check if character is operator.
bool Parser::isOperator(char C) {
    return C == '+' || C == '-'|| C == '*' || C == '/' || C == '^';
}

// Function to check if character is a parenthesis.
bool Parser::isParens(char C) {
    return C == '(' || C == ')';
}

// Function to check if character is digit.
bool Parser::isDigit(char C) {
    return C >= '0' && C <= '9';
}

// Function to check if character is letter.
bool Parser::isLetter(char C) {
    return ((C >= 'A' && C <= 'Z') || (C >= 'a' && C <= 'z'));
}

// Function to determine precedence of operator.
int Parser::prec(char C) {
    if(C == '^')
        return 3;
    else if(C == '*' || C == '/')
        return 2;
    else if(C == '+' || C == '-')
        return 1;
    else
        return -1;
}

// NEED TO WRITE
void Parser::nuke() {

}

// NEED TO WRITE
void Parser::copy(const Parser &other) {

}

// NEED TO WRITE
std::ostream& operator<<(std::ostream &out, const Parser &p) {
    return out;
}

// NEED TO WRITE
std::istream& operator>>(std::istream &in, Parser &p) {
    return in;
}
