//
// Created by davew on 6/27/23.
//

#include "countXs_just_c.h"

#include <string.h>

// a simple example that takes a string parameter and returns an int, the number of times capital-X appears
int countXs_just_c(const char s[ ]) // s is a C-style array of characters, we assume terminated by a NULL ('\n')
{
    int n_Xs = 0;
    unsigned int index = 0;
    int length = strlen(s);  // call C library function to find length of a C-style string
    for (index = 0; index < length; index++) { // 'index' takes on each valid index
        if (s[index] == 'X') n_Xs++;  // just like in C++ C-idioms version
    }

    return n_Xs;
}

/*
 * Unfortunately, doctest doesn't seem to work in classic C :-(
 * So, the tests are located in all_names.cpp.
 */


