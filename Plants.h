#pragma once

#include <map>

enum class PlantType {
	_NULL = -1,
	_Peashooter,
	_SunFlower,
};

struct PlantData {
	int lifepoint,
		attackpoint,
		speed,
		cost;
};

static std::map <PlantType, PlantData> plants;

class Plant {
private:
	int lifepoint,
		attackpoint,
		speed,
		cost;
	int x, y, birth;
	PlantType type;
public:
	Plant();
	Plant(int _x, int _y, PlantType _type);
	PlantType GetType() const;
	void SetBirth(int b);
	int GetBirth() const;
	bool AttackCheck(int tick) const;
	bool ReduceLifepoint(int atk);
	static int GetCost(PlantType _type);
};