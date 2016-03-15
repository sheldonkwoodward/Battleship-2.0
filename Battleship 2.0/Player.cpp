#include "Player.h"

//set/get functions
void Player::setName(string n)
{
	name = n;
}
string Player::getName()
{
	return name;
}
void Player::setPlayerType(int t)
{
	if (t == 0 || t == 1) playerType = 0;
}
int Player::getPlayerType()
{
	return playerType;
}
void Player::setPlayerNum(int pn)
{
	playerNum = pn;
	hitCards = new HitCard[playerNum];
}
int Player::getPlayerNum()
{
	return playerNum;
}
void Player::setPlayerID(int ID)
{
	playerID = ID;
}
int Player::getPlayerID()
{
	return playerID;
}

//standard functions
void Player::placement()
{
	const bool forceHumanPlacement = false; ///0 for user choice, 2 for semi random
	const bool forceComputerPlacement = false; ///0 for random, 1 for semi random
	int placementChoice = 0;

	//input placememntChoice
	if (playerType == 0) {
		//input choice
		cout << "Choose your setup type" << endl;
		cout << "1) Manual ship placement" << endl << "2) Random ship placement" << endl;
		cin >> placementChoice;

		//check input
		while (cin.fail() || placementChoice > 2 || placementChoice < 1) {
			cout << "Please enter a valid input" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> placementChoice;
		}

		//force semi random?
		if (forceHumanPlacement) placementChoice = 3;
	}

	system("cls");

	//random placement
	if (placementChoice == 2 && playerType == 0) {
		computerPlacement();
	}
	//semi random placement
	else if (placementChoice == 3 && playerType == 0) {
		int randVal = rand() % 3;
		for (int i = 0; i < 5; i++) {
			carrier[i] = static_cast<char>(randVal + 97) + to_string(i + 1);
			///cout << carrier[i] << endl;
			boatBoard[i][randVal] = "C";
		}
		randVal = rand() % 3;
		for (int i = 0; i < 4; i++) {
			battleship[i] = static_cast<char>(randVal + 100) + to_string(i + 1);
			///cout << battleship[i] << endl;
			boatBoard[i][randVal + 3] = "B";
		}
		randVal = rand() % 3;
		for (int i = 0; i < 3; i++) {
			submarine[i] = static_cast<char>(randVal + 103) + to_string(i + 1);
			///cout << submarine[i] << endl;
			boatBoard[i][randVal + 6] = "S";
		}
		randVal = rand() % 3;
		for (int i = 0; i < 3; i++) {
			destroyer[i] = static_cast<char>(randVal + 106) + to_string(i + 1);
			///cout << destroyer[i] << endl;
			boatBoard[i][randVal + 9] = "D";
		}
		randVal = rand() % 3;
		for (int i = 0; i < 2; i++) {
			patrolBoat[i] = static_cast<char>(randVal + 109) + to_string(i + 1);
			///cout << patrolBoat[i] << endl;
			boatBoard[i][randVal + 12] = "P";
		}
		randVal = rand() % 3;
		for (int i = 0; i < 3; i++) {
			bombs[i] = "f" + to_string(i + 11);
			///cout << bombs[i] << endl;
			boatBoard[i + 10][5] = "*";
		}

		///system("cls");
		///showBoatBoard();
		///system("pause");
	}
	//user placement
	else {
		///cout << "Player Type: " << playerType << endl;
		if (playerType == 0) {
			//cout << "HUMAN" << endl;
			humanPlacement();
		}
	}

	//rsemi random placement
	if (forceComputerPlacement == true && playerType == 1) {
		int randVal = rand() % 3;
		for (int i = 0; i < 5; i++) {
			carrier[i] = static_cast<char>(randVal + 97) + to_string(i + 1);
			///cout << carrier[i] << endl;
			boatBoard[i][randVal] = "C";
		}
		randVal = rand() % 3;
		for (int i = 0; i < 4; i++) {
			battleship[i] = static_cast<char>(randVal + 100) + to_string(i + 1);
			///cout << battleship[i] << endl;
			boatBoard[i][randVal + 3] = "B";
		}
		randVal = rand() % 3;
		for (int i = 0; i < 3; i++) {
			submarine[i] = static_cast<char>(randVal + 103) + to_string(i + 1);
			///cout << submarine[i] << endl;
			boatBoard[i][randVal + 6] = "S";
		}
		randVal = rand() % 3;
		for (int i = 0; i < 3; i++) {
			destroyer[i] = static_cast<char>(randVal + 106) + to_string(i + 1);
			///cout << destroyer[i] << endl;
			boatBoard[i][randVal + 9] = "D";
		}
		randVal = rand() % 3;
		for (int i = 0; i < 2; i++) {
			patrolBoat[i] = static_cast<char>(randVal + 109) + to_string(i + 1);
			///cout << patrolBoat[i] << endl;
			boatBoard[i][randVal + 12] = "P";
		}
		randVal = rand() % 3;
		for (int i = 0; i < 3; i++) {
			bombs[i] = "f" + to_string(i + 11);
			///cout << bombs[i] << endl;
			boatBoard[i + 10][5] = "*";
		}
	}
	//random placement
	else {
		///cout << "Player Type: " << playerType << endl;
		if (playerType == 1) {
			//cout << "COMPUTER" << endl;
			computerPlacement();
		}
	}

	//copy values from boatBoard to guessBoard
	for (int y = 0; y < 15; y++) for (int x = 0; x < 15; x++) guessBoard[y][x] = boatBoard[y][x];
}

void Player::humanPlacement()
{
	string ship = "carrier";
	int placementCount = 1;

	showBoatBoard();

	while (placementCount < 6) {
		string placeCoord;
		int coords[2];
		int orientation;
		int orientCheck[2] = { 0,0 };
		vector<int> boatCheck;
		int shipSpaces = 0;
		string * shipPtr;

		//set ship spaces
		if (ship == "carrier") {
			shipSpaces = 5;
			shipPtr = carrier;
		}
		if (ship == "battleship") {
			shipSpaces = 4;
			shipPtr = battleship;
		}
		if (ship == "submarine") {
			shipSpaces = 3;
			shipPtr = submarine;
		}
		if (ship == "destroyer") {
			shipSpaces = 3;
			shipPtr = destroyer;
		}
		if (ship == "patrol boat") {
			shipSpaces = 2;
			shipPtr = patrolBoat;
		}

		cout << "What is the initial coordinate of your " << ship << ": ";
		cin >> placeCoord;

		coords[0] = (int)tolower(placeCoord[0]) - 96;

		if (placeCoord.size() == 3) coords[1] = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else coords[1] = placeCoord[1] - 48;

		///cout << coords[0] << endl << coords[1] << endl;

		//coord checks
		placementCoordCheck(placeCoord, coords[0], coords[1]);

		/*
		do
		{
		if (placeCoord.size() > 3)
		{
		cout << "Coordinate size is too big. Please input one letter and one number: ";
		cin >> placeCoord;

		coords[0] = (int)placeCoord[0] - 96;
		if (placeCoord.size() == 3) coords[1] = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else coords[1] = placeCoord[1] - 48;
		}
		} while (placeCoord.size() > 3);
		do
		{
		if (coords[0] < 1 || coords[0] > 15)
		{
		cout << "Coordinate is off the board. Please input a letter between A-0: ";
		cin >> placeCoord;

		coords[0] = (int)placeCoord[0] - 96;
		if (placeCoord.size() == 3) coords[1] = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else coords[1] = placeCoord[1] - 48;
		}
		} while (coords[0] < 1 || coords[0] > 15);
		do {
		if (coords[1] < 1 || coords[1] > 15)
		{
		cout << "Coordinate is off the board. Please input a letter between A-0: ";
		cin >> placeCoord;

		coords[0] = (int)placeCoord[0] - 96;
		if (placeCoord.size() == 3) coords[1] = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else coords[1] = placeCoord[1] - 48;
		}
		} while (coords[1] < 1 || coords[1] > 15);
		do {
		if (boatBoard[coords[1] - 1][coords[0] - 1] != " ") {
		cout << "Coordinate overlaps one of your ships. Input a new coordinate: ";
		cin.clear();
		cin >> placeCoord;

		coords[0] = (int)placeCoord[0] - 96;
		if (placeCoord.size() == 3) coords[1] = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else coords[1] = placeCoord[1] - 48;
		}
		} while (boatBoard[coords[1] - 1][coords[0] - 1] != " ");
		*/


		//check for availabe orientations based on starting coordinate 
		//1=up 2=right 3=down 4=left

		//board edge
		if (coords[0] >= 1 && coords[0] <= shipSpaces - 1) {
			//orientation cannot be left
			if (orientCheck[0] == 0) orientCheck[0] = 4;
			else orientCheck[1] = 4;
			///cout << "NO LEFT" << endl;
		}
		if (coords[0] >= 15 - shipSpaces + 2 && coords[0] <= 15)
		{
			//orientation cannot be right
			if (orientCheck[0] == 0) orientCheck[0] = 2;
			else orientCheck[1] = 2;
			///cout << "NO RIGHT" << endl;
		}
		if (coords[1] >= 1 && coords[1] <= shipSpaces - 1)
		{
			//orientation cannot be up
			if (orientCheck[0] == 0) orientCheck[0] = 1;
			else orientCheck[1] = 1;
			///cout << "NO UP" << endl;
		}
		if (coords[1] >= 15 - shipSpaces + 2 && coords[1] <= 15)
		{
			//orientation cannot be down
			if (orientCheck[0] == 0) orientCheck[0] = 3;
			else orientCheck[1] = 3;
			///cout << "NO DOWN" << endl;
		}

		//other ships
		for (int i = 0; i < shipSpaces; i++) {
			if (coords[1] - i - 1 >= 0) {
				if (boatBoard[coords[1] - i - 1][coords[0] - 1] != " ") {
					boatCheck.push_back(1);
					///cout << "UP" << endl;
				}
			}
			if (coords[0] - i - 1 >= 0) {
				if (boatBoard[coords[1] - 1][coords[0] - i - 1] != " ") {
					boatCheck.push_back(4);
					///cout << "LEFT" << endl;
				}
			}
			if (coords[1] + i - 1 <= 15) {
				if (boatBoard[coords[1] + i - 1][coords[0] - 1] != " ") {
					boatCheck.push_back(3);
					///cout << "DOWN" << endl;
				}
			}
			if (coords[0] + i - 1 <= 15) {
				if (boatBoard[coords[1] - 1][coords[0] + i - 1] != " ") {
					boatCheck.push_back(2);
					///cout << "RIGHT" << endl;
				}
			}
		}

		///for (int i = 0; i < boatCheck.size(); i++) cout << boatCheck[i] << endl;

		boatBoard[coords[1] - 1][coords[0] - 1] = toupper(ship[0]);
		if (find(boatCheck.begin(), boatCheck.end(), 1) == boatCheck.end() && orientCheck[0] != 1 && orientCheck[1] != 1) boatBoard[coords[1] - 2][coords[0] - 1] = "1";
		if (find(boatCheck.begin(), boatCheck.end(), 2) == boatCheck.end() && orientCheck[0] != 2 && orientCheck[1] != 2) boatBoard[coords[1] - 1][coords[0]] = "2";
		if (find(boatCheck.begin(), boatCheck.end(), 3) == boatCheck.end() && orientCheck[0] != 3 && orientCheck[1] != 3) boatBoard[coords[1]][coords[0] - 1] = "3";
		if (find(boatCheck.begin(), boatCheck.end(), 4) == boatCheck.end() && orientCheck[0] != 4 && orientCheck[1] != 4) boatBoard[coords[1] - 1][coords[0] - 2] = "4";

		system("cls");
		showBoatBoard();

		cout << "What is your " << ship << "'s orientation: ";
		///cout << "Eg: 1 is up, 3 is down, 4 is left, 2 is right" << endl;

		cin >> orientation;

		bool goodOrientationCheck;
		bool goodBoatCheck;
		do {
			goodOrientationCheck = true;
			goodBoatCheck = true;
			if (orientation == orientCheck[0] || orientation == orientCheck[1]) goodOrientationCheck = false;
			for (int i = 0; i < boatCheck.size(); i++) if (boatCheck[i] == orientation) goodBoatCheck = false;

			if (goodOrientationCheck == false || goodBoatCheck == false) {
				cout << "That is not an option" << endl;
				cin.clear();
				cin >> orientation;
			}
		} while (goodOrientationCheck == false || goodBoatCheck == false);

		char charHolder;

		for (int i = 0; i < shipSpaces; i++)
		{
			if (orientation == 1) {
				shipPtr[i] = placeCoord[0] + to_string(coords[1] - i);
				boatBoard[coords[1] - 1 - i][coords[0] - 1] = toupper(ship[0]);
			}

			if (orientation == 2) {
				charHolder = (coords[0] + i) + 96;
				shipPtr[i] = charHolder + to_string(coords[1]);
				boatBoard[coords[1] - 1][coords[0] - 1 + i] = toupper(ship[0]);
			}

			if (orientation == 3) {
				shipPtr[i] = placeCoord[0] + to_string(coords[1] + i);
				boatBoard[coords[1] - 1 + i][coords[0] - 1] = toupper(ship[0]);
			}

			if (orientation == 4) {
				charHolder = (coords[0] - i) + 96;
				shipPtr[i] = charHolder + to_string(coords[1]);
				boatBoard[coords[1] - 1][coords[0] - 1 - i] = toupper(ship[0]);
			}
		}

		if (orientation != 2 && boatBoard[coords[1] - 1][coords[0]] == "2") boatBoard[coords[1] - 1][coords[0]] = " ";
		if (orientation != 1 && boatBoard[coords[1] - 2][coords[0] - 1] == "1") boatBoard[coords[1] - 2][coords[0] - 1] = " ";
		if (orientation != 4 && boatBoard[coords[1] - 1][coords[0] - 2] == "4") boatBoard[coords[1] - 1][coords[0] - 2] = " ";
		if (orientation != 3 && boatBoard[coords[1]][coords[0] - 1] == "3") boatBoard[coords[1]][coords[0] - 1] = " ";

		system("cls");
		showBoatBoard();
		cout << endl;

		placementCount++;
		if (placementCount == 2) ship = "battleship";
		if (placementCount == 3) ship = "submarine";
		if (placementCount == 4) ship = "destroyer";
		if (placementCount == 5) ship = "patrol boat";
	}

	//place bombs
	for (int bombNum = 0; bombNum < 3; bombNum++) {
		string placeCoord;
		int coords[2];

		cout << "What is the coordinate of bomb " << bombNum + 1 << ": ";
		cin >> placeCoord;

		coords[0] = (int)tolower(placeCoord[0]) - 96;

		if (placeCoord.size() == 3) coords[1] = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else coords[1] = placeCoord[1] - 48;

		//coord checks
		placementCoordCheck(placeCoord, coords[0], coords[1]);

		/*
		do  {
		if (placeCoord.size() > 3)
		{
		cout << "Coordinate size is too big. Please input one letter and one number: ";
		cin >> placeCoord;

		coords[0] = (int)placeCoord[0] - 96;
		if (placeCoord.size() == 3) coords[1] = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else coords[1] = placeCoord[1] - 48;
		}
		} while (placeCoord.size() > 3);
		do
		{
		if (coords[0] < 1 || coords[0] > 15)
		{
		cout << "Coordinate is off the board. Please input a letter between A-0: ";
		cin >> placeCoord;

		coords[0] = (int)placeCoord[0] - 96;
		if (placeCoord.size() == 3) coords[1] = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else coords[1] = placeCoord[1] - 48;
		}
		} while (coords[0] < 1 || coords[0] > 15);
		do {
		if (coords[1] < 1 || coords[1] > 15)
		{
		cout << "Coordinate is off the board. Please input a letter between A-0: ";
		cin >> placeCoord;

		coords[0] = (int)placeCoord[0] - 96;
		if (placeCoord.size() == 3) coords[1] = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else coords[1] = placeCoord[1] - 48;
		}
		} while (coords[1] < 1 || coords[1] > 15);
		do {
		if (boatBoard[coords[1] - 1][coords[0] - 1] != " ") {
		cout << "Coordinate overlaps one of your ships. Input a new coordinate: ";
		cin.clear();
		cin >> placeCoord;

		coords[0] = (int)placeCoord[0] - 96;
		if (placeCoord.size() == 3) coords[1] = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else coords[1] = placeCoord[1] - 48;
		}
		} while (boatBoard[coords[1] - 1][coords[0] - 1] != " ");
		*/

		//place bomb
		for (int i = 0; i < placeCoord.size(); i++)
			bombs[bombNum] += tolower(placeCoord[i]);
		boatBoard[coords[1] - 1][coords[0] - 1] = "*";

		system("cls");
		showBoatBoard();
	}

	string ans = "y";
	cout << "Do you want to keep this arrangement? (y or n): ";
	cin >> ans;
	if (ans == "n" || ans == "N") {
		for (int y = 0; y < 15; y++) {
			for (int x = 0; x < 15; x++) {
				boatBoard[y][x] = " ";
			}
		}
		system("cls");
		humanPlacement();
	}
}

void Player::placementCoordCheck(string &placeCoord, int &CX, int &CY)
{
	if (placeCoord.size() > 3) {
		cout << "Coordinate size is too big. Please input one letter and one number: ";
		cin >> placeCoord;

		CX = (int)placeCoord[0] - 96;
		if (placeCoord.size() == 3) CY = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else CY = placeCoord[1] - 48;

		placementCoordCheck(placeCoord, CX, CY);
	}
	if (CX < 1 || CX > 15) {
		cout << "Coordinate is off the board. Please input a letter between A-0: ";
		cin >> placeCoord;

		CX = (int)placeCoord[0] - 96;
		if (placeCoord.size() == 3) CY = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else CY = placeCoord[1] - 48;

		placementCoordCheck(placeCoord, CX, CY);
	}
	if (CY < 1 || CY > 15) {
		cout << "Coordinate is off the board. Please input a letter between A-0: ";
		cin >> placeCoord;

		CX = (int)placeCoord[0] - 96;
		if (placeCoord.size() == 3) CY = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else CY = placeCoord[1] - 48;

		placementCoordCheck(placeCoord, CX, CY);
	}
	if (boatBoard[CY - 1][CX - 1] != " ") {
		cout << "Coordinate overlaps one of your ships. Input a new coordinate: ";
		cin.clear();
		cin >> placeCoord;

		CX = (int)placeCoord[0] - 96;
		if (placeCoord.size() == 3) CY = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
		else CY = placeCoord[1] - 48;

		placementCoordCheck(placeCoord, CX, CY);
	}
}

void Player::guessCoordCheck(string &placeCoord, int &CX, int &CY)
{
		if (placeCoord.size() > 3) {
			cout << "Coordinate size is too big. Please input one letter and one number: ";
			cin >> placeCoord;

			CX = (int)placeCoord[0] - 96;
			if (placeCoord.size() == 3) CY = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
			else CY = placeCoord[1] - 48;

			guessCoordCheck(placeCoord, CX, CY);
		}
		if (CX < 1 || CX > 15) {
			cout << "Coordinate is off the board. Please choose a different coordinate: ";
			cin >> placeCoord;

			CX = (int)placeCoord[0] - 96;
			if (placeCoord.size() == 3) CY = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
			else CY = placeCoord[1] - 48;

			guessCoordCheck(placeCoord, CX, CY);
		}
		if (CY < 1 || CY > 15) {
			cout << "Coordinate is off the board. Please choose a different coordinate: ";
			cin >> placeCoord;

			CX = (int)placeCoord[0] - 96;
			if (placeCoord.size() == 3) CY = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
			else CY = placeCoord[1] - 48;

			guessCoordCheck(placeCoord, CX, CY);
		}
		if (guessBoard[CY - 1][CX - 1] == "X") {
			cout << "You have already guessed here. Please choose a different coordinate: ";
			cin >> placeCoord;

			CX = (int)placeCoord[0] - 96;
			if (placeCoord.size() == 3) CY = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48);
			else CY = placeCoord[1] - 48;

			guessCoordCheck(placeCoord, CX, CY);
		}
}

void Player::computerPlacement()
{
	string ship = "carrier";
	int placementCount = 1;
	///showBoatBoard();

	while (placementCount < 6) {
		string placeCoord = "  ";
		int coords[2];
		int orientation;
		int orientCheck[2] = { 0,0 };
		vector<int> boatCheck;
		int shipSpaces = 0;
		string * shipPtr;

		//set ship spaces
		if (ship == "carrier") {
			shipSpaces = 5;
			shipPtr = carrier;
		}
		if (ship == "battleship") {
			shipSpaces = 4;
			shipPtr = battleship;
		}
		if (ship == "submarine") {
			shipSpaces = 3;
			shipPtr = submarine;
		}
		if (ship == "destroyer") {
			shipSpaces = 3;
			shipPtr = destroyer;
		}
		if (ship == "patrol boat") {
			shipSpaces = 2;
			shipPtr = patrolBoat;
		}
		//Computer is selecting intial coordinate for ship
		///cout << "Selecting " << ship << "'s intial coordinate... " << endl;

		coords[0] = rand() % 15 + 1;
		coords[1] = rand() % 15 + 1;

		//coord checks
		do
		{
			if (size(coords) > 3)
			{
				///cout << "Coordinate size is too big. Please input one letter and one number: ";
				//Randomly generates another coordinate
				coords[0] = rand() % 15 + 1;
				coords[1] = rand() % 15 + 1;
			}
		} while (size(coords) > 3);
		do
		{
			if (coords[0] < 1 || coords[0] > 15)
			{
				///cout << "Coordinate is off the board. Please input a letter between A-0: ";

				//Randomly generates another coordinate
				coords[0] = rand() % 15 + 1;
				coords[1] = rand() % 15 + 1;

			}
		} while (coords[0] < 1 || coords[0] > 15);
		do {
			if (coords[1] < 1 || coords[1] > 15)
			{
				///cout << "Coordinate is off the board. Please input a letter between A-0: ";

				//Randomly generates another coordinate
				coords[0] = rand() % 15 + 1;
				coords[1] = rand() % 15 + 1;

			}
		} while (coords[1] < 1 || coords[1] > 15);

		do {
			if (boatBoard[coords[1] - 1][coords[0] - 1] != " ") {
				///cout << "Coordinate overlaps one of your ships. Input a new coordinate: ";
				cin.clear();

				//Randomly generates another coordinate
				coords[0] = rand() % 15 + 1;
				coords[1] = rand() % 15 + 1;
			}
		} while (boatBoard[coords[1] - 1][coords[0] - 1] != " ");

		//check for availabe orientations based on starting coordinate 
		//1=up 2=right 3=down 4=left

		//board edge
		if (coords[0] >= 1 && coords[0] <= shipSpaces - 1) {
			//orientation cannot be left
			if (orientCheck[0] == 0) orientCheck[0] = 4;
			else orientCheck[1] = 4;
			///cout << "NO LEFT" << endl;
		}
		if (coords[0] >= 15 - shipSpaces + 2 && coords[0] <= 15)
		{
			//orientation cannot be right
			if (orientCheck[0] == 0) orientCheck[0] = 2;
			else orientCheck[1] = 2;
			///cout << "NO RIGHT" << endl;
		}
		if (coords[1] >= 1 && coords[1] <= shipSpaces - 1)
		{
			//orientation cannot be up
			if (orientCheck[0] == 0) orientCheck[0] = 1;
			else orientCheck[1] = 1;
			///cout << "NO UP" << endl;
		}
		if (coords[1] >= 15 - shipSpaces + 2 && coords[1] <= 15)
		{
			//orientation cannot be down
			if (orientCheck[0] == 0) orientCheck[0] = 3;
			else orientCheck[1] = 3;
			///cout << "NO DOWN" << endl;
		}

		//other ships
		for (int i = 0; i < shipSpaces; i++) {
			if (coords[1] - i - 1 >= 0) {
				if (boatBoard[coords[1] - i - 1][coords[0] - 1] != " ") {
					boatCheck.push_back(1);
					///cout << "UP" << endl;
				}
			}
			if (coords[0] - i - 1 >= 0) {
				if (boatBoard[coords[1] - 1][coords[0] - i - 1] != " ") {
					boatCheck.push_back(4);
					///cout << "LEFT" << endl;
				}
			}
			if (coords[1] + i - 1 <= 15) {
				if (boatBoard[coords[1] + i - 1][coords[0] - 1] != " ") {
					boatCheck.push_back(3);
					///cout << "DOWN" << endl;
				}
			}
			if (coords[0] + i - 1 <= 15) {
				if (boatBoard[coords[1] - 1][coords[0] + i - 1] != " ") {
					boatCheck.push_back(2);
					///cout << "RIGHT" << endl;
				}
			}
		}

		///for (int i = 0; i < boatCheck.size(); i++) cout << boatCheck[i] << endl;

		boatBoard[coords[1] - 1][coords[0] - 1] = toupper(ship[0]);
		if (find(boatCheck.begin(), boatCheck.end(), 1) == boatCheck.end() && orientCheck[0] != 1 && orientCheck[1] != 1) boatBoard[coords[1] - 2][coords[0] - 1] = "1";
		if (find(boatCheck.begin(), boatCheck.end(), 2) == boatCheck.end() && orientCheck[0] != 2 && orientCheck[1] != 2) boatBoard[coords[1] - 1][coords[0]] = "2";
		if (find(boatCheck.begin(), boatCheck.end(), 3) == boatCheck.end() && orientCheck[0] != 3 && orientCheck[1] != 3) boatBoard[coords[1]][coords[0] - 1] = "3";
		if (find(boatCheck.begin(), boatCheck.end(), 4) == boatCheck.end() && orientCheck[0] != 4 && orientCheck[1] != 4) boatBoard[coords[1] - 1][coords[0] - 2] = "4";

		///system("cls");
		///showBoatBoard();

		///cout << "Selecting " << ship << "'s orientation... ";
		///cout << "Eg: 1 is up, 3 is down, 4 is left, 2 is right" << endl;
		orientation = rand() % 4 + 1;

		bool goodOrientationCheck;
		bool goodBoatCheck;
		do {
			goodOrientationCheck = true;
			goodBoatCheck = true;
			if (orientation == orientCheck[0] || orientation == orientCheck[1]) goodOrientationCheck = false;
			for (int i = 0; i < boatCheck.size(); i++) if (boatCheck[i] == orientation) goodBoatCheck = false;

			if (goodOrientationCheck == false || goodBoatCheck == false) {
				///cout << "That is not an option" << endl;
				cin.clear();
				orientation = rand() % 4 + 1;
			}
		} while (goodOrientationCheck == false || goodBoatCheck == false);

		char charHolder;

		for (int i = 0; i < shipSpaces; i++)
		{
			if (orientation == 1) {
				charHolder = (coords[0]) + 96;
				shipPtr[i] = charHolder + to_string(coords[1] - i);
				boatBoard[coords[1] - 1 - i][coords[0] - 1] = toupper(ship[0]);
			}

			if (orientation == 2) {
				charHolder = (coords[0] + i) + 96;
				shipPtr[i] = charHolder + to_string(coords[1]);
				boatBoard[coords[1] - 1][coords[0] - 1 + i] = toupper(ship[0]);
			}

			if (orientation == 3) {
				charHolder = (coords[0]) + 96;
				shipPtr[i] = charHolder + to_string(coords[1] + i);
				boatBoard[coords[1] - 1 + i][coords[0] - 1] = toupper(ship[0]);
			}

			if (orientation == 4) {
				charHolder = (coords[0] - i) + 96;
				shipPtr[i] = charHolder + to_string(coords[1]);
				boatBoard[coords[1] - 1][coords[0] - 1 - i] = toupper(ship[0]);
			}
		}

		if (orientation != 2 && boatBoard[coords[1] - 1][coords[0]] == "2") boatBoard[coords[1] - 1][coords[0]] = " ";
		if (orientation != 1 && boatBoard[coords[1] - 2][coords[0] - 1] == "1") boatBoard[coords[1] - 2][coords[0] - 1] = " ";
		if (orientation != 4 && boatBoard[coords[1] - 1][coords[0] - 2] == "4") boatBoard[coords[1] - 1][coords[0] - 2] = " ";
		if (orientation != 3 && boatBoard[coords[1]][coords[0] - 1] == "3") boatBoard[coords[1]][coords[0] - 1] = " ";

		///system("cls");
		///showBoatBoard();
		///cout << endl;

		placementCount++;
		if (placementCount == 2) ship = "battleship";
		if (placementCount == 3) ship = "submarine";
		if (placementCount == 4) ship = "destroyer";
		if (placementCount == 5) ship = "patrol boat";
	}

	//place bombs
	for (int i = 0; i < 3; i++) {
		string placeCoord = "  ";
		int coords[2];

		//Randomly generates another coordinate
		do {
			coords[0] = rand() % 15 + 1;
			coords[1] = rand() % 15 + 1;
		} while (boatBoard[coords[1] - 1][coords[0] - 1] != " ");

		//create placeCoord
		placeCoord = (char)(coords[0] + 96) + to_string(coords[1]);

		//set boat coords
		boatBoard[coords[1] - 1][coords[0] - 1] = "*";
		bombs[i] = placeCoord;
	}


	/*
	for (int bombNum = 0; bombNum < 3; bombNum++) {
	string placeCoord = "  ";
	int coords[2];

	///cout << "What is the coordinate of bomb " << bombNum << ": ";

	///cout << "Selecting intial coordinate of bomb number " << bombNum << "..." << endl;

	//Randomly generates another coordinate
	coords[0] = rand() % 15 + 1;
	coords[1] = rand() % 15 + 1;


	do {
	if (size(coords) > 3)
	{
	///cout << "Coordinate size is too big. Please input one letter and one number: ";
	//Randomly generates another coordinate
	coords[0] = rand() % 15 + 1;
	coords[1] = rand() % 15 + 1;

	}
	} while (size(coords) > 3);
	do
	{
	if (coords[0] < 1 || coords[0] > 15)
	{
	///cout << "Coordinate is off the board. Please input a letter between A-0: ";
	//Randomly generates another coordinate
	coords[0] = rand() % 15 + 1;
	coords[1] = rand() % 15 + 1;


	}
	} while (coords[0] < 1 || coords[0] > 15);
	do {
	if (coords[1] < 1 || coords[1] > 15)
	{
	///cout << "Coordinate is off the board. Please input a letter between A-0: ";
	//Randomly generates another coordinate
	coords[0] = rand() % 15 + 1;
	coords[1] = rand() % 15 + 1;

	}
	} while (coords[1] < 1 || coords[1] > 15);
	do {
	if (boatBoard[coords[1] - 1][coords[0] - 1] != " ") {
	///cout << "Coordinate overlaps one of your ships. Input a new coordinate: ";

	cin.clear();

	//Randomly generates another coordinate
	coords[0] = rand() % 15 + 1;
	coords[1] = rand() % 15 + 1;
	}
	} while (boatBoard[coords[1] - 1][coords[0] - 1] != " ");

	//place bomb
	for (int i = 0; i < size(coords); i++)
	bombs[bombNum] += coords[i]; //tolower(placeCoord[i]);
	boatBoard[coords[1] - 1][coords[0] - 1] = "*";
	}
	*/
	///showBoatBoard();
}

int Player::numShots(int turn)
{
	int shotNum = 3;

	shotNum = 10 - (hitCards[turn].numHits() / 2); ///calculate number of shots
	if (shotNum < 3) shotNum = 3; ///at least 3 shots ever turn

	return shotNum;
}

void Player::getBoatBoardVal(int x, int y)
{
	//ship color
	if (boatBoard[y][x] == "C")
		setTextColor("green", "none");
	if (boatBoard[y][x] == "B")
		setTextColor("blue", "none");
	if (boatBoard[y][x] == "S")
		setTextColor("red", "none");
	if (boatBoard[y][x] == "D")
		setTextColor("pink", "none");
	if (boatBoard[y][x] == "P")
		setTextColor("yellow", "none");

	//bomb color
	if (boatBoard[y][x] == "*")
		setTextColor("darkRed", "none");

	//num color
	if (boatBoard[y][x] == "1" || boatBoard[y][x] == "2" || boatBoard[y][x] == "3" || boatBoard[y][x] == "4")
		setTextColor("white", "none");

	//show val
	cout << boatBoard[y][x];

	//original color
	if (boatBoard[y][x] != "")
		setTextColor("gray", "none");
}

void Player::getGuessBoardVal(int x, int y)
{
	//ship color
	if (guessBoard[y][x] == "C")
		setTextColor("white", "none");
	if (guessBoard[y][x] == "B")
		setTextColor("white", "none");
	if (guessBoard[y][x] == "S")
		setTextColor("white", "none");
	if (guessBoard[y][x] == "D")
		setTextColor("white", "none");
	if (guessBoard[y][x] == "P")
		setTextColor("white", "none");

	//bomb color
	if (guessBoard[y][x] == "*")
		setTextColor("white", "none");

	//guess display and color
	if (checkGuessBoardVal(x, y) == 'X') {
		string coord;
		bool hit = false, sunk = false;

		//check HitCards
		pointCoordConversion(x, y, coord);
		for (int i = 0; i < playerNum; i++) {
			if (hitCards[i].searchHitPool(coord) > 0) hit = true;

			if (hitCards[i].searchHitPool(coord) == 1 && hitCards[i].getCarrierSunk() == true) sunk = true;
			if (hitCards[i].searchHitPool(coord) == 2 && hitCards[i].getBattleshipSunk() == true) sunk = true;
			if (hitCards[i].searchHitPool(coord) == 3 && hitCards[i].getSubmarineSunk() == true) sunk = true;
			if (hitCards[i].searchHitPool(coord) == 4 && hitCards[i].getDestroyerSunk() == true) sunk = true;
			if (hitCards[i].searchHitPool(coord) == 5 && hitCards[i].getPatrolBoatSunk() == true) sunk = true;
		}

		//set appropriate color
		if (hit && !sunk) setTextColor("red", "none");
		else if (hit && sunk) setTextColor("blue", "none");
		else setTextColor("yellow", "none");

		cout << guessBoard[y][x];
	}
	else if (checkGuessBoardVal(x, y) == '!') {
		setTextColor("white", "red");
		cout << boatBoard[y][x];
	}
	else cout << guessBoard[y][x];

	//original color
	if (guessBoard[y][x] != "")
		setTextColor("gray", "none");
}

void Player::getMinimalGuessBoardVal(int x, int y)
{
	//ship color
	if (guessBoard[y][x] == "C")
		setTextColor("white", "none");
	if (guessBoard[y][x] == "B")
		setTextColor("white", "none");
	if (guessBoard[y][x] == "S")
		setTextColor("white", "none");
	if (guessBoard[y][x] == "D")
		setTextColor("white", "none");
	if (guessBoard[y][x] == "P")
		setTextColor("white", "none");

	//bomb color
	if (guessBoard[y][x] == "*")
		setTextColor("white", "none");

	//guess display and color
	if (checkGuessBoardVal(x, y) == 'X') {
		string coord;
		bool hit = false, sunk = false;

		//check HitCards
		pointCoordConversion(x, y, coord);
		for (int i = 0; i < playerNum; i++) {
			if (hitCards[i].searchHitPool(coord) > 0) hit = true;

			if (hitCards[i].searchHitPool(coord) == 1 && hitCards[i].getCarrierSunk() == true) sunk = true;
			if (hitCards[i].searchHitPool(coord) == 2 && hitCards[i].getBattleshipSunk() == true) sunk = true;
			if (hitCards[i].searchHitPool(coord) == 3 && hitCards[i].getSubmarineSunk() == true) sunk = true;
			if (hitCards[i].searchHitPool(coord) == 4 && hitCards[i].getDestroyerSunk() == true) sunk = true;
			if (hitCards[i].searchHitPool(coord) == 5 && hitCards[i].getPatrolBoatSunk() == true) sunk = true;
		}

		//set appropriate color
		if (hit && !sunk) setTextColor("red", "none");
		else if (hit && sunk) setTextColor("blue", "none");

		if (hit) cout << guessBoard[y][x];
		else cout << " ";
	}
	else if (checkGuessBoardVal(x, y) == '!') {
		setTextColor("white", "red");
		cout << boatBoard[y][x];
	}
	else cout << guessBoard[y][x];

	//original color
	if (guessBoard[y][x] != "")
		setTextColor("gray", "none");
}

void Player::getHitBoardVal(int x, int y)
{
	string coord;
	pointCoordConversion(x, y, coord);

	if (hitCards[playerID].searchHitPool(coord) > 0) {
		if (hitCards[playerID].searchHitPool(coord) == 1 && hitCards[playerID].getCarrierSunk() == true) {
			setTextColor("blue", "none");
			cout << "X";
			setTextColor("gray", "none");
		}
		else if (hitCards[playerID].searchHitPool(coord) == 2 && hitCards[playerID].getBattleshipSunk() == true) {
			setTextColor("blue", "none");
			cout << "X";
			setTextColor("gray", "none");
		}
		else if (hitCards[playerID].searchHitPool(coord) == 3 && hitCards[playerID].getSubmarineSunk() == true) {
			setTextColor("blue", "none");
			cout << "X";
			setTextColor("gray", "none");
		}
		else if (hitCards[playerID].searchHitPool(coord) == 4 && hitCards[playerID].getDestroyerSunk() == true) {
			setTextColor("blue", "none");
			cout << "X";
			setTextColor("gray", "none");
		}
		else if (hitCards[playerID].searchHitPool(coord) == 5 && hitCards[playerID].getPatrolBoatSunk() == true) {
			setTextColor("blue", "none");
			cout << "X";
			setTextColor("gray", "none");
		}
		
		else {
			setTextColor("red", "none");
			cout << "X";
			setTextColor("gray", "none");
		}
	}
	else cout << " ";
}

void Player::showBoatBoard()
{
	//white text
	setTextColor("white", "none");

	//x coord vals
	cout << "     A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  " << endl;

	//default text color
	setTextColor("gray", "none");

	for (int y = 0; y < 15; y++) {
		cout << "   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|" << endl;

		//y coord vals
		if (y < 9) {
			setTextColor("white", "none");
			cout << " " << y + 1;
			setTextColor("gray", "none");
			cout << " | ";
		}
		else {
			setTextColor("white", "none");
			cout << y + 1;
			setTextColor("gray", "none");
			cout << " | ";
		}

		//main board
		for (int x = 0; x < 15; x++) {
			getBoatBoardVal(x, y);
			cout << " | ";
		}
		setTextColor("white", "none");
		cout << y + 1 << endl;
		setTextColor("gray", "none");
	}
	cout << "   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|" << endl;
	setTextColor("white", "none");
	cout << "     A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  " << endl;
}

void Player::showGuessBoard()
{
	//white text
	setTextColor("white", "none");

	//x coord vals
	cout << "     A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  " << endl;

	//default text color
	setTextColor("gray", "none");

	for (int y = 0; y < 15; y++) {
		cout << "   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|" << endl;

		//y coord vals
		if (y < 9) {
			setTextColor("white", "none");
			cout << " " << y + 1;
			setTextColor("gray", "none");
			cout << " | ";
		}
		else {
			setTextColor("white", "none");
			cout << y + 1;
			setTextColor("gray", "none");
			cout << " | ";
		}

		//main board
		for (int x = 0; x < 15; x++) {
			getGuessBoardVal(x, y);
			cout << " | ";
		}
		setTextColor("white", "none");
		cout << y + 1 << endl;
		setTextColor("gray", "none");
	}
	cout << "   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|" << endl;
	setTextColor("white", "none");
	cout << "     A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  " << endl;
}

void Player::showMinimalGuessBoard()
{
	//white text
	setTextColor("white", "none");

	//x coord vals
	cout << "     A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  " << endl;

	//default text color
	setTextColor("gray", "none");

	for (int y = 0; y < 15; y++) {
		cout << "   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|" << endl;

		//y coord vals
		if (y < 9) {
			setTextColor("white", "none");
			cout << " " << y + 1;
			setTextColor("gray", "none");
			cout << " | ";
		}
		else {
			setTextColor("white", "none");
			cout << y + 1;
			setTextColor("gray", "none");
			cout << " | ";
		}

		//main board
		for (int x = 0; x < 15; x++) {
			getMinimalGuessBoardVal(x, y);
			cout << " | ";
		}
		setTextColor("white", "none");
		cout << y + 1 << endl;
		setTextColor("gray", "none");
	}
	cout << "   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|" << endl;
	setTextColor("white", "none");
	cout << "     A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  " << endl;
}

void Player::showHitBoard()
{
	//white text
	setTextColor("white", "none");

	//x coord vals
	cout << "     A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  " << endl;

	//default text color
	setTextColor("gray", "none");

	for (int y = 0; y < 15; y++) {
		cout << "   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|" << endl;

		//y coord vals
		if (y < 9) {
			setTextColor("white", "none");
			cout << " " << y + 1;
			setTextColor("gray", "none");
			cout << " | ";
		}
		else {
			setTextColor("white", "none");
			cout << y + 1;
			setTextColor("gray", "none");
			cout << " | ";
		}

		//main board
		for (int x = 0; x < 15; x++) {
			getHitBoardVal(x, y);
			cout << " | ";
		}
		setTextColor("white", "none");
		cout << y + 1 << endl;
		setTextColor("gray", "none");
	}
	cout << "   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|" << endl;
	setTextColor("white", "none");
	cout << "     A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  " << endl;
}

char Player::checkGuessBoardVal(int x, int y)
{
	if (guessBoard[y][x] == "X" && boatBoard[y][x] == " ") return 'X';
	if (guessBoard[y][x] == "X" && boatBoard[y][x] != " ") return '!';
}

void Player::showHitCards()
{
	for (int i = 0; i < playerNum; i++) {
		if (hitCards[i].numHits() >= 0) {
			setTextColor("white", "none");
			cout << "Player " << i + 1 << ": ";
			hitCards[i].showHitPool();
			cout << endl;
		}
	}
}

void Player::showSunkBoats()
{
	setTextColor("red", "none");
	for (int i = 0; i < playerNum; i++) {
		if (hitCards[i].getCarrierSunk()) cout << "Player " << i + 1 << "'s Carrier Sunk" << endl;
		if (hitCards[i].getBattleshipSunk()) cout << "Player " << i + 1 << "'s Battleship Sunk" << endl;
		if (hitCards[i].getSubmarineSunk()) cout << "Player " << i + 1 << "'s Submarine Sunk" << endl;
		if (hitCards[i].getDestroyerSunk()) cout << "Player " << i + 1 << "'s Destroyer Sunk" << endl;
		if (hitCards[i].getPatrolBoatSunk()) cout << "Player " << i + 1 << "'s Patrol Boat Sunk" << endl;
	}
	setTextColor("gray", "none");
}

void Player::showBoatPositions()
{
	showBoatBoard();
	cout << "Carrier: "; for (int i = 0; i < 5; i++) cout << carrier[i] << " ";
	cout << endl << "Battleship: "; for (int i = 0; i < 4; i++) cout << battleship[i] << " ";
	cout << endl << "Submarine: "; for (int i = 0; i < 3; i++) cout << submarine[i] << " ";
	cout << endl << "Destroyer: "; for (int i = 0; i < 3; i++) cout << destroyer[i] << " ";
	cout << endl << "Patrol Boat: "; for (int i = 0; i < 2; i++) cout << patrolBoat[i] << " ";
	cout << endl << "Bombs: "; for (int i = 0; i < 3; i++) cout << bombs[i] << " ";
	cout << endl;
}

bool Player::playerDefeated()
{
	if (!hitCards[playerID].getCarrierSunk()) return false;
	else if (!hitCards[playerID].getBattleshipSunk()) return false;
	else if (!hitCards[playerID].getSubmarineSunk()) return false;
	else if (!hitCards[playerID].getDestroyerSunk()) return false;
	else if (!hitCards[playerID].getPatrolBoatSunk()) return false;
	else return true;
}

void Player::writeToFile()
{
	ofstream playerData;

	//append to existing file
	playerData.open("playerData.txt", ios::app);

	if (!playerData) {
		cout << "Can't open file" << endl;
		return;
	}

	playerData << "Player " << playerID + 1 << endl;

	playerData << "Carrier Location: ";
	for (int i = 0; i < 5; i++) playerData << carrier[i] << " ";
	playerData << endl;
	playerData << "Battleship Location: ";
	for (int i = 0; i < 4; i++) playerData << battleship[i] << " ";
	playerData << endl;
	playerData << "Submarine Location: ";
	for (int i = 0; i < 3; i++) playerData << submarine[i] << " ";
	playerData << endl;
	playerData << "Destroyer Location: ";
	for (int i = 0; i < 3; i++) playerData << destroyer[i] << " ";
	playerData << endl;
	playerData << "Patrol Boat Location: ";
	for (int i = 0; i < 2; i++) playerData << patrolBoat[i] << " ";
	playerData << endl;
	playerData << "Bomb Locations: ";
	for (int i = 0; i < 3; i++) playerData << bombs[i] << " ";
	playerData << endl << endl;

	/*
	for (int i = 0; i < 5; i++) {
		
		cout << i << " What to write? " << endl;
		getline(cin, line);
		playerData << "line " << i + 1 << ": " << line << endl;
		
	}
	*/

	playerData.close();
}

string Player::broadcastGuess()
{
	//input placeCoord and convert to coords[]
	string placeCoord;
	int coords[2];

	if (playerType == 0) {
		cin >> placeCoord; ///input placeCoord
		coords[0] = (int)tolower(placeCoord[0]) - 96; ///make letter lowercase and set coords[0]
		if (placeCoord.size() == 3) coords[1] = (placeCoord[1] - 48) * 10 + (placeCoord[2] - 48); ///set coords[1] > 9
		else coords[1] = placeCoord[1] - 48; ///set coords[1] < 10
		guessCoordCheck(placeCoord, coords[0], coords[1]); ///check coords and placeCoord
	}
	else {
		Sleep(0);
		computerGuess(placeCoord, coords[1], coords[0]);
	}

	return placeCoord;
}

void Player::computerGuess(string &placeCoord, int &x, int &y)
{
	//Test modification

	do {
		x = rand() % 15 + 1;
		y = rand() % 15 + 1;
	} while (guessBoard[y - 1][x - 1] == "X");
	string coord;
	pointCoordConversion(x - 1, y - 1, coord);
	placeCoord = coord;
}


void Player::recieveAnswer(string * answers, string guess, int &shotCount, int turnShotNum)
{
	int x, y;
	coordPointConversion(guess, x, y);

	//mark guessBoard
	guessBoard[y][x] = "X";

	for (int i = 0; i < playerNum; i++) {
		if (answers[i] == "1") {
			hitCards[i].markHitPool(guess);
			hitCards[i].markCarrier(guess);
		}
		if (answers[i] == "2") {
			hitCards[i].markHitPool(guess);
			hitCards[i].markBattleship(guess);
		}
		if (answers[i] == "3") {
			hitCards[i].markHitPool(guess);
			hitCards[i].markSubmarine(guess);
		}
		if (answers[i] == "4") {
			hitCards[i].markHitPool(guess);
			hitCards[i].markDestroyer(guess);
		}
		if (answers[i] == "5") {
			hitCards[i].markHitPool(guess);
			hitCards[i].markPatrolBoat(guess);
		}
		if (answers[i] == "6") {
			shotCount = turnShotNum;
		}
	}
}

void Player::showInGameInfo(string * answers, string guess, int turn, int shotCount, int turnShotNum)
{
	bool pauseAtEnd = false;
	int noHitCount = 0;

	system("cls");
	showGuessBoard();

	setTextColor("gray", "none");
	cout << "===================================================================" << endl;

	setTextColor("green", "none");
	cout << " Player " << turn + 1 << "'s Turn        "; ///show whos turn
	setTextColor("white", "none");
	cout << "Most Recent Guess: "; ///show most recent guess
	setTextColor("yellow", "none");
	cout << guess << "        ";
	setTextColor("white", "none");
	cout << "Shot: " << shotCount + 1 << "/" << turnShotNum << endl; ///show shot count remaining
	setTextColor("gray", "none");
	cout << "===================================================================" << endl;
	setTextColor("red", "none");
	for (int i = 0; i < playerNum; i++) if (answers[i] != "0" && answers[i] != "6") cout << "Player " << i + 1 << " Hit" << endl;
	for (int i = 0; i < playerNum; i++) {
		if (answers[i] == "6") {
			cout << "Player " << i + 1 << "'s Bomb Hit" << endl;
			pauseAtEnd = true;
		}
	}
	for (int i = 0; i < playerNum; i++) if (answers[i] == "0") noHitCount++;
	setTextColor("yellow", "none");
	if (noHitCount == playerNum && guess != "--") cout << "No Players Hit" << endl;
	setTextColor("red", "none");

	cout << "Hit Cards" << endl;
	showHitCards();
	cout << "===================================================================" << endl;
	///showSunkBoats();

	if (pauseAtEnd) Sleep(0);
}

string Player::analyzeGuess(string guess)
{
	for (int i = 0; i < 5; i++) if (carrier[i] == guess) {
		return "1";
	}
	for (int i = 0; i < 4; i++) if (battleship[i] == guess) {
		return "2";
	}
	for (int i = 0; i < 3; i++) if (submarine[i] == guess) {
		return "3";
	}
	for (int i = 0; i < 3; i++) if (destroyer[i] == guess) {
		return "4";
	}
	for (int i = 0; i < 2; i++) if (patrolBoat[i] == guess) {
		return "5";
	}
	for (int i = 0; i < 3; i++) if (bombs[i] == guess) return "6";

	return "0";
}
