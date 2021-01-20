#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "GamePhase.h"
#include "TicketToRideAPI.h"

#include <sys/types.h>
#include <sys/wait.h>

#define SERVEUR_ADRESS "li1417-56.members.linode.com"
#define SERVEUR_PORT "1234"

#define ENNEMY_NAME "NICE_BOT"
#define BOT_NAME "Kant1s_bot_Discount"
#define TIMEOUT "30"
#define SEED "88"
#define START "0"
#define MAP "USA"

extern int debug;

int main(int argc, char const *argv[])
{
	/*
		DEBUG AREA
	*/
	//debug=2;
	/* ####################################### */



	/*
		TESTING AREA
	*/

	
	/*char colorCardsOrder[108];
	fprintf(stdout, "ARGC : %i\n", argc);
	
	if (argc == 1)
	{
	
		char *args[6] = {
			"test2.out",
			SERVEUR_ADRESS,
			SERVEUR_PORT,
			SEED,
			MAP,
			NULL
		};

		pid_t pid = fork();

		if (pid == -1)
		{
			fprintf(stderr, "ERROR : unknown problem.\n");
			exit(EXIT_FAILURE);
		}

		if (!pid)
		{
	    	execv("test2.out", args);
			fprintf(stderr, "ERROR : program B not found.\n");
			exit(EXIT_FAILURE);
		}

		sleep(15);
		fprintf(stdout, "The program can go on.\n");

		wait(NULL);
		
		exit(EXIT_SUCCESS);
	
	}
	

	strcpy(colorCardsOrder, argv[1]);
	fprintf(stdout, "\n\n\nAU FINAL, NOUS AVONS : %s\n\n\n", colorCardsOrder);

	sleep(5);*/

	
	

	/* #################################"" */

	/*
		CONNECTING TO THE SERVER
	*/
	//connectToServer(SERVEUR_ADRESS, SERVEUR_PORT, BOT_NAME);
	connectToServer(SERVEUR_ADRESS, (int)strtol(SERVEUR_PORT, NULL, 10), BOT_NAME);
	fprintf(stdout, "OK\n");
	/* ##################################################### */

	/*
		VARIABLES
	*/
	/*  ###################################################################### */
	/*  #--------------------------GAME SETUP VARIABLES----------------------# */
	/*  ###################################################################### */
	/*
		__GAMETYPE_SIZE_CALCULATION__
	*/
	/* 9 + MAX_ENNEMY_NAME_SIZE + 9 + MAX_UNSIGNED_INT_SIZE + 6 + MAX_UNSIGNED_INT_SIZE + 13 + MAX_COUNTRY_NAME_SIZE + 1 */
	/* 9 + ? + 9 + 10 + 6 + 9 + 13 + ? + 1*/
	/* 57 + MAX_ENNEMY_NAME_SIZE + MAX_COUNTRY_NAME_SIZE */
	/* 57 + =?20 + =?20 */
	/* 97 */
	/* ############################################################################################################## */
	//char gameType[16] = "TOURNAMENT EISE3";
	char gameType[97] = "TRAINING ";	
	buildGameType(gameType, ENNEMY_NAME, TIMEOUT, SEED, START, MAP);
	char gameName[20] = "";
	int nbrCities = 0;
	int nbrTracks = 0;
	int *rawTracks = NULL;
	t_return_code bothMove = NORMAL_MOVE;
	//char colors[9][11] = {"PURPLE", "WHITE", "BLUE", "YELLOW", "ORANGE", "BLACK", "RED", "GREEN", "MULTICOLOR"};
	int start = 1;
	/* _______________________________________________________________________ */
	/*  ###################################################################### */
	/*  #------------------------------BOT VARIABLES-------------------------# */
	/*  ###################################################################### */
	int objectiveCards[3] = {0,0,0};
	t_objective obj[3];
	t_player Bot = Player(&Bot);
	/* _______________________________________________________________________ */
	/*  ###################################################################### */
	/*  #----------------------------ENNEMY VARIABLES------------------------# */
	/*  ###################################################################### */
	t_move ennemyMove;
	int ennemyReplay = 0;
	t_player ennemyBot = Player(&ennemyBot);
	/* " "###################################################################### */



	/*
		INITIALIZING THE GAME
	*/
	t_game Game = gameStart(&Bot, &ennemyBot, gameType, gameName, &nbrCities, &nbrTracks, &rawTracks);
	/* ################################################### */



	/*
		MAIN LOOP
	*/

	printf("ALLEZ C'EST TIPAR\n");

	while (!bothMove) /* while (bothMove == NORMAL_MOVE) */
	{
		if (Game.playingBotID)
		{
			fprintf(stdout, "C'est à l'adversaire de jouer ! ");
			bothMove = getMove(&ennemyMove, &ennemyReplay);
			fprintf(stdout, "L'adversaire chosit le coup : %i. ", ennemyMove.type);

			ennemyPlayMove(ennemyMove, &bothMove, &Game, Game.TracksMap, nbrTracks);

			fprintf(stdout, "L'adversaire joue le coup : %i\n", ennemyMove.type);

			if (bothMove)
				break;

			if (ennemyReplay)
			{
				bothMove = getMove(&ennemyMove, &ennemyReplay);
				ennemyReplay = 0; /* Supposed unnecessary */
				ennemyPlayMove(ennemyMove, &bothMove, &Game, Game.TracksMap, nbrTracks);
			}
		}

		else
		{
		/*
			USER CHOICE
		*/
			//int **ways = multipliedAppliedDijkstraAlgorithm(Bot.objectives, Bot.nbrObjectives, Game.TracksMap, nbrTracks, nbrCities);
			//playMove((move = action(&Game, &ways, &start)), &bothMove, &Game, Game.TracksMap, colors, objectiveCards, obj, &start, nbrTracks);
			action(&Game, &bothMove, obj, objectiveCards, &start);

			if (bothMove)
				break;

			if (Bot.replay)
			{
				action(&Game, &bothMove, obj, objectiveCards, &start);
				//playMove((move = action(&Game, &ways, &start)), &bothMove, &Game, Game.TracksMap, colors, objectiveCards, obj, &start, nbrTracks);
				Bot.replay = 0;
			}

			printf("\n");
			//(t_objective *objectives, int nbrObjectives, t_track **TracksMap, int nbrTracks, int nbrCities)

			/*sendComment("JPP M'SIEUR HILAIRE LAISSEZ MON BOT AVOIR SON NOM SANS LE PID JE VOUS EN SUPPLIE, CE NUMERO N'EST\n");
			sendComment("PAS CE QUI LE DEFINIT, NOUS SOMMES EN 2020 LES MENTALITES ONT CHANGE, IL EST NON BINAIRE ET ENTIER\n");
			sendComment("IL FAUT CESSER DE STIGMATISER LES APPLICATEURS D'INSTRUCTIONS SIMPLEMENT PAR CE QU'ILS SONT CONS,\n");
			sendComment("ET CHERCHER AU DELA D'UNE INEXISTANTE INTELLIGENCE UNE VERTUE DE DEVOTION INEGALEE, PROPRE A MON\n");
			sendComment("BOT. SON NOM EST 'Kant1s_bot', pas 'Kant1s_bot'XXXX. Merci. Cordiallement, envoyé depuis le bot.\n");*/
		}

		if (bothMove)
			break;

		Game.playingBotID = !Game.playingBotID;

		if (start)
			start = 0;
		else
		{
			printMap();
			//printGame(&Game, BOT_NAME, ENNEMY_NAME, colors);
		}

		/*
			__U_PRINT__
		*/
		/* #################################################################################### */

	}

	endGame(bothMove, Game.playingBotID);

	closeConnection();

	return EXIT_SUCCESS;
}