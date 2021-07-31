#pragma once
#include "Enemy.h"
#include "Map.h"

#define SLIME_HEIGHT 120
#define SLIME_WIDTH 115
#define SLIME_AREA 1200
#define SLIME_SPEED 3

class EnemySlime : public Enemy
{
private:

public:
	EnemySlime(int a_x)
	{
		posX = a_x;
		posY = 353;
		formX = 9;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Slime.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 0));

	}

	EnemySlime()
	{
		posX = 0;
		posY = 353;
		formX = 9;
		formY = 0;
		originalLocation = 0;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Slime.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 0));
	}

	~EnemySlime()
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
			SLIME_WIDTH,
			SLIME_HEIGHT,
			hdcMem,
			SLIME_WIDTH * formX,
			SLIME_HEIGHT * formY,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			posX - BaseObject::mapSlider,
			posY,
			SLIME_WIDTH,
			SLIME_HEIGHT,
			hdcMem,
			SLIME_WIDTH * formX,
			SLIME_HEIGHT * formY,
			SRCPAINT
		);
		//SelectObject(hdcMem, oldBitmap);
		//DeleteDC(hdcMem);
	}

	void MoveLeft() override
	{
		posX = posX - SLIME_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + SLIME_SPEED;
	}

	bool IsGoLeft() override
	{
		if ((formX >= 0) && (formX <= 8))
			return true;
		return false;
	}

	bool IsGoRight() override
	{
		if ((formX >= 9) && (formX <= 17))
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
			if (EnemySlime::IsGoRight())
			{
				if (clock >= 10)
				{
					clock = 0;
					if (formX >= 17)
						formX = 9;
					else
						formX = formX + 1;
				}


				EnemySlime::MoveRight();

				if (posX >= originalLocation + SLIME_AREA)
				{
					formX = 8;
				}
			}

			else if (EnemySlime::IsGoLeft())
			{
				if (clock >= 10)
				{
					clock = 0;
					if (formX <= 0)
						formX = 8;
					else
						formX = formX - 1;
				}


				EnemySlime::MoveLeft();

				if (posX <= originalLocation)
				{
					formX = 9;
				}
			}
		}
	}

	int GetWidth() override
	{
		return SLIME_WIDTH;
	}

	int GetHeight() override
	{
		return SLIME_HEIGHT;
	}

};