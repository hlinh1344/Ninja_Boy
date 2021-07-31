#pragma once
#include "Weapon.h"
#include "Map.h"

#define FIRE_HEIGHT 28
#define FIRE_WIDTH 70
#define FIRE_AREA 600
#define FIRE_SPEED 15

//L = 0, R = 1;

class WeaponFire : public Weapon
{
private:
	int originalLocation;
public:
	WeaponFire(int a_x, int a_dir, int	a_posY)
	{
		posX = a_x;
		posY = a_posY;
		if (a_dir == 0)
		{
			formX = 6;
		}
		else if (a_dir == 1)
		{
			formX = 7;
		}
		dir = a_dir;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Fire.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(0, 128, 0));
	}

	WeaponFire()
	{
		posX = 0;
		posY = 421;
		formX = 1;
		formY = 0;
		originalLocation = 0;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Fire.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB( 0, 128, 0));
	}
	~WeaponFire()
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
				posY--,
				FIRE_WIDTH,
				FIRE_HEIGHT,
				hdcMem,
				FIRE_WIDTH * formX,
				FIRE_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY--,
				FIRE_WIDTH,
				FIRE_HEIGHT,
				hdcMem,
				FIRE_WIDTH * formX,
				FIRE_HEIGHT * formY,
				SRCPAINT
			);
			//SelectObject(hdcMem, oldBitmap);
			//DeleteDC(hdcMem);
			if (dir == 0)
			{
				MoveLeft();
				if (formX <= 0)
				{
					formX = 6;
				}
				else
					formX--;
			}
			else if (dir == 1)
			{
				MoveRight();
				if (formX >= 13)
				{
					formX = 7;
				}
				else
					formX++;
			}
		CheckDistance();
		}
	}

	void MoveLeft() override
	{
		posX = posX - FIRE_SPEED;
		posY--;
		posY--;
	}

	void MoveRight() override
	{
		posX = posX + FIRE_SPEED;
		posY--;
		posY--;
	}

	void SetDeath(bool a_isDead) override
	{
		isDead = a_isDead;

	}

	void CheckDistance() override
	{
		int distance = abs(originalLocation - posX);
		if (distance >= FIRE_AREA)
		{
			isDead = true;
		}
	}

	bool IsGoLeft() override
	{
		if ((formX >= 0) && (formX <= 6))
			return true;
		return false;
	}

	bool IsGoRight()override
	{
		if ((formX >= 7) && (formX <= 13))
			return true;
		return false;
	}

	int GetWidth() override
	{
		return FIRE_WIDTH;
	}

	int GetHeight() override
	{
		return FIRE_HEIGHT;
	}
};