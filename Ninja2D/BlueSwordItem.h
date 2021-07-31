#pragma once
#include "Item.h"
#include "Map.h"

#define BLUE_SWORD_ITEM_HEIGHT 177
#define BLUE_SWORD_ITEM_WIDTH 59
#define BLUE_SWORD_ITEM_AREA 50
#define BLUE_SWORD_ITEM_SPEED 1

//L = 0, R = 1;

class BlueSwordItem : public Item
{
private:

public:
	
	BlueSwordItem()
	{
		posX = 1100;
		posY = 50;
		formX = 1;
		formY = 0;
		typeOfWeapn = 0;
		hBitmap = (HBITMAP)LoadImage(hInst, L"BlueSwordItem.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	BlueSwordItem(int a_x)
	{
		posX = a_x;
		posY = 50;
		formX = 1;
		formY = 0;
		typeOfWeapn = 0;
		hBitmap = (HBITMAP)LoadImage(hInst, L"BlueSwordItem.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	~BlueSwordItem()
	{

	}
	void Draw(HWND hwnd, HDC hdc, HDC hdcMem) override
	{
		if (!isDead)
		{
			//hdcMem = CreateCompatibleDC(hdc);
			oldBitmap = SelectObject(hdcMem, hbmMask);
			GetObject(hbmMask, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				BLUE_SWORD_ITEM_WIDTH,
				BLUE_SWORD_ITEM_HEIGHT,
				hdcMem,
				BLUE_SWORD_ITEM_WIDTH * formX,
				BLUE_SWORD_ITEM_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				BLUE_SWORD_ITEM_WIDTH,
				BLUE_SWORD_ITEM_HEIGHT,
				hdcMem,
				BLUE_SWORD_ITEM_WIDTH * formX,
				BLUE_SWORD_ITEM_HEIGHT * formY,
				SRCPAINT
			);
			//SelectObject(hdcMem, oldBitmap);
			//DeleteDC(hdcMem);
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
		isDead = a_isDead;

	}


	int GetWidth() override
	{
		return BLUE_SWORD_ITEM_WIDTH;
	}

	int GetHeight() override
	{
		return BLUE_SWORD_ITEM_HEIGHT;
	}
};