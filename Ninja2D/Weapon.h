#pragma once
#include "Map.h"
#include "LiveObject.h"

class Weapon : public LiveObject
{
protected:
	bool isMoving;
	int dir; // left = 0, right = 1
public:
	Weapon();
	~Weapon();
	void SetIsMoving(bool a_isMoving);
	bool GetIsMoving();
	void virtual CheckDistance();
};

