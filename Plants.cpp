#include "Plants.h"

#include <map>
using namespace std;

bool PlantDataInit() {
	// lifepoint; attackpoint; speed; cost;
	plants[PlantType::_NULL] = PlantData{
		0, 0, 0, 0
	};
	plants[PlantType::_Peashooter] = PlantData{
		300, 20, 14, 100
	};
	return true;
}

Plant::Plant() {
	PlantData pd = plants[PlantType::_NULL];
	lifepoint = pd.lifepoint;
	attackpoint = pd.attackpoint;
	speed = pd.speed;
	cost = pd.cost;
	x = y = -1;
	type = PlantType::_NULL;
	birth = 0;
}
Plant::Plant(int _x, int _y, PlantType _type) {
	PlantData pd = plants[_type];
	lifepoint = pd.lifepoint;
	attackpoint = pd.attackpoint;
	speed = pd.speed;
	cost = pd.cost;
	x = _x, y = _y;
	type = _type;
	birth = 0;
}
PlantType Plant::GetType() const {
	return type;
}
void Plant::SetBirth(int b) {
	birth = b;
}
int Plant::GetBirth() const {
	return birth;
}
bool Plant::AttackCheck(int tick) const {
	return !((tick - birth) % speed);
}
bool Plant::ReduceLifepoint(int atk) {
	lifepoint -= atk;
	return lifepoint > 0;
}

int Plant::GetCost(PlantType _type) {
	return plants[_type].cost;
}