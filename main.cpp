#include <iostream>
#include "Binary.h"
#include "Calculator.h"
using namespace std;

int main() {
    bool permit;
    string input;
    Stack<Binary> values;
    Binary result(Binary(0));
    do
    {
        cout << "Enter the expression: ";
        getline(cin, input);
        try
        {
            checkInput(input);
            permit = true;
            if (permit)
            {
                result = calculate(values, input, permit);
                permit = true;
            }
        }
        catch (int excType)
        {
            switch (excType)
            {
                case 10:
                {
                    cout << "\nInvalid input.\n" << endl;
                    break;
                }
                case 20:
                {
                    cout << "\nOverflow of the input value.\n" << endl;
                    break;
                }
                case 100:
                {
                    cout << "\nThe calculated value is too large.\n" << endl;
                    break;
                }
            }
            permit = false;
            if (!(values.isEmpty())) values.clear();
        }
    } while (!permit);
    printBinary(values, input);
    cout << "\n\nThe result is: " << result.getDecimal() << endl;
    cout << "The result in binary is: ";
    result.print(); cout << endl;
}