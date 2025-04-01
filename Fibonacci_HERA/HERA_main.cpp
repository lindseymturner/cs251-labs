// iterative factorial calculation just for 6! and 9! in HERA
// by Dave Wonnacott, Summer 2005 (and later revised), as an example for CMSC 245/240

#include <HERA.h>		/* This is required for HERA projects */
#include <HERA-print.h>	/*  This is needed to use print_reg and print for debugging in HERA-C */

void HERA_main()
{
    // We'll use "single-precision", i.e., one-register values, for most of this course,
    //  so we set the carry-block flag here.
    // I label files that assume single-precision "P1", those with two-register precision "P2", etc.

    CBON()

    // COMPUTE AND PRINT 6! AND 9!, SEVERAL OPTIONS (UN-COMMENT THE ONES YOU WANT)

    // Since HERA programs are pretty long, we'll put components into different files,
    //  and then just use #include to bring that code into this file to be run.
#include "factorial_6_9_P1_noloop.hera"
#include "double_precision_demo_P2.hera"

    // Now demonstrate a loop --- once again, find 6!
#include "factorial_6_loop_P1.hera"

    // Then use a general-purpose factorial to find either 3! or 5!
    SET(R1, 3)
#include "factorial_R1_loop_P1.hera"
    print("tried to find 3!, which should be 6...")
    print_reg(R1)

//    SET(R1, 5)
//#include "factorial_R1_loop_P1.hera"
//    print("tried to find 5!, which should be 120...")
//    print_reg(R1)

    // Feel free to add an example of a double-precision loop, if you like :-)

    // Now, Lab 1H: fill in
  HALT()
}
