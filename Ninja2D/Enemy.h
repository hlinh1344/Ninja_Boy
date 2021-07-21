#pragma once
#include "BaseObject.h"
#include "Map.h"

class Enemy : public BaseObject
{
protected:
	int originalLocation;
public:
	Enemy();
	~Enemy();
	virtual void MakeAnimation();
};

