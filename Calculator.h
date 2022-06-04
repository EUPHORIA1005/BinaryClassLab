#ifndef ALGOLAB_CALCULATOR_H
#define ALGOLAB_CALCULATOR_H
#include "Binary.h"
#include <String>

using namespace std;

void checkInput(string input);
int countSpaces(string input);

template <typename T>
class Stack
{
public:

    struct Node;

    struct Node* top;

    void push(T value);

    T pop();

    void clear();

    bool isEmpty();
};

void isOperator(Stack<Binary>& values, string input, int i, Binary n, Binary n2);
Binary calculate(Stack<Binary>& values, string input, bool permit);
void printBinary(Stack<Binary>& values, string input);

template class Stack<Binary>;

#endif //ALGOLAB_CALCULATOR_H
