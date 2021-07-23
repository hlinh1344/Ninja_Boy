#pragma once
#include "BaseObject.h"

#define MAP_WIDTH 985
#define MAP_HEIGHT 290
#define CLOUD_HEIGHT 246
#define CLOUD_WIDTH 5218
#define CLOUD_SPEED 1
#define NUMBER_OF_MONSTERS 20
#define END_OF_MAP 3650
#define NUMBER_OF_ITEMS 5

class Map :public BaseObject
{
private:
	HBITMAP hbmGround, hbmCloud;
	int enemiesPosition[NUMBER_OF_MONSTERS] = { 1000, 1005, 1010, 1800, 2195,
		2400 ,2495 ,2600, 2700,
		2800, 3000, 3035,3070, 3100,
		3150, 3200,  3245,  3270, 3300, 3360 };
	int itemsPosition[NUMBER_OF_ITEMS] = { 1000, 1500, 2000, 2500, 3000 };
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
