//
// Created by Arman Mansourian on 10/11/18.
//

#include "Calculator.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;


Calculator::Calculator(){
    memory_exp = new string[26];
    memory_val = new double[26];
    for (int i = 0; i < 26; ++i) {
        memory_exp[i] = "";
        memory_val[i] = 0;
        exp_values[i] = "";
    }

    m1.insert({EVAL, "EVAL"});
    m1.insert({ADDV,"ADDV"});
    m1.insert({DELV,"DELV"});
    
    m2.insert({"EVAL", EVAL});
    m2.insert({"ADDV", ADDV});
    m2.insert({"DELV", DELV});
}

Calculator::~Calculator(){
    nuke();
}

Calculator::Calculator(const Calculator &other) {
    copy(other);
}

Calculator& Calculator::operator=(const Calculator &other) {

    if (this != &other) {
        nuke();
        copy(other);
    }

    return *this;
}

void Calculator::nuke(){

    for(int i = 0; i < 26; i++){
        memory_exp[i] = "";
        memory_val[i] = 0;
    }

    delete [] memory_exp;
    delete [] memory_val;

    memory_exp = nullptr;
    memory_val = nullptr;
}

void Calculator::copy(const Calculator &other){

    memory_exp = new string[26];
    memory_val = new double[26];

    for(int i = 0; i < 26; i++){
        memory_exp[i] = other.memory_exp[i];
        memory_val[i] = other.memory_val[i];
    }

}

bool Calculator::isValidVar(string s){
    //TODO improve this with a better check
    return isalpha(s[0]) && s[2] == '=';
}

string Calculator::evaluate(string s){
    cout<<"Evaluating "<<s<<"..."<<endl;
    double d;

    try {
        exp_action.push(EVAL);
        exp_values.push(s);
        p.tokenize(s);
        p.infixToPostfix();
        d = p.evaluatePostfix();
    }
    catch (EXPRESSION_ERRORS e) {
        if (e){
            ptree temp;
            temp.put<bool>("expression", false);
            temp.put<double>("value",0);
            stringstream ss;
            write_json(ss, temp);
            return ss.str();
        }

    }
    catch (STACK_ERRORS e) {
        ptree temp;
        temp.put<bool>("expression", false);
        temp.put<double>("value",0);
        stringstream ss;
        write_json(ss, temp);
        return ss.str();
    }

    ptree temp;
    temp.put<bool>("expression", true);
    temp.put<double>("value",d);
    stringstream ss;
    write_json(ss, temp);
    return ss.str();
}

void Calculator::addVar(string s){

    if(!isValidVar(s))
        throw BAD_EXP;

    exp_action.push(ADDV);
    exp_values.push(s);

    auto pos = s.find("=");

    auto sub_var = static_cast<char>(toupper(s[0]));

    cout<<"Adding "<<sub_var<<"..."<<endl;
    memory_exp[sub_var-65] = s.substr(pos + 1,s.length());

    p.tokenize(memory_exp[sub_var-65]);
    p.infixToPostfix();

    double d;
    d = p.evaluatePostfix();

    memory_val[sub_var-65] = d;
}

string Calculator::getVars(){

    ptree arr;
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < 26; ++i) {
        ptree temp;
        temp.put<string>("expression", memory_exp[i]);
        temp.put<double>("value", memory_val[i]);

        arr.push_back( std::make_pair(alphabet.substr(i,1), temp));
    }

    stringstream ss;
    write_json(ss, arr);

    return ss.str();
};

void Calculator::delVar(string s){

    char c = s[s.find("clear") + 6];
    exp_action.push(DELV);
    exp_values.push(s);

    memory_val[toupper(c)-65] = 0;
    memory_exp[toupper(c)-65] = "";
}

string Calculator::action_to_string(CALC_ACTIONS c){
    return m1[c];
}

CALC_ACTIONS Calculator::string_to_action(string s){
    return m2[s];
}

string Calculator::exportSession(){
    string result = "";

    for(int i = 0; i < exp_action.getSize(); i++){
        result += action_to_string(exp_action[i]);
        result += " ";
        result += exp_values[i];
        result += "\n";
    }

    return result;
}

void Calculator::importSession(string s){
    //TODO understand why this is erroring out.
    //nuke();

    stringstream ss;

    ss<<s;

    string line;

    while(getline(ss,line)){
        exp_action.push(string_to_action(line.substr(0,4)));
        exp_values.push(line.substr(5, s.length()));
    }

    runCommands(exp_action, exp_values);
}

void Calculator::runCommands(Stack<CALC_ACTIONS> s, Stack<string> s2){
    for(int i = 0 ; i < s.getSize(); i++){
        switch(s[i]) {
            case EVAL:
                evaluate(s2[i]);
                break;
            case ADDV:
                addVar(s2[i]);
                break;
            case DELV:
                delVar(s2[i]);
                break;
        }
    }
}