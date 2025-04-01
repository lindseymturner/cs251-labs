#include <HERA.h>        /* This is required for HERA projects */
#include <HERA-print.h>  /*  This is needed to use print_reg and print for debugging in HERA-C */

void HERA_main()
{
	// Set up input here
	SET(R1, 47)
	// include your algorithm
#include "fibonacci.hera"
	// print output here
	print("tried to find the 47th Fibonacci number")
	print("expect: 0xb119 in R3, 0x24e1 in R2")
	print_reg(R3)
	print_reg(R2)
	// stop the CPU
	HALT()
}
