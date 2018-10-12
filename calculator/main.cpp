#include <iostream>
#include <fstream>
#include "Parser.h"
#include "Queue.h"
#include "Stack.h"
using namespace std;

int main() {
    // running tests on stack and queue classes
    Stack<char> operators(7);
    Stack<double> operands(20);
    Queue<char> q_ops(7);
    Queue<double> q_nums(20);

    try {
        // running tests on stack and queue classes
        q_ops << '+' << '-' << '*' << '/' << '^' << '(' << ')';
        q_nums << 2 << 3.14 << 7.5 << 1.0 / 3;
        cout << q_ops << endl;
        cout << q_nums << endl;

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