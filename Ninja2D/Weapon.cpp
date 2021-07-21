#include "Weapon.h"

Weapon::Weapon()
{
	bool isMoving = false;
}

Weapon::~Weapon()
{

}

void Weapon::SetIsMoving(bool a_isMoving)
{
	this->isMoving = a_isMoving;
}

bool  Weapon::GetIsMoving()
{
	return this->isMoving;
}

void  Weapon::CheckDistance()
{

}
