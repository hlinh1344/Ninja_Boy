#pragma once
#include "Weapon.h"
#include "Map.h"

#define THUNDER_HEIGHT 58
#define THUNDER_WIDTH 78
#define THUNDER_AREA 800
#define THUNDER_SPEED 10

//L = 0, R = 1;

class WeaponThunder : public Weapon
{
private:
	int originalLocation;
	bool isFalling;
	int originalposY;
public:
	WeaponThunder(int a_x, int a_dir, int	a_posY)
	{
		posX = a_x;
		posY = a_posY;
		if (a_dir == 0)
		{
			formX = 8;
		}
		else if (a_dir == 1)
		{
			formX = 9;
		}
		dir = a_dir;
		formY = 0;
		originalLocation = a_x;
		isFalling = true;
		originalposY = a_posY;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Thunder.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(0, 128, 0));
	}

	WeaponThunder()
	{
		posX = 0;
		posY = 421;
		formX = 1;
		formY = 0;
		originalLocation = 0;
		life = 1;
		isFalling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Thunder.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(0, 128, 0));
	}
	~WeaponThunder()
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
				THUNDER_WIDTH,
				THUNDER_HEIGHT,
				hdcMem,
				THUNDER_WIDTH * formX,
				THUNDER_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				THUNDER_WIDTH,
				THUNDER_HEIGHT,
				hdcMem,
				THUNDER_WIDTH * formX,
				THUNDER_HEIGHT * formY,
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
			else if (dir == 1)
			{
				MoveRight();
				if (formX >= 17)
				{
					formX = 9;
				}
				else
					formX++;
			}
			CheckDistance();

			if (isFalling)
			{
				posY = posY + 5;
				if (posY >= originalposY + 70)
				{
					isFalling = false;
				}
			}
			else if (!isFalling)
			{
				posY = posY - 5;
				if (posY <= originalposY - 70)
				{
					isFalling = true;
				}
			}
		}
	}

	void MoveLeft() override
	{
		posX = posX - THUNDER_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + THUNDER_SPEED;
	}

	void SetDeath(bool a_isDead) override
	{
		isDead = a_isDead;

	}

	void CheckDistance() override
	{
		int distance = abs(originalLocation - posX);
		if (distance >= THUNDER_AREA)
		{
			isDead = true;
		}
	}

	bool IsGoLeft() override
	{
		if ((formX >= 0) && (formX <= 8))
			return true;
		return false;
	}

	bool IsGoRight()override
	{
		if ((formX >= 9) && (formX <= 17))
			return true;
		return false;
	}

	int GetWidth() override
	{
		return THUNDER_WIDTH;
	}

	int GetHeight() override
	{
		return THUNDER_HEIGHT;
	}
};