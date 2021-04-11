#pragma once

#include <map>

enum class ZombieType {
	_NULL = -1,
	_NORMAL,
};

struct ZombieData {
	int lifepoint,
		attackpoint,
		movespeed,
		attackspeed,
		point;
};

static std::map <ZombieType, ZombieData> zombies;

class Zombie {
private:
	int lifepoint,
		attackpoint,
		movespeed,
		attackspeed;
	int x, y, birth;
	ZombieType type;
public:
	Zombie();
	Zombie(int _x, int _y, ZombieType _type);
	ZombieType GetType() const;
	void SetBirth(int b);
	int GetBirth() const;
	bool MoveCheck(int tick) const;
	bool AttackCheck(int tick) const;
	bool ReduceLifepoint(int atk);
	void SetLocation(int _x, int _y);
	static int GetPoint(ZombieType _type);
	static int GetAttackPoint(ZombieType _type);
};