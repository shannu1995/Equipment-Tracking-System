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

enum int_result get_int(int *n, unsigned size, int min, int max, FILE *stream)
{
	char temp_str[BUFFER_SIZE];
	int temp_int = 0;
	char *end_ptr;
	enum string_result input_res;
	input_res = get_string(temp_str, size, stream);
	if(input_res == STRING_TOOLONG)
	{
		return INT_STRINGTOOBIG;
	}
	else if(input_res == STRING_EMPTY)
	{
		return INT_STRINGEMPTY;
	}
	else /* String successfully read */
	{
		temp_int = (int)strtol(temp_str, &end_ptr, 10);
		if(strcmp(end_ptr, "") != 0)
		{
			printf("Please enter an integer\n");
			return INT_NOTINT;
		}
		else if(temp_int < min || temp_int > max + 1)
		{
			printf("Please enter an integer between %d and %d\n",min, max + 1);
			return INT_OUTOFRANGE;
		}
		else
		{
			*n = temp_int;
			return INT_SUCCESS;
		}
	}
}

BOOLEAN str_to_unsigned(char *s, unsigned *u)
{
	if(!is_unsigned(s))
		return FALSE;
	*u = (unsigned)strtol(s,NULL,10);
	return TRUE;
}

BOOLEAN is_unsigned(char *s)
{
	int i;
	char *end_ptr;
	i = (int)strtol(s, &end_ptr, 10);
	if(i < 0 || strcmp(end_ptr,"") != 0)
	{
		return FALSE;
	}
	return TRUE;
}
