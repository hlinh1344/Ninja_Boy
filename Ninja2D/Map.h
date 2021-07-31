#pragma once
#include "BaseObject.h"

#define MAP_WIDTH 985
//#define MAP_HEIGHT 290
#define MAP_HEIGHT 536
//#define CLOUD_HEIGHT 246

#define NUMBER_OF_MONSTERS 20
#define END_OF_MAP 3655
#define NUMBER_OF_ITEMS 10

class Map :public BaseObject
{
private:
	HBITMAP hbmGround, hbmCloud, hbmMask;
	
	int enemiesPosition[NUMBER_OF_MONSTERS] = { 1000, 1230, 1345, 1460,
		1575 ,1690 ,1805, 1920,
		2035, 2150, 2265, 2380, 2495,
		2610, 2725,  2840,  2955, 3070, 3185, 3300 };

	int itemsPosition[NUMBER_OF_ITEMS] = { 1050, 1350, 1600, 1800, 2000, 2200,
		2400, 2600, 2800, 3000};
public:

	Map();
	~Map();
	void Draw(HWND hwnd, HDC hdc, HDC hdcMem) override;
	void increseMapSlider(int a);
	int getMapSlider();
	void checkToAddEnemy(int a_posX, int &enemyID, bool &checkToAdd);
	void checkToAddItem(int a_posX, int& itemyID, bool& checkToAdd);
};
