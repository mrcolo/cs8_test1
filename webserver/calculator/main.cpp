#include <iostream>
#include "Calculator.h"
#include "Parser.h"
using namespace std;

int main() {
    try{
        Calculator c;
        string s = c.evaluate("(");
        cout<<c.evaluate("(")<<c.evaluate("2")<<c.evaluate("(2 + ")<<endl;
    }
    catch (EXPRESSION_ERRORS e) {
        switch (e) {
            case BAD_EXP: cout << "BAD EXPRESSION" << endl; break;
            case EMPTY_EXP: cout << "EMPTY EXPRESSION" << endl; break;
        }
    }
    catch (...) {
        cout << "UNKNOWN ERROR" << endl;
    }

    return 0;
}
