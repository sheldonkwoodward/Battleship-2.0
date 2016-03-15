#include "basicFunctions.h"

void coordPointConversion(string coord, int &x, int &y)
{
	x = (int)coord[0] - 97;
	if (coord.size() == 2) y = (int)coord[1] - 49;
	if (coord.size() == 3) y = ((int)coord[1] - 48) * 10 + ((int)coord[2] - 48) - 1;
}

void pointCoordConversion(int x, int y, string &coord)
{
	char charHolder = x + 97;
	coord = charHolder + to_string(y + 1);
}

void setTextColor(string text, string background)
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	///CONSOLE_SCREEN_BUFFER_INFO originalColor;
	///GetConsoleScreenBufferInfo(hstdout, &originalColor);

	if (text == "red" && background == "none") {
		SetConsoleTextAttribute(hstdout, 0x0C);
	}
	if (text == "yellow" && background == "none") {
		SetConsoleTextAttribute(hstdout, 0x0E);
	}
	if (text == "green" && background == "none") {
		SetConsoleTextAttribute(hstdout, 0x0A);
	}
	if (text == "blue" && background == "none") {
		SetConsoleTextAttribute(hstdout, 0x0B);
	}
	if (text == "pink" && background == "none") {
		SetConsoleTextAttribute(hstdout, 0x0D);
	}
	if (text == "white" && background == "none") {
		SetConsoleTextAttribute(hstdout, 0x0F);
	}
	if (text == "gray" && background == "none") {
		SetConsoleTextAttribute(hstdout, 0x07);
	}
	if (text == "darkRed" && background == "none") {
		SetConsoleTextAttribute(hstdout, 0x04);
	}

	if (text == "white" && background == "red") {
		SetConsoleTextAttribute(hstdout, 0xCF);
	}
}

int getInt()
{
	string input;
	do {
		getline(cin, input);
	} while (input.size() > 1);
	cin.clear();
	return (int)input[0] - 48;
}

void welcomeScreen()
{
	setTextColor("white", "none");
	cout << "Welcome to: " << endl;
	setTextColor("red", "none");
	cout << "    ____  ___  ______________    ___________ __  __________     ___    ____  " << endl;
	cout << "   / __ )/   |/_  __/_  __/ /   / ____/ ___// / / /  _/ __ \\   |__ \\  / __ \\ " << endl;
	cout << "  / __  / /| | / /   / / / /   / __/  \\__ \\/ /_/ // // /_/ /   __/ / / / / / " << endl;
	cout << " / /_/ / ___ |/ /   / / / /___/ /___ ___/ / __  // // ____/   / __/_/ /_/ /  " << endl;
	cout << "/_____/_/  |_/_/   /_/ /_____/_____//____/_/ /_/___/_/       /____(_)____/   " << endl;
	cout << endl;
	setTextColor("white", "none");
do {
	cout << "Press enter to continue..." << endl;
} while (cin.get() != '\n');
cin.clear();
system("cls");
}