#include <String>
#include <iostream>
#include "Binary.h"
#include "Stack.h"
#include "Calculator.h"

using namespace std;


int Calculator::countSpaces(string input) {
    int numberOfSpaces(0);
    for (int i = 0; i < input.length(); i++)
        if (input[i] == ' ') numberOfSpaces += 1;
    return numberOfSpaces;
}

bool Calculator::isInputNotNull(string input) {
    return !input.length() != 0;
}

bool Calculator::isInputFirstCharacterCorrect(string input) {
    return ((((input[0] == '*') || ((input[0] == '-') && (!isdigit(input[1]))) || (input[0] == '+') ||
              (input[0] == ' '))));
}

bool Calculator::isCharacterBeforeAfterOperatorCorrect(string input) {
    bool isCorrect = true;
    for (int i = 1; i < input.length() - 1; i++)
        if (((input[i] == '+') | (input[i] == '*') | ((input[0] == '-') && (!isdigit(input[1])))) &
            ((input[i - 1] != ' ') && (input[i + 1] != ' '))) {
            isCorrect = false;
            throw 10;
        }
    return isCorrect;
};

bool Calculator::isNumberOfOperandsOperatorsCorrect(string input) {
    int operators(0), wrongMinuses(0);
    bool isCorrect = true;

    for (int i = 0; i < input.length(); i++)
        if ((i != (input.length() - 1)) && (input[i] == '-') && (isdigit(input[i + 1])))
            wrongMinuses += 1;
        else if ((((isdigit(input[i]) == false) && (input[i] != ' ') &
                                                   (!((input[i] == '*') || (input[i] == '-') || (input[i] == '+'))))) |
                 ((i == input.length() - 1) && (input[i] != '+') && (input[i] != '*') && (input[i] != '-')))
            throw 10;

    for (int i = 0; i < input.length(); i++) {
        if ((input[i] == '*') || (input[i] == '-') || (input[i] == '+')) operators += 1;
        if (isdigit(input[i]))
            for (int j = i; j < input.length(); j++)
                if ((!(isdigit(input[j]))) && (input[j] != ' ')) {
                    isCorrect = false;
                    throw 10;
                } else if ((!(isdigit(input[j]))) && (input[j] == ' '))
                    break;
    }

    operators -= wrongMinuses;
    if (operators != (countSpaces(input) / 2)) throw 10;

    bool operatorsDetected(false), valuesDetected(false);
    for (int i = 0; i < input.length(); i++)
        if (isdigit(input[i])) valuesDetected = true;
    if (operators != 0) operatorsDetected = true;
    if ((valuesDetected == false) || (operatorsDetected == false)) throw 10;
}

void Calculator::checkInput(string input) {
    if (isInputNotNull(input))
        throw 10;

    if (isInputFirstCharacterCorrect(input))
        throw 10;

    isCharacterBeforeAfterOperatorCorrect(input);

    isNumberOfOperandsOperatorsCorrect(input);
}


void Calculator::calculateOperation(Stack<Binary> &values, string input, int i, Binary n, Binary n2) {
    n2 = values.pop();
    n = values.pop();

    switch (input[i]) {
        case '+':
            n.add(n2, true);
            break;

        case '-':
            n.subtract(n2);
            break;

        case '*':
            n.multiply(n2);
            break;
    }
    values.push(n);
}

Binary Calculator::calculate(Stack<Binary> &values, string input, bool permit) {
    Binary temp = Binary(0);
    Binary n(Binary(0)), n2(Binary(0));

    for (int i = 0; i < input.length() - 1; i++) {
        if ((isdigit(input[i])) | ((input[i] == '-') && (isdigit(input[i + 1])))) {
            for (int j = i; j < input.length() - 1; j++)
                if (input[j] == ' ') {
                    temp = Binary(stoi(input.substr(i, (j - i))));
                    if (!permit) break;
                    values.push(temp);
                    i = j - 1;
                    break;
                }
        } else if (((input[i] == '*') || ((input[i] == '-') && (!isdigit(input[i + 1]))) || (input[i] == '+')) &&
                   permit)
            calculateOperation(values, input, i, n, n2);
    }
    calculateOperation(values, input, input.length() - 1, n, n2);
    return values.pop();
}

void Calculator::printBinary(Stack<Binary> &values, string input) {
    cout << "\nRPN in binary: \n";
    Binary temp = Binary(0);

    for (int i = 0; i < input.length(); i++) {
        if ((isdigit(input[i])) | ((input[i] == '-') && (isdigit(input[i + 1])))) {
            for (int j = i; j < input.length() - 1; j++)
                if (input[j] == ' ') {
                    temp = Binary(stoi(input.substr(i, (j - i))));
                    temp.print();
                    i = j - 1;
                    break;
                }
        } else if ((input[i] == '*') || ((input[i] == '-') && (!isdigit(input[i + 1]))) || (input[i] == '+'))
            cout << input[i] << ' ';
    }
}

