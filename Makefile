## [M1]
#  Explaint the following here
#  ...
CUR_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

## [M2]
#  Explaint the following here
#  ...
CC = gcc
CFLAGS += -g -O2 -Werror -Wall
LDFLAGS +=

## [M3] -- REMOVED
#  ...

## [M5]
#  Explaint the following here
#  ...
SRC_FILES = $(wildcard *.c)

## [M6]
#  Explaint the following here
#  ...
EXE_FILES = $(SRC_FILES:.c=)

## [M7]
#  Explaint the following here
#  ...
all: $(EXE_FILES)

## [M8] -- UPDATED
#  Explaint the following here
#  ...
%:%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< 

## [M9]
#  Explaint the following here
#  ...
clean:
	rm -f $(EXE_FILES)

## [M10]
#  Explaint the following here
#  ...
.PHONY: all clean
