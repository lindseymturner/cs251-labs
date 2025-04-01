//
// Created by davew on 6/28/23.
//

#include "safe_int_just_c.h"
#include <doctest.h>


TEST_CASE("safe_int initializing constructor and casting-back operator int")
{
    safe_int z = make_safe_int(0);
    safe_int f = make_safe_int(42);
    CHECK(z.theValue  == 0);
    CHECK(f.theValue  == 42);
    CHECK(make_int_from_safe_int(z)  == 0);
    CHECK(make_int_from_safe_int(f)  == 42);
}

TEST_CASE("safe_int addition")
{
    safe_int z = make_safe_int(0);
    safe_int f = make_safe_int(42);
    CHECK(add_safe_int(z, z).theValue  == 0);
    CHECK(add_safe_int(f, z).theValue  == 42);

    safe_int i = make_safe_int(25);
    safe_int j = make_safe_int(17);
    CHECK(add_safe_int(i, j).theValue  == 42);
}

TEST_CASE("safe_int add-assign")
{
    safe_int i = make_safe_int(0);
    CHECK((i).theValue  == 0);
    add_to_safe_int(&i, make_safe_int(25));
    CHECK((i).theValue  == 25);
    safe_int j = make_safe_int(17);
    CHECK(add_to_safe_int(&i, j)->theValue == 42);  // i += j is the sum, like i+j ...
    CHECK((i).theValue  == 42);      //        ... but also changes i
    CHECK((j).theValue  == 17);      // i += j must _not_ change j
}

// @ToDo: really should test subtraction and division, but this is just a simple example for reference...

TEST_CASE("safe_int comparisons")
{
    safe_int i = make_safe_int(7), j = make_safe_int(3);
    CHECK(are_safe_ints_equal(i, i)  == true);
    CHECK(are_safe_ints_equal(i, j)  == false);
    CHECK(are_safe_ints_equal(j, i)  == false);
    CHECK(are_safe_ints_different(i, i)  == false);
    CHECK(are_safe_ints_different(i, j)  == true);
    CHECK(are_safe_ints_different(j, i)  == true);

    CHECK((i).theValue  == 7);
    CHECK((j).theValue  == 3);
}

// can't easily make input and output operations, without either
//   adding separate functions equivalent to "sprintf" and "sscanf", or
//   creating a pipe or temporary file, too annoying to mess with today

