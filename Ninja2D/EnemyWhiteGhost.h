#pragma once
#include "Enemy.h"
#include "Map.h"

#define WHITE_GHOST_HEIGHT 100
#define WHITE_GHOST_WIDTH 100
#define WHITE_GHOST_AREA 200
#define WHITE_GHOST_SPEED 7


class EnemyWhiteGhost : public Enemy
{
private:

public:
	EnemyWhiteGhost(int a_x)
	{
		posX = a_x;
		posY = 370;
		formX = 6;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"WhiteGhost.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));

	}

	EnemyWhiteGhost()
	{
		posX = 0;
		posY = 370;
		formX = 6;
		formY = 0;
		originalLocation = 0;
		life = 1;
		hBitmap = (HBITMAP)LoadImage(hInst, L"WhiteGhost.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	~EnemyWhiteGhost()
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
			WHITE_GHOST_WIDTH,
			WHITE_GHOST_HEIGHT,
			hdcMem,
			WHITE_GHOST_WIDTH * formX,
			WHITE_GHOST_HEIGHT * formY,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			posX - BaseObject::mapSlider,
			posY,
			WHITE_GHOST_WIDTH,
			WHITE_GHOST_HEIGHT,
			hdcMem,
			WHITE_GHOST_WIDTH * formX,
			WHITE_GHOST_HEIGHT * formY,
			SRCPAINT
		);
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
	}

	void MoveLeft() override
	{
		posX = posX - WHITE_GHOST_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + WHITE_GHOST_SPEED;
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
		this->isDead = a_isDead;
	}




	void MakeAnimation() override
	{
		if (!isDead)
		{
			if (EnemyWhiteGhost::IsGoRight())
			{
				if (formX >= 11)
					formX = 6;
				else
					formX = formX + 1;

				EnemyWhiteGhost::MoveRight();

				if (posX >= originalLocation + WHITE_GHOST_AREA)
				{
					formX = 5;
				}
			}

			else if (EnemyWhiteGhost::IsGoLeft())
			{
				if (formX <= 0)
					formX = 5;
				else
					formX = formX - 1;

				EnemyWhiteGhost::MoveLeft();

				if (posX <= originalLocation)
				{
					formX = 6;
				}
			}
		}
	}

};