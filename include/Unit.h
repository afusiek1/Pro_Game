#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"

class Unit: public Entity {
protected:
	double health;
	int shootingRange;
	int detectionRange;
	double damage;
	double shootingSpeed;
	int armor;
	bool isArmorPiercing;
	std::string type;

public:
	Unit(double HP, int SR, int DR, double DMG, double SS, int MS, int A, bool iAP, std::string Class, Vec2D pos, const LTexture* pointer, Vec2D size2);
	Unit();

	bool istype(const std::string& isClass) const { return type == isClass; }
};

#endif //UNIT_H