//
// Created by Arman Mansourian on 10/11/18.
//
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <iostream>
#include <fstream>
#include "Parser.h"
#include "Stack.h"
using namespace std;
enum CALC_ACTIONS { ADDV, DELV, EVAL};

class Calculator {

public:
    Calculator();
    ~Calculator();
    Calculator(const Calculator &other);
    Calculator& operator=(const Calculator &other);

    string evaluate(string s);
    void addVar(string s);
    string getVars();
    void delVar(string s);
    string exportSession();
    void importSession(string s);

private:
    Stack<CALC_ACTIONS> exp_action = Stack<CALC_ACTIONS>(128);
    Stack<string> exp_values = Stack<string>(128);
    string* memory_exp;
    double* memory_val;

    Parser p;
    map<CALC_ACTIONS,string> m1;
    map<string,CALC_ACTIONS> m2;

    // Private functions.
    void nuke();
    void runCommands(Stack<CALC_ACTIONS> s, Stack<string> s2);
    bool isValidVar(string s);
    string action_to_string(CALC_ACTIONS c);
    CALC_ACTIONS string_to_action(string s);
    void copy(const Calculator &other);
};

#endif //CALCULATOR_H
