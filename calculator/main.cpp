#include <iostream>
#include <fstream>
#include "Parser.h"
#include "Queue.h"
#include "Stack.h"
using namespace std;

int main() {
    Parser test;
    string exp("12 + 8 / (2)");
    try {
        test.tokenize(exp);
        test.infixToPostfix();
        double answer = test.evaluatePostfix();
        cout << answer;
    } catch (EXPRESSION_ERRORS e) {
        switch (e) {
            case BAD_EXP: cout << "BAD EXPRESSION" << endl; break;
            case EMPTY_EXP: cout << "EMPTY EXPRESSION" << endl; break;
        }
    } catch (STACK_ERRORS e) {
        switch (e) {
            case SFULL: cout << "STACK FULL" << endl; break;
            case SEMPTY: cout << "STACK EMPTY" << endl; break;
            case SBAD_SIZE: cout << "STACK BAD SIZE" << endl; break;
        }
    } catch (QUEUE_ERRORS e) {
        switch (e) {
            case QFULL: cout << "QUEUE FULL" << endl; break;
            case QEMPTY: cout << "QUEUE EMPTY" << endl; break;
            case QBAD_SIZE: cout << "QUEUE BAD SIZE" << endl; break;
        }
    } catch (...) {
        cout << "UNKNOWN ERROR" << endl;
    }
    return 0;
}