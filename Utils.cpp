//
// Created by mswat on 11.12.17.
//

#include "Utils.h"
#include <stdint.h>

BigUnsigned Utils::generateNumOfSpecifiedBitLength(long bitLength) {
    long unsigned int lowBitMask = 0x0000000000000001;
    long unsigned int twoHighestBitMask = 0xC000000000000000;
    long unsigned int random = rand() % (UINT64_MAX - 2) + 2;
    BigUnsigned bigInt = BigUnsigned(random);
    while (bigInt.getLength() * bigInt.getBlockSize() < bitLength){
        bigInt = bigInt << 1;
    }
    for (BigInteger::Index block=0; block < bigInt.getLength() - 1; block++){
        bigInt.setBlock(block, rand() % (UINT64_MAX - 2) + 2);
    }
    BigInteger::Index lastBlock = bigInt.getLength() - 1;
    bigInt.setBlock(lastBlock, bigInt.getBlock(lastBlock) | twoHighestBitMask);
    bigInt.setBlock(0, bigInt.getBlock(0) | lowBitMask);
    return bigInt;
}

bool Utils::checkIfPrime(BigUnsigned n) {
    int k = 10;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    BigUnsigned r = 0;
    BigUnsigned s = n - 1;

    while (s % 2 == 0) {
        r += 1;
        s /= 2;
    }
    for (int test=0; test < k; test++) {
        BigUnsigned a;
        if (n < UINT64_MAX){
            a = BigUnsigned(rand() % (n.toUnsignedLong() - 3) + 2);
        } else {
            long unsigned int randInt = rand() % (UINT64_MAX - 2) + 2;
            a = modexp(randInt, BigUnsigned(rand() % 60), n - 3) + 2;
        }
        BigUnsigned x = modexp(a, s, n);
        if (x == 1 or x == n - 1)
            continue;
        bool found = false;
        for (BigUnsigned i=0; i < r-1; i+=1) {
            x = modexp(x, 2, n);
            if (x == n - 1) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

BigUnsigned Utils::generateLargePrimeNumber(long bitLength) {
    BigUnsigned largeNum = generateNumOfSpecifiedBitLength(bitLength);
    while (!checkIfPrime(largeNum))
        largeNum += 2;
    return largeNum;
}

BigUnsigned Utils::generateSafePrime(long bitLength) {
    BigUnsigned q;
    BigUnsigned p;
    while (true){
        q = generateLargePrimeNumber(bitLength);
        p = BigUnsigned(2)*q + 1;
        if (checkIfPrime(p))
            return p;
    }
}

BigUnsigned Utils::generateUnsafePrime(long bitLength) {
    BigUnsigned q1,q2,q3,q4;
    BigUnsigned p;
    while (true){
        q1 = generateLargePrimeNumber(bitLength / 4);
        q2 = generateLargePrimeNumber(bitLength / 4);
        q3 = generateLargePrimeNumber(bitLength / 4);
        q4 = generateLargePrimeNumber(bitLength / 4);
        p = q1 * q2 * q3 * q4 + 1;
        if (checkIfPrime(p))
            return p;
    }
}
