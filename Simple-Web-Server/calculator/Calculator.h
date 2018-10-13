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
    // Big bad calculator class that takes care of everything.
public:
    Calculator();
    ~Calculator();
    Calculator(const Calculator &other);
    Calculator& operator=(const Calculator &other);

    bool evaluate(string s, double& d);
    void addVar(string s);
    string getVars();
    void deleteVar(char c);
    string exportSession();
    void importSession(string s);

private:
    Stack<CALC_ACTIONS> exp_action = Stack<CALC_ACTIONS>(128);
    Stack<string> exp_values = Stack<string>(128);
    string* memory_exp;
    double* memory_val;

    //Parser p;
    map<CALC_ACTIONS,string> m1;
    map<string,CALC_ACTIONS> m2;

    // Private functions.
    void nuke();
    bool isValidVar(string s);
    string action_to_string(CALC_ACTIONS c);
    CALC_ACTIONS string_to_action(string s);
    void copy(const Calculator &other);
};

#endif //CALCULATOR_H