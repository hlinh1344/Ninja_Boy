#pragma once
#include "Enemy.h"
#include "Map.h"

#define BUZZY_HEIGHT 45
#define BUZZY_WIDTH 44
#define BUZZY_AREA 300
#define BUZZY_SPEED 2

class EnemyBuzzyBeetle : public Enemy
{
private:

public:
	EnemyBuzzyBeetle(int a_x)
	{
		posX = a_x;
		posY = 421;
		formX = 3;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"BuzzyBeetle.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 255));

	}

	EnemyBuzzyBeetle()
	{
		posX = 0;
		posY = 421;
		formX = 3;
		formY = 0;
		originalLocation = 0;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"BuzzyBeetle.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 255));
	}

	~EnemyBuzzyBeetle()
	{

	}

	void Draw(HWND hwnd, HDC hdc, HDC hdcMem) override
	{
		//hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hbmMask);
		GetObject(hbmMask, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			posX - BaseObject::mapSlider,
			posY,
			BUZZY_WIDTH,
			BUZZY_HEIGHT,
			hdcMem,
			BUZZY_WIDTH * formX,
			BUZZY_HEIGHT * formY,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			posX - BaseObject::mapSlider,
			posY,
			BUZZY_WIDTH,
			BUZZY_HEIGHT,
			hdcMem,
			BUZZY_WIDTH * formX,
			BUZZY_HEIGHT * formY,
			SRCPAINT
		);
		//SelectObject(hdcMem, oldBitmap);
		//DeleteDC(hdcMem);
	}

	void MoveLeft() override
	{
		posX = posX - BUZZY_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + BUZZY_SPEED;
	}

	bool IsGoLeft() override
	{
		if ((formX == 0) || (formX == 1))
			return true;
		return false;
	}

	bool IsGoRight() override
	{
		if ((formX == 3) || (formX == 4))
			return true;
		return false;
	}
	void SetDeath(bool a_isDead) override
	{
		isDead = a_isDead;
		formX = 2;
	}

	void MakeAnimation() override
	{
		clock++;
		if (!isDead)
		{
			if (EnemyBuzzyBeetle::IsGoRight())
			{
				if (clock >= 20)
				{
					clock = 0;
					if (formX >= 4)
						formX = 3;
					else
						formX = formX + 1;
				}
				

				EnemyBuzzyBeetle::MoveRight();

				if (posX >= originalLocation + BUZZY_AREA)
				{
					formX = 1;
				}
			}

			else if (EnemyBuzzyBeetle::IsGoLeft())
			{
				if (clock >= 20)
				{
					clock = 0;
					if (formX <= 0)
						formX = 1;
					else
						formX = formX - 1;
				}
				

				EnemyBuzzyBeetle::MoveLeft();

				if (posX <= originalLocation)
				{
					formX = 3;
				}
			}
		}
	}

	int GetWidth() override
	{
		return BUZZY_WIDTH;
	}

	int GetHeight() override
	{
		return BUZZY_HEIGHT;
	}

};