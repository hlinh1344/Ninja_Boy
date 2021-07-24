#pragma once
#include "Item.h"
#include "Map.h"

#define SHURIKEN_ITEM_HEIGHT 87
#define SHURIKEN_ITEM_WIDTH 98
#define SHURIKEN_ITEM_AREA 70
#define SHURIKEN_ITEM_SPEED 2

//L = 0, R = 1;

class ShurikenItem : public Item
{
private:;

public:


	ShurikenItem()
	{
		posX = 1600;
		posY = 50;
		formX = 1;
		formY = 0;
		typeOfWeapn = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"ShurikenItem.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 0));
	}

	ShurikenItem(int a_x)
	{
		posX = a_x;
		posY = 50;
		formX = 1;
		formY = 0;
		typeOfWeapn = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"ShurikenItem.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 0));
	}

	~ShurikenItem()
	{

	}
	void Draw(HWND hwnd, HDC hdc) override
	{
		if (!isDead)
		{
			hdcMem = CreateCompatibleDC(hdc);
			oldBitmap = SelectObject(hdcMem, hbmMask);
			GetObject(hbmMask, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				SHURIKEN_ITEM_WIDTH,
				SHURIKEN_ITEM_HEIGHT,
				hdcMem,
				SHURIKEN_ITEM_WIDTH * formX,
				SHURIKEN_ITEM_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				SHURIKEN_ITEM_WIDTH,
				SHURIKEN_ITEM_HEIGHT,
				hdcMem,
				SHURIKEN_ITEM_WIDTH * formX,
				SHURIKEN_ITEM_HEIGHT * formY,
				SRCPAINT
			);
			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);
			if (formX == 0)
			{
				posY++;
				if (posY >= 60)
				{
					formX = 1;
				}
			}
			else if (formX == 1)
			{
				posY--;
				if (posY <= 50)
				{
					formX = 0;
				}
			}

		}
	}



	void SetDeath(bool a_isDead) override
	{
		this->isDead = a_isDead;

	}


	int GetWidth() override
	{
		return SHURIKEN_ITEM_WIDTH;
	}

	int GetHeight() override
	{
		return SHURIKEN_ITEM_HEIGHT;
	}
};