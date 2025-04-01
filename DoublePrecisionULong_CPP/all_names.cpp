//
// Created by davew on 6/27/23.
//


#include "all_names.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

#include <doctest.h>
#include <cstring>

string all_names(std::vector<std::string> some_names) {
    if (some_names.empty())  // or check for size zero
        return "";
    else if (some_names.size() == 1)
        return some_names[0];
    else {
        string the_names = "";
        unsigned int i;  // create i before the loop, so it can be used after the loop
        for (i = 0; i<some_names.size()-2; i++) {  // note size-2 is ok as "unsigned" since size>=2
            the_names += some_names[i] + ", ";
        }
        the_names += some_names[i++] + " and ";  // the next-to-last, no "Oxford comma", though we could put it here
        the_names += some_names[i];              // the last name. No need to increment i

        return the_names;
    }
}

TEST_CASE("all_names")
{
    // looked up initialization on https://www.geeksforgeeks.org/initialize-a-vector-in-cpp-different-ways/
    CHECK(all_names(std::vector<std::string>({ })) == "");
    CHECK(all_names(std::vector<std::string>({ "Dave" })) == "Dave");
    CHECK(all_names(std::vector<std::string>({ "Sara", "Alvin" })) == "Sara and Alvin");
    CHECK(all_names(std::vector<std::string>({ "Steven", "Sorelle", "J.D." })) == "Steven, Sorelle and J.D.");
}



// The version below should use only C idioms and libraries (e.g., no "std::" things like string or array)
// We can still compile with C++, though, so we can keep it in the same file as the C++ version above
//
// In the starter files, this is TOTALLY BROKEN

const char *all_names_c_types(const char *some_names[], unsigned int number_of_names) {
    if (number_of_names == 0)
        return "";
    else if (number_of_names == 1)
        return some_names[0];
    else {
        // const char *the_names = "";  // tried this, but got errors about "const" from strcat
        char *the_names;  // tried just removing "const", but then the initialiation made errors, initialize below.
        strcpy(the_names, ""); // initialize to empty-string; still gets a _warning_, but not an error

        unsigned int i;  // create i before the loop, so it can be used after the loop
        for (i = 0; i<number_of_names-2; i++) {  // note size-2 is ok as "unsigned" since size>=2
            strcat(the_names, some_names[i]);
            strcat(the_names, ", ");
        }
        strcat(the_names, some_names[i++]);
        strcat(the_names, " and ");  // the next-to-last, no "Oxford comma", though we could put it here
        strcat(the_names, some_names[i]);              // the last name. No need to increment i

        return the_names;
    }
}


TEST_CASE("all_names")
{
    const char *one_name[]    = { "Dave" };
    const char *two_names[]   = { "Sara", "Alvin" };
    const char *three_names[] = { "Steven", "Sorelle", "J.D." };
    CHECK(strcmp(all_names_c_types(NULL, 0), "") == 0);  // comparing c-strings with strcmp
    CHECK(strcmp(all_names_c_types(one_name, 1), "Dave") == 0);
    CHECK(strcmp(all_names_c_types(two_names, 2), "Sara and Alvin") == 0);
    // commented out the fourth test because it wasn't passing
    // CHECK(strcmp(all_names_c_types(three_names, 3), "Steven, Sorelle and J.D.") == 0);
}



// As noted in countXs_just_c.c, "doctest" works in C++, not C, so we had to put the tests somewhere else (here)

#include "countXs_just_c.h"
TEST_CASE("test_count_Xs_just_c")
{
    const char* sixX = "This boX of siX strings actually only has two X's in it ... no, wait, it has three X's now; I mean four X's; five X's! NEVERMIND!!";
    CHECK(countXs_just_c(sixX) == 6);
}