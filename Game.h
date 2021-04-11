#pragma once
#include "Platform.h"

const int WIDTH = 3, LENGTH = 7;
const int SUNLIGHTINCREMENT = 25;
const int SUNLIGHTPRODUCECYCLE = 15;
const int CYCLE = 1e6;
const int ZOMBIEPRODUCECYCLE = 30;

class Game {
private:
	Platform* platforms[WIDTH][LENGTH];
	int sunlight, point, tick;
public:
	Game();
	~Game();
	void Display(int x, int y) const;
	bool Run();
	bool PlantAffordable(PlantType type) const;
	void PlantTrade(PlantType type);
	bool AddPlant(int x, int y, PlantType type);
	bool AddZombie(int x, int y, ZombieType type);
	bool AddBullet(int x, int y, BulletType type);
	int GetPoint() const;
};