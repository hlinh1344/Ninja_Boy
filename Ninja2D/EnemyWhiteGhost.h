#pragma once
#include "Enemy.h"
#include "Map.h"

#define WHITE_GHOST_HEIGHT 100
#define WHITE_GHOST_WIDTH 100
#define WHITE_GHOST_AREA 850
#define WHITE_GHOST_SPEED 4


class EnemyWhiteGhost : public Enemy
{
private:
	bool isFalling;
public:
	EnemyWhiteGhost(int a_x)
	{
		posX = a_x;
		posY = 200;
		formX = 6;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		isFalling = true;
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
		isFalling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"WhiteGhost.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	~EnemyWhiteGhost()
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

		if (isFalling)
		{
			posY = posY + 7;
			if (posY >= 400)
			{
				isFalling = false;
			}
		}
		else if (!isFalling)
		{
			posY = posY - 7;
			if (posY <= 100)
			{
				isFalling = true;
			}
		}
		//SelectObject(hdcMem, oldBitmap);
		//DeleteDC(hdcMem);
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
		isDead = a_isDead;
	}




	void MakeAnimation() override
	{
		clock++;
		if (!isDead)
		{
			if (EnemyWhiteGhost::IsGoRight())
			{
				if (clock >= 10)
				{
					clock = 0;
					if (formX >= 11)
						formX = 6;
					else
						formX = formX + 1;
				}
				

				EnemyWhiteGhost::MoveRight();

				if (posX >= originalLocation + WHITE_GHOST_AREA)
				{
					formX = 5;
				}
			}

			else if (EnemyWhiteGhost::IsGoLeft())
			{
				if (clock >= 10)
				{
					clock = 0;
					if (formX <= 0)
						formX = 5;
					else
						formX = formX - 1;
				}
				

				EnemyWhiteGhost::MoveLeft();

				if (posX <= originalLocation)
				{
					formX = 6;
				}
			}
		}
	}

	int GetWidth() override
	{
		return WHITE_GHOST_WIDTH;
	}

	int GetHeight() override
	{
		return WHITE_GHOST_HEIGHT;
	}

};