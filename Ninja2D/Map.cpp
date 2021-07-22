#include "Map.h"

Map::Map()
{
	posX = 0;
	posY = 0;
	hbmGround = (HBITMAP)LoadImage(hInst, L"map.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmCloud = (HBITMAP)LoadImage(hInst, L"cloud.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}
Map::~Map()
{

}

void Map::increseMapSlider(int a)
{
	BaseObject::mapSlider = BaseObject::mapSlider + a;
}

void Map::increseClousDrifting(int a)
{
	BaseObject::clousDrifting = BaseObject::clousDrifting + a;
}

int Map::getMapSlider()
{
	return BaseObject::mapSlider;
}

void Map::Draw(HWND hwnd, HDC hdc)
{
	if (BaseObject::clousDrifting >= CLOUD_WIDTH - MAP_WIDTH - 2)
	{
		BaseObject::clousDrifting = 0;
	}
	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = SelectObject(hdcMem, hbmGround);
	GetObject(hbmGround, sizeof(bitmap), &bitmap);
	BitBlt
	(
		hdc,
		posX,
		CLOUD_HEIGHT,
		MAP_WIDTH,
		MAP_HEIGHT,
		hdcMem,
		BaseObject::mapSlider,
		0,
		SRCCOPY
	);
	oldBitmap = SelectObject(hdcMem, hbmCloud);
	GetObject(hbmCloud, sizeof(bitmap), &bitmap);
	BitBlt
	(
		hdc,
		posX,
		posY,
		MAP_WIDTH,
		CLOUD_HEIGHT,
		hdcMem,
		BaseObject::clousDrifting,
		0,
		SRCCOPY
	);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);
}

int Map::checkToAddEnemy(int a_posX)
{
	int checkPosition = 0;
	for (int i = 0; i < NUMBER_OF_MONSTERS; i++)
	{
		if (a_posX == enemiesPosition[i])
		{
			checkPosition = i + 1;
		}
	}
	return checkPosition;
}

int Map::checkToAddItem(int a_posX)
{
	int checkPosition = 0;
	for (int i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		if (a_posX == itemsPosition[i])
		{
			checkPosition = i + 1;
		}
	}
	return checkPosition;
}

