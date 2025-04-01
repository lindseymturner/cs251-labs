//
// Created by davew on 10/12/21.
// See README-running.md for details on how to run the program
//

#include <iostream>  // access to I.O. Streams library, for std::cout and std::endl
#include "SafeInt.h"

using namespace std;


#define DOCTEST_CONFIG_IMPLEMENT  // keeps the doctests in other files from giving errors even if we're not running them
#include <doctest.h>
// above two lines copied from https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
// as are various "doctest" related things below

SafeInt safeFib(int element_number) {  // requires element_number > 0
    // check precondition
    if (element_number <= 0) throw std::domain_error("Illegal request for fibonacci sequence");

    int i=2;  // which element of the sequence have we figured out, so far?
    SafeInt fib_i = SafeInt(1);  // i'th element, starting with i=2, i.e., fib(2); also works for fib(1), of course
    SafeInt fib_p = SafeInt(1);  // previous element, fib(i-1), with i=2 this is fib(1)

    while(i<element_number) {
        // at this point, fib_i = fib(i), fib_p = fib(i-1)
        SafeInt fib_next = fib_i + fib_p;
        fib_p = fib_i;
        fib_i = fib_next;
        i++;
    }
    // at this point, fib_i = fib(i), including special case of i=1 but fib_i = fib(2)

    return fib_i;
}


int main(int argc, char **argv)
{
    // ===================== Run tests, copied from doctest main.md cited above ======================
    doctest::Context context;
    context.applyCommandLine(argc, argv);                // let doctest consider command-line arguments
    // might want the following, not sure?
    // context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail
    int res = context.run();                             // run the tests
    if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;          // return the result of the test, rather than continuing code below, if appropriate
    // ===================== End of test-running boilerplate ==========================================


    std::cout << "Hello, world" << std::endl;

    /// Put your demo of bigFib here

    return 0+res; // success, unless doctest set "res" to indicate otherwise
}
