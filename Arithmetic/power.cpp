//
// Created by lturner on 2/5/25.
//

#include "power.h"
#include <logic.h>
#include <iostream>

double power_iter(double base, int exponent) {
    precondition(exponent>=0);
    double result = 1.0;
    for (int i=0; i < exponent; i++)
        result *= base;
    return result;
}

long power_rec(int base, int exponent) {
    precondition(exponent>=0);
    if (exponent>0) {
        return (long)base * power_rec(base, exponent-1);
    }
    else {
        return 1;
    }
}
double power_fast(double base, int exponent) {
    precondition(exponent>=0);
    if (exponent == 0) {
        return 1;
    }

    if (exponent % 2 == 0) {
        double double_half = power_fast(base, exponent/2);
        return double_half * double_half;
    }
    else {
        return base * power_fast(base, exponent-1);
    }
}

void printULong2X(unsigned long ulongs, unsigned long ones) {
    char hexDigits[] = "0123456789ABCDEF";  // Lookup table for hex representation

    // Step 1: Print "0x" prefix
    std::cout << "0x";

    // Step 2: Convert `ulongs` to hexadecimal and print it
    char ulongsHex[16];  // Array to store hex digits of ulongs
    unsigned long temp = ulongs;
    int index = 0;

    if (temp == 0) {
        std::cout << "0";  // Ensure at least one zero if ulongs is 0
    } else {
        while (temp > 0) {
            ulongsHex[index++] = hexDigits[temp % 16];  // Extract last hex digit
            temp /= 16;  // Move to the next hex digit
        }

        // Print ulongs in reverse order
        for (int i = index - 1; i >= 0; i--) {
            std::cout << ulongsHex[i];
        }
    }

    // Step 3: Convert `ones` to hexadecimal with leading zeros
    char onesHex[16];  // Array to store hex digits of ones
    index = 0;
    temp = ones;

    while (temp > 0) {
        onesHex[index++] = hexDigits[temp % 16];  // Extract last hex digit
        temp /= 16;  // Move to the next hex digit
    }

    // Ensure exactly 16 digits for ones (adding leading zeros if needed)
    for (int i = 0; i < 16 - index; i++) {
        std::cout << "0";
    }

    // Print ones in reverse order
    for (int i = index - 1; i >= 0; i--) {
        std::cout << onesHex[i];
    }

    std::cout << std::endl;

}

// helper function
int sum_helper(unsigned int x, int y){
    if (y==x) {
        return 0;
    }
    else {
        return power_fast(x-y, y) + sum_helper(x, y+1);
    }
}

// recursive solution
int sum_rec(unsigned int x) {
    return sum_helper(x, 1);
}

// iterative solution
int sum_iter(unsigned int x) {
    int sum = 0;
    for (int y=1; y<x; y++) {
        sum += power_fast(x-y, y);
    }
    return sum;
}


#include <doctest.h>

// the following is based on https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
TEST_CASE("testing the power functions") {
    CHECK(power_rec(5, 2)  == 25);
    CHECK(power_iter(5.0,2) == 25.0);
    CHECK(power_fast(5.0, 2) == 25.0);
    CHECK(power_rec(5, 5)  == 3125);
    CHECK(power_iter(5.0,5) == 3125.0);
    CHECK(power_fast(5.0, 5) == 3125.0);

    CHECK(power_rec(2, 2)  == 4);
    CHECK(power_iter(2.0,2) == 4.0);
    CHECK(power_fast(2.0, 2) == 4.0);

    for (int i = 0; i<=32; i++) {
        CHECK(power_rec(2, i) == power_iter(2,i));
        CHECK(power_rec(2, i) == power_fast(2,i));
    }

}

TEST_CASE("testing solo functions") {
    CHECK(sum_iter(5) == 22);
    CHECK(sum_rec(5) == 22);

    CHECK(sum_iter(5) == sum_rec(5));

    CHECK(sum_iter(10) == sum_rec(10));

    CHECK(sum_rec(2) == 1);  // (2-1)*1 = 1
    CHECK(sum_iter(2) == 1);

}












