#pragma once
#include "Enemy.h"
#include "Map.h"

#define MONSTER_GIRL_HEIGHT 65
#define MONSTER_GIRL_WIDTH 70
#define MONSTER_GIRL_AREA 1200
#define MONSTER_GIRL_SPEED 20


class EnemyMonsterGirl : public Enemy
{
private:
	bool isFalling;
public:
	EnemyMonsterGirl(int a_x)
	{
		posX = a_x;
		posY = 50;
		//CHANGE FORM
		formX = 4;
		formY = 0;
		originalLocation = a_x;
		life = 1;
		isFalling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"MonsterGirl.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));

	}

	EnemyMonsterGirl()
	{
		posX = 0;
		posY = 50;
		//CHANGE FORM
		formX = 4;
		formY = 0;
		originalLocation = 0;
		life = 1;
		isFalling = true;
		hBitmap = (HBITMAP)LoadImage(hInst, L"MonsterGirl.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	}

	~EnemyMonsterGirl()
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
			MONSTER_GIRL_WIDTH,
			MONSTER_GIRL_HEIGHT,
			hdcMem,
			MONSTER_GIRL_WIDTH * formX,
			MONSTER_GIRL_HEIGHT * formY,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			posX - BaseObject::mapSlider,
			posY,
			MONSTER_GIRL_WIDTH,
			MONSTER_GIRL_HEIGHT,
			hdcMem,
			MONSTER_GIRL_WIDTH * formX,
			MONSTER_GIRL_HEIGHT * formY,
			SRCPAINT
		);

		if (isFalling)
		{
			posY = posY + 5;
			if (posY >= 300)
			{
				isFalling = false;
			}
		}
		else if (!isFalling)
		{
			posY = posY - 7;
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
		posX = posX - MONSTER_GIRL_SPEED;
	}

	void MoveRight() override
	{
		posX = posX + MONSTER_GIRL_SPEED;
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
		isDead = a_isDead;
	}




	void MakeAnimation() override
	{
		clock++;
		if (!isDead)
		{
			if (EnemyMonsterGirl::IsGoRight())
			{
				if (clock >= 2)
				{
					clock = 0;
					if (formX >= 5)
						formX = 3;
					else
						formX = formX + 1;
				}
				

				EnemyMonsterGirl::MoveRight();

				if (posX >= originalLocation + MONSTER_GIRL_AREA)
				{
					formX = 2;
				}
			}

			else if (EnemyMonsterGirl::IsGoLeft())
			{
				if (clock >= 2)
				{
					clock = 0;
					if (formX <= 0)
						formX = 2;
					else
						formX = formX - 1;
				}
				

				EnemyMonsterGirl::MoveLeft();

				if (posX <= originalLocation)
				{
					formX = 4;
				}
			}
		}
	}

	int GetWidth() override
	{
		return MONSTER_GIRL_WIDTH;
	}

	int GetHeight() override
	{
		return MONSTER_GIRL_HEIGHT;
	}

};