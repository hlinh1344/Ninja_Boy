#include "LiveObject.h"

LiveObject::LiveObject()
{
	clock = 0;
}


LiveObject::~LiveObject() 
{

}

void LiveObject::MoveLeft()
{

}

void LiveObject::MoveRight()
{

}

void LiveObject::MoveUp()
{

}

void LiveObject::MoveDown()
{

}
bool LiveObject::IsGoLeft()
{
	return false;
}

bool LiveObject::IsGoRight()
{
	return false;
}


bool LiveObject::CheckDeath()
{
	return isDead;
}


void LiveObject::MakeAnimation()
{

}