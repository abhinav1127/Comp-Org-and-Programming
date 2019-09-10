# Makefile for Lab 23

PROGNAME = copy
SRC = copy.c
OBJ = $(SRC:%.c=%.o)
CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra -g \
         -Wstrict-prototypes -Wold-style-definition
LFLAGS =

all : $(OBJ)
	@echo "[LINK] Linking $(PROGNAME)"
	@gcc -o $(PROGNAME) $^ $(LFLAGS)

%.o : %.c
	@echo "[COMPILE] Compiling $@"
	@gcc $(CFLAGS) -c $< -o $@

clean :
	@echo "[CLEAN] Removing all compiled files"
	@rm -f *.o $(PROGNAME)
