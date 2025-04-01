#include <string>	// std::string
#include <logic.h>	// Haverford's logic.h, for precondition, assert, etc.

#include "countXs.h"  // note that this .h includes <string> for us

using std::string;   // lets us write string rather than std::string
using namespace std::string_literals;  // allows "string"s notation for C++ literal strings; more on this later

// a simple example that takes a string parameter and returns an int, the number of times capital-X appears
// https://stackoverflow.com/a/3871346
#include <algorithm> // this is from stackoverflow

int countXs(std::string s) // used stack overflow example
{
    // std::string s = "a_b_c"; // this is from stack overflow
    // std::string::difference_type n = std::count(s.begin(), s.end(), '_'); // this is from stack overflow

    std::string::difference_type n = std::count(s.begin(), s.end(), 'X'); // used stack overflow example
    return static_cast<int>(n);

	/* code from original file
	 *
	 * int n_Xs = 0;
	for (char c : s) {
		if (c == 'X') n_Xs++;
	}

	// Old-style C equivalent still works, too:
	int n_XsAgain = 0;
	unsigned int i; // the one above could be 'unsigned' too
	for (i = 0; i<s.length(); i++) { // 'i' takes on each valid index
		if (s[i] == 'X') n_XsAgain++;
	}

    hccs_assert(n_Xs == n_XsAgain); // let me know, if this isn't true

	return n_Xs;
	 */
}

/*
 * a) If a student finds a solution to a lab assignment written by a professional developer on a paid coding
 * tutorial website, and follows the procedure to implement it into their own code, even though the student has not
 * committed academic dishonesty, they cannot use copyrighted material.
 *
 * b) Now, consider a student who is struggling with a lab assignment and copies a solution from a friend in the class,
 * submitting it as their own work. Since the friend willingly shared their code and has no copyright claim over it,
 * no copyright law is violated. However, this act is still academic dishonesty because the student is falsely
 * representing someone else's work as their own, violating the class's integrity policies.
 */

#include <doctest.h>

TEST_CASE("Test countXs") {
    string sixX = "This boX of siX strings actually only has two X's in it ... no, wait, it has three X's now; I mean four X's; five X's! NEVERMIND!!"s;
    CHECK(countXs(sixX) == 6);
    string fiveX = "xXxXxXxXxXx";
    CHECK(countXs(fiveX) == 5);
}
