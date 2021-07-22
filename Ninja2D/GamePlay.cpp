#include "GamePlay.h"


GamePlay::GamePlay()
{
	enemyID = 0;
	ninja = new Character();
}

GamePlay::~GamePlay()
{
	RemoveObject(ninja);

	for (auto enemy : enemies) {
		RemoveObject(enemy);
	}

	for (auto weapon : weapons) {
		RemoveObject(weapon);
	}
	
}

void GamePlay::Run()
{
	map.increseClousDrifting(CLOUD_SPEED);
	enemyID = (map.checkToAddEnemy(BaseObject::mapSlider + MAP_WIDTH));

	switch (enemyID)
	{
	case 1:
		enemies.push_back(new EnemyWhiteGhost(BaseObject::mapSlider + MAP_WIDTH));
		enemyID = 0;
		break;
	case 2:
		enemies.push_back(new EnemyBuzzyBeetle(BaseObject::mapSlider + MAP_WIDTH));
		enemyID = 0;
		break;
	case 3:
		enemies.push_back(new EnemySpinyBeetle(BaseObject::mapSlider + MAP_WIDTH));
		enemyID = 0;
		break;
	case 4:
		enemies.push_back(new EnemyMushroom(BaseObject::mapSlider + MAP_WIDTH));
		enemyID = 0;
		break;
	case 5:
		enemies.push_back(new EnemyBuzzyBeetle(BaseObject::mapSlider + MAP_WIDTH));
		enemyID = 0;
		break;
	default:
		break;
	}

	for (auto enemy : enemies)
	{
		bool checkCollision = CheckCollision(ninja, enemy);
		if (checkCollision)
		{
			ninja->SetDeath(true);
		}
	}


	for (auto weapon : weapons) {
		for (auto enemy : enemies)
		{
			bool checkCollision = CheckCollision(weapon, enemy);
			if (checkCollision)
			{
				enemy->SetDeath(true);
				weapon->SetDeath(true);
			}
		}
	}
		



}

void GamePlay::Draw(HWND hwnd, HDC hdc)
{
	timer++;
	map.Draw(hwnd, hdc);
 	ninja->Draw(hwnd, hdc);
	//for () 
	if (timer >= 2)
	{
		if (ninja->CheckDeath())
		{
			ninja->IncreseJumpingHeight(10);
		}
		else if (ninja->GetJumpingHeight() > 0 && (ninja->CheckFalling()))
		{
			ninja->IncreseJumpingHeight(-5);
		}
		else if (ninja->CheckJumping() && (ninja->GetJumpingHeight() < 250) && (!ninja->CheckFalling()))
		{
			ninja->MoveUp();
		}

		for (auto enemy : enemies) {
			if (enemy->CheckDeath() == true)
			{
				enemies.erase(enemies.begin());
			}
			else
			{
				enemy->Draw(hwnd, hdc);
				enemy->MakeAnimation();
			}
		}

		for (auto weapon : weapons) {
			if (weapon->CheckDeath() == true)
			{
				//RemoveObject(weapon);
				weapons.erase(weapons.begin());
			}
			else
			{
				weapon->Draw(hwnd, hdc);
			}

		}

		timer = 0;
	}
	else
	{
		if (ninja->CheckDeath())
		{
			ninja->IncreseJumpingHeight(10);
		}
		else if (ninja->GetJumpingHeight() > 0 && (ninja->CheckFalling()))
		{
			ninja->IncreseJumpingHeight(-5);
		}
		else if (ninja->CheckJumping() && (ninja->GetJumpingHeight() < 250) && (!ninja->CheckFalling()))
		{
			ninja->MoveUp();
		}

		
		for (auto enemy : enemies) {
			if (enemy->CheckDeath() == true)
			{
				enemies.erase(enemies.begin());
			}
			else
			{
				enemy->Draw(hwnd, hdc);

			}
		}

		for (auto weapon : weapons) {
			if (weapon->CheckDeath() == true)
			{
				//RemoveObject(weapon);
				weapons.erase(weapons.begin());
			}
			else
			{
				weapon->Draw(hwnd, hdc);
			}
			
		}

	}

}
void GamePlay::Attack()
{
	if (!ninja->CheckDeath())
	{
		int typeOfWeapon = ninja->GetTypeOfWeapon();

		if (ninja->IsGoLeft() == true)
		{
			ninja->SetFormX(0);

			if (ninja->CheckSitting() == true)
			{
				AddWeapon(typeOfWeapon, 0, 0);
			}
			else if (ninja->CheckJumping() == true)
			{
				AddWeapon(typeOfWeapon, 0, 1);
			}
			else if (ninja->CheckJumping() == false)
			{
				AddWeapon(typeOfWeapon, 0, 2);
			}
			
			
		}
		else if (ninja->IsGoRight() == true)
		{
			ninja->SetFormX(19);

			if (ninja->CheckSitting() == true)
			{
				AddWeapon(typeOfWeapon, 1, 0);
			}
			else if (ninja->CheckJumping() == true)
			{
				AddWeapon(typeOfWeapon, 1, 1);
			}
			else if (ninja->CheckJumping() == false)
			{
				AddWeapon(typeOfWeapon, 1, 2);
			}

		}
		

	}
 
}

void GamePlay::KeyUpSpace()
{
	if (!ninja->CheckDeath())
	{
		if (ninja->IsGoRight() == true)
		{
			ninja->SetFormX(10);
		}
		else if (ninja->IsGoLeft() == true)
		{
			ninja->SetFormX(9);
		}
	}

}

void GamePlay::MoveNinjaLeft()
{
	if (!ninja->CheckDeath())
	{
		ninja->MoveLeft();
		if (ninja->GetPosX() + 20 - map.getMapSlider() <= 0)
		{
			ninja->IncresePosX(PLAYER_SPEED);
		}

		//change sprite
		if (ninja->CheckJumping() == true)
		{
			if (ninja->IsGoRight())
			{
				ninja->SetFormX(9);
			}
			else
			{
				if (ninja->GetFormX() <= 6)
					ninja->SetFormX(9);
				else
					ninja->IncreseFormX(-1);
			}
		}
		else
		{
			if (ninja->IsGoRight())
				ninja->SetFormX(9);
			else
			{
				if (ninja->GetFormX() <= 1)
					ninja->SetFormX(8);
				else
					ninja->IncreseFormX(-1);
			}
		}
	}


	//for (auto enemy : enemies) {
	//	enemy->MakeAnimation();
	//}
}

void GamePlay::MoveNinjaRight()
{
	if (!ninja->CheckDeath())
	{
		ninja->MoveRight();

		if (ninja->GetPosX() - map.getMapSlider() >= 500)
		{
			map.increseMapSlider(PLAYER_SPEED);
		}

		if (ninja->GetPosX() >= END_OF_MAP)
		{
			map.increseMapSlider(-PLAYER_SPEED);
			ninja->MoveLeft();
		}

		//change sprite
		if (ninja->CheckJumping() == true)
		{
			if (ninja->IsGoLeft())
			{
				ninja->SetFormX(10);
			}
			else
			{
				if (ninja->GetFormX() >= 13)
					ninja->SetFormX(10);
				else
					ninja->IncreseFormX(1);
			}
		}
		else
		{
			if (ninja->IsGoLeft())
				ninja->SetFormX(10);
			else
			{
				if (ninja->GetFormX() >= 18)
					ninja->SetFormX(11);
				else
					ninja->IncreseFormX(1);
			}
		}
	}


	//for (auto enemy : enemies) {
	//	enemy->MakeAnimation();
	//}
}

void GamePlay::MoveNinjaUp()
{
	if (!ninja->CheckDeath())
	{
		ninja->MoveUp();
		if (ninja->IsGoRight())
		{
			ninja->SetFormX(13);
			ninja->SetFormY(1);
		}
		else if (ninja->IsGoLeft())
		{
			ninja->SetFormX(6);
			ninja->SetFormY(1);
		}
	}

}

void GamePlay::MoveNinjaDown()
{
	if (!ninja->CheckDeath())
	{
		ninja->MoveDown();
		if (ninja->CheckJumping() == true)
		{
			if (ninja->IsGoRight())
			{
				ninja->SetFormX(13);
				ninja->SetFormY(1);
			}
			else if (ninja->IsGoLeft())
			{
				ninja->SetFormX(6);
				ninja->SetFormY(1);
			}
		}
		else
		{
			ninja->SetSit(true);
			if (ninja->IsGoRight())
			{
				ninja->SetFormX(10);
				ninja->SetFormY(2);
			}
			else if (ninja->IsGoLeft())
			{
				ninja->SetFormX(9);
				ninja->SetFormY(2);
			}
		}
		
	}
}

void GamePlay::KeyUpDown()
{
	if (!ninja->CheckDeath())
	{
		ninja->SetSit(false);
		if (ninja->CheckJumping() == true)
		{
			if (ninja->IsGoRight())
			{
				ninja->SetFormX(12);
				ninja->SetFormY(1);
			}
			else if (ninja->IsGoLeft())
			{
				ninja->SetFormX(7);
				ninja->SetFormY(1);
			}
		}
		else
		{
			if (ninja->IsGoRight())
			{
				ninja->SetFormX(10);
				ninja->SetFormY(0);
			}
			else if (ninja->IsGoLeft())
			{
				ninja->SetFormX(9);
				ninja->SetFormY(0);
			}
		}
	}
}

void GamePlay::KeyUpUp()
{
	if (!ninja->CheckDeath())
	{
		if (ninja->CheckJumping() == true)
		{
			if (ninja->IsGoRight())
			{
				ninja->SetFormX(10);
				ninja->SetFormY(1);
			}
			else if (ninja->IsGoLeft())
			{
				ninja->SetFormX(9);
				ninja->SetFormY(1);
			}
		}
		else
		{
			if (ninja->IsGoRight())
			{
				ninja->SetFormX(10);
				ninja->SetFormY(0);
			}
			else if (ninja->IsGoLeft())
			{
				ninja->SetFormX(9);
				ninja->SetFormY(0);
			}
		}
	}
}

void GamePlay::KeyUpRight()
{
	if (!ninja->CheckDeath())
	{
		ninja->SetFormX(10);
	}

}

void GamePlay::KeyUpLeft()
{
	if (!ninja->CheckDeath())
	{
		ninja->SetFormX(9);
	}

}

bool GamePlay::CheckCollision(LiveObject* object, LiveObject* monster)
{
	Point2D monsterPos = Point2D(monster->GetPosX(), monster->GetPosY());
	int monsterWidth = monster->GetWidth();
	int monsterHeight = monster->GetHeight();

	Point2D aPoint = Point2D(object->GetPosX(), object->GetPosY());
	Point2D bPoint = Point2D(object->GetPosX() + object->GetWidth(), object->GetPosY());
	Point2D cPoint = Point2D(object->GetPosX(), object->GetPosY() + object->GetHeight());
	Point2D dPoint = Point2D(object->GetPosX() + object->GetWidth(), object->GetPosY() + object->GetHeight());

	bool aCheck = aPoint.CheckPointInsideRect(monsterPos, monsterHeight, monsterWidth);
	bool bCheck = bPoint.CheckPointInsideRect(monsterPos, monsterHeight, monsterWidth);
	bool cCheck = cPoint.CheckPointInsideRect(monsterPos, monsterHeight, monsterWidth);
	bool dCheck = dPoint.CheckPointInsideRect(monsterPos, monsterHeight, monsterWidth);

	bool isColliding = false;

	if (bCheck)
	{
		isColliding = true;
	}
	else if (dCheck)
	{
		isColliding = true;
	}
	else if (aCheck)
	{
		isColliding = true;
	}
	else if (cCheck)
	{
		isColliding = true;
	}

	return isColliding;
}


void GamePlay::RemoveObject(BaseObject* object)
{
	delete object;
	object = nullptr;
}

void  GamePlay::AddWeapon(int type, int dir_Moving, int stage)
{
	//type: 0 = sword, 1 is shuriken, 2 = kunai, 3 = fire
	//dir_Moving: 0 = Left, 1 = Right, 
	//stage: 0 = sitting, 1 = jumping, 2 = on the ground

	if (type == 0)
	{
		if (dir_Moving == 0)
		{
			if (stage == 0)
			{
				weapons.push_back(new BlueSword(ninja->GetPosX() - BLUE_SWORD_WIDTH + 40 , dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 65));
			}
			else if (stage == 1)
			{
				weapons.push_back(new BlueSword(ninja->GetPosX() - BLUE_SWORD_WIDTH + 45, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 60));
			}
			else if (stage == 2)
			{
				weapons.push_back(new BlueSword(ninja->GetPosX() - BLUE_SWORD_WIDTH + 45, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 35));
			}
		}
		else if (dir_Moving == 1)
		{
			if (stage == 0)
			{
				weapons.push_back(new BlueSword(ninja->GetPosX()  + 80, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 65));
			}
			else if (stage == 1)
			{
				weapons.push_back(new BlueSword(ninja->GetPosX()  + 85, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 60));
			}
			else if (stage == 2)
			{
				weapons.push_back(new BlueSword(ninja->GetPosX() + 85, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 35));
			}
		}
	}
	else if (type == 1)
	{
		if (dir_Moving == 0)
		{
			if (stage == 0)
			{
				weapons.push_back(new WeaponShuriken(ninja->GetPosX() - SHURIKEN_WIDTH , dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 65));
			}
			else if (stage == 1)
			{
				weapons.push_back(new WeaponShuriken(ninja->GetPosX() - SHURIKEN_WIDTH + 5, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 60));
			}
			else if (stage == 2)
			{
				weapons.push_back(new WeaponShuriken(ninja->GetPosX() - SHURIKEN_WIDTH + 5, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 35));
			}
		}
		else if (dir_Moving == 1)
		{
			if (stage == 0)
			{
				weapons.push_back(new WeaponShuriken(ninja->GetPosX() + 120, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 65));
			}
			else if (stage == 1)
			{
				weapons.push_back(new WeaponShuriken(ninja->GetPosX() + 125, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 60));
			}
			else if (stage == 2)
			{
				weapons.push_back(new WeaponShuriken(ninja->GetPosX() + 125, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 35));
			}
		}
	}
	else if (type == 2)
	{
		if (dir_Moving == 0)
		{
			if (stage == 0)
			{
				weapons.push_back(new WeaponKunai(ninja->GetPosX() - KUNAI_WIDTH + 10, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 75));
			}
			else if (stage == 1)
			{
				weapons.push_back(new WeaponKunai(ninja->GetPosX() - KUNAI_WIDTH + 15, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 70));
			}
			else if (stage == 2)
			{
				weapons.push_back(new WeaponKunai(ninja->GetPosX() - KUNAI_WIDTH + 15, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 40));
			}
		}
		else if (dir_Moving == 1)
		{
			if (stage == 0)
			{
				weapons.push_back(new WeaponKunai(ninja->GetPosX() + 110, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 75));
			}
			else if (stage == 1)
			{
				weapons.push_back(new WeaponKunai(ninja->GetPosX() + 115, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 70));
			}
			else if (stage == 2)
			{
				weapons.push_back(new WeaponKunai(ninja->GetPosX() + 115, dir_Moving
					, ninja->GetPosY() - ninja->GetJumpingHeight() + 40));
			}
		}
	}
	else if (type == 3)
	{
	if (dir_Moving == 0)
	{
		if (stage == 0)
		{
			weapons.push_back(new WeaponFire(ninja->GetPosX() - FIRE_WIDTH + 10, dir_Moving
				, ninja->GetPosY() - ninja->GetJumpingHeight() + 70));
		}
		else if (stage == 1)
		{
			weapons.push_back(new WeaponFire(ninja->GetPosX() - FIRE_WIDTH + 15, dir_Moving
				, ninja->GetPosY() - ninja->GetJumpingHeight() + 65));
		}
		else if (stage == 2)
		{
			weapons.push_back(new WeaponFire(ninja->GetPosX() - FIRE_WIDTH + 15, dir_Moving
				, ninja->GetPosY() - ninja->GetJumpingHeight() + 35));
		}
	}
	else if (dir_Moving == 1)
	{
		if (stage == 0)
		{
			weapons.push_back(new WeaponFire(ninja->GetPosX() + 110, dir_Moving
				, ninja->GetPosY() - ninja->GetJumpingHeight() + 70));
		}
		else if (stage == 1)
		{
			weapons.push_back(new WeaponFire(ninja->GetPosX() + 115, dir_Moving
				, ninja->GetPosY() - ninja->GetJumpingHeight() + 65));
		}
		else if (stage == 2)
		{
			weapons.push_back(new WeaponFire(ninja->GetPosX() + 115, dir_Moving
				, ninja->GetPosY() - ninja->GetJumpingHeight() + 35));
		}
	}
	}
}
