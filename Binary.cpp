#include <iostream>
#include "Binary.h"

using namespace std;

long long power(int base, int exp) {
    long long result(1);
    for (int i = 0; i < exp; i++)
        result = result * base;
    return result;
}


Binary::Binary(int dec) {
    if (!(dec >= -power(2, size - 1) && dec <= power(2, size - 1) - 1)) throw "\nOverflow";
    else{

    //if (dec >= -power(2, size - 1) && dec <= power(2, size - 1) - 1) {
        int shifted(0);
        if (dec < 0) {
            for (int i = size - 1; i >= 0; i--) {
                shifted = -dec >> i;
                if (shifted & 1)
                    binary[i] = 0;
                else
                    binary[i] = 1;
            }
            for (int i = 0; i < size / 2; i++)
                swap(binary[i], binary[size - 1 - i]);

            addition(Binary(1));
        } else {
            for (int i = size - 2; i >= 0; i--) {
                shifted = dec >> i;
                if (shifted & 1) binary[i] = 1; else binary[i] = 0;
            }
            for (int i = 0; i < size / 2; i++)
                swap(binary[i], binary[size - 1 - i]);
        }
    }
}

void Binary::reverse() {
    if (binary[0] == 1) {
        addition(Binary(-1));
        for (int i = 0; i < size; i++)
            if (binary[i] == 1)
                binary[i] = 0;
            else
                binary[i] = 1;
    } else {
        for (int i = 0; i < size; i++)
            if (binary[i] == 1)
                binary[i] = 0;
            else
                binary[i] = 1;
        addition(Binary(1));
    }
}

int Binary::getSize() {
    return size;
}

void Binary::subtraction(Binary n) {
    n.reverse();
    addition(n);
}

void Binary::addition(Binary n) {
    int signFirst = binary[0];
    int signSecond = n.binary[0];
    int carry(0), d1(0), d2(0), sum(0);

    for (int i = size - 1; i >= 0; i--) {
        d1 = binary[i];
        d2 = n.binary[i];
        sum = d1 + d2 + carry;
        if (sum == 0)
            binary[i] = 0;
        else if (sum == 1) {
            binary[i] = 1;
            carry = 0;
        } else if (sum == 2) {
            binary[i] = 0;
            carry = 1;
        } else if (sum == 3) {
            binary[i] = 1;
            carry = 1;
        }
    }
    if ((signFirst == 0 && signSecond == 0 && binary[0] == 1) ||
        ( signFirst == 1 && signSecond == 1 && binary[0] == 0))
        throw "\nOverflow!";
}

void Binary::multiplication(Binary n) {
    bool negative(false), overflow(false);
    if (binary[0] == 1) {
        reverse();
        negative = !negative;
    }
    if (n.binary[0] == 1) {
        n.reverse();
        negative = !negative;
    }
    int *sndBinary = new int[size];
    for (int i = 0; i < size; i++) {
        sndBinary[i] = binary[i];
        binary[i] = 0;
    }
    for (int i = size - 1; i >= 0; i--) {
        if (sndBinary[i] == 1) {
            if (overflow) throw "\nOverflow!";
            else addition(n);
        }
        for (int i = 0; i < size; i++)
            swap(n.binary[i], n.binary[i + 1]);
        if (n.binary[0] == 1) overflow = true;
    }
    if (binary[0] == 1) throw "\nOverflow!";
    if (negative) {
        int temp(1);
        for (int i = 0; i < size; i++)
            if (binary[i] == 1) binary[i] = 0; else binary[i] = 1;
        for (int i = size - 1; i >= 0; i--) {
            if (binary[i] == 1 && temp == 1) binary[i] = 0;
            else if (binary[i] == 0 && temp == 1) {
                binary[i] = 1;
                temp = 0;
            } else
                binary[i] = binary[i];
        }
    }
}

void Binary::printer() {
    for (int i = 0; i < getSize(); i++)
        cout << binary[i] <<endl;
    cout << endl;
}

int Binary::getDecimal() {
    int result(0);
    if (binary[0] == 1) {
        for (int i = 0; i < size; i++)
            if (binary[i] == 1) binary[i] = 0; else binary[i] = 1;
        for (int i = 0; i < size; i++)
            result = result + binary[i] * power(2, (size - i - 1));
        result = (result + 1) * (-1);
    } else
        for (int i = 0; i < size; i++)
            result = result + binary[i] * power(2, (size - i - 1));
    return result;
}


void input(int &dec1, char &operand, int &dec2) {
    cout << "Enter the expression: ";
    do {
        if (!(cin >> dec1 >> operand >> dec2)) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Try again." << endl;
        } else if (operand != '+' && operand != '-' && operand != '*') {
            cout << "Please enter '+', '-' or '*'. \n";
            cin.clear();
        } else
            break;
    } while (true);
}