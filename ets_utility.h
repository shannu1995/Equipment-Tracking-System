/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Summer 2015 Assignment #2
 * Full Name        : Shanmuka Prasad Sivapurapu
 * Student Number   : s3453738
 * Course Code      : COSC 1076
 * Program Code     : BP   0096
 * Start up code provided by David Shaw
 * Based on 2014 code by Paul Miller and Virginia King
 **********************************************************************/
#include "ets_structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ETS_UTILITY
#define ETS_UTILITY
#define BUFFER_SIZE 1024
#define NUM_MENU_OPTS 13
#define NUM_FIELDS 3
#define DELIMETER "|"
typedef enum truefalse
{
	FALSE, TRUE
} BOOLEAN;



enum string_result
{
	STRING_TOOLONG, STRING_EMPTY, STRING_SUCCESS
};

enum int_result
{
	INT_STRINGTOOBIG, INT_STRINGEMPTY, INT_NOTINT,
	INT_OUTOFRANGE, INT_SUCCESS
};
void read_rest_of_line(void);
enum string_result get_string(char *s, unsigned size, FILE *stream);
BOOLEAN str_to_unsigned(char *s, unsigned *u);
BOOLEAN is_unsigned(char *s);
enum int_result get_int(int *n, unsigned size, int min,
	       	int max, FILE *stream);
#endif

