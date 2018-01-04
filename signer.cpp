//#include <iostream>
//#include "bigint/BigInteger.hh"
//#include "bigint/BigIntegerUtils.hh"
//#include "bigint/BigIntegerLibrary.hh"
//#include <chrono>
//
//using  ns = std::chrono::nanoseconds;
//using get_time = std::chrono::high_resolution_clock;
//
//int main(int argc, char* argv[]){
//    BigUnsigned d = stringToBigUnsigned("94969879183472043601622709428064174017");
//    BigUnsigned N = stringToBigUnsigned("191408831443466719636476202400984410829");
//
//    std::string msgAsString = std::string(argv[1]);
//    BigUnsigned msg = stringToBigUnsigned(msgAsString);
//
////    // signing
//    auto start1 = get_time::now();
////    BigUnsigned r;
////        do {
////            r = Utils::generateNumOfSpecifiedBitLength(1024);
////        } while (gcd(r, N) != 1);
////        BigUnsigned y = modexp(modexp(r, 65537, N) * msg, d, N);
////        BigUnsigned encoded = (y * modinv(r, N)) % N;
//
//    BigUnsigned signedMsg = modexp(msg, d, N);  // TA LINIJKE MIERZYMY
//    auto end1 = get_time::now();
//    auto diff = end1 - start1;
//    std::cout << msg << '\t' << std::chrono::duration_cast<ns>(diff).count() << '\n';
//    return 0;
//}
//
////TODO: constant time