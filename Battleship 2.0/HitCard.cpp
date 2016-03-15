#include "HitCard.h"

void HitCard::markCarrier(string coord)
{
	carrier.push_back(coord);
	if (carrier.size() >= 5) carrierSunk = true;
}

void HitCard::markBattleship(string coord)
{
	battleship.push_back(coord);
	if (battleship.size() >= 4) battleshipSunk = true;
}

void HitCard::markSubmarine(string coord)
{
	submarine.push_back(coord);
	if (submarine.size() >= 3) submarineSunk = true;
}

void HitCard::markDestroyer(string coord)
{
	destroyer.push_back(coord);
	if (destroyer.size() >= 3) destroyerSunk = true;
}

void HitCard::markPatrolBoat(string coord)
{
	patrolBoat.push_back(coord);
	if (patrolBoat.size() >= 2) patrolBoatSunk = true;
}

void HitCard::markHitPool(string coord)
{
	hitPool.push_back(coord);
}

bool HitCard::getCarrierSunk()
{
	return carrierSunk;
}

bool HitCard::getBattleshipSunk()
{
	return battleshipSunk;
}

bool HitCard::getSubmarineSunk()
{
	return submarineSunk;
}

bool HitCard::getDestroyerSunk()
{
	return destroyerSunk;
}

bool HitCard::getPatrolBoatSunk()
{
	return patrolBoatSunk;
}

string HitCard::getRandomHit()
{
	string randHit;
	if (hitPool.size() > 0) randHit = hitPool[rand() % hitPool.size()];
	else return "none";

}

int HitCard::numHits()
{
	return hitPool.size();
}

void HitCard::showHitPool()
{
	setTextColor("red", "none");
	for (int i = 0; i < hitPool.size(); i++) {
		bool showCoord = true;

		if (searchBoats(hitPool[i]) == 1 && carrierSunk) showCoord = false;
		if (searchBoats(hitPool[i]) == 2 && battleshipSunk) showCoord = false;
		if (searchBoats(hitPool[i]) == 3 && submarineSunk) showCoord = false;
		if (searchBoats(hitPool[i]) == 4 && destroyerSunk) showCoord = false;
		if (searchBoats(hitPool[i]) == 5 && patrolBoatSunk) showCoord = false;

		if (showCoord) {
			if (hitPool[i].size() == 2) {
				cout << (char)toupper(hitPool[i][0]) << hitPool[i][1] << " ";
			}
			else {
				cout << (char)toupper(hitPool[i][0]) << hitPool[i][1] << hitPool[i][2] << " ";
			}
		}
	}
	setTextColor("gray", "none");
}

void HitCard::showShipHits()
{
	cout << "Boat Hits" << endl;

	cout << "Carrier: ";
	for (int i = 0; i < carrier.size(); i++) cout << carrier[i] << " ";

	cout << endl << "Battleship: ";
	for (int i = 0; i < battleship.size(); i++) cout << battleship[i] << " ";

	cout << endl << "Submarine: ";
	for (int i = 0; i < submarine.size(); i++) cout << submarine[i] << " ";

	cout << endl << "Destroyer: ";
	for (int i = 0; i < destroyer.size(); i++) cout << destroyer[i] << " ";

	cout << endl << "Patrol Boat: ";
	for (int i = 0; i < patrolBoat.size(); i++) cout << patrolBoat[i] << " ";
	cout << endl;
}

int HitCard::searchHitPool(string coord)
{
	for (int i = 0; i < carrier.size(); i++) if (carrier[i] == coord) return 1;
	for (int i = 0; i < battleship.size(); i++) if (battleship[i] == coord) return 2;
	for (int i = 0; i < submarine.size(); i++) if (submarine[i] == coord) return 3;
	for (int i = 0; i < destroyer.size(); i++) if (destroyer[i] == coord) return 4;
	for (int i = 0; i < patrolBoat.size(); i++) if (patrolBoat[i] == coord) return 5;

	return 0;
}

int HitCard::searchBoats(string coord)
{
	for (int i = 0; i < carrier.size(); i++) if (carrier[i] == coord) return 1;
	for (int i = 0; i < battleship.size(); i++) if (battleship[i] == coord) return 2;
	for (int i = 0; i < submarine.size(); i++) if (submarine[i] == coord) return 3;
	for (int i = 0; i < destroyer.size(); i++) if (destroyer[i] == coord) return 4;
	for (int i = 0; i < patrolBoat.size(); i++) if (patrolBoat[i] == coord) return 5;

	return 0;
}
