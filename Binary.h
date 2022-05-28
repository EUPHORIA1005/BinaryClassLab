//
// Created by Дмитрий on 5/27/2022.
//

#ifndef ALGOLAB_BINARY_H
#define ALGOLAB_BINARY_H

long long power(int base, int exp);
void input(int &dec1, char &operand, int &dec2);

class Binary{
private:
    static const int size = 8;
    int *binary = new int[size];
public:
    Binary(int dec);
    void reverse();
    int getSize();
    void subtraction(Binary n);
    void addition(Binary n);
    void multiplication(Binary n);
    void printer();
    int getDecimal();
    void input(int &dec1, char &operand, int &dec2);
};

#endif //ALGOLAB_BINARY_H
