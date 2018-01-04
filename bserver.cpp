#include <iostream>
#include "bigint/BigInteger.hh"
#include "Utils.h"
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include <chrono>

using  ns = std::chrono::nanoseconds;
using get_time = std::chrono::steady_clock ;

void getRandomPassword(char *s, const int len) {
    static const char alphanum[] =
            "0123456789"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
}

/*
 * Example usage:
 * Setup mode: ./blind 1 1024 priv.key pub.key
 * Setup mode: ./blind 2
 */
int main(int argc, char *argv[]) {
    srand(static_cast<unsigned int>(time(nullptr)));
    const char *confFilePath = ".conf";
    int mode = atoi(argv[1]);
    if (mode == 1) {
        /*Setup mode*/
        BigUnsigned e = 65537;
        BigUnsigned p, q;
        int keyLength = atoi(argv[2]);
        auto start = get_time::now();
        do {
            p = Utils::generateLargePrimeNumber((long) keyLength / 2);
        } while (p % e == 1);
        do {
            q = Utils::generateLargePrimeNumber((long) keyLength - (keyLength / 2));
        } while (q % e == 1);
        BigUnsigned N = p * q;
        BigUnsigned eulers_phi = (p - 1) * (q - 1);
        BigUnsigned d = modinv(e, eulers_phi);
        auto end = get_time::now();
        auto diff = end - start;
        std::cout << "Time of key generation: " << std::chrono::duration_cast<ns>(diff).count() << std::endl;
        // save keys to files
        char *privKeyFile = argv[3];
        char *pubKeyFile = argv[4];
        std::ofstream filePtr;
        // save priv key
        filePtr.open(privKeyFile, std::ios::out);
        filePtr << N << "\t" << d << std::endl;
        filePtr.close();
        //save public key
        filePtr.open(pubKeyFile, std::ios::out);
        filePtr << N << "\t" << e << std::endl;
        filePtr.close();
        // generate password
        char password[12];
        getRandomPassword(password, 12);
        std::cout << "Your password (keep it securely): " << password << std::endl;
        filePtr.open(confFilePath, std::ios::app);
        filePtr << std::hash<std::string>()(password) << "\t" << privKeyFile << std::endl;
        filePtr.close();
    } else if (mode == 2){
        std::cout << "Enter your password please" << std::endl;
        std::string password;
        std::cin >> password;
        std::stringstream ss;
        std::size_t passwordHashNumerical = std::hash<std::string>()(password);
        ss << passwordHashNumerical;
        std::string passwordHash = ss.str();
        // check if obtained hash is present in .conf file
        std::ifstream confReader(confFilePath);
        std::string hash, keyFilePath;
        bool passwordAccepted = false;
        BigUnsigned N, d;
        while (confReader >> hash >> keyFilePath){
            if (hash == passwordHash){
                std::ifstream filePtr(keyFilePath);
                std::string a, b;
                filePtr >> a >> b;
                N = stringToBigUnsigned(a);
                d = stringToBigUnsigned(b);
                passwordAccepted = true;
                break;
            }
        }
        if (!passwordAccepted) {
            std::cout << "Wrong password" << std::endl;
            exit(1);
        }
        // start server

        int sockfd, newsockfd, portno=7777;
        socklen_t clilen;
        char buffer[16384];
        struct sockaddr_in serv_addr, cli_addr;
        int n;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);
        if (bind(sockfd, (struct sockaddr *) &serv_addr,
                 sizeof(serv_addr)) < 0) {
            std::cout << "Error on binding" << std::endl;
            exit(1);
        }
        listen(sockfd,5);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd,
                           (struct sockaddr *) &cli_addr,
                           &clilen);
        if (newsockfd < 0) {
            std::cout << "ERROR on accept" << std::endl;
            exit(1);
        }
        bzero(buffer, 16384);
        n = static_cast<int>(read(newsockfd, buffer, 16383));
        if (n < 0) {
            std::cout << "ERROR reading from socket" << std::endl;
            exit(1);
        }
        std::string msgAsString = std::string(buffer);
        BigUnsigned message = stringToBigUnsigned(msgAsString);
        std::cout << "MSG: " << message << std::endl;

//        std::ifstream filePtr(argv[2]);
//        std::string a, b;
//        filePtr >> a >> b;
//        N = stringToBigUnsigned(a);
//        BigUnsigned e = stringToBigUnsigned(b);
//        auto start1 = get_time::now();
//        BigUnsigned r;
//        do {
//            r = Utils::generateNumOfSpecifiedBitLength(1024);
//        } while (gcd(r, N) != 1);
//        BigUnsigned y = modexp(modexp(r, e, N) * message, d, N);
//        BigUnsigned encoded = (y * modinv(r, N)) % N;
//        auto end1 = get_time::now();
//        auto diff = end1 - start1;
//        std::cout << "Time of signing: " << std::chrono::duration_cast<ns>(diff).count() << std::endl;

        auto start1 = get_time::now();
        BigUnsigned encoded = modexp(message, d, N);
        auto end1 = get_time::now();
        auto diff = end1 - start1;
        std::cout << "Time of signing: " << std::chrono::duration_cast<ns>(diff).count() << std::endl;

        std::string asString = bigUnsignedToString(encoded);
        char outBuffer[16384];
        strcpy(outBuffer, asString.c_str());
        n = static_cast<int>(write(newsockfd, outBuffer, 16384));
        if (n < 0) {
            std::cout << "ERROR writing to socket" << std::endl;
            exit(1);
        }
        close(newsockfd);
        close(sockfd);
    }

    return 0;
}