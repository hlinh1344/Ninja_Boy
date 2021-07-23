#include "GamePlay.h"


GamePlay::GamePlay()
{
	enemyID = 0;
	itemID = 0;
	countID = 0;
	checkToAdd = false;
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

	for (auto item : items) {
		RemoveObject(item);
	}

}

void GamePlay::Run()
{
	map.increseClousDrifting(CLOUD_SPEED);

	map.checkToAddEnemy(BaseObject::mapSlider + MAP_WIDTH, enemyID, checkToAdd);

	if (checkToAdd == true)
	{
		switch (enemyID)
		{
		case 1:
			enemies.push_back(new EnemyMushroom(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 2:
			enemies.push_back(new EnemyBird(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 3:
			enemies.push_back(new EnemyBuzzyBeetle(BaseObject::mapSlider + MAP_WIDTH));
			
			break;
		case 4:
			enemies.push_back(new EnemyWhiteGhost(BaseObject::mapSlider + MAP_WIDTH));
			
			break;
		case 5:
			enemies.push_back(new EnemySpinyBeetle(BaseObject::mapSlider + MAP_WIDTH));
			
			break;
		case 6:
			enemies.push_back(new EnemyDarkRaven(BaseObject::mapSlider + MAP_WIDTH));
			
			break;
		case 7:
			enemies.push_back(new EnemyMushroom(BaseObject::mapSlider + MAP_WIDTH));
		
			break;
		case 8:
			enemies.push_back(new EnemyBuzzyBeetle(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 9:
			enemies.push_back(new EnemyBird(BaseObject::mapSlider + MAP_WIDTH));
			
			break;
		case 10:
			enemies.push_back(new EnemySpinyBeetle(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 11:
			enemies.push_back(new EnemyDarkGirl(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 12:
			enemies.push_back(new EnemyDarkDragon(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 13:
			enemies.push_back(new EnemyBird(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 14:
			enemies.push_back(new EnemyBuzzyBeetle(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 15:
			enemies.push_back(new EnemyWhiteGhost(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 16:
			enemies.push_back(new EnemyMonsterGirl(BaseObject::mapSlider + MAP_WIDTH));
			
			break;
		case 17:
			enemies.push_back(new EnemyDarkRaven(BaseObject::mapSlider + MAP_WIDTH));
			break;
			
		case 18:
			enemies.push_back(new EnemyDarkGirl(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 19:
			enemies.push_back(new EnemyDarkDragon(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 20:
			enemies.push_back(new EnemyMonsterGirl(BaseObject::mapSlider + MAP_WIDTH));
			break;
		default:
			break;
		}
	}
	

	map.checkToAddItem(BaseObject::mapSlider + MAP_WIDTH, itemID, checkToAdd);
	if (checkToAdd == true)
	{
		switch (itemID)
		{
		case 1:
			items.push_back(new BlueSwordItem(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 2:
			items.push_back(new ShurikenItem(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 3:
			items.push_back(new KunaiItem(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 4:
			items.push_back(new FlameItem(BaseObject::mapSlider + MAP_WIDTH));
			break;
		case 5:
			items.push_back(new ThunderDragonItem(BaseObject::mapSlider + MAP_WIDTH));
			break;
		default:
			break;
		}
	}

	

	//main character
	ninja->MakeAnimation();


	//check collision main vs monster
	for (auto enemy : enemies)
	{
		if (CheckCollision(ninja, enemy))
		{
			ninja->SetDeath(true);
		}
	}

	//////item
	
	for (auto item : items)
	{
		if (CheckCollision(ninja,item))
		{
			ninja->SetTypeOfWeapon(item->GetTypeOfWeapn());
			item->SetDeath(true);
			items.erase(items.begin() + countID);
		}
		countID++;
	}
	countID = 0;

	//weapon
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

		if (weapon->CheckDeath() == true)
		{
			weapons.erase(weapons.begin());
			RemoveObject(weapon);
		}
	}
		
	//enemy

	for (auto enemy : enemies) {
		enemy->MakeAnimation();
		if (enemy->CheckDeath() == true)
		{
			enemies.erase(enemies.begin() + countID);
			RemoveObject(enemy);
		}
		countID++;
	}
	countID = 0;
}

void GamePlay::Draw(HWND hwnd, HDC hdc)
{
	timer++;
	map.Draw(hwnd, hdc);
 	ninja->Draw(hwnd, hdc);
	for (auto item : items) {
		item->Draw(hwnd, hdc);
	}

	for (auto weapon : weapons)
	{
		if (weapon->CheckDeath() == true)
		{
			weapons.erase(weapons.begin());
		}
		else
			weapon->Draw(hwnd, hdc);
	}


	if (timer >= 3)
	{

		for (auto enemy : enemies)
		{
				enemy->Draw(hwnd, hdc);
		}
		timer = 0;
	}
	else
	{
		for (auto enemy : enemies) 
		{
			enemy->Draw(hwnd, hdc);
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
}

void GamePlay::MoveNinjaRight()
{
	if (!ninja->CheckDeath())
	{
		ninja->MoveRight();

		if (ninja->GetPosX() - map.getMapSlider() >= 250)
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

bool GamePlay::CheckCollision(BaseObject* object1, BaseObject* object2)
{
	Point2D A1 = Point2D(object1->GetPosX(), object1->GetPosY());
	Point2D A2 = Point2D(object2->GetPosX(), object2->GetPosY());

	int width1 = object1->GetWidth();
	int height1 = object1->GetHeight();
	int width2 = object2->GetWidth();
	int height2 = object2->GetHeight();


	bool isColliding = false;
	isColliding = A1.CheckCollision(height1, width1, A2, height2, width2);

	return isColliding;
}


void GamePlay::RemoveObject(BaseObject* object)
{
	delete object;
	object = nullptr;
}

void  GamePlay::AddWeapon(int type, int dir_Moving, int stage)
{
	//type: 0 = sword, 1 is shuriken, 2 = kunai, 3 = fire, 4 = thunder
	//dir_Moving: 0 = Left, 1 = Right, 
	//stage: 0 = sitting, 1 = jumping, 2 = on the ground

	if (type == 0)
	{
		if (dir_Moving == 0)
		{
			if (stage == 0)
			{
				weapons.push_back(new BlueSword(ninja->GetPosX() - BLUE_SWORD_WIDTH + 40 , dir_Moving, ninja->GetPosY()  + 65));
			}
			else if (stage == 1)
			{
				weapons.push_back(new BlueSword(ninja->GetPosX() - BLUE_SWORD_WIDTH + 45, dir_Moving, ninja->GetPosY() + 60));
			}
			else if (stage == 2)
			{
				weapons.push_back(new BlueSword(ninja->GetPosX() - BLUE_SWORD_WIDTH + 45, dir_Moving, ninja->GetPosY() + 35));
			}
		}
		else if (dir_Moving == 1)
		{
			if (stage == 0)
			{
				weapons.push_back(new BlueSword(ninja->GetPosX()  + 80, dir_Moving, ninja->GetPosY()  + 65));
			}
			else if (stage == 1)
			{
				weapons.push_back(new BlueSword(ninja->GetPosX()  + 85, dir_Moving, ninja->GetPosY() + 60));
			}
			else if (stage == 2)
			{
				weapons.push_back(new BlueSword(ninja->GetPosX() + 85, dir_Moving, ninja->GetPosY() + 35));
			}
		}
	}
	else if (type == 1)
	{
		if (dir_Moving == 0)
		{
			if (stage == 0)
			{
				weapons.push_back(new WeaponShuriken(ninja->GetPosX() - SHURIKEN_WIDTH , dir_Moving, ninja->GetPosY() + 65));
			}
			else if (stage == 1)
			{
				weapons.push_back(new WeaponShuriken(ninja->GetPosX() - SHURIKEN_WIDTH + 5, dir_Moving, ninja->GetPosY() + 60));
			}
			else if (stage == 2)
			{
				weapons.push_back(new WeaponShuriken(ninja->GetPosX() - SHURIKEN_WIDTH + 5, dir_Moving, ninja->GetPosY() + 35));
			}
		}
		else if (dir_Moving == 1)
		{
			if (stage == 0)
			{
				weapons.push_back(new WeaponShuriken(ninja->GetPosX() + 120, dir_Moving, ninja->GetPosY() + 65));
			}
			else if (stage == 1)
			{
				weapons.push_back(new WeaponShuriken(ninja->GetPosX() + 125, dir_Moving, ninja->GetPosY() + 60));
			}
			else if (stage == 2)
			{
				weapons.push_back(new WeaponShuriken(ninja->GetPosX() + 125, dir_Moving, ninja->GetPosY() + 35));
			}
		}
	}
	else if (type == 2)
	{
		if (dir_Moving == 0)
		{
			if (stage == 0)
			{
				weapons.push_back(new WeaponKunai(ninja->GetPosX() - KUNAI_WIDTH + 10, dir_Moving, ninja->GetPosY() + 75));
			}
			else if (stage == 1)
			{
				weapons.push_back(new WeaponKunai(ninja->GetPosX() - KUNAI_WIDTH + 15, dir_Moving, ninja->GetPosY() + 70));
			}
			else if (stage == 2)
			{
				weapons.push_back(new WeaponKunai(ninja->GetPosX() - KUNAI_WIDTH + 15, dir_Moving, ninja->GetPosY() + 40));
			}
		}
		else if (dir_Moving == 1)
		{
			if (stage == 0)
			{
				weapons.push_back(new WeaponKunai(ninja->GetPosX() + 110, dir_Moving, ninja->GetPosY() + 75));
			}
			else if (stage == 1)
			{
				weapons.push_back(new WeaponKunai(ninja->GetPosX() + 115, dir_Moving, ninja->GetPosY() + 70));
			}
			else if (stage == 2)
			{
				weapons.push_back(new WeaponKunai(ninja->GetPosX() + 115, dir_Moving, ninja->GetPosY() + 40));
			}
		}
	}
	else if (type == 3)
	{
		if (dir_Moving == 0)
		{
			if (stage == 0)
			{
				weapons.push_back(new WeaponFire(ninja->GetPosX() - FIRE_WIDTH + 10, dir_Moving, ninja->GetPosY() + 70));
			}
			else if (stage == 1)
			{
				weapons.push_back(new WeaponFire(ninja->GetPosX() - FIRE_WIDTH + 15, dir_Moving, ninja->GetPosY() + 65));
			}
			else if (stage == 2)
			{
				weapons.push_back(new WeaponFire(ninja->GetPosX() - FIRE_WIDTH + 15, dir_Moving, ninja->GetPosY() + 35));
			}
		}
		else if (dir_Moving == 1)
		{
			if (stage == 0)
			{
				weapons.push_back(new WeaponFire(ninja->GetPosX() + 110, dir_Moving, ninja->GetPosY() + 70));
			}
			else if (stage == 1)
			{
				weapons.push_back(new WeaponFire(ninja->GetPosX() + 115, dir_Moving, ninja->GetPosY() + 65));
			}
			else if (stage == 2)
			{
				weapons.push_back(new WeaponFire(ninja->GetPosX() + 115, dir_Moving, ninja->GetPosY() + 35));
			}
		}
	}
	else if (type == 4)
		{
		if (dir_Moving == 0)
		{
			if (stage == 0)
			{
				weapons.push_back(new WeaponThunder(ninja->GetPosX() - THUNDER_WIDTH + 10, dir_Moving, ninja->GetPosY() + 70));
			}
			else if (stage == 1)
			{
				weapons.push_back(new WeaponThunder(ninja->GetPosX() - THUNDER_WIDTH + 15, dir_Moving, ninja->GetPosY() + 65));
			}
			else if (stage == 2)
			{
				weapons.push_back(new WeaponThunder(ninja->GetPosX() - THUNDER_WIDTH + 15, dir_Moving, ninja->GetPosY() + 35));
			}
		}
		else if (dir_Moving == 1)
		{
			if (stage == 0)
			{
				weapons.push_back(new WeaponThunder(ninja->GetPosX() + 110, dir_Moving, ninja->GetPosY() + 70));
			}
			else if (stage == 1)
			{
				weapons.push_back(new WeaponThunder(ninja->GetPosX() + 115, dir_Moving, ninja->GetPosY() + 65));
			}
			else if (stage == 2)
			{
				weapons.push_back(new WeaponThunder(ninja->GetPosX() + 115, dir_Moving, ninja->GetPosY() + 35));
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
