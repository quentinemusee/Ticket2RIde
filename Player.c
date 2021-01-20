#include "Player.h"

t_player Player(t_player *Bot)
{
	Bot->nbrLocomotives = 45;
	Bot->nbrCards = 0;
	Bot->nbrObjectives = 0;
	Bot->replay = 0;
	for (int i = 0; i < 10; i++)
		Bot->cards[i] = 0;

	return *Bot;
}

void printPlayer(t_player *Bot, char *BOT_NAME, char colors[9][11], int botSwitch)
{
	fprintf(stdout, "BOT %s :\n  *Nbr :\n    nbrLocomotives : %i\n    nbrCards : %i\n    nbrObjectives : %i\n", BOT_NAME, Bot->nbrLocomotives, Bot->nbrCards, Bot->nbrObjectives);
	if (!botSwitch)
	{
		fprintf(stdout, "  *Cartes :\n");

		for (int i = 1; i < 10; i++)
			fprintf(stdout, "    nbr%sCards : %i \n", colors[i-1], Bot->cards[i]);

		fprintf(stdout, "  *Objectives :\n");

		for (int i = 0; i < Bot->nbrObjectives; i++)
		{
			fprintf(stdout, "    Objectif n°%i : ", i);
			printCity(Bot->objectives[i].city1);
			fprintf(stdout, " - ");
			printCity(Bot->objectives[i].city2);
			fprintf(stdout, " / score --> %i\n", Bot->objectives[i].score);
		}
	}
}

void PlayerDrawColorCard(t_player *Bot, t_color card, int botSwitch)
{
	if (!botSwitch)
		Bot->cards[card]++;
	Bot->nbrCards++;
}

void PlayerDrawObjectiveCard(t_player *Bot, t_objective *objective, int botSwitch)
{
	if (!botSwitch)
		Bot->objectives[Bot->nbrObjectives++] = *objective;
	else
		Bot->nbrObjectives++;
	/*
		Bot->objectives[Bot->nbrObjectives].city1 = objective->city1;
		Bot->objectives[Bot->nbrObjectives].city2 = objective->city2;
		Bot->objectives[Bot->nbrObjectives++].score = objective->score;
	*/
}

void PlayerDropColorCard(t_player *Bot, t_color *card, int botSwitch)
{
	if (!botSwitch)
		Bot->cards[*card]--;
	Bot->nbrCards--;
	Bot->nbrLocomotives--;
}

void PlayerDropObjectiveCard(t_player *Bot, t_objective *objective, int botSwitch) /* botSwitch is not used but still there */
{
	Bot->nbrObjectives--;
	/*
		Bot->objectives[Bot->nbrObjectives].city1 = objective->city1;
		Bot->objectives[Bot->nbrObjectives].city2 = objective->city2;
		Bot->objectives[Bot->nbrObjectives++].score = objective->score;
	*/
}