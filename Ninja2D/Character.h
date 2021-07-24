#pragma once
#include <cmath>
#include "LiveObject.h"
#include "Map.h"


#define CHARACTER_WIDTH 125
#define CHARACTER_HEIGHT 115
#define PLAYER_SPEED 5
#define NOTIFICATION_WIDTH 500
#define NOTIFICATION_HEIGHT 270
#define HEAR_WIDTH 40
#define HEAR_HEIGHT 30

class Character : public LiveObject
{
private:
	int jumpHeight;
	bool isJumping;
	bool isSitting;
	bool isAttack;
	int typeOfWeapon;
	HBITMAP hBitmap_GameOver, hbmMask_GameOver, hBitmap_YouWin, hbmMask_YouWin;
	HBITMAP hBitmap_Hear, hbmMask_Hear;
	int countGameOver;
	int formXOver;
	bool isWin;
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
	void MakeAnimation() override;
	void Regeneration();
	void IncreseLife(int a_life);
	void Win();
	void IncreseClock();
	int GetClock();
	void ResetClock();
};



