/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Validation check: If the end user does not provide 3 or 4 command-line 
    // arguments, prompt the user and exit the program with an error.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // set the integer variable n, to be the second command-line argument
    // inputted by the end-user
    int n = atoi(argv[1]);

    // If the end-user has provided 4 command-line arguments, create a random
    // number based on the third input being used as the seed value
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // For the number of times equal to the second command-line argument (n),
    // print the integer results of a randon number between 0 and 1 by our max
    // value possible for each result to produce random values between 0 and max
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}