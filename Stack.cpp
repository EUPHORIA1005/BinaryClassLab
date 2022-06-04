#include <string>
#include "Binary.h"
#include "Stack.h"

using namespace std;

template<typename T>
void Stack<T>::push(T value) {
    struct Node *newnode = (struct Node *) malloc(sizeof(struct Node));
    newnode->data = value;
    newnode->next = top;
    top = newnode;
}

template<typename T>
T Stack<T>::pop() {
    if (top == NULL) throw 10;
    else {
        T temp = T(0);
        temp = top->data;
        top = top->next;
        return temp;
    }
}

template<typename T>
T Stack<T>::peek() {
    if (top == NULL)
        throw 10;
    return top->data;
}

template<typename T>
bool Stack<T>::isEmpty() {
    bool result;
    return top == NULL;
}

template<typename T>
void Stack<T>::clear() {
    T out = T(0);
    do {
        out = pop();
    } while (!isEmpty());
}

template
class Stack<Binary>;