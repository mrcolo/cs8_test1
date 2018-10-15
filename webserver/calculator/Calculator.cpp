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
        exp_values.emplace_back("");
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
    double d = 0;

    try {
        exp_action.push_back(EVAL);
        exp_values.push_back(s);
        p.tokenize(s,memory_val);
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
    catch (QUEUE_ERRORS e) {
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
    try {
        if (!isValidVar(s))
            throw BAD_EXP;

        exp_action.push_back(ADDV);
        exp_values.push_back(s);

        auto pos = s.find('=');

        //TODO this is not efficient, it should get the function in isvalid.
        auto sub_var = static_cast<char>(toupper(s[0]));

        cout << "Adding " << sub_var << "..." << endl;
        memory_exp[sub_var - 65] = s.substr(pos + 1, s.length());

        p.tokenize(memory_exp[sub_var - 65], memory_val);
        p.infixToPostfix();

        double d;
        d = p.evaluatePostfix();

        memory_val[sub_var - 65] = d;
    }
    catch(EXPRESSION_ERRORS e) {
        cout<<"Expression error occurred"<<endl;
    }

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
    exp_action.push_back(DELV);
    exp_values.push_back(s);

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
    string result;

    for(int i = 0; i < exp_action.size(); i++){
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
        exp_action.push_back(string_to_action(line.substr(0,4)));
        exp_values.push_back(line.substr(5, s.length()));
    }

    runCommands(exp_action, exp_values);
}

void Calculator::runCommands(vector<CALC_ACTIONS> s, vector<string> s2){
    for(unsigned int i = 0 ; i < s.size(); i++){
        cout<<s[i]<<endl;
        if(s2[i].length() != 0)
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