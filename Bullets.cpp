#include "Bullets.h"

#include <map>
using namespace std;

bool BulletDataInit() {
	// attackpoint; speed;
	bullets[BulletType::_NULL] = BulletData{
		0, 0
	};
	bullets[BulletType::_NORMAL] = BulletData{
		20, 5
	};
	return true;
}
Bullet::Bullet() {
	BulletData bd = bullets[BulletType::_NULL];
	attackpoint = bd.attackpoint;
	speed = bd.speed;
	x = y = -1;
	type = BulletType::_NULL;
	birth = 0;
}
Bullet::Bullet(int _x, int _y, BulletType _type) {
	BulletData bd = bullets[_type];
	attackpoint = bd.attackpoint;
	speed = bd.speed;
	x = _x, y = _y;
	type = _type;
	birth = 0;
}
BulletType Bullet::GetType() const {
	return type;
}
void Bullet::SetBirth(int b) {
	birth = b;
}
int Bullet::GetBirth() const {
	return birth;
}
bool Bullet::MoveCheck(int tick) const {
	return !((tick - birth) % speed);
}
void Bullet::AddBullet(const Bullet& bullet) {
	attackpoint += bullet.attackpoint;
	switch (bullet.type) {
	case BulletType::_NULL:
		break;
	case BulletType::_NORMAL:
		break;
	default:
		break;
	}
}
void Bullet::SetLocation(int _x, int _y) {
	x = _x, y = _y;
}
int Bullet::GetAttackPoint() const {
	return attackpoint;
}