#pragma once
#include "LiveObject.h"
#include "Map.h"

class Enemy : public LiveObject
{
protected:
	int originalLocation;
public:
	Enemy();
	~Enemy();
};

