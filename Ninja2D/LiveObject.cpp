#include "LiveObject.h"

LiveObject::LiveObject()
{
	isDead = false;
}


LiveObject::~LiveObject() 
{

}



int  LiveObject::GetWidth()
{
	return 0;
}

int  LiveObject::GetHeight()
{
	return 0;
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
	return this->isDead;
}

void LiveObject::SetDeath(bool a_isDead)
{
	this->isDead = a_isDead;
}

