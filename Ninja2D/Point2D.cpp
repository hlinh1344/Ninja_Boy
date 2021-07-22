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

bool Point2D::CheckCollision(int height1, int width1,
	Point2D A2, int height2, int width2)
{
	bool isColliding = false;

	int left1 = this->posX;
	int right1 = this->posX + width1;
	int top1 = this->posY;
	int bot1 = this->posY + height1;

	int left2 = A2.GetPosX();
	int right2 = A2.GetPosX() + width2;
	int top2 = A2.GetPosY();
	int bot2 = A2.GetPosY() + height2;

	Point2D A1 = Point2D(this->posX, this->posY);
	Point2D B1 = Point2D(right1, top1);
	Point2D C1 = Point2D(right1, bot1);
	Point2D D1 = Point2D(left1, bot1);

	Point2D B2 = Point2D(right2, top2);
	Point2D C2 = Point2D(right2, bot2);
	Point2D D2 = Point2D(left2, bot2);

	if (A1.CheckPointInsideRect(left2, right2, top2, bot2))
	{
		isColliding = true;
	}
	else if (B1.CheckPointInsideRect(left2, right2, top2, bot2))
	{
		isColliding = true;
	}
	else if (C1.CheckPointInsideRect(left2, right2, top2, bot2))
	{
		isColliding = true;
	}
	else if (D1.CheckPointInsideRect(left2, right2, top2, bot2))
	{
		isColliding = true;
	}
	else if (A2.CheckPointInsideRect(left1, right1, top1, bot1))
	{
		isColliding = true;
	}
	else if (B2.CheckPointInsideRect(left1, right1, top1, bot1))
	{
		isColliding = true;
	}
	else if (C2.CheckPointInsideRect(left1, right1, top1, bot1))
	{
		isColliding = true;
	}
	else if (D2.CheckPointInsideRect(left1, right1, top1, bot1))
	{
		isColliding = true;
	}

	return isColliding;
}

bool Point2D::CheckPointInsideRect(int left, int right, int top, int bot)
{

	bool checkInside = false;

	if ((this->posX >= left) && (this->posX <= right)
		&& (this->posY >= top) && (this->posY <= bot))
	{
		checkInside = true;
	}
	return checkInside;
}