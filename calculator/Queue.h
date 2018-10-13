//
// Created by Arman Mansourian on 10/10/18.
//
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <fstream>

enum QUEUE_ERRORS {QFULL, QEMPTY, QBAD_SIZE};

template<typename T>
class Queue {
public:
    explicit Queue(int c = 69);
    ~Queue();
    Queue(const Queue<T> &other);
    Queue<T>& operator=(const Queue<T> &other);

    bool full() const;
    bool empty() const;
    int getSize() const;
    int getCapacity() const;
    void clear();
    void resize(int s = 10);
    void enqueue(const T &data);
    T dequeue();
    T peek();
    T& operator[](int index) const;
    Queue<T>& operator<<(const T &data);
    Queue<T>& operator>>(T &data);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, const Queue<U> &q);
    template<typename U>
    friend std::istream& operator>>(std::istream& in, Queue<U> &q);

private:
    T* que;
    int head{}, tail{}, mySize{}, myCapacity{};

    void nuke();
    void copy(const Queue<T> &other);
};

template<typename T>
Queue<T>::Queue(int c) {
    if (c + 1 < 3)
        throw QBAD_SIZE;
    que = new T[(myCapacity = c) + 1];
    mySize = head = tail = 0;
}

template<typename T>
Queue<T>::~Queue() {
    nuke();
    head = tail = mySize = myCapacity = 0;
}

template<typename T>
Queue<T>::Queue(const Queue<T> &other) {
    copy(other);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T> &other) {
    if (this != &other) {
        nuke();
        copy(other);
    }
    return *this;
}

template<typename T>
bool Queue<T>::full() const {
    return mySize == myCapacity;
}

template<typename T>
bool Queue<T>::empty() const {
    return mySize == 0;
}

template<typename T>
int Queue<T>::getSize() const {
    return mySize;
}

template<typename T>
int Queue<T>::getCapacity() const {
    return myCapacity;
}

template<typename T>
void Queue<T>::clear() {
    head = tail = mySize = 0;
}

template<typename T>
void Queue<T>::resize(int s) {
    int j = 0;
    auto temp = new T[s + 1];
    if (s >= myCapacity) {
        for (int i = head; j < mySize; i = (i + 1) % (myCapacity + 1), ++j) {
            temp[j] = que[i];
            que[i] = T();
        }
        delete [] que;
        que = temp;
        tail = mySize;
        head = 0;
        myCapacity = s;
    } else {
        for (int i = head; (j < s) || (j < mySize); i = (i + 1) % (myCapacity + 1), ++j)
            temp[j] = que[i];
        for (int k = 0; k < myCapacity + 1; ++k)
            que[k] = T();
        delete [] que;
        que = temp;
        (mySize < s) ? tail = mySize : tail = mySize = s;
        head = 0;
        myCapacity = s;
    }
}

template<typename T>
void Queue<T>::enqueue(const T &data) {
    if (full())
        throw QFULL;
    que[tail] = data;
    tail = (tail + 1) % (myCapacity + 1);
    ++mySize;
}

template<typename T>
T Queue<T>::dequeue() {
    if (empty())
        throw QEMPTY;
    T data = que[head];
    head = (head + 1) % (myCapacity + 1);
    --mySize;
    return data;
}

template<typename T>
T Queue<T>::peek() {
    if(empty())
        throw QEMPTY;
    return que[mySize - 1];
}

template<typename T>
T& Queue<T>::operator[](int index) const {
    if (index >= myCapacity)
        throw QBAD_SIZE;
    return *(que + index);
}

template<typename T>
Queue<T>& Queue<T>::operator<<(const T &data) {
    enqueue(data);
    return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator>>(T &data) {
    data = dequeue();
    return *this;
}

template<typename T>
void Queue<T>::nuke() {
    for (int i = 0; i < myCapacity + 1; ++i)
        que[i] = T();
    delete [] que;
    que = nullptr;
}

template<typename T>
void Queue<T>::copy(const Queue<T> &other) {
    if (other.empty())
        return;
    head = other.head;
    tail = other.tail;
    mySize = other.mySize;
    myCapacity = other.myCapacity;
    que = new T[myCapacity + 1];
    for (int i =  0; i < myCapacity + 1; ++i)
        que[i] = other.que[i];
}

template<typename U>
std::ostream& operator<<(std::ostream& out, const Queue<U> &q) {
    if (&out != &std::cout) {
        out << "Queue size: " << q.mySize << std::endl
            << "Queue myCapacity: " << q.myCapacity << std::endl;
    }
    for (int i = 0; i < q.mySize; ++i)
        out << q[i] << ' ';
    return out;
}

template<typename U>
std::istream& operator>>(std::istream& in, Queue<U> &q) {
    std::string line;
    U data;
    q.nuke();
    if (&in == &std::cin) {
        std::cout << "Queue size: ";
        in >> q.myCapacity;
        q.que = new U[q.myCapacity + 1];
        std::cout << std::endl << "Enter data, ending with a ctrl D:\n" << std::endl;
        while ((in >> data) && !q.full())
            q << data;
    } else {
        int tempSize;
        getline(in, line, ':');
        in >> tempSize;
        getline(in, line, ':');
        in >> q.myCapacity;
        q.que = new U[q.myCapacity + 1];
        while (in >> data)
            q << data;
    }
    return in;
}

#endif //QUEUE_H