//
// Created by Arman Mansourian on 10/10/18.
//
#include "Parser.h"
struct perform {
    typedef double (*operation)(double, double);
};

//TODO NEED TO WRITE
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

// Function to take input expression (string) and convert into tokens for queue.
void Parser::tokenize(const std::string input, double* memory_val) {
    if (!isValid(input))
        throw BAD_EXP;
    int j = 0;
    // Increment input until the end.
    for (unsigned int i = 0; i < input.length(); ++i, ++j) {
        if (tokens.full())
            throw QFULL;
        // If character is a delimiter, move on.
        if (input[i] == ' ' || input[i] == ',') {
            continue;
        }
        // If character is an operator or parenthesis, add to token queue.
        if (isOperator(input[i]) || isParens(input[i])) {
            tokens.enqueue(input[i]);
        }
        // If character is a letter (A-Z), grab memory value and add to token queue.
        if (isLetter(input[i])) {

            tokens.enqueue(memory_val[toupper(input[i])-65]);
        }
        // If character is a number, check for decimal and add double to token queue.
        else if (isDigit(input[i]) || input[i] == '.') {
            std::string num;
            while (isDigit(input[i]) || input[i] == '.') {
                num += input[i];
                ++i;
            }
            --i;
            tokens.enqueue(std::stod(num));
        }
    }
    std::cout << tokens << std::endl;
}

// Function to convert queue of tokens into postfix (RPN) string.
void Parser::infixToPostfix() {
    variant<double,char> token;
    variant<double,char> prev;
    bool isNegative = false;
    // Increment tokens queue until empty.
    while (!tokens.empty()) {
        token = tokens.dequeue();
        // If the scanned character is an operand, add it to output queue.
        try {
            if (token.type() == typeid(double)) {
                if (isNegative) {
                    token = get<double>(token) * -1;
                    isNegative = false;
                }
                postfix.enqueue(token);
            }
                // If the scanned character is an ‘(‘, push it to the operator stack.
            else if (get<char>(token) == '(') {
                operators.push(get<char>(token));
            }
                // If the scanned character is an ‘)’, pop to output string from the stack until an ‘(‘ is encountered.
            else if (get<char>(token) == ')') {
                while (operators.peek() != '(')
                    postfix.enqueue(operators.pop());
                operators.pop();
            }
                // If an operator is scanned
            else if (isOperator(get<char>(token))) {
                // Special case for negatives. TODO ISSUE IS HERE WITH NEGATIVE I THINK I FIXED IT
                if (prev.type() == typeid(char)) {
                    if (get<char>(token) == '-' && get<char>(prev) == '(')
                        isNegative = true;
                    else {
                        // Check for operator precedence and add operators to output queue accordingly.
                        while (!operators.empty() && operators.peek() != '(' &&
                               (prec(get<char>(token)) <= prec(operators.peek()))) {
                            postfix.enqueue(operators.pop());
                        }
                        operators.push(get<char>(token));
                    }
                } else {
                    // Check for operator precedence and add operators to output queue accordingly.
                    while (!operators.empty() && operators.peek() != '(' &&
                           (prec(get<char>(token)) <= prec(operators.peek()))) {
                        postfix.enqueue(operators.pop());
                    }
                    operators.push(get<char>(token));
                }
            }
        }
        catch(STACK_ERRORS e){
            std::cout << e << std::endl;
        }
        catch(QUEUE_ERRORS e){
            std::cout << e << std::endl;
        }
        prev = token;
    }
    //Pop all the remaining elements from the stack
    while (!operators.empty()) {
        postfix.enqueue(operators.pop());
    }
    std::cout << postfix << std::endl;
}

// Function to evaluate Postfix expression (string) and return output.
double Parser::evaluatePostfix() {
    variant<double,char> token;
    // Increment postfix queue until empty.
    while (!postfix.empty()) {
        token = postfix.dequeue();
        // If character is an operand, push to operand stack;
        if (token.type() == typeid(double)) {
            operands.push(get<double>(token));
        }
        // If character is operator, pop two elements from stack, perform operation and push the result back.
        else if (isOperator(get<char>(token))) {
            // Pop two operands.
            double operand2 = operands.pop();
            double operand1 = operands.pop();
            // Perform operation
            double result = performOperation(get<char>(token), operand1, operand2);
            //Push back result of operation on stack.
            operands.push(result);
        }
    }
    double d = operands.pop();
    tokens.clear();
    postfix.clear();
    operands.clear();
    operators.clear();
    // If input is in correct format, operand stack will have one element. This will be the output.
    return d;
}

double add(double operand1, double operand2) {
        return operand1 + operand2;

}
double sub(double operand1, double operand2) {
        return operand1 - operand2;
}

double multiply(double operand1, double operand2) {
        return operand1 * operand2;
}

double divide(double operand1, double operand2) {
        return operand1 / operand2;
}

double exp(double operand1, double operand2) {
        return pow(operand1, operand2);
}
// Function to perform an operation and return output.
double Parser::performOperation(char operation, double operand1, double operand2) {
    perform::operation os [128];

    os['+'] = &add;
    os['-'] = &sub;
    os['*'] = &multiply;
    os['/'] = &divide;
    os['^'] = &exp;

    return os[operation](operand1, operand2);
}

// TODO WRITE ISVALID FUNCTION IN CALCULATOR CLASS
// Function to check if input expression is valid.
bool Parser::isValid(const std::string input) {
    // check std::string expression and return true or false...
    return true;
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

// TODO WRITE NUKE
void Parser::nuke() {

}

// TODO WRITE COPY
void Parser::copy(const Parser &other) {

}

// TODO WRITE <<
std::ostream& operator<<(std::ostream &out, const Parser &p) {
    return out;
}

// TODO WRITE >>
std::istream& operator>>(std::istream &in, Parser &p) {
    return in;
}
