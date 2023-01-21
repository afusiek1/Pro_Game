#include "Unit.h"



Unit::Unit(double HP, int SR, int DR, double DMG, double SS, int MS, int A, bool iAP, std::string Class, Vec2D pos, const LTexture* pointer, Vec2D size2)
	:Entity(pos, pointer, size2), health(HP), shootingRange(SR), detectionRange(DR), damage(DMG), shootingSpeed(SS), armor(A), isArmorPiercing(iAP), type(Class) {
	maximumSpeed = MS;
}

Unit::Unit()
	:Entity(), health(100), shootingRange(100), detectionRange(120), damage(30), shootingSpeed(1), isArmorPiercing(false), armor(0), type("None") {
}



