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
	bool CheckCollision(int height1, int width1, Point2D A2, int height2, int width2);

	bool CheckPointInsideRect(int left, int right, int top, int bot);

};

