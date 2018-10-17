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
    //Big 4.
    Calculator();
    ~Calculator();
    Calculator(const Calculator &other);
    Calculator& operator=(const Calculator &other);

    //Evaluate an expression.
    string evaluate(string s);

    //Add variable to memory.
    void addVar(string s);
    //Get current variables.
    string getVars();
    //Delete a variable.
    void delVar(string s);
    //Delete all variables.
    void delAll();
    //Export a session.
    string exportSession();
    //Import a session.
    void importSession(string s);

private:
    //Track all the actions that the user does.
    vector<CALC_ACTIONS> exp_action;
    vector<string> exp_values;
    //store the expression and the value associated to it.
    string* memory_exp;
    double* memory_val;

    //Initialize an instance of the parser.
    Parser p;
    //Helper maps to convert calc actions to strings and viceversa.
    map<CALC_ACTIONS,string> m1;
    map<string,CALC_ACTIONS> m2;

    // Private functions.
    void nuke();
    //Reset all expressions to 0.
    void reset();
    //Run commands based on calc_actions and its expressions.
    void runCommands(vector<CALC_ACTIONS> s, vector<string> s2);
    //Recompute (UPDATE) expressions (For instance, when a new value is added).
    void recompute();
    //Sanitizes the string to prepare it to be evaluated.
    void sanitize(string& s);
    //Checks if s is a valid var.
    bool isValidVar(string& s);

    //Converters from action to s.
    string action_to_string(CALC_ACTIONS c);
    CALC_ACTIONS string_to_action(string s);

    //Copy calculator into another calculator.
    void copy(const Calculator &other);

    friend class Parser;
};

#endif //CALCULATOR_H
