#pragma once
#include "BaseObject.h"

#define MAP_WIDTH 984
#define MAP_HEIGHT 290
#define CLOUD_HEIGHT 246
#define CLOUD_WIDTH 5218
#define CLOUD_SPEED 1
#define NUMBER_OF_MONSTERS 6
#define END_OF_MAP 3650

class Map :public BaseObject
{
private:
	HBITMAP hbmGround, hbmCloud;
	int enemiesPosition[NUMBER_OF_MONSTERS] = { 1000, 1600, 2100, 2700, 3200 };
public:

	Map();
	~Map();
	void Draw(HWND hwnd, HDC hdc) override;
	void increseMapSlider(int a);
	void increseClousDrifting(int a);
	int getMapSlider();
	int checkToAddEnemy(int a_posX);
};


