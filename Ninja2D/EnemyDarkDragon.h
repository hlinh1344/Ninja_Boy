#pragma once
#include "Enemy.h"
#include "Map.h"

#define DARK_DRAGON_HEIGHT 108
#define DARK_DRAGON_WIDTH 120
#define DARK_DRAGON_AREA 1200
#define DARK_DRAGON_SPEED 17

class EnemyDarkDragon : public Enemy
{
private:

public:
	EnemyDarkDragon(int a_x)
	{
		posX = a_x;
		posY = 357;
		formX = 3;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"DarkDragon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));

	}

	EnemyDarkDragon()
	{
		posX = 0;
		posY = 357;
		formX = 3;
		formY = 0;
		originalLocation = 0;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"DarkDragon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	~EnemyDarkDragon()
	{

	}

	void Draw(HWND hwnd, HDC hdc) override
	{
		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hbmMask);
		GetObject(hbmMask, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			posX - BaseObject::mapSlider,
			posY,
			DARK_DRAGON_WIDTH,
			DARK_DRAGON_HEIGHT,
			hdcMem,
			DARK_DRAGON_WIDTH * formX,
			DARK_DRAGON_HEIGHT * formY,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			posX - BaseObject::mapSlider,
			posY,
			DARK_DRAGON_WIDTH,
			DARK_DRAGON_HEIGHT,
			hdcMem,
			DARK_DRAGON_WIDTH * formX,
			DARK_DRAGON_HEIGHT * formY,
			SRCPAINT
		);
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
	}

	void MoveLeft() override
	{
		posX = posX - DARK_DRAGON_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + DARK_DRAGON_SPEED;
	}

	bool IsGoLeft() override
	{
		if ((formX >= 0) && (formX <=3))
			return true;
		return false;
	}

	bool IsGoRight() override
	{
		if ((formX >= 4) && (formX <= 7))
			return true;
		return false;
	}
	void SetDeath(bool a_isDead) override
	{
		isDead = a_isDead;
	}

	void MakeAnimation() override
	{
		clock++;
		if (!isDead)
		{
			if (EnemyDarkDragon::IsGoRight())
			{
				if (clock >= 4)
				{
					clock = 0;
					if (formX >= 7)
						formX = 4;
					else
						formX = formX + 1;
				}
				

				EnemyDarkDragon::MoveRight();

				if (posX >= originalLocation + DARK_DRAGON_AREA)
				{
					formX = 3;
				}
			}

			else if (EnemyDarkDragon::IsGoLeft())
			{
				if (clock >= 4)
				{
					clock = 0;
					if (formX <= 0)
						formX = 3;
					else
						formX = formX - 1;
				}
			

				EnemyDarkDragon::MoveLeft();

				if (posX <= originalLocation)
				{
					formX = 4;
				}
			}
		}
	}

	int GetWidth() override
	{
		return DARK_DRAGON_WIDTH;
	}

	int GetHeight() override
	{
		return DARK_DRAGON_HEIGHT;
	}

};