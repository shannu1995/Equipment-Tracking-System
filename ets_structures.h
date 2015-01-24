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
#ifndef ETS_STRUCTURES
#define ETS_STRUCTURES
#include "ets_utility.h"
/* this will remove warnings on unused variables in the skeleton code */
#define UNUSED(var) (void)var
#define NUMARGS 4
#define IDLEN 5
#define NAMELEN 31
#define EQUIP_FIELDS 3

/* This is the ets structure you will pass to many functions */


/*
 * ***********************   LOAN LINKED LIST   ***********************
 * */
struct loan_info
{
	char memberID[IDLEN + 1];
	char equipID[IDLEN + 1];
	unsigned number;
};

struct loan_node
{
	struct loan_info *data;
	struct loan_node *next;
};

struct loan_list
{
	struct loan_node *head;
	unsigned length;
};
/****************************  END   ******************************/


/*
 ***********************  MEMBER LINKED LISTS***********************
 **/
struct member_info
{
	char memberID[IDLEN + 1];
	char lastName[NAMELEN + 1];
	char firstName[NAMELEN + 1];
};

struct member_node
{
	struct member_info *data;
	struct member_node *next;
};

struct member_list
{
	struct member_node *head;
	unsigned length;
};
/****************************  END  *******************************/


/*
 ***********************  EQUIPMENT LINKED LISTS***********************
 **/
struct equipment_info
{
	char equipID[IDLEN + 1];
	char equipName[NAMELEN + 1];
	unsigned quantity;
};

struct equipment_node
{
	struct equipment_info *data;
	struct equipment_node *next;
};

struct equipment_list
{
	struct equipment_node *head;
	unsigned length;
};

enum equip_fields
{
	ID, NAME, QUANTITY
};
/****************************  END  *******************************/

struct ets 
{
	struct loan_list *loans;
	struct equipment_list *equipment;
	struct member_list *members;
	char *loan_file;
	char *equip_file;
	char *member_file;
};
BOOLEAN ets_init(struct ets * ets);
BOOLEAN load_data(struct ets * ets, const char * equip_fname, const char * member_fname, const char * loan_fname);
BOOLEAN add_item_node(struct equipment_list *list, struct equipment_info *item);
void ets_free(struct ets * ets);
void create_equipment(struct equipment_info *item, char *id, char *name, unsigned quantity);
#endif
