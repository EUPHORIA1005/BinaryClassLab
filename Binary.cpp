#include <iostream>
#include "Binary.h"

using namespace std;

long long Binary::power(int base, int exp) {
    long long result(1);

    for (int i = 0; i < exp; i++)
        result = result * base;
    return result;
}


Binary::Binary(int decimalNumber) {
    if (decimalNumber >= power(2, size - 1) || decimalNumber < -power(2, size - 1))
        throw 20;

    if (!(decimalNumber >= power(2, size - 1) || decimalNumber <= -power(2, size - 1))) {
        int shift(0);

        if (decimalNumber < 0) {
            for (int i = size - 1; i >= 0; i--) {
                shift = -decimalNumber >> i;
                if (shift & 1) binary[i] = 0; else binary[i] = 1;
            }
            for (int i = 0; i < size / 2; i++)
                swap(binary[i], binary[size - 1 - i]);
            add(Binary(1), true);
        } else {
            for (int i = size - 1; i >= 0; i--) {
                shift = decimalNumber >> i;
                if (shift & 1) binary[i] = 1; else binary[i] = 0;
            }
            for (int i = 0; i < size / 2; i++)
                swap(binary[i], binary[size - 1 - i]);
        }
    }

    if (decimalNumber == -power(2, size - 1)) {
        binary[0] = 1;
        for (int i = 1; i < size; i++)
            binary[i] = 0;
    }
}

bool Binary::isHigherThanLowerBorder() {
    if (binary[0] != 1)
        return false;

    for (int i = 1; i < size; i++)
        if (binary[i] != 0)
            return false;
    return true;
}

void Binary::reverse() {
    if (binary[0] == 1) {
        add(Binary(-1), true);

        for (int i = 0; i < size; i++)
            if (binary[i] == 1) binary[i] = 0; else binary[i] = 1;
    } else {
        for (int i = 0; i < size; i++)
            if (binary[i] == 1) binary[i] = 0; else binary[i] = 1;

        add(Binary(1), true);
    }
}

int Binary::getSize() {
    return size;
}

void Binary::subtract(Binary n) {
    n.reverse();
    add(n, 1);
}

void Binary::add(Binary n, bool isNotForMultiplication) {
    int signFirst = binary[0];
    int signSecond = n.binary[0];
    int carry(0), d1(0), d2(0), sum(0);

    for (int i = size - 1; i >= 0; i--) {
        d1 = binary[i];
        d2 = n.binary[i];
        sum = d1 + d2 + carry;
        if (sum == 0) binary[i] = 0;
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
    if (((isNotForMultiplication) && signFirst == 0 && signSecond == 0 && binary[0] == 1) ||
        ((isNotForMultiplication) && signFirst == 1 && signSecond == 1 && binary[0] == 0))
        throw 100;
}

void Binary::multiply(Binary n) {
    if (isHigherThanLowerBorder()) {
        for (int i = 0; i < size - 1; i++)
            if (n.binary[i] != 0)
                throw 100;

        if (n.binary[size - 1] == 0)
            binary[0] = 0;

    } else if (n.isHigherThanLowerBorder()) {
        for (int i = 0; i < size - 1; i++)
            if (binary[i] != 0)
                throw 100;

        if (binary[size - 1] == 0)
            n.binary[0] = 0;

    } else {
        bool negative(false), isOverflow(false);

        if (binary[0] == 1) {
            reverse();
            negative = !negative;
        }
        if (n.binary[0] == 1) {
            n.reverse();
            negative = !negative;
        }
        int *secondBinary = new int[size];

        for (int i = 0; i < size; i++) {
            secondBinary[i] = binary[i];
            binary[i] = 0;
        }
        for (int i = size - 1; i >= 0; i--) {

            if (secondBinary[i] == 1) {
                if (isOverflow)
                    throw 100;
                else add(n, false);
            }

            for (int i = 0; i < size; i++)
                swap(n.binary[i], n.binary[i + 1]);

            if (n.binary[0] == 1)
                isOverflow = true;
        }
        if (binary[0] == 1)
            throw 100;
    }
}

void Binary::print() {
    for (int i = 0; i < getSize(); i++)
        cout << binary[i];
    cout << endl;
}

int Binary::getDecimal() {
    int result(0);
    int *secondBinary = new int[size];

    for (int i = 0; i < size; i++)
        secondBinary[i] = binary[i];
    if (secondBinary[0] == 1) {
        for (int i = 0; i < size; i++)
            if (secondBinary[i] == 1)
                secondBinary[i] = 0;
            else
                secondBinary[i] = 1;

        for (int i = 0; i < size; i++)
            result = result + secondBinary[i] * power(2, (size - i - 1));

        result = (result + 1) * (-1);
    } else
        for (int i = 0; i < size; i++)
            result = result + secondBinary[i] * power(2, (size - i - 1));

    delete[] secondBinary;
    return result;
}


void performInput(int &decimalNumber1, char &operand, int &decimalNumber2) {
    cout << "Enter the expression: ";
    do {
        if (!(cin >> decimalNumber1 >> operand >> decimalNumber2)) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid performInput. Try again." << endl;
        } else if (operand != '+' && operand != '-' && operand != '*') {
            cout << "Please enter '+', '-' or '*'. \n";
            cin.clear();
        } else
            break;
    } while (true);
}