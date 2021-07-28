#pragma once
#include "Item.h"
#include "Map.h"

#define THUNDER_DRAGON_ITEM_HEIGHT 195
#define THUNDER_DRAGON_ITEM_WIDTH 195
#define THUNDER_DRAGON_ITEM_AREA 30
#define THUNDER_DRAGON_ITEM_SPEED 5

//L = 0, R = 1;

class ThunderDragonItem : public Item
{
private:;

public:


	ThunderDragonItem()
	{
		posX = 1600;
		posY = 0;
		formX = 1;
		formY = 0;
		typeOfWeapn = 4;
		hBitmap = (HBITMAP)LoadImage(hInst, L"ThunderDragonItem.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(0, 128, 0));
	}

	ThunderDragonItem(int a_x)
	{
		posX = a_x;
		posY = 0;
		formX = 1;
		formY = 0;
		typeOfWeapn = 4;
		hBitmap = (HBITMAP)LoadImage(hInst, L"ThunderDragonItem.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(0, 128, 0));
	}

	~ThunderDragonItem()
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
				THUNDER_DRAGON_ITEM_WIDTH,
				THUNDER_DRAGON_ITEM_HEIGHT,
				hdcMem,
				THUNDER_DRAGON_ITEM_WIDTH * formX,
				THUNDER_DRAGON_ITEM_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				THUNDER_DRAGON_ITEM_WIDTH,
				THUNDER_DRAGON_ITEM_HEIGHT,
				hdcMem,
				THUNDER_DRAGON_ITEM_WIDTH * formX,
				THUNDER_DRAGON_ITEM_HEIGHT * formY,
				SRCPAINT
			);
			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);
			if (formX == 0)
			{
				posY++;
				if (posY >= 10)
				{
					formX = 1;
				}
			}
			else if (formX == 1)
			{
				posY--;
				if (posY <= 0)
				{
					formX = 0;
				}
			}

		}
	}



	void SetDeath(bool a_isDead) override
	{
		isDead = a_isDead;

	}


	int GetWidth() override
	{
		return THUNDER_DRAGON_ITEM_WIDTH;
	}

	int GetHeight() override
	{
		return THUNDER_DRAGON_ITEM_HEIGHT;
	}
};