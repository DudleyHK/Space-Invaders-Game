/*





*/
#include <time.h>

#include "Constants.h"
#include "EnemyManager.h"
#include "GameData.h"
#include "ObjectType.h"



EnemyManager::EnemyManager(std::shared_ptr<ASGE::Renderer> _r) :
	enemy_spawner(std::make_unique<Spawner>(_r)),
	renderer(_r), diff(DIFFICULTY), 
	enemy_x_speed(ENEMY_X_SPEED), enemy_y_speed(ENEMY_Y_SPEED), 
	wait_time(ENEMY_WAIT_TIME)
{
	srand(static_cast<unsigned int>(time(0)));
	command_list.reserve(5);
}



GameObject* EnemyManager::getSpriteAt(const int _idx)
{
	return enemy_spawner->getSpriteAt(_idx);
}



void EnemyManager::createEnemies()
{
	int pos_x = 0;
	int pos_y = 0;
	int row_counter = 0;

	for (int i = 0; i < TOTAL_ENEMIES; i++)
	{
		if (i % (TOTAL_ENEMIES / 5) == 0)
		{
			pos_x = ENEMY_POS_X;
			pos_y += ENEMY_POS_Y;
			row_counter++;
		}
		else
		{
			pos_x += 75;
		}
		enemy_spawner->setSpriteType(getEnemyType(row_counter));
		enemy_spawner->setSpritePos(pos_x, pos_y, i);
		enemy_spawner->setSpriteSize(ENEMY_WIDTH, ENEMY_HEIGHT, i);
		enemy_spawner->getSpriteAt(i)->setID(i);
	}
}



void EnemyManager::update(GameData* _gd)
{
	if (_gd)
	{
		game_data = _gd;
	}

	// Enemy Movement commands
	if (isTimeUp())
	{
		updateDirection();
	}

	speedUp();

	// update each enemy
	for (int i = 0; i < TOTAL_ENEMIES; i++)
	{
		enemy_spawner->getSpriteAt(i)->update(nullptr, _gd);

		if (enemy_spawner->getSpriteAt(i)->getIsAlive())
		{
			enemy_spawner->draw(i);

			int rand_val = (rand() % diff + 1);
			if (rand_val == diff)
			{
				handleShoot(i, ShootCommands::SHOOTING);
			}
		}
		else
		{
			continue;
		}
	}
}



void EnemyManager::clearObjects() 
{
	enemy_spawner->removeAllObjects();

	diff = DIFFICULTY;
	wait_time = ENEMY_WAIT_TIME;
	half_diff = false;
	quater_diff = false;
}



/**
*   Check if any enemy has hit the edge of the window, if so check enemy pos. 
*   If none of the enemies have hit the edge, just pushback their current
*		direction of travel. 
*/
void EnemyManager::updateDirection()
{                                                                              
	int counter = 0;
	bool dir_set = false;


	for (int i = 0; i < TOTAL_ENEMIES; i++)
	{
		dir_set = checkEnemiesPos(i);
		if (dir_set)
		{
			break;
		}
	}
	if (!dir_set)
	{
		command_list.push_back(Enemy::getCurrentDirection());
	}
	setCommand();
}



void EnemyManager::handleShoot(const int _idx, ShootCommands _command)
{
	current_command =
		command_manager->getShootCommand(_command);

	if (current_command)
	{
		current_command->execute(
			enemy_spawner->getSpriteAt(_idx), game_data);
		current_command.reset(nullptr);
	}
}


/**
*   If the enemy has hit the edge of the window and depending on their current
*    direction of travel, push back a certain set of move commands. Followed
*    by setting their new current direction of travel.
*/
bool EnemyManager::checkEnemiesPos(const int _idx)
{
	if (enemy_spawner->getSpriteAt(_idx)->getIsAlive())
	{
		if (enemy_spawner->getSpriteAt(_idx)->getPosX() <= BOUNDARY_L ||
			enemy_spawner->getSpriteAt(_idx)->getPosX() >= BOUNDARY_R)
		{
			switch (Enemy::getCurrentDirection())
			{
				case Direction::LEFT:
					command_list.push_back(Direction::RIGHT);
					command_list.push_back(Direction::DOWN);
					Enemy::setCurrentDirection(Direction::RIGHT);
					break;

				case Direction::RIGHT:
					command_list.push_back(Direction::LEFT);
					command_list.push_back(Direction::DOWN);
					Enemy::setCurrentDirection(Direction::LEFT);
					break;
			}
			return true;
		}
		return false;
	}
	return false;
}



const ObjectType EnemyManager::getEnemyType(const int _row) const
{
	if (_row <= 1)
	{
		return ObjectType::ENEMY_T;
	}
	else if (_row <= 3)
	{
		return ObjectType::ENEMY_M;
	}
	else if (_row <= 5)
	{
		return ObjectType::ENEMY_B;
	}
	return ObjectType::NONE;
}



void EnemyManager::speedUp()
{
	if (!half_diff)
	{
		if (enemy_spawner->getListSize() == (TOTAL_ENEMIES / 2))
		{
  			wait_time *= 0.8f;
			diff *= 0.25f;
			half_diff = true;
		}
	}

	if (!quater_diff)
	{
		if (enemy_spawner->getListSize() == (TOTAL_ENEMIES / 4))
		{
			wait_time *= 0.25f;
			diff *= 0.01f;
		    quater_diff = true;
		}
	}
}



const int EnemyManager::getListSize() const
{
	return enemy_spawner->getListSize();
}



//void EnemyManager::resetParameters()
//{
//	diff          = DIFFICULTY;
//	enemy_x_speed = ENEMY_X_SPEED;
//	enemy_y_speed = ENEMY_Y_SPEED;
//	half_diff     = false;
//	quater_diff   = false;
//}



/**
*   Run through each element of the command list, get the appropriate command, 
*   Call a function that will execute the command for each enemy. 
*
*
*/
void EnemyManager::setCommand()
{
	while (command_list.size() > 0)
	{
		switch (command_list.back())
		{
			case Direction::DOWN:
				current_command =
					command_manager->getMoveCommand(Direction::DOWN);
				break;
			case Direction::LEFT:
				current_command =
					command_manager->getMoveCommand(Direction::LEFT);
				changeSpriteFrame();
				break;
			case Direction::RIGHT:
				current_command =
					command_manager->getMoveCommand(Direction::RIGHT);
				changeSpriteFrame();
				break;
			case Direction::NONE:
				current_command =
					command_manager->getMoveCommand(Direction::NONE);
				return;
		}
		exeCommand();
	}
}


/**
*  Set the new x and y speeds. 
*  Run through each enemy, check if it should be rendered and then execute the 
	relative command for them. 
*  Once complete remove the element from the list. 
*/
void EnemyManager::exeCommand()
{
	game_data->x_speed = enemy_x_speed;
	game_data->y_speed = enemy_y_speed;

	for (int i = 0; i < TOTAL_ENEMIES; i++)
	{
		if (enemy_spawner->getSpriteAt(i)->getIsAlive())
		{
			current_command->execute(
				enemy_spawner->getSpriteAt(i), game_data);
		}
	}
	command_list.pop_back();
}


/**
*  Simple function to swap the sprites frame, depending on what is already 
*   being drawn.
*/
void EnemyManager::changeSpriteFrame()
{
	for(int i = 0; i < TOTAL_ENEMIES; i++)
	{
		if (enemy_spawner->getSpriteAt(i)->getIsAlive())
		{
			if (enemy_spawner->getSpriteAt(i)->getCurrentFrame() == 1)
			{
				enemy_spawner->getSpriteAt(i)->setCurrentFrame(2);
			}
			else
			{
				enemy_spawner->getSpriteAt(i)->setCurrentFrame(1);
			}
		}
	}
}



bool EnemyManager::isTimeUp()
{
	if (timer >= wait_time)
	{
		timer = 0;
		return true;
	}
	timer += game_data->dt;
	return false;
}
