cmake_minimum_required(VERSION 3.8)
project(blind)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O3")
set(SOURCE_FILES bclient.cpp bserver.cpp Utils.cpp Utils.h bigint/BigInteger.hh bigint/BigInteger.cc signer.cpp generator.cpp)
file(GLOB SOURCE_FILES
        "*.h"
        "*.cpp"
        "bigint/*.hh"
        "bigint/*.cc"
        )
add_executable(bserver ${SOURCE_FILES})