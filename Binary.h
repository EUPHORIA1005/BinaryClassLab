#ifndef ALGOLAB_BINARY_H
#define ALGOLAB_BINARY_H


void performInput(int &dec1, char &operand, int &dec2);

class Binary {
private:

    static const int size = 8;

    long long power(int base, int exp);

    bool isHigherThanLowerBorder();

    void reverse();


public:

    int *binary = new int[size];

    Binary(int dec);

    int getSize();

    void subtract(Binary n);

    void add(Binary n, bool isNotForMultiplication);

    void multiply(Binary n);

    void print();

    int getDecimal();
};

#endif //ALGOLAB_BINARY_H
