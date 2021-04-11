#include "Game.h"
#include "Platform.h"
#include "Plants.h"

#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

Game::Game() {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			platforms[i][j] = new Platform(i, j);
		}
	}
	sunlight = 50;
	point = tick = 0;
}
Game::~Game() {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			platforms[i][j]->RemovePlant();
			platforms[i][j]->RemoveBullet();
			platforms[i][j]->RemoveZombie();
			delete platforms[i][j];
		}
	}
}
void Game::Display(int x, int y) const {
	// Green
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	for (int j = 0; j < WIDTH; j++) {
		for (int i = 0; i <= 3 * LENGTH + 1; i++) {
			cout << '=';
		}
		cout << endl;
		for (int i = 0; i < LENGTH; i++) {
			cout << "#";

			if (platforms[j][i]->GetBullet() == nullptr) {
				cout << ' ';
			}
			else {
				switch (platforms[j][i]->GetBullet()->GetType()) {
				case BulletType::_NORMAL:
					// Cyan
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
					cout << 'O';
					// Green
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
					break;
				default:
					break;
				}
			}

			if (platforms[j][i]->GetZombie() == nullptr) {
				cout << ' ';
			}
			else {
				switch (platforms[j][i]->GetZombie()->GetType()) {
				case ZombieType::_NORMAL:
					// Yellow
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
					cout << '@';
					// Green
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
					break;
				default:
					break;
				}
			}
		}
		cout << '#' << endl;
		for (int i = 0; i < LENGTH; i++) {
			cout << "#";
			if (platforms[j][i]->GetPlant() == nullptr) {
				cout << ' ';
			}
			else {
				switch (platforms[j][i]->GetPlant()->GetType()) {
				case PlantType::_Peashooter:
					// White
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					cout << 'P';
					// Green
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
					break;
				default:
					break;
				}
			}
			// Yellow
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			if (j == x && i == y) {
				cout << '*';
			}
			else {
				cout << ' ';
			}
			// Green
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		}
		cout << '#' << endl;
	}
	for (int i = 0; i <= 3 * LENGTH + 1; i++) {
		cout << '=';
	}
	cout << endl;
	cout << "Present Sunlight : " << sunlight << endl;
	cout << "Present Point : " << point << endl;
}
bool Game::Run() {
	tick = (tick + 1) % CYCLE;
	if (!(tick % SUNLIGHTPRODUCECYCLE)) {
		sunlight += SUNLIGHTINCREMENT;
	}
	srand(time(NULL));
	if (!(tick % ZOMBIEPRODUCECYCLE)) {
		int ind = rand() % WIDTH;
		while (!platforms[ind][LENGTH - 1]->AddZombie(ZombieType::_NORMAL)) {
			ind = rand() % WIDTH;
		}
	}

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			Platform* platform = platforms[i][j];
			Plant* plant = platform->GetPlant();
			if (plant != nullptr && plant->AttackCheck(tick)) {
				switch (plant->GetType()) {
				case PlantType::_NULL:
					break;
				case PlantType::_Peashooter:
					AddBullet(i, j, BulletType::_NORMAL);
					break;
				default:
					break;
				}
			}
		}
		for (int j = LENGTH - 1; j >= 0; j--) {
			Platform* platform = platforms[i][j];
			Bullet* bullet = platform->GetBullet();
			if (bullet != nullptr) {
				Zombie* zombie = platform->GetZombie();
				if (zombie != nullptr) {
					if (!zombie->ReduceLifepoint(bullet->GetAttackPoint())) {
						point += Zombie::GetPoint(zombie->GetType());
						platform->RemoveZombie();
					}
					platform->RemoveBullet();
				}
				if (bullet->MoveCheck(tick)) {
					if (j + 1 < LENGTH) {
						platforms[i][j + 1]->AddBullet(bullet);
					}
					platform->RemoveBullet();
				}
			}
		}
		for (int j = 0; j < LENGTH; j++) {
			Platform* platform = platforms[i][j];
			Zombie* zombie = platform->GetZombie();
			Plant* plant = platform->GetPlant();
			if (zombie != nullptr && zombie->AttackCheck(tick)) {
				if (plant != nullptr && !plant->ReduceLifepoint(Zombie::GetAttackPoint(zombie->GetType()))) {
					platform->RemovePlant();
				}
			}
			plant = platform->GetPlant();
			if (zombie != nullptr && zombie->MoveCheck(tick) && plant == nullptr) {
				if (j > 0 && platforms[i][j - 1]->AddZombie(zombie)) {
					platform->RemoveZombie();
				}
				else {
					return false;
				}
			}
		}
	}
	return true;
}
bool Game::PlantAffordable(PlantType type) const {
	return Plant::GetCost(type) <= sunlight;
}
void Game::PlantTrade(PlantType type) {
	sunlight -= Plant::GetCost(type);
}
bool Game::AddPlant(int x, int y, PlantType type) {
	bool res = platforms[x][y]->AddPlant(type);
	if (res) {
		platforms[x][y]->GetPlant()->SetBirth(tick);
	}
	return res;
}
bool Game::AddZombie(int x, int y, ZombieType type) {
	return true;
}
bool Game::AddBullet(int x, int y, BulletType type) {
	platforms[x][y]->AddBullet(type);
	return true;
}
int Game::GetPoint() const {
	return point;
}