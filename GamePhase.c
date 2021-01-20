#include "GamePhase.h"

t_game gameStart(t_player *Bot, t_player *ennemyBot, char *gameType, char *gameName, int *nbrCities, int *nbrTracks, int **rawTracks)
{
	t_game Game;
	waitForT2RGame(gameType, gameName, nbrCities, nbrTracks);
	*rawTracks = (int *) malloc(5*(*nbrTracks)*sizeof(int));
													//fprintf(stdout, "---------------------%i\n", *rawTracks[78]);
	t_color initialCards[4];
	Game.playingBotID = getMap(*rawTracks, Game.faceUp, initialCards);
	Game.nbrCities = *nbrCities;
	Game.nbrTracks = *nbrTracks;
	
													//fprintf(stdout, "-------------------------%i\n", *rawTracks[78]);

/*
	t_color *p_initialCards = initialCards;
	for (int i = 0; i < 4; i++)
		Bot->cards[*(p_initialCards++)]++;
	Bot->nbrCards += 4;
*/
	for (int i = 0; i < 4; i++)
		PlayerDrawColorCard(Bot, initialCards[i], 0);

	ennemyBot->nbrCards += 4; /* We count the initial nbrCards value here */

	Game.Bots[0] = Bot;
	Game.Bots[1] = ennemyBot;

	Game.TracksMap = buildTracksMap(*rawTracks, *nbrTracks, *nbrCities);

	return Game;
}

void endGame(t_return_code move, int playerTurn)
{
	if ((move == -1 && playerTurn) || (move == 1 && !playerTurn)) /* if (move = LOOSING_MOVE and playerTurn == 1 || move = WINNING_MOVE and playerTurn == 0) */
		fprintf(stdout, "We won !\n");

	else
		fprintf(stdout, "We lost !\n");
}

void buildGameType(char *gameType, char *ENNEMY_NAME, char *TIMEOUT, char *SEED, char *START, char *MAP)
{
	strcat(gameType, ENNEMY_NAME);
	strcat(gameType, " timeout=");
	strcat(gameType, TIMEOUT);
	strcat(gameType, " seed=");
	strcat(gameType, SEED);
	strcat(gameType, " start=");
	strcat(gameType, START);
	strcat(gameType, " map=");
	strcat(gameType, MAP);
}

t_track** buildTracksMap(int *rawTracks, int nbrTracks, int nbrCities)
{
	t_track **TracksMap = (t_track **) malloc(nbrCities * nbrCities * sizeof(t_track)); /* 78 different tracks */

	t_track **p_TracksMap = TracksMap;	/* if we value a NULL pointer, I want the program to exit cause it would be my bad */
	for (int i = 0; i < nbrCities * nbrCities; i++)
		*(p_TracksMap++) = NULL;


	
	//char DebugColors[10][11] = {"None", "PURPLE", "WHITE", "BLUE", "YELLOW", "ORANGE", "BLACK", "RED", "GREEN", "MULTICOLOR"};
	

	for (int i = 0; i < nbrTracks; i++)
	{
		/*
			fprintf(stdout, "#--------#\nChemin n°%i : relie ", i);
			printCity(rawTracks[5*i + 0]);
			fprintf(stdout," à ");
			printCity(rawTracks[5*i + 1]);
			fprintf(stdout, ", est composé de %i wagons et des deux couleurs %s et %s\n", rawTracks[5*i + 2], DebugColors[rawTracks[5*i + 3]], DebugColors[rawTracks[5*i + 4]]);
		*/

		TracksMap[rawTracks[5*i + 0]*nbrCities + rawTracks[5*i + 1]%nbrCities] = (t_track*) malloc(sizeof(t_track));
		TracksMap[rawTracks[5*i + 0]*nbrCities + rawTracks[5*i + 1]%nbrCities]->length = rawTracks[5*i + 2];
		TracksMap[rawTracks[5*i + 0]*nbrCities + rawTracks[5*i + 1]%nbrCities]->owner = 0;
		TracksMap[rawTracks[5*i + 0]*nbrCities + rawTracks[5*i + 1]%nbrCities]->color1 = rawTracks[5*i + 3];
		TracksMap[rawTracks[5*i + 0]*nbrCities + rawTracks[5*i + 1]%nbrCities]->color2 = rawTracks[5*i + 4];

		TracksMap[rawTracks[5*i + 1]*nbrCities + rawTracks[5*i + 0]%nbrCities] = TracksMap[rawTracks[5*i + 0]*nbrCities + rawTracks[5*i + 1]%nbrCities];
	}

	return TracksMap;
}

/*
t_move action(t_game *Game, int *start)
{
	t_move move;
	if (*start)
	{
		move.type = 4;
		return move;
	}

	char rawAction[2];
	__ACTION_PRINT__(rawAction);
	move.type = atoi(rawAction);
	return move;
}
*/

/* ----------------------------------------------------------------------------------------------------------------------------------------------------- */

int trackCounter(int *countMap, int nbrCities)
{
	int count = 0;
	for (int i = 0; i < nbrCities; i++)
		for (int j = 0; j < nbrCities; j++)
			if (countMap[i*nbrCities + j%nbrCities] > 0)
				count++;

	//printf("COUNT = %i\n", count);

	return count;
}

int *wayToFormatted(int *countMap, int nbrCities, int count)
{
	int *res = (int *) malloc((2*count + 1) * sizeof(int));

	for (int i = 0; i < 2*count + 1; i++)
		res[i] = 0;

	res[0] = count;
	count = 1;
	for (int i = 0; i < nbrCities; i++)
	{
		for (int j = 0; j < nbrCities; j++)
		{
			if (countMap[i*nbrCities + j%nbrCities] > 0)
			{
				res[count++] = i;
				res[count++] = j;
			}
		}
	}

	/*
	printf("RES[0] = %i\n", res[0]);
	for (int i = 1; i <= 2*res[0]; i += 2)
	{
		printf("VILLE 1 --> ");printCity(res[i]);printf(" || VILLE 2 --> ");printCity(res[i+1]);printf("\n");
	}
	printf("\n------------------------------\n");
	*/
	

	return res;
}

int max(t_color *list, int N, int switcher)
{
	int max = 0, index = 0;
	for (int i = 0; i < N; i++)
	{
		if (list[i] > max)
		{
			max = list[i];
			index = i;
		}
	}
	if (switcher)
		return max;
	return index;
}

int *maxs(int *countMap, int nbrCities)
{
	int max = 0;
	for (int i = 0; i < nbrCities; i++)
		for (int j = 0; j < nbrCities; j++)
			if (countMap[i*nbrCities + j%nbrCities] > max)
				max = countMap[i*nbrCities + j%nbrCities];

	int count = 0;
	for (int i = 0; i < nbrCities; i++)
	{
		for (int j = 0; j < nbrCities; j++)
		{
			if (countMap[i*nbrCities + j%nbrCities] == max)
			{
				count++;
			}
		}
	}

	int *res = wayToFormatted(countMap, nbrCities, count);

	return res;
}

int *sortMaxs(int *res, t_game *Game, int nbrCities)
{
	int temp1, temp2;

	for (int i = 1; i <= 2*res[0] - 2; i += 2)
	{
		for (int j = 1; j <= 2*res[0] - 1 - 2; j += 2)
		{
			if (Game->TracksMap[res[j]*nbrCities + res[j+1]%nbrCities]->length < Game->TracksMap[res[j+2]*nbrCities + res[j+3]%nbrCities]->length)
			{
				temp1 = res[j]; temp2 = res[j+1];
				res[j] = res[j+2]; res[j+1] = res[j+3];
				res[j+2] = temp1; res[j+3] = temp2;
			}
		}
	}

	return res;
}

int isIn(t_color element, t_color *list, int size)
{
	for (int i = 0; i < size; i++)
		if (list[i] == element)
			return 1;
	return 0;
}


t_color requiredColorList(int *majorRes, int *minorRes, t_game *Game)
{
	if (isIn(9, Game->faceUp, 5))
		return 9;

	/*
	for (int i = 0; i < 5; i++)
	{
		printf("CARTE n°%i : %i\n", i, Game->faceUp[i]);
	}
	*/

	int drawBlind = 1;
	for (int i = 1; i <= 2*majorRes[0]; i += 2)
	{
		/*
		printf("i = %i\n", i);
		printf("City i-1 : ");printCity(majorRes[i]);printf(" / City i-2 : ");printCity(majorRes[i+1]);printf("\n");
		printf("True index = %i\n", majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities);
		*/
		if (isIn(Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color1, Game->faceUp, 5)
			||
			isIn(Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color2, Game->faceUp, 5))
		{
			drawBlind = 0;
		}
	}

	for (int i = 1; i <= 2*minorRes[0]; i += 2)
	{
		if (isIn(Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color1, Game->faceUp, 5)
			||
			isIn(Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color2, Game->faceUp, 5))
		{
			drawBlind = 0;
		}
	}

	if (!drawBlind)
		return 0;

	int i=1;
	while (i++)
	{
		//TROUVER LA COULEUR A PIOCHER
		for (int i = 1; i <= 2*majorRes[0]; i += 2)
		{
			if (isIn(Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color1, Game->faceUp, 5)
				&&
				Game->Bots[0]->cards[Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color1]
				==
				Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->length - i)
				return Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color1;

			else if ((isIn(Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color2, Game->faceUp, 5)
					  &&
					  Game->Bots[0]->cards[Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color2]
					  ==
					  Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->length - i))
				return Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color2;
		}
		for (int i = 1; i <= 2*minorRes[0]; i += 2)
		{
			if (isIn(Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color1, Game->faceUp, 5)
				&&
				Game->Bots[0]->cards[Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color1]
				==
				Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->length - i)
				return Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color1;

			else if ((isIn(Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color2, Game->faceUp, 5)
					  &&
					  Game->Bots[0]->cards[Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color2]
					  ==
					  Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->length - i))
				return Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color2;
		}
	}

	return 0;
}




void action(t_game *Game, t_return_code *bothMove, t_objective obj[3], int objectiveCards[3], int *start)
{
	if (*start)
	{
		botDrawAndChooseObjectives(Game, bothMove, start);
		return;
	}

	int **ways = multipliedAppliedDijkstraAlgorithm(Game->Bots[0]->objectives, Game->Bots[0]->nbrObjectives, Game->TracksMap, Game->nbrTracks, Game->nbrCities, Game);
	/* */

	/* */
	for (int i = 0; i < Game->Bots[0]->nbrObjectives; i++)
	{
		int objectiveClaimedFlag = 1;
		for (int j = 1; j < ways[i][0]; j ++)
		{
			if (Game->TracksMap[ways[i][j]*Game->nbrCities + ways[i][j+1]%Game->nbrCities]->owner != 1)
				objectiveClaimedFlag = 0;
		}

		if (!objectiveClaimedFlag)
			continue;

		printf("\n\n\n\n\n");
		for (int j = i+1; j < Game->Bots[0]->nbrObjectives; j++)
		{
			Game->Bots[0]->objectives[i].city1 = Game->Bots[0]->objectives[j].city1;
			Game->Bots[0]->objectives[i].city2 = Game->Bots[0]->objectives[j].city2;
			Game->Bots[0]->objectives[i].score = Game->Bots[0]->objectives[j].score;
		}
		Game->Bots[0]->nbrObjectives--;

		if (!Game->Bots[0]->nbrObjectives)
		{
			botDrawAndChooseObjectives(Game, bothMove, start);
			return;
		}
	}

	int *countMap = (int *) calloc(Game->nbrCities * Game->nbrCities, sizeof(int));

	for (int i = 0; i < Game->Bots[0]->nbrObjectives; i++)
		for (int j = 1; j < (ways)[i][0]; j++)
			countMap[(ways)[i][j]*Game->nbrCities + (ways)[i][j+1]%Game->nbrCities]++;

	int *majorRes = sortMaxs(maxs(countMap, Game->nbrCities), Game, Game->nbrCities);
	int *minorRes = sortMaxs(wayToFormatted(countMap, Game->nbrCities, trackCounter(countMap, Game->nbrCities)), Game, Game->nbrCities);

	char DebugColors[10][11] = {"None", "PURPLE", "WHITE", "BLUE", "YELLOW", "ORANGE", "BLACK", "RED", "GREEN", "MULTICOLOR"};

	if (!Game->Bots[0]->replay)
	{
		for (int i = 1; i <= 2*majorRes[0]; i += 2)
		{
			if ((Game->Bots[0]->cards[Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color1]
					+
				Game->Bots[0]->cards[9]
					>
				Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->length
					||
				Game->Bots[0]->cards[Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color2]
					+
				Game->Bots[0]->cards[9]
					>
				Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->length
					||
				(max(Game->Bots[0]->cards, 9, 1) >= Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->length
					&&
				Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color1 == 0
				))
					&&
				Game->Bots[0]->nbrLocomotives
					>
				Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->length
					&&
				!Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->owner
				)
			{
				/*
				printf("ON CLAIM LA ROUTE SUIVANTE :\n");
				printCity(majorRes[i]);
				printf(" - ");
				printCity(majorRes[i+1]);
				printf(" : \n        length = %i\n", Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->length);
				printf(		"        owner = %i\n", Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->owner);
				*/
				if (Game->Bots[0]->cards[Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color1]
				+
				Game->Bots[0]->cards[9]
				>
				Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->length
				)
				{
					//printf(		"        color1 = %s\n", DebugColors[Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color1]);
					botClaimRoute(bothMove, majorRes[i], majorRes[i+1], Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color1,
					Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->length, Game);
				}
				else if (Game->Bots[0]->cards[Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color2]
				+
				Game->Bots[0]->cards[9]
				>
				Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->length
				)
				{
					//printf(		"        color2 = %s\n", DebugColors[Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color2]);
					botClaimRoute(bothMove, majorRes[i], majorRes[i+1], Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->color2,
					Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->length, Game);
				}
				else if (max(Game->Bots[0]->cards, 9, 1) >= Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->length)
				{
					t_color colorNone = max(Game->Bots[0]->cards, 9, 0);
					//printf(		"        colorNone = %s\n", DebugColors[colorNone]);
					botClaimRoute(bothMove, majorRes[i], majorRes[i+1], colorNone,
					Game->TracksMap[majorRes[i]*Game->nbrCities + majorRes[i+1]%Game->nbrCities]->length, Game);
				}
				free(ways);
				free(countMap);
				free(majorRes);
				free(minorRes);
				return;
			}
		}

		for (int i = 1; i <= 2*minorRes[0]; i += 2)
			if ((Game->Bots[0]->cards[Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color1]
					+
				Game->Bots[0]->cards[9]
					>
				Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->length
					||
				Game->Bots[0]->cards[Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color2]
					+
				Game->Bots[0]->cards[9]
					>
				Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->length
					||
				(max(Game->Bots[0]->cards, 9, 1) >= Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->length
					&&
				Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color1 == 0
				))
					&&
				Game->Bots[0]->nbrLocomotives
					>
				Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->length
					&&
				!Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->owner
				)
			{
				/*
				printf("ON CLAIM LA ROUTE SUIVANTE :\n");
				printCity(minorRes[i]);
				printf(" - ");
				printCity(minorRes[i+1]);
				printf(" : \n        length = %i\n", Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->length);
				printf(		"        owner = %i\n", Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->owner);
				*/
				if (Game->Bots[0]->cards[Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color1]
				+
				Game->Bots[0]->cards[9]
				>
				Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->length
				)
				{
					//printf(		"        color1 = %s\n", DebugColors[Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color1]);
					botClaimRoute(bothMove, minorRes[i], minorRes[i+1], Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color1,
					Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->length, Game);
				}
				else if (Game->Bots[0]->cards[Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color2]
				+
				Game->Bots[0]->cards[9]
				>
				Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->length
				)
				{
					//printf(		"        color2 = %s\n", DebugColors[Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color2]);
					botClaimRoute(bothMove, minorRes[i], minorRes[i+1], Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->color2,
					Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->length, Game);
				}
				else if (max(Game->Bots[0]->cards, 9, 1) >= Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->length)
				{
					t_color colorNone = max(Game->Bots[0]->cards, 9, 0);
					//printf(		"        colorNone = %s\n", DebugColors[colorNone]);
					botClaimRoute(bothMove, minorRes[i], minorRes[i+1], colorNone,
					Game->TracksMap[minorRes[i]*Game->nbrCities + minorRes[i+1]%Game->nbrCities]->length, Game);
				}
				free(ways);
				free(countMap);
				free(majorRes);
				free(minorRes);
				return;
			}
		}

	t_color colorToDraw;

	printf("On ne claim pas de routes. ");

	if (!(colorToDraw = requiredColorList(majorRes, minorRes, Game)))
	{
		printf("Piochons une blind carte ! ");
		botDrawBlindCard(bothMove, Game);
	}
	else
	{
		printf("Piochons une carte face recto ! ");
		botDrawCard(bothMove, colorToDraw, Game);

	}

	free(ways);
	free(countMap);
	free(majorRes);
	free(minorRes);
}

/*
void playMove(t_return_code *bothMove, t_game *Game, int objectiveCards[3], t_objective obj[3], int *start)
{
	//int city1, city2, color, nbrLocomotives, cardNumber;
	//t_color card;

	printf("Start = %i\n", *start);

	int toDo;

	if (!(toDo = action(Game, bothMove, multipliedAppliedDijkstraAlgorithm(Game->Bots[0]->objectives, Game->Bots[0]->nbrObjectives, Game->TracksMap, Game->nbrTracks, Game->nbrCities), start)))
		return;

	printf("ON NE CLAIM PAS DE ROUTE !!\ntoDo = %i\n", toDo);

	switch(toDo)
	{
		case 1:
			//botClaimRoute(Game, bothMove, TracksMap, &city1, &city2, &color, &nbrLocomotives, nbrTracks);
			return;
		case 2:
			//botDrawBlindCard(Game, bothMove, &card);
			return;
		case 3:
			//botDrawCard(Game, bothMove, &cardNumber, colors);
			return;

		case 4:
			botDrawAndChooseObjectives(Game, bothMove, obj, objectiveCards, start);
			return;
		default:return;
	}
}
*/

/* ----------------------------------------------------------------------------------------------------------------------------------------------------- */

/*
void playMove(t_move move, t_return_code *bothMove, t_game *Game, t_track **TracksMap, char colors[9][11], int objectiveCards[3], t_objective obj[3], int *start, int nbrTracks)
{
	int city1, city2, color, nbrLocomotives, cardNumber;
	t_color card;

	switch(move.type)
	{
		case 1:
			botClaimRoute(Game, bothMove, TracksMap, &city1, &city2, &color, &nbrLocomotives, nbrTracks);
			return;
		case 2:
			botDrawBlindCard(Game, bothMove, &card);
			return;
		case 3:
			botDrawCard(Game, bothMove, &cardNumber, colors);
			return;

		case 4:
			botDrawAndChooseObjectives(Game, bothMove, obj, objectiveCards, start);
			return;

		default:return;
	}
}
*/

void ennemyPlayMove(t_move ennemyMove, t_return_code *bothMove, t_game *Game, t_track **TracksMap, int nbrTracks)
{
	switch(ennemyMove.type)
	{
		case 1:
			for (int i = 0; i < ennemyMove.claimRoute.nbLocomotives; i++) /* I think I understood some data are shard with us, some other not */
			  	PlayerDropColorCard(Game->Bots[1], 0, 1);

			TracksMap[ennemyMove.claimRoute.city1*Game->nbrCities + ennemyMove.claimRoute.city2%Game->nbrCities]->owner = 2;
		case 2:
			PlayerDrawColorCard(Game->Bots[1], 0, 1);
			break;
		case 3:
			PlayerDrawColorCard(Game->Bots[1], ennemyMove.drawCard.card, 0);
			for (int i = 0; i < 5; i++)
				Game->faceUp[i] = ennemyMove.drawCard.faceUp[i];
			break;
		case 4:
			PlayerDrawObjectiveCard(Game->Bots[1], 0, 1);

		default:return ;
	}
}

void botClaimRoute(t_return_code *bothMove, int city1, int city2, t_color color, int nbrLocomotives, t_game *Game)
{
	__PLAYMOVE_PRINT_1_1__(city1, city2);
	__PLAYMOVE_PRINT_1_2__(color);
	__PLAYMOVE_PRINT_1_3__(nbrLocomotives);
	int difference = nbrLocomotives - Game->Bots[0]->cards[color];

	if (difference <= 0)
	{
		Game->Bots[0]->nbrCards -= nbrLocomotives;
		Game->Bots[0]->nbrLocomotives -= nbrLocomotives;
		Game->Bots[0]->cards[color] -= nbrLocomotives;
		difference = 0;
	}
	else
	{
		Game->Bots[0]->nbrCards -= nbrLocomotives;
		Game->Bots[0]->nbrLocomotives -= nbrLocomotives;
		Game->Bots[0]->cards[color] = 0;
		Game->Bots[0]->cards[9] -= difference;
	}

	*bothMove = claimRoute(city1, city2, color, difference);

	Game->TracksMap[city1*Game->nbrCities + city2%Game->nbrCities]->owner = 1;
}

void botDrawBlindCard(t_return_code *bothMove, t_game *Game)
{
	t_color card;
	*bothMove = drawBlindCard(&card);
	Game->Bots[0]->cards[card]++;
	Game->Bots[0]->nbrCards++;
	Game->Bots[0]->replay = 1;
}

void botDrawCard(t_return_code *bothMove, t_color color, t_game *Game)
{
	__PLAYMOVE_PRINT_3__(color);
	*bothMove = drawCard(color, Game->faceUp);
	Game->Bots[0]->cards[color]++;
	Game->Bots[0]->nbrCards++;
	if (color < 9)
		Game->Bots[0]->replay = 1;
}

void botDrawAndChooseObjectives(t_game *Game, t_return_code *bothMove, int *start)
{
	t_objective obj[3];
	int objectiveCards[3];
	*bothMove = drawObjectives(obj);

	if (*start)
		for (int i = 0; i < 3; i++)
			objectiveCards[i] = 1;
	else
	{
		//printf("IL NOUS FAUT CHOISIR DES OBJECTIFS ATTEIGNABLES !\n");
		int lengths[3];
		//char DebugColors[10][11] = {"None", "PURPLE", "WHITE", "BLUE", "YELLOW", "ORANGE", "BLACK", "RED", "GREEN", "MULTICOLOR"};
		objectiveCards[0] = 0;objectiveCards[1] = 0;objectiveCards[2] = 0;
		int **ways = multipliedAppliedDijkstraAlgorithm(obj, 3, Game->TracksMap, Game->nbrTracks, Game->nbrCities, Game);

		for (int i = 0; i < 3; i++)
		{
			int length = ways[i][ways[i][0] + 1];
			int difference;
			//printf("initial required color cards : %i\n", length);
			for (int j = 1; j < 10; j++)
			{
				//printf("number of %s cards : %i\n", DebugColors[j], ways[i][ways[i][0] + 1 + j]);
				difference = ways[i][ways[i][0] + 1 + j] - Game->Bots[0]->cards[j];
				if (difference < 0)
					difference = 0;
				length -= difference;
			}
			//printf("FINAL DISTANCE TO REACH WITHOUT ENOUGH COLOR MOTHER RUSTER = %i\n", length);
			lengths[i] = length;
		}

		int min = 42;
		int minIndex = 42;
		for (int i = 0; i < 3; i++)
		{
			if (lengths[i] < min)
			{
				min = lengths[i];
				minIndex = i;	
			}
		}

		//printf("minIndex = %i\n", minIndex);

		objectiveCards[minIndex] = 1;

		for (int i = 0; i < 3; i++)
		{
			if (lengths[i] < min && !objectiveCards[i] && lengths[i] < 5)
				objectiveCards[i] = 1;

		}


		free(ways[0]);
		free(ways[1]);
		free(ways);
	}

	for (int i = 0; i < 3; i++)
		if (objectiveCards[i])
			PlayerDrawObjectiveCard(Game->Bots[0], &obj[i], 0);
	*bothMove = chooseObjectives(objectiveCards);

}

int distanceMini(int *D, int *visited, int nbrCities)
{
	int min = 42, indice_min = 0;

	for (int i=0; i<nbrCities; i++)
	{
		//printf("%i\n", D[i]);
		if (!visited[i] && D[i]<min)
		{
			min = D[i];
			indice_min = i;
		}
	}

	return indice_min;
}

int **DijkstraAlgorithm(int src, t_track **TracksMap, int nbrTracks, int nbrCities)
{
	//char DebugColors[10][11] = {"None", "PURPLE", "WHITE", "BLUE", "YELLOW", "ORANGE", "BLACK", "RED", "GREEN", "MULTICOLOR"};
	int *G = (int *) malloc (nbrCities * nbrCities * sizeof(int));
	for (int i = 0; i < nbrCities; i++)
	{
		for (int j = 0; j < nbrCities; j++)
		{
			if (TracksMap[i*nbrCities + j%nbrCities] != NULL)
			{
				switch(TracksMap[i*nbrCities + j%nbrCities]->owner)
				{
					case 0:
						G[i*nbrCities + j%nbrCities] = TracksMap[i*nbrCities + j%nbrCities]->length;
						break;

					case 1:
						G[i*nbrCities + j%nbrCities] = 0;
						break;

					case 2:
						G[i*nbrCities + j%nbrCities] = 9999;
						break;

					default:
						fprintf(stdout, "Error : Le possesseur de la route est incorrectement défini !\n");
						return NULL;
				}
				
				/*
					printCity(i);
					fprintf(stdout, " <=> ");
					printCity(j);
					fprintf(stdout, ": %i wagons\n", G[i*nbrCities + j%nbrCities]);
				*/
			}
			else
				G[i*nbrCities + j%nbrCities] = 9999;
		}
	}



	int *D = (int *) malloc (nbrCities * sizeof(int));
	int *prec = (int *) malloc (nbrCities * sizeof(int));
	int *visited = (int *) malloc (nbrCities * sizeof(int));

	for (int i=0; i < nbrCities; i++)
	{
		D[i] = 9999;
		visited[i] = 0;
	}

	D[src] = 0;
	int u;

	for (int i = 0; i < nbrCities; i++)
	{
		u = distanceMini(D, visited, nbrCities);
		visited[u] = 1;
		for (int v = 0; v < nbrCities; v++)
		{
			if ((!visited[v])
			 && (G[u*nbrCities + v%nbrCities] != 9999)
			 && (D[u] + G[u*nbrCities + v%nbrCities] < D[v])
			 )
			{
				D[v] = D[u] + G[u*nbrCities + v%nbrCities];
				prec[v] = u;
			}
		}
	}

	free(G);
	free(visited);

	int **res = (int **) malloc(2 * sizeof(int *));
	res[0] = D;
	res[1] = prec;
	/*
		printf("Départ :\n");
		printCity(src);
		printf("D :\n");
		for (int i = 0; i < nbrCities; i++)
		{
			printf("Plus courte distance entre ");printCity(src);printf(" et ");printCity(i);printf(" : %i [prec[i] = ", D[i]);printCity(prec[i]);printf("\n");
		}
	*/
	return res;
}

int *appliedDijkstraAlgorithm(int src, int dest, t_track **TracksMap, int nbrTracks, int nbrCities, t_game *Game)
{
	int nbrOfCheckpoint = 0;
	int length = 0;
	int *way = (int *) malloc(nbrCities * sizeof(int));
	int **res = DijkstraAlgorithm(src, TracksMap, nbrTracks, nbrCities);
	way[nbrOfCheckpoint] = dest;

	do {
		way[++nbrOfCheckpoint] = res[1][dest];
		dest = res[1][dest];;
	} while (dest != src);

	int *reversedWay = (int *) malloc((nbrOfCheckpoint+12) * sizeof(int));
	for (int i = 0; i < nbrOfCheckpoint+12; i++)
		reversedWay[i] = 0;

	reversedWay[0] = nbrOfCheckpoint+1;

	for (int i = 1; i <= nbrOfCheckpoint + 1; i++)
		reversedWay[i] = way[nbrOfCheckpoint - i + 1];

	//printf("CHEMIN DE %i ETAPES DANS LE SENS :\n", reversedWay[0]-1);
	for (int i=1; i <= reversedWay[0]; i++)
	{
		//printCity(reversedWay[i]);printf(" / ");
		if (i > 1)
		{
			switch(TracksMap[reversedWay[i-1]*nbrCities + reversedWay[i]%nbrCities]->owner)
			{
				case 0:
					length += TracksMap[reversedWay[i-1]*nbrCities + reversedWay[i]%nbrCities]->length;
					if (!TracksMap[reversedWay[i-1]*nbrCities + reversedWay[i]%nbrCities]->color1)
						continue;
					else if (TracksMap[reversedWay[i-1]*nbrCities + reversedWay[i]%nbrCities]->color2 && Game->Bots[0]->cards[TracksMap[reversedWay[i-1]*nbrCities + reversedWay[i]%nbrCities]->color1] < Game->Bots[0]->cards[TracksMap[reversedWay[i-1]*nbrCities + reversedWay[i]%nbrCities]->color2])
						reversedWay[nbrOfCheckpoint+2 + TracksMap[reversedWay[i-1]*nbrCities + reversedWay[i]%nbrCities]->color2] += TracksMap[reversedWay[i-1]*nbrCities + reversedWay[i]%nbrCities]->length;
					else
						reversedWay[nbrOfCheckpoint+2 + TracksMap[reversedWay[i-1]*nbrCities + reversedWay[i]%nbrCities]->color1] += TracksMap[reversedWay[i-1]*nbrCities + reversedWay[i]%nbrCities]->length;
					break;
				case 1:
					break;
				case 2:
					printf("Okay il y a clairement une couille dans l'algo là");
					length += 808584657378; //En ascii, toutes les paires de chiffres forment une lettre majuscule (sauvez moi svp)
			}
		}
	}
	reversedWay[nbrOfCheckpoint+2] = length;
	//printf("LA TAILLE TOTALE DU PARCOURS EST DE : %i, SON INDEX EST DE : %i, ET RES[0] = %i\n", length, nbrOfCheckpoint+2, reversedWay[0]);
	//printf("\n");

	/*	DEBUG	*/
	for (int i=1; i < reversedWay[0]; i++)
	{
		if (TracksMap[reversedWay[i]*nbrCities + reversedWay[i+1]%nbrCities]->owner == 1)
		{
			//printf("La route entre ");printCity(reversedWay[i]);printf(" et ");printCity(reversedWay[i+1]);printf(" a déjà été claim !\n");
		}
	}
	/*	-----	*/
	
	free(res);
	return reversedWay;
}

int **multipliedAppliedDijkstraAlgorithm(t_objective *objectives, int nbrObjectives, t_track **TracksMap, int nbrTracks, int nbrCities, t_game *Game)
{
	int **ways = (int **) malloc (nbrObjectives * sizeof(int));

	for (int i = 0; i < nbrObjectives; i++)
	{
		ways[i] = appliedDijkstraAlgorithm(objectives[i].city1, objectives[i].city2, TracksMap, nbrTracks, nbrCities, Game);
	}
	return ways;
}

/*
void __ACTION_PRINT__(char *rawAction)
{
	fprintf(stdout, "Rappel des actions :\n1. Prendre possession d’une route (fonction claimRoute)\n2. Prendre une carte de la pioche (fonction drawBlindCard)\n3. Prendre une carte face visible (fonction drawCard)\n4. Prendre des cartes objectifs (fonction drawObjectives et ChooseObjectives)\n");
	fprintf(stdout, "Faites attention, si vous rejouez, toutes les actions ne vous sont pas autorisées.\n");
	fprintf(stdout, "Entrer l'action à mener : ");
	fscanf(stdin, "%s", rawAction);
	fprintf(stdout, "Chaîne entrée : %s ET conversion atoi : %i\n", rawAction, atoi(rawAction));
}
*/



void __ACTION_PRINT__()
{
	fprintf(stdout, "Rappel des actions :\n1. Prendre possession d’une route (fonction claimRoute)\n2. Prendre une carte de la pioche (fonction drawBlindCard)\n3. Prendre une carte face visible (fonction drawCard)\n4. Prendre des cartes objectifs (fonction drawObjectives et ChooseObjectives)\n");
	fprintf(stdout, "Faites attention, si vous rejouez, toutes les actions ne vous sont pas autorisées.\n");
	fprintf(stdout, "Entrer l'action à mener : ");
}

/*
void __PLAYMOVE_PRINT_1_1__(int *city1, int *city2)
{
	fprintf(stdout, "Rappel des villes et de leurs identifiants :\nID : 0 --> Vancouver\nID : 1 --> Seattle\nID : 2 --> Portland\nID : 3 --> San Francisco\nID : 4 --> Los Angeles\nID : 5 --> Phoenix\nID : 6 --> Las Vegas\nID : 7 --> Salt Lake City\nID : 8 --> Calgary\nID : 9 --> Helena\nID : 10 --> Winnipeg\nID : 11 --> Denver\nID : 12 --> Santa Fe\nID : 13 --> El Paso\nID : 14 --> Houston\nID : 15 --> Dallas\nID : 16 --> Oklahoma City\nID : 17 --> Kansas City\nID : 18 --> Omaha\nID : 19 --> Duluth\nID : 20 --> Sault St. Marie\nID : 21 --> Chicago\nID : 22 --> Saint Louis\nID : 23 --> Little Rock\nID : 24 --> New Orleans\nID : 25 --> Atlanta\nID : 26 --> Nashville\nID : 27 --> Pittsburgh\nID : 28 --> Toronto\nID : 29 --> Montréal\nID : 30 --> Boston\nID : 31 --> New York\nID : 32 --> Washington\nID : 33 --> Raleigh\nID : 34 --> Charleston\nID : 35 --> Miami\n");
	fprintf(stdout, "Relier quelles villes ? (séparées d'un espace) : ");
	fscanf(stdin, "%i %i", city1, city2);
	fprintf(stdout, "Les deux villes entrées sont : ");
	printCity(*city1);
	fprintf(stdout, ", et ");
	printCity(*city2);
	fprintf(stdout, "\n");
}
*/

void __PLAYMOVE_PRINT_1_1__(int city1, int city2)
{
	fprintf(stdout, "Le bot a décidé de rellier ");
	printCity(city1);
	fprintf(stdout, " à ");
	printCity(city2);
	fprintf(stdout, ". ");
}

/*
void __PLAYMOVE_PRINT_1_2__(int *color)
{
	fprintf(stdout, "Rappel des couleurs et de leurs identifiants :\nID : 0 --> NONE\nID : 1 --> PURPLE\nID : 2 --> WHITE\nID : 3 --> BLUE\nID : 4 --> YELLOW\nID : 5 --> ORANGE\nID : 6 --> BLACK\nID : 7 --> RED\nID : 8 --> GREEN\nID : 9 --> MULTICOLOR\n");
	fprintf(stdout, "Quelle est la couleur des wagons à utiliser ? : ");
	fscanf(stdin, "%i", color);
	fprintf(stdout, "La couleur entrée est : %i\n", *color);
}
*/

void __PLAYMOVE_PRINT_1_2__(t_color color)
{
	char DebugColors[10][11] = {"None", "PURPLE", "WHITE", "BLUE", "YELLOW", "ORANGE", "BLACK", "RED", "GREEN", "MULTICOLOR"};
	fprintf(stdout, "Le bot a décidé d'utiliser la couleur %s. ", DebugColors[color]);
}

/*
void __PLAYMOVE_PRINT_1_3__(int *nbrLocomotives)
{
	fprintf(stdout, "Rappel : le nombre de locomotives nécessaire peut aller de 1 à 6.\n");
	fprintf(stdout, "Quel est le nombre de locomotives requis ? : ");
	fscanf(stdin, "%i", nbrLocomotives);
	fprintf(stdout, "Le nombre de locomotives entré est : %i\n", *nbrLocomotives);
}
*/

void __PLAYMOVE_PRINT_1_3__(int nbrWagons)
{
	fprintf(stdout, "Le bot utilise donc %i wagons.", nbrWagons);
}

/*
void __PLAYMOVE_PRINT_3__(int *cardNumber, char colors[9][11], t_color faceUp[5])
{
	fprintf(stdout, "Rappel des 5 cartes face visible :\n");
	for (int i = 0; i < 5; i++)
		fprintf(stdout, "Carte n°%i : %s\n", i, colors[faceUp[i] - 1]); // -1 Par ce qu'une carte ne peut pas être grise
	fprintf(stdout, "Rappel des couleurs et de leurs identifiants :\nID : 0 --> NONE\nID : 1 --> PURPLE\nID : 2 --> WHITE\nID : 3 --> BLUE\nID : 4 --> YELLOW\nID : 5 --> ORANGE\nID : 6 --> BLACK\nID : 7 --> RED\nID : 8 --> GREEN\nID : 9 --> MULTICOLOR\n");
	fprintf(stdout, "Piocher quelle carte ? (entrer l'identifiant de la couleur de la carte choisie) : ");
	fscanf(stdin, "%i", cardNumber);
	fprintf(stdout, "Vous avez pioché la carte de couleur %s\n", colors[*cardNumber]);
}
*/

void __PLAYMOVE_PRINT_3__(int color)
{
	char DebugColors[10][11] = {"None", "PURPLE", "WHITE", "BLUE", "YELLOW", "ORANGE", "BLACK", "RED", "GREEN", "MULTICOLOR"};
	fprintf(stdout, "Le bot a décidé de piocher la carte %s.", DebugColors[color]);
}

/*
void __PLAYMOVE_PRINT_4__(t_objective obj[3], int objectiveCards[3], int *start)
{
	fprintf(stdout, "Vous avez pioché les cartes objectifs suivantes : \n");
	for (int i = 0; i < 3; ++i)
	{
		fprintf(stdout, "Objectif n°%i : ", i);
		printCity(obj[i].city1);
		fprintf(stdout, " - ");
		printCity(obj[i].city2);
		fprintf(stdout, " / score --> %i\n", obj[i].score);
	}
	if (*start)
		fprintf(stdout, "Il vous faut garder au moins deux carte.\n");
	else
		fprintf(stdout, "Il vous faut garder au moins une carte.\n");
	while (1)
	{
		fprintf(stdout, "Quelles cartes objectifs garder ? Indiquez 0 ou 1 pour chacune d'entre elles, séparées toutes les trois d'un espace : ");
		fscanf(stdin, "%i %i %i", objectiveCards, objectiveCards + 1, objectiveCards + 2); //= &objectiveCards[0-2]
		fprintf(stdout, "Vous avez fait les choix suivants : %i, %i, %i\n", *objectiveCards, *(objectiveCards + 1), *(objectiveCards + 2));
		if (((objectiveCards[0] || objectiveCards[1] || objectiveCards[2]) && !(*start)) || ((objectiveCards[0] + objectiveCards[1] + objectiveCards[2] > 1) && (*start)))
			break;
		fprintf(stdout, "Vous n'avez pas gardé suffisament de cartes !\n");
	}

	if (*start)
		*start = 0;
}
*/

void __PLAYMOVE_PRINT_4__(t_objective obj[3], int objectiveCards[3], int *start)
{
	fprintf(stdout, "Vous avez pioché les cartes objectifs suivantes : \n");
	for (int i = 0; i < 3; ++i)
	{
		fprintf(stdout, "Objectif n°%i : ", i);
		printCity(obj[i].city1);
		fprintf(stdout, " - ");
		printCity(obj[i].city2);
		fprintf(stdout, " / score --> %i\n", obj[i].score);
	}

	if (*start)
	{
		*start = 0;
		for (int i = 0; i < 3; i++)
			objectiveCards[i] = 1;
	}
	else
	{
		/*
			Choose and Good
		*/
	}

}