#include "ets_utility.h"

BOOLEAN ets_init(struct ets * ets);
BOOLEAN load_data(struct ets * ets, const char * equip_fname, const char * member_fname, const char * loan_fname);
void ets_free(struct ets * ets); 
