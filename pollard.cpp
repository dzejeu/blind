////
//// Created by mswat on 19.12.17.
////
//#include <stdio.h>
//#include "bigint/BigUnsigned.hh"
//#include "Utils.h"
//
//BigUnsigned factorial(BigUnsigned k) {
//    BigUnsigned result = 1;
//    for (BigUnsigned i = 2; i <= k; i++) {
//        result *= i;
//    }
//    return result;
//}
//
//int main(int argc, char *argv[]) {
////    std::cout << modexp(2,5,3) << std::endl;
////    srand(static_cast<unsigned int>(time(nullptr)));
////    BigUnsigned N = 152054113;
////    //try factoring
////    BigUnsigned x = 2;
////    for (BigUnsigned k=1; k <= 1000; k++){
////        BigUnsigned B = factorial(k);
////        BigUnsigned val = modexp(x, B, N) - 1;
////        BigUnsigned p1 = gcd(val, N);
////        if (p1 != 1 && p1 != N){
////            std::cout<< p1 << std::endl;
////            std::cout << k << std::endl;
////            std::cout << B << std::endl;
////            break;
////        }
////    }
//    BigUnsigned n = 87463;
//    for (int k = 2; k <= 26; k++) {
//        std::cout << k << "\t" << modexp(n, (k - 1) / 2, k) << std::endl;
//    }
//    return 0;
//}