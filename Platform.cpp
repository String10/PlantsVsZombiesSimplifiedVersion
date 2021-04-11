#include "Platform.h"

Platform::Platform() {
	x = y = -1;
	plant = nullptr;
	zombie = nullptr;
	bullet = nullptr;
}
Platform::Platform(int _x, int _y) {
	x = _x, y = _y;
	plant = nullptr;
	zombie = nullptr;
	bullet = nullptr;
}
bool Platform::AddPlant(PlantType type) {
	if (plant != nullptr) {
		return false;
	}
	plant = new Plant(x, y, type);
	return true;
}
bool Platform::AddZombie(ZombieType type) {
	if (zombie != nullptr) {
		return false;
	}
	zombie = new Zombie(x, y, type);
	return true;
}
bool Platform::AddZombie(Zombie const* _zombie) {
	if (zombie != nullptr) {
		return false;
	}
	zombie = new Zombie(*_zombie);
	zombie->SetLocation(x, y);
	return true;
}
bool Platform::AddBullet(BulletType type) {
	if (bullet == nullptr) {
		bullet = new Bullet(x, y, type);
	}
	else {
		bullet->AddBullet(Bullet(-1, -1, type));
	}
	return true;
}
bool Platform::AddBullet(Bullet const* _bullet) {
	if (bullet == nullptr) {
		bullet = new Bullet(*_bullet);
		bullet->SetLocation(x, y);
	}
	else {
		bullet->AddBullet(*_bullet);
	}
	return true;
}
void Platform::RemovePlant() {
	if (plant != nullptr) {
		delete plant;
		plant = nullptr;
	}
}
void Platform::RemoveZombie() {
	if (zombie != nullptr) {
		delete zombie;
		zombie = nullptr;
	}
}
void Platform::RemoveBullet() {
	if (bullet != nullptr) {
		delete bullet;
		bullet = nullptr;
	}
}
Plant* Platform::GetPlant() {
	return plant;
}
Zombie* Platform::GetZombie() {
	return zombie;
}
Bullet* Platform::GetBullet() {
	return bullet;
}