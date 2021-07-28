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
	return typeOfWeapn;
}

bool Item::CheckDeath()
{
	return isDead;
}