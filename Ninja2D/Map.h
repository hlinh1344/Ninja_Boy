#pragma once
#include "BaseObject.h"

#define MAP_WIDTH 984
#define MAP_HEIGHT 290
#define CLOUD_HEIGHT 246
#define CLOUD_WIDTH 5218
#define CLOUD_SPEED 1
#define NUMBER_OF_MONSTERS 9
#define END_OF_MAP 3650
#define NUMBER_OF_ITEMS 5

class Map :public BaseObject
{
private:
	HBITMAP hbmGround, hbmCloud;
	int enemiesPosition[NUMBER_OF_MONSTERS] = {1000, 1300, 1600, 1900, 2100, 2400, 2700, 3000, 3300 };
	int itemsPosition[NUMBER_OF_ITEMS] = { 1100, 1500, 2200, 2700, 3100 };
public:

	Map();
	~Map();
	void Draw(HWND hwnd, HDC hdc) override;
	void increseMapSlider(int a);
	void increseClousDrifting(int a);
	int getMapSlider();
	void checkToAddEnemy(int a_posX, int &enemyID, bool &checkToAdd);
	void checkToAddItem(int a_posX, int& itemyID, bool& checkToAdd);
};
