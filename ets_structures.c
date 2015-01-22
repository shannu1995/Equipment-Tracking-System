#include "ets_structures.h"

/* initialises the ets data structure to safe initial values. */
BOOLEAN ets_init(struct ets * ets)
{
	
	return FALSE;
}

/* loads data from the .dat files into memory. */
BOOLEAN load_data(struct ets * ets, const char * equip_fname, const char * member_fname, const char * loan_fname)
{
	/* The UNUSED() function is designed to prevent warnings while
	* your code is only partially complete. Delete this function
	* call once you are using your own code */
	FILE *equip_file, *member_file, *loan_file;
	char line[BUFFER_SIZE];
	UNUSED(ets);
	UNUSED(equip_fname);
	UNUSED(member_fname);
	UNUSED(loan_fname);      
	return FALSE;
}

