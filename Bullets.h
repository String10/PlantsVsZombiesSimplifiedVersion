#pragma once

#include <map>

enum class BulletType {
	_NULL = -1,
	_NORMAL,
	_FREEZING,
	_BURNING,
};

struct BulletData {
	int attackpoint,
		speed;
};

static std::map <BulletType, BulletData> bullets;

class Bullet {
private:
	int attackpoint,
		speed;
	int x, y, birth;
	BulletType type;
public:
	Bullet();
	Bullet(int _x, int _y, BulletType _type);
	BulletType GetType() const;
	void SetBirth(int b);
	int GetBirth() const;
	bool MoveCheck(int tick) const;
	void AddBullet(const Bullet& bullet);
	void SetLocation(int _x, int _y);
	int GetAttackPoint() const;
};