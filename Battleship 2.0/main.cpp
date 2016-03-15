///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ____  ___  ______________    ___________ __  __________     ___    ____
   / __ )/   |/_  __/_  __/ /   / ____/ ___// / / /  _/ __ \   |__ \  / __ \
  / __  / /| | / /   / / / /   / __/  \__ \/ /_/ // // /_/ /   __/ / / / / /
 / /_/ / ___ |/ /   / / / /___/ /___ ___/ / __  // // ____/   / __/_/ /_/ /
/_____/_/  |_/_/   /_/ /_____/_____//____/_/ /_/___/_/       /____(_)____/

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//http://patorjk.com/software/taag/ ///////////////////////////////////////////////////////////////////////////////////////////
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

By:
Sheldon Woodward
Evan Taylor
Andrew Yamada

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Class: CPTR142
Assignment: Final Project
Date Started: 3/1/16

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include "Player.h"
#include "basicFunctions.h"
using namespace std;

int main()
{
	Player * players;
	string broadcast;
	string * responses;
	bool * playersInGame;
	string guess = "--";
	int turn = 0, playerNum = 0;
	const bool showComGuesses = false;
	const int comGuessDelay = 500;

	srand(time(NULL)); ///seed rand()

	setTextColor("gray", "none");

	welcomeScreen();

	//set playerNum
	cout << "How many computer players: ";
	cin >> playerNum; ///input com num
	playerNum++; ///increase to playerNum
	system("cls");

	//setup players
	players = new Player[playerNum]; ///define player array
	playersInGame = new bool[playerNum]; ///define array of bools for players still in the game
	for (int i = 0; i < playerNum; i++) players[i].setPlayerNum(playerNum); ///set Player playerNums
	for (int i = 0; i < playerNum; i++) players[i].setPlayerID(i);
	players[0].setPlayerType(0); ///set first player as human

	//setup responses
	responses = new string[playerNum]; ///define response array
	for (int i = 0; i < playerNum; i++) responses[i] = "0"; ///set responses to default of 0

	//boat placement
	for (int i = 0; i < playerNum; i++) players[i].placement(); ///run placement for all players
	
	//write data to file
	for (int i = 0; i < playerNum; i++) players[i].writeToFile(); ///write all palyer boats to playerData.txt

	//run game
	bool gameover = false;
	while (gameover == false) { ///run till gameover

		//loop player turn for numShots
		int turnShotNum = players[turn].numShots(turn); ///calculate numShots
		for (int shotCount = 0; shotCount < turnShotNum; shotCount++) { ///loop

			int realOption = 0;
			string storedGuess = guess;
			guess = "none";
			if (turn == 0) {
				do {
					players[0].showInGameInfo(responses, storedGuess, turn, shotCount, turnShotNum); ///shpw output on screen for palyer to interact with

					//show options
					setTextColor("white", "none");
					cout << "1) Guess" << endl;
					cout << "2) See minimal hit board" << endl;
					cout << "3) See individual player hit board" << endl;
					cout << "What would you like to do: ";

					//get options
					cin.clear();
					if (realOption == 0) cin.ignore(256, '\n');
					do {
						realOption = getInt();
					} while (realOption < 1 || realOption > 3);

					//switch options
					switch (realOption) {
					//guess
					case 1:
						cout << "Coordinate: ";
						guess = players[turn].broadcastGuess(); ///get guess from player
						for (int i = 0; i < playerNum; i++) responses[i] = players[i].analyzeGuess(guess); ///analyze guess
						for (int i = 0; i < playerNum; i++) players[i].recieveAnswer(responses, guess, shotCount, turnShotNum); ///recieve answers
						for (int i = 0; i < playerNum; i++) if (players[i].playerDefeated()) {
							playersInGame[i] = false;
							///cout << "Player " << i + 1 << " defeated!" << endl;
						}
						break;
					//show minimal guess board
					case 2:
						system("cls");
						players[0].showMinimalGuessBoard();
						do {
							cout << "Press enter to go back" << endl;
						} while (cin.get() != '\n');
						cin.clear();
						break;
						//show player hit board
					case 3:
						int player;
						do {
							cout << "Which player: ";
							player = getInt() - 1;
						} while (player >= playerNum);
						system("cls");
						players[player].showHitBoard();
						do {
							cout << "Press enter to go back" << endl;
						} while (cin.get() != '\n');
						cin.clear();
						break;
					default:
						///realOption = 0;
						break;
					}
				} while (realOption != 1);
			}
			else {
				//compute guess
				guess = players[turn].broadcastGuess(); ///get guess from player
				for (int i = 0; i < playerNum; i++) responses[i] = players[i].analyzeGuess(guess); ///analyze guess
				for (int i = 0; i < playerNum; i++) players[i].recieveAnswer(responses, guess, shotCount, turnShotNum); ///recieve answers
				for (int i = 0; i < playerNum; i++) if (players[i].playerDefeated()) {
					playersInGame[i] = false; ///remove player from game
				}
				if (showComGuesses) {
					system("cls");
					//show info for player
					players[0].showInGameInfo(responses, storedGuess, turn, shotCount, turnShotNum);
					Sleep(comGuessDelay);
				}
			}

			//check for winner
			int defeatNum = 0;
			for (int i = 0; i < playerNum; i++) if (players[i].playerDefeated()) defeatNum++;
			if (defeatNum >= playerNum - 1) {
				gameover = true;
				shotCount = turnShotNum;
			}
		}

		//advance turn
		do {
			if (turn + 1 < playerNum) turn++;
			else turn = 0;
		} while (players[turn].playerDefeated() == true);
	}

	//reset winner
	int winner = -1;
	int winnerCount = 0;
	for (int i = 0; i < playerNum; i++) {
		if (playersInGame[i]) winner = i;
	}

	//check for gameover
	system("cls");
	setTextColor("red", "none");
	cout << "GAMEOVER!" << endl;
	if (winner == -1) cout << "Tie game, nobody won!" << endl;
	else cout << "Player " << winner + 1 << " won!" << endl;
	system("pause");

	return 0;
}