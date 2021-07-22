#pragma once
#include <windows.h>
#include <WindowsX.h>
#include <vector>

#include "Character.h"
#include "BaseObject.h"
#include "EnemyMushroom.h"
#include "EnemyBuzzyBeetle.h"
#include "EnemySpinyBeetle.h"
#include "EnemyWhiteGhost.h"
#include "Map.h"
#include "Weapon.h"
#include "WeaponKunai.h"
#include "WeaponShuriken.h"
#include "WeaponFire.h"
#include "Enemy.h"
#include "Point2D.h"
#include "LiveObject.h"

class GamePlay
{
private:
	std::vector <Enemy*> enemies; // enemy objects
	std::vector <Weapon*> weapons;
	Map map;
	Character * ninja;
	int enemyID;
	int timer;
public:
	GamePlay();
	~GamePlay();

	void Run();
	void Draw(HWND hwnd, HDC hdc);
	void Attack();
	void MoveNinjaLeft();
	void MoveNinjaRight();
	void MoveNinjaUp();
	void MoveNinjaDown();
	void KeyUpDown();
	void KeyUpUp();
	void KeyUpLeft();
	void KeyUpRight();
	void KeyUpSpace();
	bool CheckCollision(LiveObject* object, LiveObject* monster);
	void RemoveObject(BaseObject* object);
};

