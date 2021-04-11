/***************************************
cout << "原色testCOLOR（没有设置字体颜色）" << endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
	FOREGROUND_GREEN | FOREGROUND_BLUE);
//设置三色相加
cout << "白色testCOLOR（红色绿色蓝色相加）" << endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
//设置红色
cout << "红色testCOLOR（设置的颜色为红色）" << endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
//设置绿色
cout << "绿色testCOLOR（设置的颜色为绿色）" << endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
//设置蓝色
cout << "蓝色testCOLOR（设置的颜色为蓝色）" << endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
	FOREGROUND_GREEN);
//设置红色和绿色相加
cout << "黄色testCOLOR（红色和绿色相加色）" << endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
	FOREGROUND_BLUE);
//设置红色和蓝色相加
cout << "粉色testCOLOR（红色和蓝色相加色）" << endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
	FOREGROUND_BLUE);
//设置绿色和蓝色相加
cout << "青色testCOLOR（绿色和蓝色相加色）" << endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
//设置颜色，没有添加颜色，故为原色
cout << endl;
***************************************/

#include "Game.h"

#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
#include <thread>
using namespace std;

const int PlantCount = 1;

static thread display;
static Game game;
static bool showingShop = false;
static bool showingPlace = false;
static int selectedPlant = -1;
static int selectedPlaceX = -1, selectedPlaceY = -1;
static bool gameover = false;

// Funtions
bool Welcome();
void Exit();
void GameStart();
void ShowShop(int _i);
void PrintToScreen();
void GameOver();

bool Welcome() {
	system("cls");
	cout << "-------------------------------------------------------------" << endl;
	cout << "|                Welcome to PlantsVsZombies!                |" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << endl;
	cout << "            Press E to start, or press X to exit.            " << endl;
	char c = _getch();
	while (c != 'e' && c != 'x') {
		c = _getch();
	}
	return c == 'e';
}
void Exit() {
	cout << "-------------------------------------------------------------" << endl;
	cout << "|                Do you really want to exit?                |" << endl;
	cout << "|      Press E to confirm or something else to cancel.      |" << endl;
	cout << "-------------------------------------------------------------" << endl;
	char c = _getch();
	if (c == 'e') {
		system("cls");
		cout << "Looking forward to see you again!" << endl;
		Sleep(500);
		exit(0);
	}
}
void GameStart() {
	while (!Welcome()) {
		Exit();
	}
	display = thread(PrintToScreen);
	display.detach();
	char c;
	while (true && !gameover) {
		c = _getch();

		if (!showingPlace) {
			switch (c)
			{
			case 'e':
				if (!showingShop) {
					showingShop = true;
					selectedPlant = 0;
				}
				else {
					if (game.PlantAffordable((PlantType)selectedPlant)) {
						showingShop = false;
						showingPlace = true;
						selectedPlaceX = selectedPlaceY = 0;
					}
				}
				break;
			case 'a':
				if (showingShop && selectedPlant > 0) {
					--selectedPlant;
				}
				break;
			case 'd':
				if (showingShop && selectedPlant < PlantCount - 1) {
					++selectedPlant;
				}
				break;
			default:
				showingShop = showingPlace = false;
				selectedPlant = selectedPlaceX = selectedPlaceY = -1;
				break;
			}
		}
		else {
			switch (c)
			{
			case 'e':
				if (game.AddPlant(selectedPlaceX, selectedPlaceY, (PlantType)selectedPlant)) {
					game.PlantTrade((PlantType)selectedPlant);
					showingShop = showingPlace = false;
					selectedPlant = selectedPlaceX = selectedPlaceY = -1;
				}
				break;
			case 'w':
				if (selectedPlaceX > 0) {
					--selectedPlaceX;
				}
				break;
			case 's':
				if (selectedPlaceX < WIDTH - 1) {
					++selectedPlaceX;
				}
				break;
			case 'a':
				if (selectedPlaceY > 0) {
					--selectedPlaceY;
				}
				break;
			case 'd':
				if (selectedPlaceY < LENGTH - 1) {
					++selectedPlaceY;
				}
				break;
			default:
				showingShop = true;
				showingPlace = false;
				selectedPlaceX = selectedPlaceY = -1;
				break;
			}
		}
	}
}
void ShowShop(int _i) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "----------------------------------------------------------" << endl;
	cout << "|    Press E and buy some plants to protect YOURSELF!    |" << endl;
	cout << "| Use A and D to select plant and E to confirm purchase. |" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "| Peashooter |" << endl;
	cout << "|    100     |" << endl;
	for (int i = 0; i < PlantCount; i++) {
		if (i == _i) {
			cout << "@@@@@@@@@@@@@@" << endl;
		}
		else {
			cout << "--------------" << endl;
		}
	}
}
void PrintToScreen() {
	// system("cls");
	/*cout << "               Press Q to quit this game.               " << endl;
	cout << endl;*/

	//// Get DefaultStandardOutputBuffer
	//HANDLE hOutput;
	//COORD coord = { 0, 0 };
	//hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	//// Create NewOutputBuffer
	//HANDLE hOutBuf = CreateConsoleScreenBuffer(
	//	GENERIC_READ | GENERIC_WRITE,
	//	FILE_SHARE_READ | FILE_SHARE_WRITE,
	//	NULL,
	//	CONSOLE_TEXTMODE_BUFFER,
	//	NULL
	//);

	//// Set NewOutputBuffer as ScreenBuffer
	//SetConsoleActiveScreenBuffer(hOutBuf);

	//// Hide the cursor
	//CONSOLE_CURSOR_INFO cci;
	//cci.bVisible = false;
	//cci.dwSize = 1;
	//SetConsoleCursorInfo(hOutput, &cci);
	//SetConsoleCursorInfo(hOutBuf, &cci);

	//// DoubleBuffer Settings
	//const int len = 2000;
	//DWORD bytes = 0;
	//char data[len];

	while (true) {
		if (!game.Run()) {
			break;
		}
		system("cls");
		game.Display(selectedPlaceX, selectedPlaceY);
		ShowShop(selectedPlant);

		//// DoubleBuffer
		//ReadConsoleOutputCharacterA(hOutput, data, len, coord, &bytes);
		//WriteConsoleOutputCharacterA(hOutBuf, data, len, coord, &bytes);

		Sleep(100);
	}
	gameover = true;
	GameOver();
}
void GameOver() {
	system("cls");
	// Red
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "----------------------------------------------------------" << endl;
	cout << "|               ZOMBIES EAT YOUR BRIAN!!!                |" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "Point: " << game.GetPoint() << endl;
	// Default
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}