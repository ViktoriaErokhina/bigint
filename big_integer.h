//
// Created by Viktoria Erokhina on 30.04.17.
//



/*
 *
 cmake_minimum_required(VERSION 2.8)

project(BIGINT)

include_directories(${BIGINT_SOURCE_DIR})

add_executable(big_integer_testing
        big_integer_testing.cpp
        big_integer.h
        big_integer.cpp
        gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -D_GLIBCXX_DEBUG")

target_link_libraries(big_integer_testing -lpthread)
 */

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

//#include <cstddef>
#include <vector>

struct big_integer
{
    big_integer();
    big_integer(big_integer const& other);
    big_integer(int a);
    explicit big_integer(std::string const& str);
    ~big_integer();

    big_integer& operator=(big_integer const& other);

    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);
    big_integer& operator*=(big_integer const& rhs);
    big_integer& operator/=(big_integer const& rhs);
    big_integer& operator%=(big_integer const& rhs);

    big_integer& operator&=(big_integer const& rhs);
    big_integer& operator|=(big_integer const& rhs);
    big_integer& operator^=(big_integer const& rhs); //

    big_integer& operator<<=(int rhs);
    big_integer& operator>>=(int rhs);

    big_integer operator+() const;
    big_integer operator-() const;
    big_integer operator~() const;

    big_integer& operator++();
    big_integer operator++(int);

    big_integer& operator--();
    big_integer operator--(int);

    friend bool operator==(big_integer const& a, big_integer const& b);
    friend bool operator!=(big_integer const& a, big_integer const& b);
    friend bool operator<(big_integer const& a, big_integer const& b);
    friend bool operator>(big_integer const& a, big_integer const& b);
    friend bool operator<=(big_integer const& a, big_integer const& b);
    friend bool operator>=(big_integer const& a, big_integer const& b);

    friend std::string to_string(big_integer const& a);
private:
    void update_size();
    void shift_left(int k);
    void shift_right(int k);
    void resize(int new_size);
    void ensure_capacity(int size);
    void remove_zeroes();
    void cancel_small(int new_capacity);
    friend int cmp_abs(big_integer const& lhs, big_integer const& rhs);
    big_integer& add(big_integer const& rhs);
    big_integer& sub(big_integer const& rhs);

    int size;
    int capacity;
    union {
        long long value;
        unsigned int *digits;
    };
    int sign;
    static const int POWER = 31;
    static big_integer ONE;
    static const int DIGITS_IN_ONE = 16;
    static const long long MAX_VALUE = (1LL << 31LL);
    static const long long MAX = (1LL << 31LL) - 1;
    static const long long MIN = -(1LL << 31LL);
    static const int DIG_LEN = 10;
    void sw(big_integer& tmp);
    void add_small(long long x);
    void sub_small(long long x);
    bool is_ok(long long x);
    std::pair <bool, long long> is_relevant_string(std::string const &str, int cnt, int s);
    void make_copy();
    void mul_small(long long x);
    void div_small(long long x);
    void and_small(long long x);
    void or_small(long long x);
    void xor_small(long long x);
};

big_integer operator+(big_integer a, big_integer const& b);
big_integer operator-(big_integer a, big_integer const& b);
big_integer operator*(big_integer a, big_integer const& b);
big_integer operator/(big_integer a, big_integer const& b);
big_integer operator%(big_integer a, big_integer const& b);

big_integer operator&(big_integer a, big_integer const& b);
big_integer operator|(big_integer a, big_integer const& b);
big_integer operator^(big_integer a, big_integer const& b);

big_integer operator<<(big_integer a, int b);
big_integer operator>>(big_integer a, int b);

bool operator==(big_integer const& a, big_integer const& b);
bool operator!=(big_integer const& a, big_integer const& b);
bool operator<(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);

std::string to_string(big_integer const& a);
std::ostream& operator<<(std::ostream& s, big_integer const& a);

#endif // BIG_INTEGER_H