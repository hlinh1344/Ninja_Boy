#pragma once
#include "Enemy.h"
#include "Map.h"

#define BIRD_HEIGHT 65
#define BIRD_WIDTH 64
#define BIRD_AREA 1000
#define BIRD_SPEED 8


class EnemyBird : public Enemy
{
private:
	bool isFalling;
public:
	EnemyBird(int a_x)
	{
		posX = a_x;
		posY = 150;
		formX = 6;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		isFalling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Bird.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));

	}

	EnemyBird()
	{
		posX = 0;
		posY = 150;
		formX = 6;
		formY = 0;
		originalLocation = 0;
		life = 1;
		isFalling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Bird.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	~EnemyBird()
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
			BIRD_WIDTH,
			BIRD_HEIGHT,
			hdcMem,
			BIRD_WIDTH * formX,
			BIRD_HEIGHT * formY,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			posX - BaseObject::mapSlider,
			posY,
			BIRD_WIDTH,
			BIRD_HEIGHT,
			hdcMem,
			BIRD_WIDTH * formX,
			BIRD_HEIGHT * formY,
			SRCPAINT
		);

		if (isFalling)
		{
			posY = posY + 6;
			if (posY >= 300)
			{
				isFalling = false;
			}
		}
		else if (!isFalling)
		{
			posY = posY - 6;
			if (posY <= 150)
			{
				isFalling = true;
			}
		}

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
	}

	void MoveLeft() override
	{
		posX = posX - BIRD_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + BIRD_SPEED;
	}

	bool IsGoLeft() override
	{
		if ((formX >= 0) && (formX <= 3))
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
		if (!isDead)
		{
			if (EnemyBird::IsGoRight())
			{
				if (formX >= 7)
					formX = 4;
				else
					formX = formX + 1;

				EnemyBird::MoveRight();

				if (posX >= originalLocation + BIRD_AREA)
				{
					formX = 3;
				}
			}

			else if (EnemyBird::IsGoLeft())
			{
				if (formX <= 0)
					formX = 3;
				else
					formX = formX - 1;

				EnemyBird::MoveLeft();

				if (posX <= originalLocation)
				{
					formX = 4;
				}
			}
		}
	}

	int GetWidth() override
	{
		return BIRD_WIDTH;
	}

	int GetHeight() override
	{
		return BIRD_HEIGHT;
	}

};