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
#include "ets_utility.h"
#define MEMBER_PROMPT "Please enter the member ID: "
#define ITEM_PROMPT "Please enter the equipment ID: "
#define QUANTITY_PROMPT "Please enter the quantity: "
#define MEMBER_HEADING "Member List"
#define MEMBER_SUBHEADING "ID      Name                             # Lent"
#define EQUIPMENT_CHANGE_HEADING "Change Equipment Amount"
#define NEW_MEMBER_HEADING "Add New Memeber"
#define NEW_EQUIPMENT_HEADING "Add New Equipment"
#define DELETE_MEMBER_HEADING "Delete Member"
#define ABORT_HEADING "Abort"
#define LOAN_EQUIPMENT_HEADING "Loan Equipment"
#define RETURN_EQUIPMENT_HEADING "Return Equipment"
#define LOAN_LIST "Loan List"
#define QUERY_MEMBER_HEADING "Query Member ID" 
#define QUERY_EQUIPMENT_HEADING "Query Equipment ID"
#ifndef ETS_OPTIONS
#define ETS_OPTIONS
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
#endif
