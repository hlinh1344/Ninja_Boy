#pragma once
#include "Weapon.h"
#include "Map.h"

#define MOON_HEIGHT 81
#define MOON_WIDTH 82
#define MOON_AREA 500
#define MOON_SPEED 10

//L = 0, R = 1;

class Moon : public Weapon
{
private:
	int originalLocation;
	bool isFalling;
	int originalposY;
public:
	Moon( int a_posY)
	{
		posX = 3500;
		posY = a_posY;
		formX = 7;
		dir = 0;
		formY = 0;
		originalLocation = posX;
		isFalling = true;
		originalposY = a_posY;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Moon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	Moon(int a_posX, int a_posY)
	{
		posX = a_posX;
		posY = a_posY;
		formX = 7;
		dir = 0;
		formY = 0;
		originalLocation = posX;
		isFalling = true;
		originalposY = a_posY;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Moon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}
	Moon()
	{
		posX = 3600;
		posY = 421;
		formX = 1;
		formY = 0;
		originalLocation = 0;
		life = 1;
		isFalling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Moon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}
	~Moon()
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
				MOON_WIDTH,
				MOON_HEIGHT,
				hdcMem,
				MOON_WIDTH * formX,
				MOON_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				MOON_WIDTH,
				MOON_HEIGHT,
				hdcMem,
				MOON_WIDTH * formX,
				MOON_HEIGHT * formY,
				SRCPAINT
			);
			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);
			if (dir == 0)
			{
				MoveLeft();
				if (formX <= 0)
				{
					formX = 8;
				}
				else
					formX--;
			}
			
			CheckDistance();

			if (isFalling)
			{
				posY = posY + 20;
				if (posY >= originalposY + 70)
				{
					isFalling = false;
				}
			}
			else if (!isFalling)
			{
				posY = posY - 20;
				if (posY <= originalposY -70)
				{
					isFalling = true;
				}
			}
		}
	}

	void MoveLeft() override
	{
		posX = posX - MOON_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + MOON_SPEED;
	}

	void SetDeath(bool a_isDead) override
	{
		isDead = a_isDead;

	}

	void CheckDistance() override
	{
		int distance = abs(originalLocation - posX);
		if (distance >= MOON_AREA)
		{
			isDead = true;
		}
	}

	int GetWidth() override
	{
		return MOON_WIDTH;
	}

	int GetHeight() override
	{
		return MOON_HEIGHT;
	}
};