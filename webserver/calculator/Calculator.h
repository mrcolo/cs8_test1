//
// Created by Arman Mansourian on 10/11/18.
//
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <iostream>
#include <fstream>
#include <vector>
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
    void delAll();
    string exportSession();
    void importSession(string s);

private:
    vector<CALC_ACTIONS> exp_action;
    vector<string> exp_values;
    string* memory_exp;
    double* memory_val;

    Parser p;
    map<CALC_ACTIONS,string> m1;
    map<string,CALC_ACTIONS> m2;

    // Private functions.
    void nuke();
    void reset();
    void runCommands(vector<CALC_ACTIONS> s, vector<string> s2);
    void recompute();
    bool isValidVar(string s);
    string action_to_string(CALC_ACTIONS c);
    CALC_ACTIONS string_to_action(string s);
    void copy(const Calculator &other);

    friend class Parser;
};

#endif //CALCULATOR_H
