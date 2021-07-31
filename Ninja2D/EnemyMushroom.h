#pragma once
#include <ctime>
#include <chrono>
#include <time.h>
#include <iomanip>

#include "Enemy.h"
#include "Map.h"


#define MUSHROOM_HEIGHT 43
#define MUSHROOM_WIDTH 44
#define MUSHROOM_AREA 200
#define MUSHROOM_SPEED 1
class EnemyMushroom : public Enemy
{
private:
	bool isGoToRight;
public:

	EnemyMushroom(int a_x)
	{
		posX = a_x;
		posY = 422;
		formX = 0;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		isGoToRight = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Mushroom.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 255));
	}

	EnemyMushroom()
	{
		posX = 0;
		posY = 422;
		formX = 0;
		formY = 0;
		originalLocation = 0;
		life = 1;
		isGoToRight = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Mushroom.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 255));
	}
	~EnemyMushroom()
	{

	}

	void Draw(HWND hwnd, HDC hdc, HDC hdcMem) override
	{
		{
			//hdcMem = CreateCompatibleDC(hdc);

			oldBitmap = SelectObject(hdcMem, hbmMask);
			GetObject(hbmMask, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				MUSHROOM_WIDTH,
				MUSHROOM_HEIGHT,
				hdcMem,
				MUSHROOM_WIDTH * formX,
				MUSHROOM_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				MUSHROOM_WIDTH,
				MUSHROOM_HEIGHT,
				hdcMem,
				MUSHROOM_WIDTH * formX,
				MUSHROOM_HEIGHT * formY,
				SRCPAINT
			);
			//SelectObject(hdcMem, oldBitmap);
			//DeleteDC(hdcMem);
		}
	}

	void MoveLeft() override
	{
		posX = posX - MUSHROOM_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + MUSHROOM_SPEED;
	}

	bool IsGoLeft() override
	{
		if ((formX >= 0) && (formX <= 3))
			return true;
		return false;
	}

	bool IsGoRight()override
	{
		if ((formX >= 4) && (formX <= 7))
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
			if (isGoToRight)
			{
				if (clock >= 10)
				{
					clock = 0;
					if (formX == 0)
						formX = 1;
					else
						formX = 0;
				}
			

				EnemyMushroom::MoveRight();

				if (posX >= originalLocation + MUSHROOM_AREA)
				{
					isGoToRight = false;
				}
			}
			else if (!isGoToRight)
			{
				if (clock >= 10)
				{
					clock = 0;
					if (formX == 0)
						formX = 1;
					else
						formX = 0;
				}
				

				EnemyMushroom::MoveLeft();

				if (posX <= originalLocation)
				{
					isGoToRight = true;
				}
			}
		}
	}


	int GetWidth() override
	{
		return MUSHROOM_WIDTH;
	}

	int GetHeight() override
	{
		return MUSHROOM_HEIGHT;
	}
};