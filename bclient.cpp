//
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h>
//#include <fstream>
//#include "bigint/BigUnsigned.hh"
//#include "bigint/BigIntegerAlgorithms.hh"
//#include "Utils.h"
//#include <chrono>
//
//using  ns = std::chrono::nanoseconds;
//using get_time = std::chrono::steady_clock ;
//
//void error(const char *msg) {
//    perror(msg);
//    exit(0);
//}
//
//int main(int argc, char *argv[]) {
//    srand(time(nullptr));
//    int sockfd, portno = 7777, n;
//    struct sockaddr_in serv_addr;
//    struct hostent *server;
//
//    char buffer[16384];
//    sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (sockfd < 0)
//        error("ERROR opening socket");
//    server = gethostbyname("localhost");
//    if (server == NULL) {
//        fprintf(stderr, "ERROR, no such host\n");
//        exit(0);
//    }
//    bzero((char *) &serv_addr, sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET;
//    bcopy((char *) server->h_addr,
//          (char *) &serv_addr.sin_addr.s_addr,
//          server->h_length);
//    serv_addr.sin_port = htons(portno);
//    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
//        error("ERROR connecting");
//    printf("Please enter the message: ");
//    bzero(buffer, 16384);
//    fgets(buffer, 16383, stdin);
//    std::string msgAsString = std::string(buffer);
//    msgAsString = msgAsString.substr(0, msgAsString.size() - 1);    //remove newline
//    BigUnsigned m = stringToBigUnsigned(msgAsString);
//    BigUnsigned r;
//    std::ifstream filePtr(argv[1]);
//    std::string a, b;
//    filePtr >> a >> b;
//    BigUnsigned N = stringToBigUnsigned(a);
//    BigUnsigned e = stringToBigUnsigned(b);
//    do {
//        r = Utils::generateNumOfSpecifiedBitLength(N.bitLength() - 1);
//    } while (gcd(r, N) != 1);
//    BigUnsigned mPrime = (m * modexp(r, e, N)) % N;
//    std::string mPrimeAsString = bigUnsignedToString(mPrime);
//    std::cout << "Mprime: " << mPrimeAsString << std::endl;
//    char outBuffer[16384];
//    strcpy(outBuffer, mPrimeAsString.c_str());
//    n = static_cast<int>(write(sockfd, outBuffer, strlen(outBuffer)));
//    if (n < 0)
//        error("ERROR writing to socket");
//    bzero(buffer, 16384);
//    n = static_cast<int>(read(sockfd, buffer, 16383));
//    if (n < 0)
//        error("ERROR reading from socket");
//    std::string response = std::string(buffer);
//    std::cout << "x^d: " << response << std::endl;
//    BigUnsigned resp = stringToBigUnsigned(response);
//    // measure verification time
//    auto start = get_time::now();
//    BigUnsigned result = (resp * modinv(r, N)) % N;
//    BigUnsigned realMessage = modexp(result, e, N);
//    // end of verification
//    auto end = get_time::now();
//    std::cout << "Result: " << realMessage << std::endl << std::endl;
//    auto diff = end - start;
//    std::cout << "Time of verification: " << std::chrono::duration_cast<ns>(diff).count() << std::endl;
//    close(sockfd);
//    return 0;
//}