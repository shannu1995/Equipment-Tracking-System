########################################################################
# COSC1076 - Advanced Programming Techniques
# Summer 2015 Assignment #2
# Full Name        : EDIT HERE
# Student Number   : EDIT HERE
# Course Code      : EDIT HERE
# Program Code     : EDIT HERE
# Start up code provided by David Shaw
# Based on 2014 code by Paul Miller and Virginia King
########################################################################

###################################
# put your Makefile targets in here
###################################

CC=gcc
CFLAGS= -ansi -Wall -pedantic
CDEBUG = -g
SOURCES = ets_main.c ets_menu.c ets_structures.c ets_utility.c ets_options.c
OBJS = $(SOURCES:.c=.o) 
HEADERS = *.h
USER = s3453738
ARCHIVE_FILES = *.c *.h Makefile README.md
EXE = ets

all:		$(EXE)

$(EXE):	$(OBJS)
		  $(CC) $(CFAGS) $(OBJS) -o $@

%.o:	%.c
		  $(CC) $(CFLAGS) $< -c -o $@  


debug:	$(SOURCES)
		  $(CC) $(CFLAGS) $(CDEBUG) $(SOURCES) -o $(EXE)

.PHONY: clean archive 

clean:
		  rm -rf *.o *.out $(EXE) 

archive:
		  zip $(USER) $(ARCHIVE_FILES) 
archive:
	zip $(USER) ets_main.c ets_options.c ets_options.h ets_type.h \
	ets_menu.c ets_menu.h ets_utility.h ets_utility.c ets_structures.h ets_structures.c Makefile README.md
