#include "Character.h"

Character::Character()
{
	posX = 0;
	posY = 353;
	formX = 10;
	formY = 0;
	life = 3;
	jumpHeight = 0;
	typeOfWeapon = 4;
	isJumping = false;
	isSitting = false;
	isAttack = false;
	isWin = false;
	score = 0;
	hBitmap_Hear = (HBITMAP)LoadImage(hInst, L"Hear.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap_GameOver = (HBITMAP)LoadImage(hInst, L"GameOver.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap_YouWin = (HBITMAP)LoadImage(hInst, L"YouWin.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap = (HBITMAP)LoadImage(hInst, L"NinjaBoy.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap_Number = (HBITMAP)LoadImage(hInst, L"FirstNumber.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


	hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
	hbmMask_GameOver = CreateBitmapMask(hBitmap_GameOver, RGB(255, 0, 255));
	hbmMask_YouWin = CreateBitmapMask(hBitmap_YouWin, RGB(255, 0, 255));
	hbmMask_Hear = CreateBitmapMask(hBitmap_Hear, RGB(255, 0, 255));
	hbmMask_Number = CreateBitmapMask(hBitmap_Number, RGB(255, 0, 255));

	countGameOver = MAP_HEIGHT;
	formXOver = 0;
	formOfUnits = 0;
	formOfTens = 0;
	isTens = false;
	formOfHundreds = 0;
	isHundreds = false;
}

Character::~Character()
{

}

int Character::GetFormX()
{
	return formX;
}

int Character::GetFormY()
{
	return formY;
}

void Character::SetFormX(int a_formX)
{
	formX = a_formX;
}

void Character::SetFormY(int a_formY)
{
	formY = a_formY;
}

void Character::IncreseFormX(int a)
{
	formX = formX + a;
}

void Character::MoveLeft()
{
	posX = posX - PLAYER_SPEED;
	//change sprite
	if (jumpHeight > 0)
	{
		if (Character::IsGoRight())
		{
			formX = 9;
		}
		else
		{
			if (formX <= 6)
				formX = 9;
			else
				formX = formX - 1;
		}
	}
	else
	{
		if (Character::IsGoRight())
			formX = 9;
		else
		{
			if (formX <= 1)
				formX = 8;
			else
				formX = formX - 1;
		}
	}
}

void Character::MoveRight()
{
	posX = posX + PLAYER_SPEED;
	//change sprite
	if (jumpHeight > 0)
	{
		if (Character::IsGoLeft())
		{
			formX= 10;
		}
		else
		{
			if (formX >= 13)
				formX = 10;
			else
				formX = formX + 1;
		}
	}
	else
	{
		if (Character::IsGoLeft())
			formX = 10;
		else
		{
			if (formX >= 18)
				formX =11;
			else
				formX = formX + 1;
		}
	}

}

void Character::MoveUp()
{

	isJumping = true;
	if (jumpHeight <= 270)
	{
		jumpHeight += 60;
	}

	//-----------

	Character::IncreaseScore(1);
	




}

void Character::MoveDown()
{
	if (jumpHeight > 0)
	{
		jumpHeight -= 10;
	}
}

void Character::Draw(HWND hwnd, HDC hdc)
{
	//Show life
	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = SelectObject(hdcMem, hbmMask_Hear);
	GetObject(hbmMask_Hear, sizeof(bitmap), &bitmap);
	BitBlt
	(
		hdc,
		90,
		0,
		HEAR_WIDTH * life,
		HEAR_HEIGHT,
		hdcMem,
		HEAR_WIDTH * 0,
		0,
		SRCAND
	);
	oldBitmap = SelectObject(hdcMem, hBitmap_Hear);
	GetObject(hBitmap_Hear, sizeof(bitmap), &bitmap);
	BitBlt
	(
		hdc,
		90,
		0,
		HEAR_WIDTH * life,
		HEAR_HEIGHT,
		hdcMem,
		HEAR_WIDTH * 0,
		0,
		SRCPAINT
	);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);

	//Show score
	//Last number
	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = SelectObject(hdcMem, hbmMask_Number);
	GetObject(hbmMask_Number, sizeof(bitmap), &bitmap);
	BitBlt
	(
		hdc,
		MAP_WIDTH - NUMBER_WIDTH,
		5,
		NUMBER_WIDTH,
		NUMBER_HEIGHT,
		hdcMem,
		0,
		0,
		SRCAND
	);
	oldBitmap = SelectObject(hdcMem, hBitmap_Number);
	GetObject(hBitmap_Number, sizeof(bitmap), &bitmap);
	BitBlt
	(
		hdc,
		MAP_WIDTH - NUMBER_WIDTH,
		5,
		NUMBER_WIDTH,
		NUMBER_HEIGHT,
		hdcMem,
		0,
		0,
		SRCPAINT
	);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);


	//Units
	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = SelectObject(hdcMem, hbmMask_Number);
	GetObject(hbmMask_Number, sizeof(bitmap), &bitmap);
	BitBlt
	(
		hdc,
		MAP_WIDTH - (NUMBER_WIDTH) * 2,
		5,
		NUMBER_WIDTH,
		NUMBER_HEIGHT,
		hdcMem,
		NUMBER_WIDTH * formOfUnits,
		0,
		SRCAND
	);
	oldBitmap = SelectObject(hdcMem, hBitmap_Number);
	GetObject(hBitmap_Number, sizeof(bitmap), &bitmap);
	BitBlt
	(
		hdc,
		MAP_WIDTH - (NUMBER_WIDTH) * 2,
		5,
		NUMBER_WIDTH,
		NUMBER_HEIGHT,
		hdcMem,
		NUMBER_WIDTH * formOfUnits,
		0,
		SRCPAINT
	);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);

	//Tens
	if (isTens == true)
	{
		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hbmMask_Number);
		GetObject(hbmMask_Number, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			MAP_WIDTH - (NUMBER_WIDTH) * 3,
			5,
			NUMBER_WIDTH,
			NUMBER_HEIGHT,
			hdcMem,
			NUMBER_WIDTH * formOfTens,
			0,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap_Number);
		GetObject(hBitmap_Number, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			MAP_WIDTH - (NUMBER_WIDTH) * 3,
			5,
			NUMBER_WIDTH,
			NUMBER_HEIGHT,
			hdcMem,
			NUMBER_WIDTH * formOfTens,
			0,
			SRCPAINT
		);
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
	}

	//Hundreds 
	if (isHundreds == true)
	{
		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hbmMask_Number);
		GetObject(hbmMask_Number, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			MAP_WIDTH - (NUMBER_WIDTH) * 4,
			5,
			NUMBER_WIDTH,
			NUMBER_HEIGHT,
			hdcMem,
			NUMBER_WIDTH * formOfHundreds,
			0,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap_Number);
		GetObject(hBitmap_Number, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			MAP_WIDTH - (NUMBER_WIDTH) * 4,
			5,
			NUMBER_WIDTH,
			NUMBER_HEIGHT,
			hdcMem,
			NUMBER_WIDTH * formOfHundreds,
			0,
			SRCPAINT
		);
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
	}

	//Thousands

	if (isThousands == true)
	{
		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hbmMask_Number);
		GetObject(hbmMask_Number, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			MAP_WIDTH - (NUMBER_WIDTH) * 5,
			5,
			NUMBER_WIDTH,
			NUMBER_HEIGHT,
			hdcMem,
			NUMBER_WIDTH * formOfThousands,
			0,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap_Number);
		GetObject(hBitmap_Number, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			MAP_WIDTH - (NUMBER_WIDTH ) * 5,
			5,
			NUMBER_WIDTH,
			NUMBER_HEIGHT,
			hdcMem,
			NUMBER_WIDTH * formOfThousands,
			0,
			SRCPAINT
		);
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
	}

	//Win game
	if (life >= 0)
	{
		if (isWin == true)
		{

			if (countGameOver > 50)
			{
				countGameOver = countGameOver - 3;
			}

			if (formXOver >= 7)
			{
				formXOver = 0;
			}
			else
			{
				formXOver++;
			}


			hdcMem = CreateCompatibleDC(hdc);
			oldBitmap = SelectObject(hdcMem, hbmMask_YouWin);
			GetObject(hbmMask_YouWin, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				(1000 - NOTIFICATION_WIDTH)/2,
				countGameOver,
				NOTIFICATION_WIDTH,
				NOTIFICATION_HEIGHT,
				hdcMem,
				NOTIFICATION_WIDTH * formXOver,
				0,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap_YouWin);
			GetObject(hBitmap_YouWin, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				(1000 - NOTIFICATION_WIDTH) / 2,
				countGameOver,
				NOTIFICATION_WIDTH,
				NOTIFICATION_HEIGHT,
				hdcMem,
				NOTIFICATION_WIDTH * formXOver,
				0,
				SRCPAINT
			);
			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);
		}
		else
		{
			//Show Character
			if (CheckSitting() == true)
			{
				formY = 2;
			}
			else if (CheckJumping() == false)
			{
				formY = 0;
			}

			hdcMem = CreateCompatibleDC(hdc);
			oldBitmap = SelectObject(hdcMem, hbmMask);
			GetObject(hbmMask, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - mapSlider,
				posY - jumpHeight,
				CHARACTER_WIDTH,
				CHARACTER_HEIGHT,
				hdcMem,
				CHARACTER_WIDTH * formX,
				CHARACTER_HEIGHT * formY,
				SRCAND
			);
			oldBitmap = SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt
			(
				hdc,
				posX - mapSlider,
				posY - jumpHeight,
				CHARACTER_WIDTH,
				CHARACTER_HEIGHT,
				hdcMem,
				CHARACTER_WIDTH * formX,
				CHARACTER_HEIGHT * formY,
				SRCPAINT
			);
			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);
		}

	}
	else
	{
		//Game Over
		if (countGameOver > 50)
		{
			countGameOver = countGameOver - 3;
		}

		if (formXOver >= 7)
		{
			formXOver = 0;
		}
		else
		{
			formXOver++;
		}
			

		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hbmMask_GameOver);
		GetObject(hbmMask_GameOver, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			(1000 - NOTIFICATION_WIDTH) / 2,
			countGameOver,
			NOTIFICATION_WIDTH,
			NOTIFICATION_HEIGHT,
			hdcMem,
			NOTIFICATION_WIDTH * formXOver,
			0,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap_GameOver);
		GetObject(hBitmap_GameOver, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			(1000 - NOTIFICATION_WIDTH) / 2,
			countGameOver,
			NOTIFICATION_WIDTH,
			NOTIFICATION_HEIGHT,
			hdcMem,
			NOTIFICATION_WIDTH * formXOver,
			0,
			SRCPAINT
		);
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
	}

}


bool Character::IsGoLeft()
{
	if ((formY != 3) && (formX <= 9))
		return true;
	return false;
}

bool  Character::IsGoRight()
{
	if ((formY != 3) && (formX >= 10))
		return true;
	return false;
}
void Character::SetJump(bool trueOrFalse)
{
	isJumping = trueOrFalse;
}

void Character::SetSit(bool trueOrFalse)
{
	isSitting = trueOrFalse;
}

bool Character::CheckJumping()
{
	if (jumpHeight > 0)
		isJumping = true;
	else
		isJumping = false;

	return isJumping;
}

bool Character::CheckSitting()
{
	return isSitting;
}

void Character::SetJumpHeight(int a_jumpHeight)
{
	jumpHeight = a_jumpHeight;
}

void Character::IncreseJumpingHeight(int a)
{
	jumpHeight += a;
}

int Character::GetJumpingHeight()
{
	return jumpHeight;
}

void Character::SetDeath(bool a_isDead)
{
	isDead = a_isDead;
}

bool Character::CheckDeath()
{
	if (isDead == true)
	{
		if (IsGoLeft() == true)
		{
			formX = 9;
			formY = 3;
		}
		else if (IsGoRight() == true)
		{
			formX = 10;
			formY = 3;
		}
	}
	return isDead;
}

int Character::GetWidth()
{
	return CHARACTER_WIDTH;
}

int Character::GetHeight()
{
	return CHARACTER_HEIGHT;
}

void Character::UpgradeWeapon()
{
	typeOfWeapon++;
}

int Character::GetTypeOfWeapon()
{
	return typeOfWeapon;
}

void Character::SetTypeOfWeapon(int a_typeOfWeapon)
{
	typeOfWeapon = a_typeOfWeapon;
}

int Character::GetPosY()
{
	return (posY - jumpHeight);
}

void Character::MakeAnimation()
{
	if (isDead == true)
	{
		jumpHeight += 10;
		if ((life >=0) && (jumpHeight >= 400))
		{
			posX = posX - 200;
			Character::Regeneration();
		}
	}

	if ((isDead == false) && (jumpHeight) > 0)
	{
		jumpHeight -= 5;
	}
}

void Character::Regeneration()
{
	posY = 353;
	formX = 10;
	formY = 0;
	jumpHeight = 0;
	isJumping = false;
	isSitting = false;
	isAttack = false;
	isDead = false;
	//life--;
	typeOfWeapon = -1;
}


void Character::IncreseLife(int a_life)
{
	life = life + a_life;
}

void Character::Win()
{
	isWin = true;
}

void Character::IncreseClock()
{
	clock = clock + 1;
}

int Character::GetClock()
{
	return clock;
}

void Character::ResetClock()
{
	clock = 0;
}


void Character::IncreaseScore(int n)
{
	score = score + n;
	//formOfThousands
	if (score > 999)
	{
		isThousands = true;
		formOfThousands = score / 1000;
		formOfHundreds = (score % 1000) / 100;
		formOfTens = (score % 100) / 10;
		formOfUnits = score % 10;
	}
	else if (score > 99)
	{
		isHundreds = true;
		formOfHundreds = score / 100;
		formOfTens = (score % 100) / 10;
		formOfUnits = score % 10;
	}
	else if (score > 9)
	{
		isTens = true;
		formOfTens = score / 10;
		formOfUnits = score % 10;
	}
	else
		formOfUnits = score;
		
}