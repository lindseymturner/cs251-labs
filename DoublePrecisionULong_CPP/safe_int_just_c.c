//
// Created by davew on 10/5/22.
//

#include "safe_int_just_c.h"  // includes stdio, so fprintf is available here
#include <stdlib.h>  // for exit function, to halt on overflow

safe_int make_safe_int(int i) // sort of like SafeInt(int i), but no type casting
{
    safe_int result;
    if (i > safe_int_maximum) {  // ToDo: Wait, we need a better limit. Also, what of -1234 + -1234?
        fprintf(stderr, "Oops, init. of safe_int from %d exceeds maximum %d\n", i, safe_int_maximum);
        exit(87);
    }
    if (i < safe_int_minimum) {  // ToDo: Wait, we need a better limit. Also, what of -1234 + -1234?
        fprintf(stderr, "Oops, init. of safe_int from %d is below minimum %d\n", i, safe_int_minimum);
        exit(87);
    }
    result.theValue = i;
    return result;
}
int make_int_from_safe_int(safe_int i)  // used to convert, since there's no cast operation
{
    return i.theValue;
}

safe_int add_safe_int(safe_int i, safe_int j)
{
    safe_int result;
    if (i.theValue + j.theValue > safe_int_maximum) {  // ToDo: Wait, we need a better limit. Also, what of -1234 + -1234?
        fprintf(stderr, "Oops, failed to add safe_int's, due to overflow");
        exit(88);
    }
    result.theValue = i.theValue + j.theValue;
    return result;
}
safe_int *add_to_safe_int(safe_int *add_to_this_one, safe_int j)
{
    if (add_to_this_one->theValue + j.theValue > safe_int_maximum) {  // ToDo: Wait, we need a better limit. Also, what of -1234 + -1234?
        fprintf(stderr, "Oops, failed to \"add-to\" for a safe_int, due to overflow");
        exit(88);
    }
    add_to_this_one->theValue += j.theValue;
    return add_to_this_one;
}
safe_int *subtract_from_safe_int(safe_int *add_to_this_one, safe_int j)
{
    if (add_to_this_one->theValue - j.theValue < safe_int_minimum) {
        fprintf(stderr, "Oops, failed to \"subtract_from\" for a safe_int, due to overflow");
        exit(88);
    }
    add_to_this_one->theValue -= j.theValue;
    return add_to_this_one;
}

safe_int div_safe_int(safe_int i, safe_int j)
{
    safe_int result;
    result.theValue = i.theValue / j.theValue;
    return result;
}
safe_int *div_to_safe_int(safe_int *div_to_this_one, safe_int j)
{
    div_to_this_one->theValue = div_to_this_one->theValue / j.theValue;
    return div_to_this_one;
}
double real_divide_safe_int(safe_int i, safe_int j)
{
    return (float) i.theValue / (float) j.theValue;
}


int are_safe_ints_equal(safe_int i, safe_int j) // true if ==
{
    return i.theValue == j.theValue;
}
int are_safe_ints_different(safe_int i, safe_int j) // true if !=
{
    return i.theValue != j.theValue;
}



int print_safe_int_to(FILE *destination, safe_int i)
{
    return fprintf(destination, "%d", i.theValue);
}
int print_safe_int(safe_int i)
{
    return print_safe_int_to(stdout, i);
}

// C uses 0 for false, 1 for true. We could "typedef int bool" and #define true and false, of course, but...
int read_safe_int(safe_int *read_my_value)  // return true if it succeeded
{
    // ToDo: mention this: the result of "scanf" is described on the "man page", type "man scanf" or "man 3 scanf"
    return scanf("%d", &read_my_value->theValue) == 1;
}

void safe_int_demo()
{
    printf("Enter a positive integer, and I'll triple it until it makes me sad to do so...\n");  // \n for endl
    printf("  to avoid the inevitable exit from the program (on overflow), enter 0 and I'll skip this.\n");
    safe_int n;
    while (read_safe_int(&n) && are_safe_ints_different(n, make_safe_int(0))) {
        // Stops when read fails, due to end-of-input or non-integer entered, or the entered integer is zero
        printf("I read in the value ");
        print_safe_int(n);  // too bad I can't easily extend printf ... maybe check the man page for that?
        printf(", time to start tripling!!!\n");
//        try {
            while (1) { // run until error; by convention, 1 is used for true, 0 for false, in C
                int one = 1;  // a regular int, to demonstrate casting below
                n = add_safe_int(add_safe_int(n, n), n);
                n = add_safe_int(n, make_safe_int(one));   // no implicitly cast to struct in C, could use 1 here
                n = add_safe_int(make_safe_int(one), n);
                add_to_safe_int(&n, make_safe_int(one));   // ToDo: Note use of "&" here
                //  one += n;      // does not work for left-hand side of operator+= in C++; does C allow this?
                subtract_from_safe_int(&n, make_safe_int(3));  // go back down so we're just tripling
                printf("Managed to triple it and get ");
                print_safe_int(n);
                printf("\n");
            }
            // no easy way to try/catch, safe_int just quits the program when it fails :-(
    }

}


/*
 * We haven't been able to use doctest directly in C, _but_ note that the C functions can be called from C++,
 *  so we just put tests for safe_int_just_c in a file safe_int_just_c_tests.cpp, which compiles with C++
 */