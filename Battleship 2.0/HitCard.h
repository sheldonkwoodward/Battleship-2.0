#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "basicFunctions.h"
using namespace std;

class HitCard {
private:
	vector<string> carrier, battleship, submarine, destroyer, patrolBoat;
	vector<string> hitPool;
	bool carrierSunk, battleshipSunk, submarineSunk, destroyerSunk, patrolBoatSunk;
public:
	HitCard()
	{
		carrierSunk = false;
		battleshipSunk = false;
		submarineSunk = false;
		destroyerSunk = false;
		patrolBoatSunk = false;

		/*
		for (int i = 0; i < 5; i++) { carrier[i] = ""; }
		for (int i = 0; i < 4; i++) { battleship[i] = ""; }
		for (int i = 0; i < 3; i++) { submarine[i] = ""; }
		for (int i = 0; i < 3; i++) { destroyer[i] = ""; }
		for (int i = 0; i < 2; i++) { patrolBoat[i] = ""; }
		for (int i = 0; i < 17; i++) { carrier[i] = ""; }
		*/
	}

	void markCarrier(string coord);
	void markBattleship(string coord);
	void markSubmarine(string coord);
	void markDestroyer(string coord);
	void markPatrolBoat(string coord);
	void markHitPool(string coord);

	bool getCarrierSunk();
	bool getBattleshipSunk();
	bool getSubmarineSunk();
	bool getDestroyerSunk();
	bool getPatrolBoatSunk();

	string getRandomHit();

	int numHits();
	void showHitPool();
	void showShipHits();
	int searchHitPool(string coord);
	int searchBoats(string coord);
};