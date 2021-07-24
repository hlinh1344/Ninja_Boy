#pragma once
#include "Item.h"
#include "Map.h"

#define FLAME_ITEM_HEIGHT 144
#define FLAME_ITEM_WIDTH 60
#define FLAME_ITEM_AREA 30
#define FLAME_ITEM_SPEED 4

//L = 0, R = 1;

class FlameItem : public Item
{
private:;
	   bool falling;
public:


	FlameItem()
	{
		posX = 1600;
		posY = 0;
		formX = 0;
		formY = 0;
		typeOfWeapn = 3;
		falling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"FlameItem.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	FlameItem(int a_x)
	{
		posX = a_x;
		posY = 0;
		formX = 0;
		formY = 0;
		typeOfWeapn = 3;
		falling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"FlameItem.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	~FlameItem()
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
				FLAME_ITEM_WIDTH,
				FLAME_ITEM_HEIGHT,
				hdcMem,
				FLAME_ITEM_WIDTH * formX,
				FLAME_ITEM_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				FLAME_ITEM_WIDTH,
				FLAME_ITEM_HEIGHT,
				hdcMem,
				FLAME_ITEM_WIDTH * formX,
				FLAME_ITEM_HEIGHT * formY,
				SRCPAINT
			);
			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);
			if (falling == true)
			{
				posY++;
				if (posY >= 10)
				{
					falling = false;
				}
			}
			else if (falling == false)
			{
				posY--;
				if (posY <= 0)
				{
					falling = true;
				}
			}


			if (formX == 6)
				formX = 0;
			else formX++;

		}
	}



	void SetDeath(bool a_isDead) override
	{
		this->isDead = a_isDead;

	}


	int GetWidth() override
	{
		return FLAME_ITEM_WIDTH;
	}

	int GetHeight() override
	{
		return FLAME_ITEM_HEIGHT;
	}
};