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
	isMoving = a_isMoving;
}

bool  Weapon::GetIsMoving()
{
	return isMoving;
}

void  Weapon::CheckDistance()
{

}
