#pragma once
#include "Weapon.h"
#include "Map.h"

//45x44
#define KUNAI_HEIGHT 17
#define KUNAI_WIDTH 80
#define KUNAI_AREA 350
#define KUNAI_SPEED 20

//posx = 100;
//posY = 421;

class WeaponKunai : public Weapon
{
private:
	int originalLocation;
public:
	WeaponKunai(int a_x, int a_dir, int	a_posY)
	{
		posX = a_x;
		posY = a_posY;
		formX = a_dir;
		dir = a_dir;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Kunai.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	WeaponKunai()
	{
		posX = 0;
		posY = 421;
		formX = 1;
		formY = 0;
		originalLocation = 0;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Kunai.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 255));
	}
	~WeaponKunai()
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
				KUNAI_WIDTH,
				KUNAI_HEIGHT,
				hdcMem,
				KUNAI_WIDTH * formX,
				KUNAI_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				KUNAI_WIDTH,
				KUNAI_HEIGHT,
				hdcMem,
				KUNAI_WIDTH * formX,
				KUNAI_HEIGHT * formY,
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
		posX = posX - KUNAI_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + KUNAI_SPEED;
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
		this->isDead = a_isDead;
	}

	void CheckDistance() override
	{
		int distance = abs(originalLocation - posX);
		if (distance >= KUNAI_AREA)
		{
			this->isDead = true;
		}
	}

	int GetWidth() override
	{
		return KUNAI_WIDTH;
	}

	int GetHeight() override
	{
		return KUNAI_HEIGHT;
	}

};