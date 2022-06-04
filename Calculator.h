#ifndef ALGOLAB_CALCULATOR_H
#define ALGOLAB_CALCULATOR_H

#include "Binary.h"
#include <string>
#include "Stack.h"

using namespace std;

class Calculator {
private:
    int countSpaces(string input);

    bool isInputNotNull(string input);

    bool isInputFirstCharacterCorrect(string input);

    bool isNumberOfOperandsOperatorsCorrect(string input);

    bool isCharacterBeforeAfterOperatorCorrect(string input);

    void calculateOperation(Stack<Binary> &values, string input, int i, Binary n, Binary n2);

public:
    void checkInput(string input);

    Binary calculate(Stack<Binary> &values, string input, bool permit);

    void printBinary(Stack<Binary> &values, string input);
};

#endif //ALGOLAB_CALCULATOR_H
