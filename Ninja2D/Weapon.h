#pragma once
#include "Map.h"
#include "BaseObject.h"

class Weapon : public BaseObject
{
protected:
	bool isMoving;
	int dir; // left = 0, right = 1
	int type; // type of weapon
public:
	Weapon();
	~Weapon();
	void SetIsMoving(bool a_isMoving);
	bool GetIsMoving();
	void virtual CheckDistance();
};

