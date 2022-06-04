#include <iostream>
#include "Binary.h"
#include "Calculator.h"
#include "Stack.h"

using namespace std;

int main() {
    bool permit;
    string input;
    Stack<Binary> values;
    Calculator calculator;
    Binary result(Binary(0));
    do {
        cout << "Enter the expression: ";
        getline(cin, input);
        try {
            calculator.checkInput(input);
            permit = true;
            if (permit) {
                result = calculator.calculate(values, input, permit);
                permit = true;
            }
        }
        catch (int exception) {
            switch (exception) {
                case 10: {
                    cout << "Invalid input." << endl;
                    break;
                }
                case 20: {
                    cout << "Overflow of the input value." << endl;
                    break;
                }
                case 100: {
                    cout << "The calculated value is too large." << endl;
                    break;
                }
            }
            permit = false;
            if (!(values.isEmpty())) values.clear();
        }
    } while (!permit);
    calculator.printBinary(values, input);
    cout << "\n\nThe result is: " << result.getDecimal() << endl;
    cout << "The result in binary is: ";
    result.print();
    cout << endl;

//Lab binary #1

/*
int num1, num2;
    bool permit(false);
    char operand;
    Binary n1 = Binary(0);
    Binary n2 = Binary(0);
    cout << "Current bitset is " << n1.getSize() << " bit.\n" << endl;
    do {
        try {
            performInput(num1, operand, num2);
            n1 = Binary(num1), n2 = Binary(num2);
            permit = true;
        }
        catch (const char *msg) {
            cout << "\nOverflow of the given number. Please, try inputting again.\n" << endl;
        }
    } while (!permit);

    cout << "\nFirst number in binary: ";
    n1.print();
    cout << "Second number in binary: ";
    n2.print();
    cout << endl;

    try {
        switch (operand) {
            case '+':
                n1.add(n2, true);
                break;

            case '-':
                n1.subtract(n2);
                break;

            case '*':
                n1.multiply(n2);
                break;
        }
        cout << "The result in binary: ";
        n1.print();
        cout << "The result in decimal: ";
        cout << n1.getDecimal() << endl;
    }
    catch (const char *msg) {
        cout << "OVERFLOW: the calculated value is too large." << endl;
    }*/
}