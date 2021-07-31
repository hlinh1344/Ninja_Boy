#pragma once
#include "Weapon.h"
#include "Map.h"

#define SHURIKEN_HEIGHT 40
#define SHURIKEN_WIDTH 45
#define SHURIKEN_AREA 300
#define SHURIKEN_SPEED 10

//L = 0, R = 1;

class WeaponShuriken : public Weapon
{
private:
	int originalLocation;
public:
	WeaponShuriken(int a_x, int a_dir, int	a_posY)
	{
		posX = a_x;
		posY = a_posY;
		if (a_dir == 0)
		{
			formX = 3;
		}
		else if (a_dir == 1)
		{
			formX = 4;
		}
		dir = a_dir;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Shuriken.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	WeaponShuriken()
	{
		posX = 0;
		posY = 421;
		formX = 1;
		formY = 0;
		originalLocation = 0;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Shuriken.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 255));
	}
	~WeaponShuriken()
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
				SHURIKEN_WIDTH,
				SHURIKEN_HEIGHT,
				hdcMem,
				SHURIKEN_WIDTH * formX,
				SHURIKEN_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				SHURIKEN_WIDTH,
				SHURIKEN_HEIGHT,
				hdcMem,
				SHURIKEN_WIDTH * formX,
				SHURIKEN_HEIGHT * formY,
				SRCPAINT
			);
			//SelectObject(hdcMem, oldBitmap);
			//DeleteDC(hdcMem);
			posY++;

			if (dir == 0)
			{
				MoveLeft();
				if (formX <= 0)
				{
					formX = 2;
				}
				else
					formX--;
			}
			else if (dir == 1)
			{
				MoveRight();
				if (formX >= 5)
				{
					formX = 3;
				}
				else
					formX++;
			}


			CheckDistance();
		}
	}

	void MoveLeft() override
	{
		posX = posX - SHURIKEN_SPEED;
		posY++;
	}

	void MoveRight() override
	{
		posX = posX + SHURIKEN_SPEED;
		posY++;
	}

	void SetDeath(bool a_isDead) override
	{
		isDead = a_isDead;
		//formX = 2;
	}

	void CheckDistance() override
	{
		int distance = abs(originalLocation - posX);
		if (distance >= SHURIKEN_AREA)
		{
			isDead = true;
		}
	}

	bool IsGoLeft() override
	{
		if ((formX >= 0) && (formX <=2))
			return true;
		return false;
	}

	bool IsGoRight()override
	{
		if ((formX >= 3) && (formX <= 5))
			return true;
		return false;
	}

	int GetWidth() override
	{
		return SHURIKEN_WIDTH;
	}

	int GetHeight() override
	{
		return SHURIKEN_HEIGHT;
	}

};