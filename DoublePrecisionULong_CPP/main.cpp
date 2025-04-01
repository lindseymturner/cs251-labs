//
// Created by davew on 10/12/21.
// See README-running.md for details on how to run the program
//

#include <iostream>  // access to I.O. Streams library, for std::cout and std::endl
#include "SafeInt.h"
#include "safe_int_just_c.h"
#include "DiS-p71and74.h"
#include "countXs_just_c.h"
#include "all_names.h"


#define DOCTEST_CONFIG_IMPLEMENT  // keeps the doctests in other files from giving errors even if we're not running them
#include <doctest.h>
// above two lines copied from https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
// as are various "doctest" related things below

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
    const char *name1 = "Dave";
    const char *name2 = "J.D.";
    std::vector<std::string> authors = {name1, name2}; // C++ will convert c-style strings to std::string
    std::cout << "Welcome to DoublePrecisionULong_CPP, A C++ lab by " << all_names(authors) << std::endl;
    std::cout << "  (The name \"" << name1 << "\" has " << countXs_just_c(name1) << " X's in it.)" << std::endl;
    std::cout << "  (The name \"" << name2 << "\" has " << countXs_just_c(name2) << " X's in it.)" << std::endl;
    std::cout << std::endl;

    std::cout << " ***  Here's the C++ \"safe integer\" demonstration " << std::endl;
    SafeInt_Demo();   /// run C++ safe integer code demo
    std::cout << " ***  Here's the C \"safe integer\" demonstration; " << std::endl;
    std::cout << "  ... note that anything other than 0 will eventually crash, so use 0 to see other tests" << std::endl;
    safe_int_demo();  /// run C safe-integer demo, which runs until crash, so we'll not make it to the next line :-(


    std::cout << " ***  Here's a demo of C-style string manipulation, from \"Dive Into Systems\", pages 71 and 74. " << std::endl;
    dis_p71_and_74();

    std::cout << "all done" << std::endl;

    return 0+res; // success, unless doctest set "res" to indicate otherwise
}
