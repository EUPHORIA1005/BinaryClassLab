#include <String>
#include <iostream>
#include "Binary.h"


using namespace std;

int countSpaces(string input) {
    int spaces(0);
    for (int i = 0; i < input.length(); i++)
        if (input[i] == ' ') spaces += 1;
    return spaces;
}

void checkInput(string input) {
    int operators(0), wrongMinuses(0);

    // The first character in the string is a space or an operator (wrong RPN case)
    if (((input[0] == '*') || ((input[0] == '-') & (!isdigit(input[1]))) || (input[0] == '+') ||
         (input[0] == ' ')))
        throw 10;

    for (int i = 0; i < input.length(); i++)
        // counting minuses that are not operators 
        if ((i != (input.length() - 1)) && (input[i] == '-') && (isdigit(input[i + 1])))
            wrongMinuses += 1;
        else if (// The character is not a space, an operator or a decimal digit
                (((isdigit(input[i]) == false) & (input[i] != ' ') &
                  (!((input[i] == '*') || (input[i] == '-') || (input[i] == '+'))))) |
                // whether the last character is not an operator
                ((i == input.length() - 1) & (input[i] != '+') & (input[i] != '*') & (input[i] != '-')))
            throw 10;


    // The character preceding or following the operator is not a space
    for (int i = 1; i < input.length() - 1; i++)
        if (((input[i] == '+') | (input[i] == '*') | ((input[0] == '-') & (!isdigit(input[1])))) &
            ((input[i - 1] != ' ') & (input[i + 1] != ' ')))
            throw 10;

    for (int i = 0; i < input.length(); i++) {
        // counting operators, including wrongMinuses
        if ((input[i] == '*') || (input[i] == '-') || (input[i] == '+')) operators += 1;
        // The character following a value is not a space
        if (isdigit(input[i]))
            for (int j = i; j < input.length(); j++)
                if ((!(isdigit(input[j]))) & (input[j] != ' ')) throw 10;
                else if ((!(isdigit(input[j]))) & (input[j] == ' ')) break;
    }
    // counting operators, excluding wrongMinuses
    operators -= wrongMinuses;
    // The counted number of operators is equal to a half of spaces in the performInput string
    if (operators != (countSpaces(input) / 2)) throw 10;
    // The performInput string contains no operators or no values at all
    bool operatorsDetected(false), valuesDetected(false);
    for (int i = 0; i < input.length(); i++)
        if (isdigit(input[i])) valuesDetected = true;
    if (operators != 0) operatorsDetected = true;
    if ((valuesDetected == false) || (operatorsDetected == false)) throw 10;
}

template<typename T>
class Stack {
public:

    struct Node {
        T data;
        struct Node *next;
    };

    struct Node *top = NULL;

    void push(T value) {
        struct Node *newnode = (struct Node *) malloc(sizeof(struct Node));
        newnode->data = value;
        newnode->next = top;
        top = newnode;
    }

    T pop() {
        if (top == NULL) throw 10;
        else {
            T temp = T(0);
            temp = top->data;
            top = top->next;
            return temp;
        }
    }

    bool isEmpty() {
        bool result;
        return top == NULL;
    }

    void clear() {
        T out = T(0);
        do {
            out = pop();
        } while (!isEmpty());
    }
};

void isOperator(Stack<Binary> &values, string input, int i, Binary n, Binary n2) {
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

Binary calculate(Stack<Binary> &values, string input, bool permit) {
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
        } else if (((input[i] == '*') || ((input[i] == '-') && (!isdigit(input[i + 1]))) || (input[i] == '+')) & permit)
            isOperator(values, input, i, n, n2);
    }
    isOperator(values, input, input.length() - 1, n, n2);
    return values.pop();
}

void printBinary(Stack<Binary> &values, string input) {
    cout << "\nThe expression in binary is: \n";
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

template
class Stack<Binary>;