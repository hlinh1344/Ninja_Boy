#pragma once
#include <cmath>
#include "BaseObject.h"
#include "Map.h"


#define CHARACTER_WIDTH 125
#define CHARACTER_HEIGHT 115
#define PLAYER_SPEED 4
//Height 115
//Width 125

class Character : public BaseObject
{
private:
	int jumpHeight;
	bool isJumping;
	bool isFalling;
	bool isSitting;
	bool isAttack;
public:
	Character();
	~Character();
	int GetFormX();
	int GetFormY();
	void SetFormX(int a_formX);
	void SetFormY(int a_formY);
	void IncreseFormX(int a);
	void Draw(HWND hwnd, HDC hdc) override;
	void MoveUp();
	void MoveDown();
	void SetJump(bool trueOrFalse);
	void SetSit(bool trueOrFalse);
	bool CheckJumping();
	bool CheckFalling();
	bool CheckSitting();
	void SetJumpHeight(int a_jumpHeight);
	void IncreseJumpingHeight(int a);
	int GetJumpingHeight();
	bool CheckDeath();
};



