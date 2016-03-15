#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <string>
using namespace std;

void coordPointConversion(string coord, int &x, int &y);
void pointCoordConversion(int x, int y, string &coord);
void setTextColor(string text, string background);
int getInt();
void welcomeScreen();