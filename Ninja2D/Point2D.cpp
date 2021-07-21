#include "Point2D.h"

Point2D::Point2D()
{
	posX = 0;
	posY = 0;
}

Point2D::~Point2D()
{

}

Point2D::Point2D(int a_posX, int a_posY)
{
	posX = a_posX;
	posY = a_posY;
}

int Point2D::GetPosX()
{
	return this->posX;
}

void Point2D::SetPosX(int a_posX)
{
	this->posX = a_posX;
}

int Point2D::GetPosY()
{
	return this->posY;
}

void Point2D::SetPosY(int a_posY)
{
	this->posX = a_posY;
}

bool Point2D::CheckPointInsideRect (Point2D origin, int height, int width)
{
	bool CheckInside = false;
	if ((posX >= origin.GetPosX()) && (posX <= origin.GetPosX() + width)
		&& (posY >= origin.GetPosY()) && posY <= origin.GetPosY() + height)
	{
		CheckInside = true;
	}
	return CheckInside;
}
