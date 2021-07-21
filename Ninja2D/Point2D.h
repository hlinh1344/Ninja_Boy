#pragma once
class Point2D
{
private:
	int posX;
	int posY;

public:
	Point2D();
	~Point2D();
	Point2D(int a_posX, int a_posY);
	int GetPosX();
	void SetPosX(int a_posX);
	int GetPosY();
	void SetPosY(int a_posY);
	bool CheckPointInsideRect(Point2D origin, int height, int width);

};

