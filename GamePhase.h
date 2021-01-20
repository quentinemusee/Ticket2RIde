#ifndef __GAME_PHASE_H__
#define __GAME_PHASE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Player.h"
#include "Track.h"
#include "Game.h"
#include "TicketToRideAPI.h"

t_game gameStart(t_player *Bot, t_player *ennemyBot, char *gameType, char *gameName, int *nbrCities, int *nbrTracks, int **rawTracks);

void endGame(t_return_code move, int playerTurn);

void buildGameType(char *gameType, char *ENNEMY_NAME, char *TIMEOUT, char *SEED, char *START, char *MAP);
t_track** buildTracksMap(int *rawTracks, int nbrTracks, int nbrCities);

void action(t_game *Game, t_return_code *bothMove, t_objective obj[3], int objectiveCards[3], int *start);

//void playMove(t_move move, t_return_code *bothMove, t_game *Game, t_track **TracksMap, char colors[9][11], int objectiveCards[3], t_objective obj[3], int *start, int nbrTracks);
void playMove(t_return_code *bothMove, t_game *Game, int objectiveCards[3], t_objective obj[3], int *start);
void ennemyPlayMove(t_move ennemyMove, t_return_code *bothMove, t_game *Game, t_track **TracksMap, int nbrTracks);

//void botClaimRoute(t_game *Game, t_return_code *bothMove, t_track **TracksMap, int *city1, int *city2, int *color, int *nbrLocomotives, int nbrTracks);
void botClaimRoute(t_return_code *bothMove, int city1, int city2, t_color color, int nbrLocomotives, t_game *Game);
//void botDrawBlindCard(t_game *Game, t_return_code *bothMove, t_color *card);
void botDrawBlindCard(t_return_code *bothMove, t_game *Game);
//void botDrawCard(t_game *Game, t_return_code *bothMove, int *cardNumber, char colors[9][11]);
void botDrawCard(t_return_code *bothMove, t_color color, t_game *Game);
void botDrawAndChooseObjectives(t_game *Game, t_return_code *bothMove, int *start);

int **DijkstraAlgorithm(int srcIndex, t_track **TracksMap, int nbrTracks, int nbrCities);
int *appliedDijkstraAlgorithm(int src, int dest, t_track **TracksMap, int nbrTracks, int nbrCities, t_game *Game);
int **multipliedAppliedDijkstraAlgorithm(t_objective *objectives, int nbrObjectives, t_track **TracksMap, int nbrTracks, int nbrCities, t_game *Game);

//void __ACTION_PRINT__(char *rawAction);
void __ACTION_PRINT__();
void __PLAYMOVE_PRINT_1_1__(int city1, int city2);
void __PLAYMOVE_PRINT_1_2__(t_color color);
void __PLAYMOVE_PRINT_1_3__(int nbrWagons);
void __PLAYMOVE_PRINT_3__(int color);
void __PLAYMOVE_PRINT_4__(t_objective obj[3], int objectiveCards[3], int *start);

#endif