#pragma once
#include "Enemy.h"
#include "Map.h"

#define DARK_GIRL_HEIGHT 65
#define DARK_GIRL_WIDTH 70
#define DARK_GIRL_AREA 500
#define DARK_GIRL_SPEED 10

//chang name
class EnemyDarkGirl : public Enemy
{
private:
	bool isFalling;
public:
	EnemyDarkGirl(int a_x)
	{
		posX = a_x;
		posY = 50;
		//CHANGE FORM
		formX = 3;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		isFalling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"DarkGirl.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));

	}

	EnemyDarkGirl()
	{
		posX = 0;
		posY = 50;
		//CHANGE FORM
		formX = 4;
		formY = 0;
		originalLocation = 0;
		life = 1;
		isFalling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"DarkGirl.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	~EnemyDarkGirl()
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
			DARK_GIRL_WIDTH,
			DARK_GIRL_HEIGHT,
			hdcMem,
			DARK_GIRL_WIDTH * formX,
			DARK_GIRL_HEIGHT * formY,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			posX - BaseObject::mapSlider,
			posY,
			DARK_GIRL_WIDTH,
			DARK_GIRL_HEIGHT,
			hdcMem,
			DARK_GIRL_WIDTH * formX,
			DARK_GIRL_HEIGHT * formY,
			SRCPAINT
		);

		if (isFalling)
		{
			posY = posY + 4;
			formX--;
			if (formX <= 0)
				formX = 2;
			else
				formX--;

			if (posY >= 300)
			{
				isFalling = false;
			}
		}
		else if (!isFalling)
		{
			posY = posY - 4;

			formX++;
			if (formX >= 5)
				formX = 3;
			else
				formX++;

			if (posY <= 100)
			{
				isFalling = true;
			}
		}
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
	}

	void MoveLeft() override
	{
		posX = posX - DARK_GIRL_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + DARK_GIRL_SPEED;
	}

	bool IsGoLeft() override
	{
		if ((formX >= 0) && (formX <= 2))
			return true;
		return false;
	}

	bool IsGoRight() override
	{
		if ((formX >= 3) && (formX <= 5))
			return true;
		return false;
	}
	void SetDeath(bool a_isDead) override
	{
		this->isDead = a_isDead;
	}




	void MakeAnimation() override
	{
		//
	}

	int GetWidth() override
	{
		return DARK_GIRL_WIDTH;
	}

	int GetHeight() override
	{
		return DARK_GIRL_HEIGHT;
	}

};