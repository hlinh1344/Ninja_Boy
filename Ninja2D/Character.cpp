#include "Character.h"

Character::Character()
{
	posX = 0;
	posY = 353;
	formX = 10;
	formY = 0;
	life = 3;
	jumpHeight = 0;
	typeOfWeapon = -1;
	isJumping = false;
	isFalling = false;
	isSitting = false;
	isAttack = false;
	hBitmap = (HBITMAP)LoadImage(hInst, L"NinjaBoy.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmMask = CreateBitmapMask(hBitmap, RGB(255, 0, 255));
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
	this->formX = a_formX;
}

void Character::SetFormY(int a_formY)
{
	this->formY = a_formY;
}

void Character::IncreseFormX(int a)
{
	this->formX = this->formX + a;
}

void Character::MoveLeft()
{
	posX = posX - PLAYER_SPEED;
}

void Character::MoveRight()
{
	posX = posX + PLAYER_SPEED;
}

void Character::MoveUp()
{

	this->isJumping = true;
	if (jumpHeight >= 250)
	{
		this->isFalling = true;
	}
	else
	{
		jumpHeight += 60;
		this->isFalling = false;
	}



}

void Character::MoveDown()
{
	if (jumpHeight > 0)
	{
		jumpHeight -= 10;
		this->isFalling = true;
	}
	else
		this->isFalling = true;
}

void Character::Draw(HWND hwnd, HDC hdc)
{
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
	this->isJumping = trueOrFalse;
}

void Character::SetSit(bool trueOrFalse)
{
	this->isSitting = trueOrFalse;
}

bool Character::CheckJumping()
{
	if (jumpHeight > 0)
		this->isJumping = true;
	else
		this->isJumping = false;

	return this->isJumping;
}

bool Character::CheckSitting()
{
	return this->isSitting;
}

bool Character::CheckFalling()
{
	return this->isJumping;
}

void Character::SetJumpHeight(int a_jumpHeight)
{
	this->jumpHeight = a_jumpHeight;
}

void Character::IncreseJumpingHeight(int a)
{
	this->jumpHeight += a;
}

int Character::GetJumpingHeight()
{
	return this->jumpHeight;
}

void Character::SetDeath(bool a_isDead)
{

	this->isDead = a_isDead;
	this->life--;
	this->typeOfWeapon = 0;

}

bool Character::CheckDeath()
{
	if (this->isDead == true)
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
	return this->isDead;
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
	this->typeOfWeapon++;
}

int Character::GetTypeOfWeapon()
{
	return this->typeOfWeapon;
}

void Character::SetTypeOfWeapon(int a_typeOfWeapon)
{
	this->typeOfWeapon = a_typeOfWeapon;
}

int Character::GetPosY()
{
	return (this->posY - this->jumpHeight);
}