#pragma once
#include <windows.h>
#include <WindowsX.h>
#include <vector>

#include "BaseObject.h"
#include "Map.h"
#include "LiveObject.h"
#include "Point2D.h"
#include "Character.h"

#include "Enemy.h"
#include "EnemyMushroom.h"
#include "EnemyBuzzyBeetle.h"
#include "EnemySpinyBeetle.h"
#include "EnemyWhiteGhost.h"
#include "EnemyBird.h"
#include "EnemyDarkDragon.h"
#include "EnemyMonsterGirl.h"
#include "EnemyDarkGirl.h"
#include "EnemyDarkRaven.h"
#include "Boss.h"

#include "Weapon.h"
#include "WeaponBlueSword.h"
#include "WeaponKunai.h"
#include "WeaponShuriken.h"
#include "WeaponFire.h"
#include "WeaponThunder.h"
#include "Moon.h"

#include "Item.h"
#include "BlueSwordItem.h"
#include "ShurikenItem.h"
#include "KunaiItem.h"
#include "FlameItem.h"
#include "ThunderDragonItem.h"

class GamePlay
{
private:
	std::vector <Enemy*> enemies;
	std::vector <Weapon*> weapons;
	std::vector <Item*> items;
	std::vector <Moon*> moons;

	Boss* boss;
	Map map;
	Character * ninja;
	int enemyID;
	int itemID;
	int timer;
	int countID;
	bool checkToAdd;
	int clock;

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
	bool CheckCollision(BaseObject* object1, BaseObject* object2);
	void RemoveObject(BaseObject* object);
	void AddWeapon(int type, int dir_Moving, int stage);
	void ResetClock();
	bool CheckClock();
};

