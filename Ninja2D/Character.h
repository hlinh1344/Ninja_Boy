#pragma once
#include <cmath>
#include "LiveObject.h"
#include "Map.h"


#define CHARACTER_WIDTH 125
#define CHARACTER_HEIGHT 115
#define PLAYER_SPEED 4


class Character : public LiveObject
{
private:
	int jumpHeight;
	bool isJumping;
	bool isFalling;
	bool isSitting;
	bool isAttack;
	int typeOfWeapon;
public:
	Character();
	~Character();
	int GetFormX();
	int GetFormY();
	void SetFormX(int a_formX);
	void SetFormY(int a_formY);
	void IncreseFormX(int a);
	void Draw(HWND hwnd, HDC hdc) override;
	void MoveLeft() override;
	void MoveRight() override;
	void MoveUp() override;
	void MoveDown() override;
	bool IsGoLeft() override;
	bool IsGoRight() override;
	void SetJump(bool trueOrFalse);
	void SetSit(bool trueOrFalse);
	bool CheckJumping();
	bool CheckFalling();
	bool CheckSitting();
	void SetJumpHeight(int a_jumpHeight);
	void IncreseJumpingHeight(int a);
	void SetDeath(bool a_isDead) override;
	int GetJumpingHeight();
	bool CheckDeath() override;
	int GetWidth() override;
	int GetHeight() override;
	void UpgradeWeapon();
	int GetTypeOfWeapon();
	void SetTypeOfWeapon(int a_typeOfWeapon);
	int GetPosY() override;
};



