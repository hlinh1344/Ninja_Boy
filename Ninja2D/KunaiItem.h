#pragma once
#include "Item.h"
#include "Map.h"

#define KUNAI_ITEM_HEIGHT 72
#define KUNAI_ITEM_WIDTH 74
#define KUNAI_ITEM_AREA 30
#define KUNAI_ITEM_SPEED 3

//L = 0, R = 1;

class KunaiItem : public Item
{
private:;

public:


	KunaiItem()
	{
		posX = 1600;
		posY = 50;
		formX = 1;
		formY = 0;
		typeOfWeapn = 2;
		hBitmap = (HBITMAP)LoadImage(hInst, L"KunaiItem.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 0));
	}

	KunaiItem(int a_x)
	{
		posX = a_x;
		posY = 50;
		formX = 1;
		formY = 0;
		typeOfWeapn = 2;
		hBitmap = (HBITMAP)LoadImage(hInst, L"KunaiItem.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 0));
	}

	~KunaiItem()
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
				KUNAI_ITEM_WIDTH,
				KUNAI_ITEM_HEIGHT,
				hdcMem,
				KUNAI_ITEM_WIDTH * formX,
				KUNAI_ITEM_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				KUNAI_ITEM_WIDTH,
				KUNAI_ITEM_HEIGHT,
				hdcMem,
				KUNAI_ITEM_WIDTH * formX,
				KUNAI_ITEM_HEIGHT * formY,
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
		return KUNAI_ITEM_WIDTH;
	}

	int GetHeight() override
	{
		return KUNAI_ITEM_HEIGHT;
	}
};