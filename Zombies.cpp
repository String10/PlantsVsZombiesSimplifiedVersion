#include "Zombies.h"

#include <map>
using namespace std;

bool ZombieDataInit() {
	// lifepoint; attackpoint; movespeed; attackspeed;
	zombies[ZombieType::_NULL] = ZombieData{
		0, 0, 0, 0, 0
	};
	zombies[ZombieType::_NORMAL] = ZombieData{
		100, 100, 47, 10, 1
	};
	return true;
}

Zombie::Zombie() {
	ZombieData zd = zombies[ZombieType::_NULL];
	lifepoint = zd.lifepoint;
	attackpoint = zd.attackpoint;
	movespeed = zd.movespeed;
	attackspeed = zd.attackspeed;
	x = y = -1;
	type = ZombieType::_NULL;
	birth = 0;
}
Zombie::Zombie(int _x, int _y, ZombieType _type) {
	ZombieData zd = zombies[_type];
	lifepoint = zd.lifepoint;
	attackpoint = zd.attackpoint;
	movespeed = zd.movespeed;
	attackspeed = zd.attackspeed;
	x = _x, y = _y;
	type = _type;
	birth = 0;
}
ZombieType Zombie::GetType() const {
	return type;
}
void Zombie::SetBirth(int b) {
	birth = b;
}
int Zombie::GetBirth() const {
	return birth;
}
bool Zombie::MoveCheck(int tick) const {
	return !((tick - birth) % movespeed);
}
bool Zombie::AttackCheck(int tick) const {
	return !((tick - birth) % attackspeed);
}
bool Zombie::ReduceLifepoint(int atk) {
	lifepoint -= atk;
	return lifepoint > 0;
}
void Zombie::SetLocation(int _x, int _y) {
	x = _x, y = _y;
}

int Zombie::GetPoint(ZombieType _type) {
	return zombies[_type].point;
}
int Zombie::GetAttackPoint(ZombieType _type) {
	return zombies[_type].attackpoint;
}