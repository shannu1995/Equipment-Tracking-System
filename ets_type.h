/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Summer 2015 Assignment #2
 * Full Name        : Shanmukha Prasad Sivapurapu
 * Student Number   : s3453738
 * Course Code      : COSC 1076
 * Program Code     : BP 094
 * Start up code provided by David Shaw
 * Based on 2014 code by Paul Miller and Virginia King
 **********************************************************************/
#ifndef ETS_TYPE
#define ETS_TYPE

/* this will remove warnings on unused variables in the skeleton code */
#define UNUSED(var) (void)var


/* type definition for our boolean type */
typedef enum truefalse
{
	FALSE, TRUE
} BOOLEAN;

enum int_result get_int(int *n, unsigned size, int min, int max, FILE *stream);
#endif