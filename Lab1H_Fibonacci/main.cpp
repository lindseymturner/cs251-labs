#include <HERA.h>        /* This is required for HERA projects */
#include <HERA-print.h>  /*  This is needed to use print_reg and print for debugging in HERA-C */

void HERA_main()
{
	// Set up input here
	SET(R1, 12)
	// include your algorithm
#include "fibonacci.hera"
	// print output here
	print("tried to find the 12th Fibonacci number, which should be 144...")
	print_reg(R1)
	// stop the CPU
	HALT()
}
