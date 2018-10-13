#include <iostream>
#include "Calculator.h"
#include "Parser.h"
using namespace std;

int main() {
    try{
        Calculator c;
        Parser pars;

        c.addVar("a = 2x^2 + 2");
        cout<<"ADDING VALUE A "<<endl;
        cout<<c.getVars();

        c.deleteVar('a');
        cout<<"AFTER DELETION: "<<endl;
        cout<<c.getVars();

        cout<<"TRYING TO EXPORT"<<endl;
        cout<<c.exportSession();

        string import = "ADDV a = 2x^2 + 2\nDELV a";
        c.importSession(import);

        string exp = "((-3) / 3) + 5 * (8 - (-3))";
        pars.tokenize(exp);
        pars.infixToPostfix();
        double d = pars.evaluatePostfix();
        cout << d;
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
