#include "Map.h"

Map::Map()
{
	posX = 0;
	posY = 0;
	hbmGround = (HBITMAP)LoadImage(hInst, L"Map2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmCloud = (HBITMAP)LoadImage(hInst, L"Castle.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmMask = CreateBitmapMask(hbmCloud, RGB(255, 255, 255));
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
		0,
		MAP_WIDTH,
		MAP_HEIGHT,
		hdcMem,
		BaseObject::mapSlider,
		0,
		SRCCOPY
	);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);

	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = SelectObject(hdcMem, hbmMask);
	GetObject(hbmMask, sizeof(bitmap), &bitmap);
	BitBlt
	(
		hdc,
		3689 - mapSlider,
		0,
		CASTLE_WIDTH,
		MAP_HEIGHT,
		hdcMem,
		0,
		0,
		SRCAND
	);

	oldBitmap = SelectObject(hdcMem, hbmCloud);
	GetObject(hbmCloud, sizeof(bitmap), &bitmap);
	BitBlt
	(
		hdc,
		3689 - mapSlider,
		0,
		CASTLE_WIDTH,
		MAP_HEIGHT,
		hdcMem,
		0,
		0,
		SRCPAINT
	);

	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);
}

void Map::checkToAddEnemy(int a_posX, int& enemyID, bool& checkToAdd)
{
	int checkPosition = 0;
	for (int i = 0; i < NUMBER_OF_MONSTERS; i++)
	{
		if (a_posX == enemiesPosition[i])
		{
			checkPosition = i + 1;
		}
	}

	if (enemyID == checkPosition)
	{
		checkToAdd = false;
	}
	else if (enemyID != checkPosition)
	{
		checkToAdd = true;
		enemyID = checkPosition;
	}
}

void Map::checkToAddItem(int a_posX, int& itemID, bool& checkToAdd)
{
	int checkPosition = 0;
	for (int i = 0; i < NUMBER_OF_ITEMS; i++)
	{
		if (a_posX == itemsPosition[i])
		{
			checkPosition = i + 1;
		}
	}

	if (itemID == checkPosition)
	{
		checkToAdd = false;
	}
	else if (itemID != checkPosition)
	{
		checkToAdd = true;
		itemID = checkPosition;
	}
}

