#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include "HitCard.h"
#include "basicFunctions.h"
using namespace std;

class Player {
private:
	string name, carrier[5], battleship[4], submarine[3], destroyer[3], patrolBoat[2], bombs[3];
	string boatBoard[15][15], guessBoard[15][15];
	HitCard * hitCards;
	int playerType, playerNum, playerID;
public:
	Player()
	{
		//name
		name = "none";
		//player type
		playerType = 1;
		//player num
		playerNum = 1;
		//guessboard
		for (int y = 0; y < 15; y++) {
			for (int x = 0; x < 15; x++) {
				guessBoard[y][x] = "   ";
				boatBoard[y][x] = " ";
				///boatBoard[y][x] = to_string(x) + "-" + to_string(y);
			}
		}
		//hitCards
		///hitCards = new HitCard[playerNum];
		//locations
		for (int i = 0; i < 5; i++) carrier[i] = "";
		for (int i = 0; i < 4; i++) battleship[i] = "";
		for (int i = 0; i < 3; i++) submarine[i] = "";
		for (int i = 0; i < 3; i++) destroyer[i] = "";
		for (int i = 0; i < 2; i++) patrolBoat[i] = "";
		for (int i = 0; i < 3; i++) bombs[i] = "";
	}
	~Player() { delete[] hitCards; }

	//set/get functions
	void setName(string n);
	string getName();
	void setPlayerType(int t);
	int getPlayerType();
	void setPlayerNum(int pn);
	int getPlayerNum();
	void setPlayerID(int ID);
	int getPlayerID();

	//standard functions
	void placement();
	void humanPlacement();
	void placementCoordCheck(string &placeCoord, int &CX, int &CY);
	void guessCoordCheck(string &placeCoord, int &CX, int &CY);
	void computerPlacement();
	int numShots(int turn);
	void getBoatBoardVal(int x, int y);
	void getGuessBoardVal(int x, int y);
	void getMinimalGuessBoardVal(int x, int y);
	void getHitBoardVal(int x, int y);
	void showBoatBoard();
	void showGuessBoard();
	void showMinimalGuessBoard();
	void showHitBoard();
	char checkGuessBoardVal(int x, int y);
	void showHitCards();
	void showSunkBoats();
	void showBoatPositions();
	bool playerDefeated();
	void writeToFile();

	//players turn
	string broadcastGuess();
	void computerGuess(string &placeCoord, int &x, int &y);
	void recieveAnswer(string * answers, string guess, int &shotCount, int turnShotNum);
	void showInGameInfo(string * answers, string guess, int turn, int shotCount, int turnShotNum);

	//not players turn
	string analyzeGuess(string guess);
};


