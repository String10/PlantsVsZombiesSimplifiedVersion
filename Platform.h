#pragma once
#include "Plants.h"
#include "Zombies.h"
#include "Bullets.h"

class Platform {
private:
	int x, y;
	Plant* plant;
	Zombie* zombie;
	Bullet* bullet;
public:
	Platform();
	Platform(int _x, int _y);
	bool AddPlant(PlantType type);
	bool AddZombie(ZombieType type);
	bool AddZombie(Zombie const* _zombie);
	bool AddBullet(BulletType type);
	bool AddBullet(Bullet const* _bullet);
	void RemovePlant();
	void RemoveZombie();
	void RemoveBullet();
	Plant* GetPlant();
	Zombie* GetZombie();
	Bullet* GetBullet();
};