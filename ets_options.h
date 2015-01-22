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
#include "ets_type.h"
#include "ets_utility.h"

#ifndef ETS_OPTIONS
#define ETS_OPTIONS

/* This an example of one of the menu functions.
 * You will need to write one for each option.
 * Each one can only take one argument, a pointer to struct ets
 * Each returns a BOOLEAN, which indicates a success or not
 */
BOOLEAN loan_equipment(struct ets *);
BOOLEAN return_equipment(struct ets *);
BOOLEAN query_equipment_id(struct ets *);
BOOLEAN query_member_id(struct ets *);
BOOLEAN display_equipment(struct ets *);
BOOLEAN display_member_list(struct ets *);
BOOLEAN display_loan_list(struct ets *);
BOOLEAN save(struct ets *);
BOOLEAN add_equipment(struct ets *);
BOOLEAN change_equipment_amount(struct ets *);
BOOLEAN add_member(struct ets *);
BOOLEAN delete_member(struct ets *);
BOOLEAN abort_program(struct ets *);
/* you will need to define many more! */

#endif
