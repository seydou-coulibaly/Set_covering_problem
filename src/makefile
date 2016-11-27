DEBUG=yes
CC=gcc
ifeq ($(DEBUG),yes)
	CFLAGS= -W -Wall -g -std=c99
	LDFLAGS= -lm
else
	CFLAGS= -W -Wall -ansi -pedantic -std=c99
	LDFLAGS=
endif
EXEC= main
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)
ifeq ($(DEBUG),yes)
	@echo "Génération en mode debug"
else
	@echo "Génération en mode release sans debug"
endif

main: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c -I/. $< $(CFLAGS)
test: main
	./$(EXEC)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
