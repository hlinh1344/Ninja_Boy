#pragma once
#include "Weapon.h"
#include "Map.h"

//45x44
#define BLUE_SWORD_HEIGHT 29
#define BLUE_SWORD_WIDTH 151
#define BLUE_SWORD_AREA 0
#define BLUE_SWORD_SPEED 15

//posx = 100;
//posY = 421;

class WeaponBlueSword : public Weapon
{
private:
	int originalLocation;
public:
	WeaponBlueSword(int a_x, int a_dir, int	a_posY)
	{
		posX = a_x;
		posY = a_posY;
		formX = a_dir;
		dir = a_dir;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"BlueSword.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	WeaponBlueSword()
	{
		posX = 0;
		posY = 421;
		formX = 1;
		formY = 0;
		originalLocation = 0;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"BlueSword.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 255));
	}
	~WeaponBlueSword()
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
				BLUE_SWORD_WIDTH,
				BLUE_SWORD_HEIGHT,
				hdcMem,
				BLUE_SWORD_WIDTH * formX,
				BLUE_SWORD_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				BLUE_SWORD_WIDTH,
				BLUE_SWORD_HEIGHT,
				hdcMem,
				BLUE_SWORD_WIDTH * formX,
				BLUE_SWORD_HEIGHT * formY,
				SRCPAINT
			);
			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);
			if (dir == 0)
			{
				MoveLeft();
			}
			else if (dir == 1)
			{
				MoveRight();
			}
			CheckDistance();
		}
	}

	void MoveLeft() override
	{
		posX = posX - BLUE_SWORD_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + BLUE_SWORD_SPEED;
	}

	bool IsGoLeft() override
	{
		if (formX == 0)
			return true;
		return false;
	}

	bool IsGoRight()override
	{
		if (formX == 1)
			return true;
		return false;
	}

	void SetDeath(bool a_isDead) override
	{
		isDead = a_isDead;
	}

	void CheckDistance() override
	{
		int distance = abs(originalLocation - posX);
		if (distance >= BLUE_SWORD_AREA)
		{
			isDead = true;
		}
	}

	int GetWidth() override
	{
		return BLUE_SWORD_WIDTH;
	}

	int GetHeight() override
	{
		return BLUE_SWORD_HEIGHT;
	}

};