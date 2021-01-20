#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "GamePhase.h"
#include "TicketToRideAPI.h"

#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	char SERVEUR_ADRESS[30];
	char SERVEUR_PORT[5];
	char SEED[9];
	char MAP[20];
	strcpy(SERVEUR_ADRESS, argv[1]);
	strcpy(SERVEUR_PORT, argv[2]);
	strcpy(SEED, argv[3]);
	strcpy(MAP, argv[4]);

	char BOT_NAME[20] = "azertyuiop";
	t_color cards[108];
	int cardsCounter = 0;

	fprintf(stdout, "The child received :\n");
	fprintf(stdout, "SERVEUR_ADRESS : %s\n", argv[1]);
	fprintf(stdout, "SERVEUR_PORT : %s\n", argv[2]);
	fprintf(stdout, "SERVEUR_SEED : %s\n", argv[3]);
	fprintf(stdout, "SERVEUR_MAP : %s\n", argv[4]);
	/* ##########################################" */



	////////////////////////////////////////////////
	////////////////////////////////////////////////
	////         ////////////////       ////////////
	////  ////// ///////////////  ///   ////////////
	////  /////////////////////  ////   ////////////
	////  ////////////////////  /////   ////////////
	////  ///       /////////////////   ////////////
	////  /////   ///////////////////   ////////////
	////  /////   ///////////////////   ////////////
	////           ///////////                  ////
	////////////////////////////////////////////////
	////////////////////////////////////////////////
	////////////////////////////////////////////////

/*______________________________________________________________________________________________________*/

	/*
		CONNECTING TO THE SERVER
	*/
	//connectToServer(SERVEUR_ADRESS, SERVEUR_PORT, BOT_NAME);
	connectToServer(SERVEUR_ADRESS, (int)strtol(SERVEUR_PORT, NULL, 10), BOT_NAME); //"RandomRobotilPlayer"
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
	char gameType[97] = "TRAINING ";	
	buildGameType(gameType, "DO_NOTHING", "10", SEED, "0", MAP);
	char gameName[20];
	int nbrCities;
	int nbrTracks;
	int *rawTracks = NULL;
	t_return_code bothMove = NORMAL_MOVE;
	char colors[10][11] = {"PURPLE", "WHITE", "BLUE", "YELLOW", "ORANGE", "BLACK", "RED", "GREEN", "MULTICOLOR"};
	int start = 1;
	/* _______________________________________________________________________ */
	/*  ###################################################################### */
	/*  #------------------------------BOT VARIABLES-------------------------# */
	/*  ###################################################################### */
	t_move move;
	int objectiveCards[3];
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
	t_track **TracksMap = buildTracksMap(rawTracks, nbrTracks);
	/* ################################################### */

	/*
		MAIN LOOP
	*/

	t_color drawnCard;
	t_color myCards[9];
	for (int i = 1; i < 10; i++)
	{
		if (Bot.cards[i] > 0)
		{
			for (int j = 0; j < Bot.cards[i]; j++)
			{
				cards[cardsCounter++] = i - 1;
			}
		}

	}

	cardsCounter += 4;

	while (!bothMove) /* while (bothMove == NORMAL_MOVE) */
	{
		if (Game.playingBotID)
		{
			bothMove = getMove(&ennemyMove, &ennemyReplay);
			PlayerDrawColorCard(&ennemyBot, NULL, 1);
			cardsCounter++;

			if (bothMove)
				break;

			bothMove = getMove(&ennemyMove, &ennemyReplay);
			ennemyReplay = 0; /* Supposed unnecessary */
			PlayerDrawColorCard(&ennemyBot, NULL, 1);
			cardsCounter++;
		}

		else
		{
		/*
			USER CHOICE
		*/
			bothMove = drawBlindCard(&drawnCard);
			cards[cardsCounter++] = drawnCard - 1;
			Bot.nbrCards++;

			if (bothMove)
				break;

			bothMove = drawBlindCard(&drawnCard);
			cards[cardsCounter++] = drawnCard - 1;
		}

		if (bothMove)
			break;

		Game.playingBotID = !Game.playingBotID;

		/*
			__U_PRINT__
		*/
		/* #################################################################################### */

	}

	endGame(bothMove, Game.playingBotID);

	closeConnection();








	/////////////////////////////////////////////
	/////////////////////////////////////////////
	////         //////////////              ////
	////  ////// //////////////  ////////   /////
	////  /////////////////////  //////   ///////
	////  ///////////////////////////   /////////
	////  ///       ///////////////   ///////////
	////  /////   ///////////////   /////////////
	////  /////   /////////////   ///////////////
	////           ///////////               ////
	/////////////////////////////////////////////
	/////////////////////////////////////////////
	/////////////////////////////////////////////

/*______________________________________________________________________________________________________*/

	/*
		CONNECTING TO THE SERVER
	*/
	//connectToServer(SERVEUR_ADRESS, SERVEUR_PORT, BOT_NAME);
	connectToServer(SERVEUR_ADRESS, (int)strtol(SERVEUR_PORT, NULL, 10), BOT_NAME); //"RandomRobotilPlayer"
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
	buildGameType(gameType, "DO_NOTHING", "10", SEED, "1", MAP);
	rawTracks = NULL;
	bothMove = NORMAL_MOVE;
	start = 1;
	/* _______________________________________________________________________ */
	/*  ###################################################################### */
	/*  #------------------------------BOT VARIABLES-------------------------# */
	/*  ###################################################################### */
	t_player Bot2 = Player(&Bot2);
	/* _______________________________________________________________________ */
	/*  ###################################################################### */
	/*  #----------------------------ENNEMY VARIABLES------------------------# */
	/*  ###################################################################### */
	ennemyReplay = 0;
	t_player ennemyBot2 = Player(&ennemyBot2);
	/* " "###################################################################### */



	/*
		INITIALIZING THE GAME
	*/
	Game = gameStart(&Bot2, &ennemyBot2, gameType, gameName, &nbrCities, &nbrTracks, &rawTracks);
	TracksMap = buildTracksMap(rawTracks, nbrTracks);
	/* ################################################### */

	/*
		MAIN LOOP
	*/

	cardsCounter = 4;

	for (int i = 1; i < 10; i++)
	{
		if (Bot2.cards[i] > 0)
		{
			for (int j = 0; j < Bot2.cards[i]; j++)
			{
				cards[cardsCounter++] = i - 1;
			}
		}

	}

	while (!bothMove) /* while (bothMove == NORMAL_MOVE) */
	{
		if (Game.playingBotID)
		{
			bothMove = getMove(&ennemyMove, &ennemyReplay);
			PlayerDrawColorCard(&ennemyBot2, NULL, 1);
			cardsCounter++;

			if (bothMove)
				break;

			bothMove = getMove(&ennemyMove, &ennemyReplay);
			ennemyReplay = 0; /* Supposed unnecessary */
			PlayerDrawColorCard(&ennemyBot2, NULL, 1);
			cardsCounter++;
		}

		else
		{
		/*
			USER CHOICE
		*/
			bothMove = drawBlindCard(&drawnCard);
			cards[cardsCounter++] = drawnCard - 1;
			Bot2.nbrCards++;

			if (bothMove)
				break;

			bothMove = drawBlindCard(&drawnCard);
			cards[cardsCounter++] = drawnCard - 1;
			Bot2.nbrCards++;
		}

		if (bothMove)
			break;

		Game.playingBotID = !Game.playingBotID;

		/*
			__U_PRINT__
		*/
		/* #################################################################################### */

	}

	endGame(bothMove, Game.playingBotID);

	closeConnection();









	char cardsStringToWrite[109] = "";

	
	fprintf(stdout, "LISTE DES CARTES DANS L'ORDRE :\n");
	for (int i = 0; i < 108; i++)
	{
		fprintf(stdout, "Carte n°%i : %i - %s\n", i, cards[i], colors[cards[i]]);
		cardsStringToWrite[i] = cards[i] + '0';
	}

	fprintf(stdout, "La chaîne de charactère correspondante :\n%s\n", cardsStringToWrite);
	

	
	char *args[3] = {
		"main.out",
		cardsStringToWrite,
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
    	execv("main.out", args);
		fprintf(stderr, "ERROR : program A not found.\n");
		exit(EXIT_FAILURE);
	}
	
	wait(NULL);

	return EXIT_SUCCESS;
}