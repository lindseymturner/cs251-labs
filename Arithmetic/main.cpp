//
// Example C++ program for CS251 Lab 1C - Last updated summer 2023 by Dave W. and J.D.
//
// Compile in C-Lion, or via "g++245" or "clang245" (in the QuaCS lab),
//         or via clang -std=c++20 -I/home/courses/include *.cc -L/home/courses/lib -lcourses -lstdc++ -o Algorithms-C++  # or g++ instead of clang
//	   after checking via clang-tidy -checks=cppcoreguidelines-* -header-filter=.* *.cc -- -std=c++17 -I/home/courses/include 
//

#include <iostream>
#include <logic.h>   // HaverfordCS "precondition", "postcondition", "assert"
#include "hc_streams.h"  // for non-standard "debug" output
#include "factorial.h"

using namespace std;
using namespace HaverfordCS;


#define DOCTEST_CONFIG_IMPLEMENT  // keeps the doctests in other files from giving errors even if we're not running them
#include <doctest.h>  // DocTest for C++ is installed on the QuaCS lab machines, and can be obtained from the site below
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

    cout << endl << "#    Welcome to the C++ example program for arithmetic." << endl;  // output for the normal user

    cout << endl << "Here's five factorial: " << factorial_rec(5) << endl;

    // note the use of C/C++ && operator to chain together three steps below, in the test of the while.
    //  using 'cin' or the result of >> as a boolean means "if cin hasn't failed due to, e.g., end-of-input"
    int request;
    while (cout << "What number would you like the factorial of? (Enter 0 or negative to stop.)  " &&
           cin >> request &&
           request >0)
    {
        cout << "Here's "<< request <<" factorial: " << factorial_rec(request) << endl;
    }

    cout << "Did you get any surprising results? For reference..." << endl;
    cout << "   The int       type uses " << sizeof(int)       * CHAR_BIT << " bits." << endl;
    cout << "   The long      type uses " << sizeof(long)      * CHAR_BIT << " bits." << endl;
    cout << "   The long long type uses " << sizeof(long long) * CHAR_BIT << " bits." << endl;

    return 0 + res; // 0 means success, anything else means failure of some sort indicated by the number
}
