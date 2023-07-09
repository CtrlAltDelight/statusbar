SRC_C=status.c
EXECUTABLE=status
CC=gcc
CFLAGS=-O3 -std=c11 -Wall -Wextra
SHELL=/bin/bash

$(EXECUTABLE): status.c
	$(CC) $(CFLAGS) $(SRC_C) -o $(EXECUTABLE)

test: $(EXECUTABLE) statusbar.sh
	timeout 3s ./statusbar.sh
