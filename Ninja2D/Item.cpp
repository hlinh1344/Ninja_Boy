#include "Item.h"

Item::Item()
{
	isDead = false;
}

Item::~Item()
{

}

int Item::GetTypeOfWeapn()
{
	return this->typeOfWeapn;
}

bool Item::CheckDeath()
{
	return this->isDead;
}