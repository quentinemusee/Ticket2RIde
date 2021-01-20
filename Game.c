#include "Game.h"

void printGame(t_game *Game, char *BOT_NAME, char *ENNEMY_NAME, char colors[9][11])
{
	fprintf(stdout, "GAME :\n  playingBotID : %i\n", Game->playingBotID);
	for (int i = 0; i < 5; i++)
		fprintf(stdout, "  faceUp card n°%i : %s \n", i, colors[Game->faceUp[i] - 1]);
	/*
		__PLATEAu_PLACEHOLDER__
	*/
	printPlayer(Game->Bots[0], BOT_NAME, colors, 0);
	fprintf(stdout, "-----------------------------------\n");
	printPlayer(Game->Bots[1], ENNEMY_NAME, colors, 1);
	fprintf(stdout, "\n");
}