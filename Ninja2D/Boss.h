#pragma once
#include "Enemy.h"
#include "Map.h"

#define BOSS_HEIGHT 125
#define BOSS_WIDTH 115
#define BOSS_AREA 350
#define BOSS_SPEED 8

//chang name
class Boss : public Enemy
{
private:
	bool isFalling;
	int count;
public:
	Boss(int a_x)
	{
		posX = a_x;
		posY = 50;
		//CHANGE FORM
		formX = 3;
		formY = 0;
		originalLocation = a_x;
		life = 20;
		isFalling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Boss.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
		count = 0;
	}

	Boss()
	{
		//posX = 3600;
		posX = 800;
		posY = 50;
		//CHANGE FORM
		formX = 3;
		formY = 0;
		originalLocation = 0;
		life = 10;
		isFalling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"Boss.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
		count = 0;
	}

	~Boss()
	{

	}

	void Draw(HWND hwnd, HDC hdc, HDC hdcMem) override
	{
		if (!isDead)
		{
			clock++;
			//hdcMem = CreateCompatibleDC(hdc);
			oldBitmap = SelectObject(hdcMem, hbmMask);
			GetObject(hbmMask, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				BOSS_WIDTH,
				BOSS_HEIGHT,
				hdcMem,
				BOSS_WIDTH * formX,
				BOSS_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - BaseObject::mapSlider,
				posY,
				BOSS_WIDTH,
				BOSS_HEIGHT,
				hdcMem,
				BOSS_WIDTH * formX,
				BOSS_HEIGHT * formY,
				SRCPAINT
			);

			if (isFalling)
			{
				posY = posY + BOSS_SPEED + BOSS_SPEED;

				if (clock >= 2)
				{
					clock = 0;
					if (formX <= 0)
						formX = 3;
					else
						formX--;
				}


				if (posY >= 470 - BOSS_HEIGHT)
				{
					isFalling = false;

					formY = 1;
				}
			}
			else if (!isFalling)
			{

				posY = posY - BOSS_SPEED;
				if (clock >= 2)
				{
					clock = 0;
					if (formX <= 0)
						formX = 3;
					else
						formX--;
				}

				if (posY <= 50)
				{
					isFalling = true;
					formY = 0;
				}

			}



			//SelectObject(hdcMem, oldBitmap);
			//DeleteDC(hdcMem);
		}
		
	}

	void MoveLeft() override
	{
		posX = posX - BOSS_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + BOSS_SPEED;
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


	void MakeAnimation() override
	{
		clock++;
		//
	}

	int GetWidth() override
	{
		return BOSS_WIDTH;
	}

	int GetHeight() override
	{
		return BOSS_HEIGHT;
	}

	void SetDeath(bool a_isDead) override
	{
		life--;
		if (life < 0)
		{
			isDead = true;
		}
	}

	bool CheckToAttack()
	{
		count++;
		if ((formX == 0) && (formY == 1) && count >= 3)
		{
			count = 0;
			return true;
		}
			
		return false;
	}


};