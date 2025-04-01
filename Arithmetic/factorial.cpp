// recursive and iterative factorial calculation in C++
//  by Dave Wonnacott, Summer 2005, as an example for CMSC 245

#include <logic.h>   // HaverfordCS "precondition", "postcondition", "assert"
#include "factorial.h"

using namespace std;

long long int factorial_rec (int n)
{
	precondition(n >= 0);  // A Haverford macro; could use C++ "static_assert"
	if (n > 0) {
		return n * factorial_rec(n - 1);
	}
	else {
		return 1;
	}
}

long long factorial_iter (int n)
{
	precondition(n >= 0);
	long long f = 1;
	for (int i=2 ; i<=n ; i++)
		f = f * i;
	return f;
}

#include <doctest.h>

// the following is based on https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
TEST_CASE("testing the factorial functions") {
	CHECK(factorial_rec(5)  == 120);
	CHECK(factorial_iter(5) == 120);

    for (int i = 0; i<=32; i++) {
        CHECK(factorial_rec(i) == factorial_iter(i));
    }
}
