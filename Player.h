#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdlib.h>
#include <stdio.h>
#include "TicketToRideAPI.h"

typedef struct {
	int nbrLocomotives;
	int nbrCards;
	int nbrObjectives;
	int replay;
	t_color cards[10]; /* 0 --> PURPLE nbr, 1 --> WHITE nbr, ... cf t_color enum */
	t_objective objectives[20]; /* Supposed no more than 20 */
} t_player;

t_player Player(t_player *Bot);

void printPlayer(t_player *Bot, char *BOT_NAME, char colors[9][11], int botSwitch);

void PlayerDrawColorCard(t_player *Bot, t_color card, int botSwitch);
void PlayerDrawObjectiveCard(t_player *Bot, t_objective *objective, int botSwitch);
void PlayerDropColorCard(t_player *Bot, t_color *card, int botSwitch);
void PlayerDropObjectiveCard(t_player *Bot, t_objective *objective, int botSwitch);

#endif