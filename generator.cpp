//#include <iostream>
//#include "bigint/BigInteger.hh"
//#include "bigint/BigIntegerLibrary.hh"
//#include "Utils.h"
//#include <chrono>
//
//using  ns = std::chrono::nanoseconds;
//using get_time = std::chrono::high_resolution_clock;
//
//int main(int argc, char* argv[]){
//    srand(static_cast<unsigned int>(time(nullptr)));
//    BigUnsigned e = 65537;
//    BigUnsigned p, q;
//    int keyLength = 128;
//    auto start = get_time::now();
//
//    do {
//        p = Utils::generateLargePrimeNumber((long) keyLength / 2);
//    } while (p % e == 1);
//    do {
//        q = Utils::generateLargePrimeNumber((long) keyLength - (keyLength / 2));
//    } while (q % e == 1);
//    BigUnsigned N = p * q;
//    BigUnsigned eulers_phi = (p - 1) * (q - 1);
//    BigUnsigned d = modinv(e, eulers_phi);
//    auto end = get_time::now();
//    auto diff = end - start;
//    std::cout << std::chrono::duration_cast<ns>(diff).count() << std::endl;
//    return 0;
//}
//
//
//TODO: 9.3