cmake_minimum_required(VERSION 3.10)

project(CreditCardRecordMatching)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(
    CreditCardRecordMatching_TDD
    src/Vec.cpp
    tests/CreditCardRecordMatching_TDD.cpp
)

target_include_directories(CreditCardRecordMatching_TDD PRIVATE
    src
    external
)

add_test(
    NAME CreditCardRecordMatchingTests
    COMMAND CreditCardRecordMatching
)