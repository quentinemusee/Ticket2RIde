# Modèle de fichier Makefile, à adapter pour le TP

# options de compilation
CC = gcc
CCFLAGS = -Wall
LIBS = 
LIBSDIR = -lm

# fichiers du projet
SRC = main.c TicketToRideAPI.c clientAPI.c Player.c GamePhase.c Game.c Track.c
OBJ = $(SRC:.c=.o)
EXEC = main.out


# règle initiale
all: $(EXEC)

# dépendance des .h

Player.o: Player.h TicketToRideAPI.h Track.h

Track.o: Track.h TicketToRideAPI.h

GamePhase.o: GamePhase.h Player.h Track.h TicketToRideAPI.h

Game.o: Game.h Player.h TicketToRideAPI.h

TicketToRideAPI.o: TicketToRideAPI.h clientAPI.h

clientAPI.c: clientAPI.h

# règles de compilation
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
	
# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBS) $(LIBSDIR)

# règles supplémentaires
clean:
	rm -f *.o
mproper:
	rm -f $(EXEC) *.o