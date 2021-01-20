#ifndef __GAME_H__
#define __GAME_H__

#include <stdlib.h>
#include <stdio.h>
#include "Player.h"
#include "Track.h"
#include "TicketToRideAPI.h"

typedef struct {
	int playingBotID;
	int nbrCities;
	int nbrTracks;
	t_color faceUp[5];
	t_track **TracksMap;
	t_player *Bots[2];
} t_game;

void printGame(t_game *Game, char *BOT_NAME, char *ENNEMY_NAME, char colors[9][11]);

#endif