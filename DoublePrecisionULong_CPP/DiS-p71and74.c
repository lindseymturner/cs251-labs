//
// Created by davew on 10/6/22.
//

#include "DiS-p71and74.h"

// P. 71

#include <stdio.h>
#include <string.h>

int change_value(int *input);

int main_p71() {
    int x;
    int y;
    x = 30;
    y = change_value(&x);
    printf("x: %d y: %d\n", x, y); // prints x: 100 y: 30
    return 0;
}
/* * changes the value of the argument * input: a pointer to the value to change * returns: the original value of the argument */
int change_value(int *input) {
    int val;
    val = *input; /* val gets the value input points to */
    if (val < 100) {
        *input = 100; /* the value input points to gets 100 */
    } else {
        *input = val * 2;
    }
    return val;
}


// P. 74

#include <stdlib.h>

int main_p74() {
    int *p;
    p = malloc(sizeof(int)); // allocate heap memory for storing an int
    if (p != NULL) {
        *p = 6; // the heap memory p points to gets the value 6
    }

    free(p);  // Dave added this, too (free isn't necessary as the program ends, usually)
    return 0; // Added by Dave because "main" should return 0 unless there's an error
}


void dis_p71_and_74()
{
    printf("Here's the example from Dive into Systems, p. 71.:\n");
    main_p71();
    printf("Here's the example from Dive into Systems, p. 74.:\n");
    main_p74();
}