/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Summer 2015 Assignment #2
 * Full Name        : Shanmukha Prasad Sivapurapu
 * Student Number   : s3453738
 * Course Code      : COSC 1076
 * Program Code     : BP 096
 * Start up code provided by David Shaw
 * Based on 2014 code by Paul Miller and Virginia King
 **********************************************************************/

***********************
FUNCTIONAL REQUIREMENTS
***********************

The only functional requirement that wasn't fulfilled completely is the loading data.
The program does read data from the files, and displays errors but there are a few minor issues.

Program can detect corruption in data files but not deeper than that

Consider the following scenario for example:-
 In the equip.dat file, there is a item with id as E0001 and has a totoal quantity of 20
 In the loan.dat file, a member(M0001) has loaned the item ID E0001 5 times
 and another member(M0005) has loaned it 20 times.
 This should give an error message saying that E0001 cannot be loaned 25 times but my program doesn't

Program doesn't detect duplicate information.
 For example two items with same id's can exist while loading from the files.

Please note that these issues are restricted to the load requirement only.
 After loading them, the aforementioned errors won't occur.
 I was unable to detect if the given files are sorted or not.
 But after reading them, the program automatically sorts them into the lists.
 And while saving also, saves in sorted order.

While deleting a member, the program first asks for confirmation,
then checks if outstanding loans exist rathar then the other way around.

****************************
SOFTWARE DESIGN REQUIREMENTS
****************************
Makefile completed to perfection, No memory leaks or uninitialized variables exist.

SOFTWARE DESIGN CHOICES:-
-----------------------
I have created an extra module called ets_structures.c/h.
In this module I have included linked lists, enumerations to assist the design.
I have also used this in functional abstraction of ets_options.c
For example, if save option is selected, the function calls 3 functions
(one for each file) from the ets_structures module

LINKED LISTS AND ADTs:-
---------------------
I have used three copies(ets->loans_list, ets->items_list, ets->members_list)
of the same linked list(ets_list).
I have not used generics.
