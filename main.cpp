#include <iostream>
#include "Binary.h"
using namespace std;

int main() {
    /*int num1, num2;
    bool permit(false);
    char operand;
    Binary n1 = Binary(0);
    Binary n2 = Binary(0);
    cout << "Current bitset is " << n1.getSize() << " bit.\n" << endl;
    do {
        try {
            input(num1, operand, num2);
            n1 = Binary(num1), n2 = Binary(num2);
            permit = true;
        }
        catch (const char *msg) {
            cout << "\nOverflow of the given number. Please, try inputting once again.\n" << endl;
        }
    } while (!permit);*/

    Binary n1(-128);
    Binary n2(127);
    char operand('+');
    cout << "\nFirst number in binary: ";
    n1.printer();
    cout << "Second number in binary: ";
    n2.printer();
    cout << endl;

    try {
        switch (operand) {
            case '+':
                n1.addition(n2);
                break;

            case '-':
                n1.subtraction(n2);
                break;

            case '*':
                n1.multiplication(n2);
                break;
        }
        cout << "The result in binary: ";
        n1.printer();
        cout << "The result in decimal: ";
        cout << n1.getDecimal() << endl;
    }
    catch (const char *msg) {
        cout << "OVERFLOW: the calculated value is too large." << endl;
    }
}