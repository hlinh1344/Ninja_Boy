#pragma once
#include "Enemy.h"
#include "Map.h"

#define DARK_RAVEN_HEIGHT 55
#define DARK_RAVEN_WIDTH 45
#define DARK_RAVEN_AREA 1000
#define DARK_RAVEN_SPEED 20


class EnemyDarkRaven : public Enemy
{
private:
	bool isFalling;
public:
	EnemyDarkRaven(int a_x)
	{
		posX = a_x;
		posY = 50;
		//CHANGE FORM
		formX = 6;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		isFalling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"DarkRaven.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));

	}

	EnemyDarkRaven()
	{
		posX = 0;
		posY = 50;
		//CHANGE FORM
		formX = 6;
		formY = 0;
		originalLocation = 0;
		life = 1;
		isFalling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Girl.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	~EnemyDarkRaven()
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
			DARK_RAVEN_WIDTH,
			DARK_RAVEN_HEIGHT,
			hdcMem,
			DARK_RAVEN_WIDTH * formX,
			DARK_RAVEN_HEIGHT * formY,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			posX - BaseObject::mapSlider,
			posY,
			DARK_RAVEN_WIDTH,
			DARK_RAVEN_HEIGHT,
			hdcMem,
			DARK_RAVEN_WIDTH * formX,
			DARK_RAVEN_HEIGHT * formY,
			SRCPAINT
		);

		if (isFalling)
		{
			posY = posY + 5;
			if (posY >= 200)
			{
				isFalling = false;
			}
		}
		else if (!isFalling)
		{
			posY = posY - 5;
			if (posY <= 50)
			{
				isFalling = true;
			}
		}
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
	}

	void MoveLeft() override
	{
		posX = posX - DARK_RAVEN_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + DARK_RAVEN_SPEED;
	}

	bool IsGoLeft() override
	{
		if ((formX >= 0) && (formX <= 5))
			return true;
		return false;
	}

	bool IsGoRight() override
	{
		if ((formX >= 6) && (formX <= 11))
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
			if (EnemyDarkRaven::IsGoRight())
			{
				if (clock >= 2)
				{
					clock = 0;
					if (formX >= 11)
						formX = 6;
					else
						formX = formX + 1;
				}
				

				EnemyDarkRaven::MoveRight();

				if (posX >= originalLocation + DARK_RAVEN_AREA)
				{
					formX = 5;
				}
			}

			else if (EnemyDarkRaven::IsGoLeft())
			{
				if (clock >= 2)
				{
					clock = 0;
					if (formX <= 0)
						formX = 5;
					else
						formX = formX - 1;
				}
				

				EnemyDarkRaven::MoveLeft();

				if (posX <= originalLocation)
				{
					formX = 6;
				}
			}
		}
	}

	int GetWidth() override
	{
		return DARK_RAVEN_WIDTH;
	}

	int GetHeight() override
	{
		return DARK_RAVEN_HEIGHT;
	}

};