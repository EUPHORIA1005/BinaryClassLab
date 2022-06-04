#ifndef ALGOLAB_STACK_H
#define ALGOLAB_STACK_H


template<typename T>
class Stack {
public:

    struct Node {
        T data;
        struct Node *next;
    };
    struct Node *top;

    void push(T value);

    T pop();

    T peek();

    bool isEmpty();

    void clear();

};

#endif
