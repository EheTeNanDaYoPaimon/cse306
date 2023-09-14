## [M1]
#  Explaint the following here
# set the working directory to 
#  ...
CUR_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

## [M2]
#  Explaint the following here
# Store the command line in a variable
# this is so that we dont have to change everywhere when we dont want to use gcc compiler
#  ...
CC = gcc
CFLAGS += -g -O2 -Werror -Wall
LDFLAGS +=

## [M3] -- REMOVED
#  ...

## [M5]
#  Explaint the following here
# Store all the source code in SRC_FILES used for reference later
#  ...
SRC_FILES = $(wildcard *.c)

## [M6]
#  Explaint the following here
# turn .c filenames to executable filenames
#  ...
EXE_FILES = $(SRC_FILES:.c=)

## [M7]
#  Explaint the following here
# all is a default target. when running make, it going to check all the executable filename and try to build them 
# this line basically will clear the need to build each of the source code file one by one
#  ...
all: $(EXE_FILES)

## [M8] -- UPDATED
#  Explaint the following here
# check if the file name end with .c and if it is then build them
# shortcut to build all the source code files using a complier, gcc in this case
#  ...
%:%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< 

## [M9]
#  Explaint the following here
# remove all the executable files using command make clean
# clean is just a name, similar to function name
#  ...
clean:
	rm -f $(EXE_FILES)

## [M10]
#  Explaint the following here
# declare all and clean process defined above as "phony" object
# this way, all and clean function will be ignored when building and will perform actions defined in makefile
#  ...
.PHONY: all clean
