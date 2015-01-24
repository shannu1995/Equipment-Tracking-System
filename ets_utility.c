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
#include "ets_utility.h"

/* clears the input buffer. */
void read_rest_of_line(void)
{
        int ch;
        while(ch = getc(stdin), ch!='\n' && ch != EOF) 
                ;
        clearerr(stdin);
}

enum string_result get_string(char *s, unsigned size, FILE *stream)
{
	unsigned len;
	if(fgets(s, size, stream) == NULL)
	{
		return STRING_EMPTY;
	}    
	len = strlen(s);
	if(len == 1)
	{
		return STRING_EMPTY;
	}
	
	else if(s[len-1] == '\n')
	{
		s[len-1] = '\0';
		return STRING_SUCCESS;
	}
	
	else
	{
		read_rest_of_line();
		return STRING_TOOLONG;
	}
}


