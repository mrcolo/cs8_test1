//
// Created by Arman Mansourian on 10/10/18.
//
#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <fstream>

enum STACK_ERRORS {SFULL, SEMPTY, SBAD_SIZE};

template<typename T>
class Stack {
public:
    explicit Stack(int c = 69);
    ~Stack();
    Stack(const Stack<T> &other);
    Stack<T>& operator=(const Stack<T> &other);

    bool full() const;
    bool empty() const;
    int getSize() const;
    int getCapacity() const;
    int roomLeft() const;
    void resize(int s);
    void push(const T &data);
    T pop();
    T peek();
    T& operator[](int index) const;
    Stack<T>& operator<<(const T &data);
    Stack<T>& operator>>(T &data);

    template<typename U>
    friend std::ostream& operator<<(std::ostream &out, const Stack<U> &stk);
    template<typename U>
    friend std::istream& operator>>(std::istream & in, Stack<U> &stk);

private:
    T* stack;
    int mySize{}, myCapacity{};

    void nuke();
    void copy(const Stack<T> &other);
};

template<typename T>
Stack<T>::Stack(int c) {
    if (c < 1)
        throw SBAD_SIZE;
    stack = new T[myCapacity = c];
    for (int i = 0; i < c; ++i)
        stack[i] = T();
    mySize = 0;
}

template<typename T>
Stack<T>::~Stack() {
    nuke();
}

template<typename T>
Stack<T>::Stack(const Stack<T> &other) {
    copy(other);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T> &other) {
    if (this != &other) {
        nuke();
        copy(other);
    }
    return *this;
}

template<typename T>
bool Stack<T>::full() const {
    return mySize == myCapacity;
}

template<typename T>
bool Stack<T>::empty() const {
    return mySize == 0;
}

template<typename T>
int Stack<T>::getSize() const {
    return mySize;
}

template<typename T>
int Stack<T>::getCapacity() const {
    return myCapacity;
}

template<typename T>
int Stack<T>::roomLeft() const {
    return myCapacity - mySize;
}

template<typename T>
void Stack<T>::resize(int s) {
    if (s < 1) {
        throw SBAD_SIZE;
    } else if (s < myCapacity) {
        T *tempStack;
        tempStack = new T[s];
        for (int i = 0; i < s; ++i)
            tempStack[i] = stack[i];
        myCapacity = s;
        delete [] stack;
        stack = tempStack;
        if (mySize > s)
            mySize = s;
    } else if (s > myCapacity) {
        T *tempStack;
        tempStack = new T[s];
        for (int i = 0; i < mySize; ++i)
            tempStack[i] = stack[i];
        for (int j = mySize; j < s; ++j)
            tempStack[j] = T();
        myCapacity = s;
        delete [] stack;
        stack = tempStack;
    }
}

template<typename T>
void Stack<T>::push(const T &data) {
    if(full())
        throw SFULL;
    stack[mySize] = data;
    ++mySize;
}

template<typename T>
T Stack<T>::pop() {
    if(empty())
        throw SEMPTY;
    T data = stack[mySize - 1];
    stack[mySize - 1] = T();
    --mySize;
    return data;
}

template<typename T>
T Stack<T>::peek() {
    if(empty())
        throw SEMPTY;
    return stack[mySize - 1];
}

template<typename T>
T& Stack<T>::operator[](int index) const {
    if (index >= myCapacity)
        throw SBAD_SIZE;
    return *(stack + index);
}

template<typename T>
Stack<T>& Stack<T>::operator<<(const T &data) {
    push(data);
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator>>(T &data) {
    data = pop();
    return *this;
}

template<typename T>
void Stack<T>::nuke() {
    for (int i = 0; i < myCapacity; ++i)
        stack[i] = T();
    delete [] stack;
    stack = nullptr;
    mySize = myCapacity = 0;
}

template<typename T>
void Stack<T>::copy(const Stack<T> &other) {
    if (other.empty())
        return;
    mySize = other.mySize;
    myCapacity = other.myCapacity;
    stack = new T[myCapacity];
    for (int i =  0; i < myCapacity; ++i)
        stack[i] = other.stack[i];
}

template<typename U>
std::ostream& operator<<(std::ostream &out, const Stack<U> &stk) {
    if (&out != &std::cout) {
        out << "Stack Size: " << stk.mySize << std::endl
            << "Stack Capacity: " << stk.myCapacity << std::endl;
    }
    for (int i = stk.mySize - 1; i >= 0; --i)
        out << stk[i] << ' ';
    return out;
}

template<typename U>
std::istream& operator>>(std::istream & in, Stack<U> &stk) {
    std::string line;
    U data;
    stk.nuke();
    if (&in == &std::cin) {
        std::cout << "Stack Capacity: ";
        in >> stk.myCapacity;
        stk.stack = new U[stk.myCapacity];
        std::cout << std::endl << "Enter data, ending with a ctrl D:\n" << std::endl;
        while ((in >> data) && !stk.full())
            stk << data;
    } else {
        Stack<U> temp;
        getline(in, line, ':');
        in >> stk.mySize;
        getline(in, line, ':');
        in >> stk.myCapacity;
        stk.stack = new U[stk.myCapacity];
        while (in >> data)
            temp << data;
        while (!temp.empty())
            stk << temp.pop();
    }
    return in;
}

#endif //STACK_H
