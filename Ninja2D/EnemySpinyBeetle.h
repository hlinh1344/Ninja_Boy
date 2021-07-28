#pragma once
#include "Map.h"
#include "Enemy.h"

#define SPINY_HEIGHT 42
#define SPINY_WIDTH 42
#define SPINY_AREA 90
#define SPINY_SPEED 12

class EnemySpinyBeetle : public Enemy
{
private:

public:

	EnemySpinyBeetle(int a_x)
	{
		posX = a_x;
		posY = 422;
		formX = 2;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"SpinyBeetle.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 255));

	}

	EnemySpinyBeetle()
	{
		posX = 0;
		posY = 422;
		formX = 2;
		formY = 0;
		originalLocation = 0;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"SpinyBeetle.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 255));
	}
	~EnemySpinyBeetle()
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
			SPINY_WIDTH,
			SPINY_HEIGHT,
			hdcMem,
			SPINY_WIDTH * formX,
			SPINY_HEIGHT * formY,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			posX - BaseObject::mapSlider,
			posY,
			SPINY_WIDTH,
			SPINY_HEIGHT,
			hdcMem,
			SPINY_WIDTH * formX,
			SPINY_HEIGHT * formY,
			SRCPAINT
		);
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
	}

	void MoveLeft() override
	{
		posX = posX - SPINY_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + SPINY_SPEED;
	}

	bool IsGoLeft() override
	{
		if ((formX == 0) || (formX == 1))
			return true;
		return false;
	}

	bool IsGoRight()override
	{
		if ((formX == 2) || (formX == 3))
			return true;
		return false;
	}

	void SetDeath(bool a_isDead) override
	{
		isDead = a_isDead;
		formX = 4;
	}

	void MakeAnimation() override
	{
		clock++;
		if (!isDead)
		{
			if (EnemySpinyBeetle::IsGoRight())
			{
				if (clock >= 3)
				{
					clock = 0;
					if (formX >= 3)
						formX = 2;
					else
						formX = formX + 1;
				}
				

				EnemySpinyBeetle::MoveRight();

				if (posX >= originalLocation + SPINY_AREA)
				{
					formX = 1;
				}
			}
			else if (EnemySpinyBeetle::IsGoLeft())
			{
				if (clock >= 3)
				{
					clock = 0;
					if (formX <= 0)
						formX = 1;
					else
						formX = formX - 1;
				}
				

				EnemySpinyBeetle::MoveLeft();

				if (posX <= originalLocation)
				{
					formX = 2;
				}
			}
		}
	}


	int GetWidth() override
	{
		return SPINY_WIDTH;
	}

	int GetHeight() override
	{
		return SPINY_HEIGHT;
	}
};