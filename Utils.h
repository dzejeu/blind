//
// Created by mswat
//

#ifndef BLIND_UTILS_H
#define BLIND_UTILS_H
#include "bigint/BigIntegerLibrary.hh"

class Utils {
public:
    static BigUnsigned generateNumOfSpecifiedBitLength(long bitLength);
    static bool checkIfPrime(BigUnsigned n);
    static BigUnsigned generateLargePrimeNumber(long bitLength);
    static BigUnsigned generateSafePrime(long bitLength);
    static BigUnsigned generateUnsafePrime(long bitLength);
};


#endif //BLIND_UTILS_H
