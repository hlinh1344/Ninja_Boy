#include "GamePlay.h"


GamePlay::GamePlay()
{
	enemyID = 0;
}

GamePlay::~GamePlay()
{
	for (auto enemy : enemies) {
		delete(enemy);
		enemy = nullptr;
	}

	for (auto weapon : weapons) {
		delete(weapon);
		weapon = nullptr;
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

	for (auto enemy : enemies) {
		Collision(ninja, enemy);
	}

	for (auto enemy : enemies) {
		for (auto weapon : weapons) {
			/// <summary>
			// toto
			/// </summary>
			Collision(ninja, enemy);
		}
		
	}





	// check to add monster
	// based map settings
	// Draw
	// check to move ninja
	// moveMonster()
	// handle collision

}

void GamePlay::Draw(HWND hwnd, HDC hdc)
{
	timer++;
	map.Draw(hwnd, hdc);
	ninja.Draw(hwnd, hdc);
	//for () 
	if (timer >= 2)
	{
		if (ninja.CheckDeath())
		{
			ninja.IncreseJumpingHeight(10);
		}
		else if (ninja.GetJumpingHeight() > 0 && (ninja.CheckFalling()))
		{
			ninja.IncreseJumpingHeight(-5);
		}
		else if (ninja.CheckJumping() && (ninja.GetJumpingHeight() < 250) && (!ninja.CheckFalling()))
		{
			ninja.MoveUp();
		}

		for (auto enemy : enemies) {
			if (enemy->GetDeath() == true)
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
			if (weapon->GetDeath() == true)
			{
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
		if (ninja.CheckDeath())
		{
			ninja.IncreseJumpingHeight(10);
		}
		else if (ninja.GetJumpingHeight() > 0 && (ninja.CheckFalling()))
		{
			ninja.IncreseJumpingHeight(-5);
		}
		else if (ninja.CheckJumping() && (ninja.GetJumpingHeight() < 250) && (!ninja.CheckFalling()))
		{
			ninja.MoveUp();
		}

		
		for (auto enemy : enemies) {
			if (enemy->GetDeath() == true)
			{
				enemies.erase(enemies.begin());
			}
			else
			{
				enemy->Draw(hwnd, hdc);

			}
		}

		for (auto weapon : weapons) {
			if (weapon->GetDeath() == true)
			{
				//enemy->SetDeath(false);
				weapons.erase(weapons.begin());
			}
			else
			{
				weapon->Draw(hwnd, hdc);
			}
			
		}

	}



	// for monster in enemy

	// monster.Draw()
}
void GamePlay::Attack()
{
	if (!ninja.CheckDeath())
	{
		if (ninja.IsGoLeft() == true)
		{
			ninja.SetFormX(0);

			if (ninja.CheckSitting() == true)
			{
				weapons.push_back(new WeaponShuriken(ninja.GetPosX() - SHURIKEN_WIDTH - 10, 0
					, ninja.GetPosY() - ninja.GetJumpingHeight() + 75));
			}
			else if (ninja.CheckJumping() == true)
			{
				weapons.push_back(new WeaponShuriken(ninja.GetPosX() - SHURIKEN_WIDTH - 10, 0
					, ninja.GetPosY() - ninja.GetJumpingHeight() + 60));
			}
			else if (ninja.CheckJumping() == false)
			{
				weapons.push_back(new WeaponShuriken(ninja.GetPosX() - SHURIKEN_WIDTH - 10, 0
					, ninja.GetPosY() - ninja.GetJumpingHeight() + 40));
			}
			
			
		}
		else if (ninja.IsGoRight() == true)
		{
			ninja.SetFormX(19);

			if (ninja.CheckSitting() == true)
			{
				weapons.push_back(new WeaponShuriken(ninja.GetPosX() + SHURIKEN_WIDTH + 40, 1
					, ninja.GetPosY() - ninja.GetJumpingHeight() + 75));
			}
			else if (ninja.CheckJumping() == true)
			{
				weapons.push_back(new WeaponShuriken(ninja.GetPosX() + SHURIKEN_WIDTH + 40, 1
					, ninja.GetPosY() - ninja.GetJumpingHeight() + 60));
			}
			else if (ninja.CheckJumping() == false)
			{
				weapons.push_back(new WeaponShuriken(ninja.GetPosX() + SHURIKEN_WIDTH + 40, 1
					, ninja.GetPosY() - ninja.GetJumpingHeight() + 40));
			}

		}
		

	}
	// for weap in enemy
	// weapon.move()
}

void GamePlay::KeyUpSpace()
{
	if (!ninja.CheckDeath())
	{
		if (ninja.IsGoRight() == true)
		{
			ninja.SetFormX(10);
		}
		else if (ninja.IsGoLeft() == true)
		{
			ninja.SetFormX(9);
		}
	}

}

void GamePlay::MoveNinjaLeft()
{
	if (!ninja.CheckDeath())
	{
		ninja.MoveLeft();
		if (ninja.GetPosX() + 20 - map.getMapSlider() <= 0)
		{
			ninja.IncresePosX(PLAYER_SPEED);
		}

		//change sprite
		if (ninja.CheckJumping() == true)
		{
			if (ninja.IsGoRight())
			{
				ninja.SetFormX(9);
			}
			else
			{
				if (ninja.GetFormX() <= 6)
					ninja.SetFormX(9);
				else
					ninja.IncreseFormX(-1);
			}
		}
		else
		{
			if (ninja.IsGoRight())
				ninja.SetFormX(9);
			else
			{
				if (ninja.GetFormX() <= 1)
					ninja.SetFormX(8);
				else
					ninja.IncreseFormX(-1);
			}
		}
	}


	//for (auto enemy : enemies) {
	//	enemy->MakeAnimation();
	//}
}

void GamePlay::MoveNinjaRight()
{
	if (!ninja.CheckDeath())
	{
		ninja.MoveRight();

		if (ninja.GetPosX() - map.getMapSlider() >= 500)
		{
			map.increseMapSlider(PLAYER_SPEED);
		}

		if (ninja.GetPosX() >= END_OF_MAP)
		{
			map.increseMapSlider(-PLAYER_SPEED);
			ninja.MoveLeft();
		}

		//change sprite
		if (ninja.CheckJumping() == true)
		{
			if (ninja.IsGoLeft())
			{
				ninja.SetFormX(10);
			}
			else
			{
				if (ninja.GetFormX() >= 13)
					ninja.SetFormX(10);
				else
					ninja.IncreseFormX(1);
			}
		}
		else
		{
			if (ninja.IsGoLeft())
				ninja.SetFormX(10);
			else
			{
				if (ninja.GetFormX() >= 18)
					ninja.SetFormX(11);
				else
					ninja.IncreseFormX(1);
			}
		}
	}


	//for (auto enemy : enemies) {
	//	enemy->MakeAnimation();
	//}
}

void GamePlay::MoveNinjaUp()
{
	if (!ninja.CheckDeath())
	{
		ninja.MoveUp();
		if (ninja.IsGoRight())
		{
			ninja.SetFormX(13);
			ninja.SetFormY(1);
		}
		else if (ninja.IsGoLeft())
		{
			ninja.SetFormX(6);
			ninja.SetFormY(1);
		}
	}

}

void GamePlay::MoveNinjaDown()
{
	if (!ninja.CheckDeath())
	{
		ninja.MoveDown();
		if (ninja.CheckJumping() == true)
		{
			if (ninja.IsGoRight())
			{
				ninja.SetFormX(13);
				ninja.SetFormY(1);
			}
			else if (ninja.IsGoLeft())
			{
				ninja.SetFormX(6);
				ninja.SetFormY(1);
			}
		}
		else
		{
			ninja.SetSit(true);
			if (ninja.IsGoRight())
			{
				ninja.SetFormX(10);
				ninja.SetFormY(2);
			}
			else if (ninja.IsGoLeft())
			{
				ninja.SetFormX(9);
				ninja.SetFormY(2);
			}
		}
		
	}
}

void GamePlay::KeyUpDown()
{
	if (!ninja.CheckDeath())
	{
		ninja.SetSit(false);
		if (ninja.CheckJumping() == true)
		{
			if (ninja.IsGoRight())
			{
				ninja.SetFormX(12);
				ninja.SetFormY(1);
			}
			else if (ninja.IsGoLeft())
			{
				ninja.SetFormX(7);
				ninja.SetFormY(1);
			}
		}
		else
		{
			if (ninja.IsGoRight())
			{
				ninja.SetFormX(10);
				ninja.SetFormY(0);
			}
			else if (ninja.IsGoLeft())
			{
				ninja.SetFormX(9);
				ninja.SetFormY(0);
			}
		}
	}
}

void GamePlay::KeyUpUp()
{
	if (!ninja.CheckDeath())
	{
		if (ninja.CheckJumping() == true)
		{
			if (ninja.IsGoRight())
			{
				ninja.SetFormX(10);
				ninja.SetFormY(1);
			}
			else if (ninja.IsGoLeft())
			{
				ninja.SetFormX(9);
				ninja.SetFormY(1);
			}
		}
		else
		{
			if (ninja.IsGoRight())
			{
				ninja.SetFormX(10);
				ninja.SetFormY(0);
			}
			else if (ninja.IsGoLeft())
			{
				ninja.SetFormX(9);
				ninja.SetFormY(0);
			}
		}
	}
}

void GamePlay::KeyUpRight()
{
	if (!ninja.CheckDeath())
	{
		ninja.SetFormX(10);
	}

}

void GamePlay::KeyUpLeft()
{
	if (!ninja.CheckDeath())
	{
		ninja.SetFormX(9);
	}

}

void GamePlay::Collision(Character& ninja, BaseObject* monster)
{
	int ninjaLeftEdge = ninja.GetPosX();
	int ninjaRightEdge = ninja.GetPosX() + (CHARACTER_WIDTH -20);
	int ninjaTopEdge = ninja.GetPosY();
	int ninjaBottomEdge = ninja.GetPosY() + (CHARACTER_HEIGHT - 10 );
	int monsterLeftEdge = monster->GetPosX();
	int monsterRightEdge = monster->GetPosX() + 45 ;
	int monsterTopEdge = monster->GetPosY();
	int monsterBottomEdge = monster->GetPosY() + 90 ;

	if ((ninjaRightEdge >= monsterLeftEdge)
		&& (ninjaRightEdge <= monsterRightEdge)
		&& (ninjaBottomEdge <= monsterBottomEdge)
		&& (ninjaBottomEdge >= monsterTopEdge)
		&& (!ninja.CheckJumping()))
	{
		ninja.SetDeath(true);
	}
	else 	if ((ninjaRightEdge >= monsterLeftEdge)
		&& (ninjaRightEdge <= monsterRightEdge)
		&& (ninjaBottomEdge <= monsterBottomEdge)
		&& (ninjaBottomEdge >= monsterTopEdge)
		&& (ninja.CheckJumping()))
	{
		//monster->SetDeath(true);
	}

}