/*




*/
#include "Actions.h"
#include "GameData.h"
#include "PlayerManager.h"




// ------------- Called from the input thread ---------------- ///
void PlayerManager::handleMove(const Direction _action)
{
	if (game_data)
	{
		if (player_spawner->getSpriteAt(0)->getPosX() < 10)
		{
			player_spawner->getSpriteAt(0)->setPos(
				player_spawner->getSpriteAt(0)->getPosX() + 10, 
				player_spawner->getSpriteAt(0)->getPosY());
		}
		if(player_spawner->getSpriteAt(0)->getPosX() > (WINDOW_WIDTH - 75))
		{
			player_spawner->getSpriteAt(0)->setPos(
				player_spawner->getSpriteAt(0)->getPosX() - 5,
				player_spawner->getSpriteAt(0)->getPosY());
		}

		current_command = input_handler->getMoveCommand(_action);
		executeAndReset();
	}
}



void PlayerManager::handleShoot(const ShootCommands _action)
{
	if (game_data)
	{
		current_command = input_handler->getShootCommand(_action);
		executeAndReset();
	}
}



void PlayerManager::executeAndReset()
{
	if (current_command)
	{
		game_data->x_speed = player_x_speed; /// SET THIS SOMEWHERE SAFER

		current_command->execute(player_spawner->getSpriteAt(0), game_data);
		current_command.reset(nullptr);
	}
}
// ------------------------------------------------------------ // 


PlayerManager::PlayerManager(std::shared_ptr<ASGE::Renderer> _r) :
	player_spawner(std::make_unique<Spawner>(_r)),
	player_health(std::make_unique<Spawner>(_r)),
	input_handler(std::make_unique<CommandManager>()),
	renderer(_r), total_lives(PLAYER_LIVES)
{

}



GameObject* PlayerManager::getPlayer() const
{
	return player_spawner->getSpriteAt(0);
}



const bool PlayerManager::getPlayerState() const
{
	return player_spawner->getSpriteAt(0)->getIsAlive();
}



const int PlayerManager::getTotalLives() const
{
	return total_lives;
}



const int PlayerManager::getScore() const
{
	return current_score;
}



void PlayerManager::setPlayerState(const bool _state)
{
	player_spawner->getSpriteAt(0)->setIsAlive(_state);
}



void PlayerManager::setTotalLives(const int _lives)
{
	total_lives = _lives;
	player_health->getSpriteAt(_lives)->setIsAlive(false);
}



void PlayerManager::setScore(ObjectType _type)
{
	switch(_type)
	{
		case ObjectType::ENEMY:
			current_score += 50;
		break;
	}
}



void PlayerManager::update(GameData* _gd)
{
	if (_gd)
	{
		game_data = _gd;
	}

	player_spawner->draw(0);
	player_spawner->getSpriteAt(0)->update(nullptr, _gd);
	
	if(!has_init_lives)
	{
		has_init_lives = initLivesGUI();
	}
	drawLives();
}



bool PlayerManager::createPlayer()
{
	for (int i = 0; i < TOTAL_PLAYERS; i++)
	{
		player_spawner->setSpriteType(ObjectType::PLAYER);
		player_spawner->setSpritePos(200, WINDOW_WIDTH / 2, i);
		player_spawner->setSpriteSize(PLAYER_WIDTH, PLAYER_HEIGHT, i);
		player_spawner->getSpriteAt(i)->setID(i);
	}
	return true;
}



void PlayerManager::resetPlayer()
{
	player_spawner->removeAllObjects();
	player_health->removeAllObjects();

	has_init_lives = false;
	total_lives    = PLAYER_LIVES;
	current_score  = 0;
}



bool PlayerManager::initLivesGUI()
{
	int pos_x = 0;
	int pos_y = 0;

	for (int i = 0; i < TOTAL_ENEMIES; i++)
	{
		if (i == 0)
		{
			pos_x = 20;
			pos_y += 20;
		}
		else
		{
			pos_x += 75;
		}
		player_health->setSpriteType(ObjectType::PLAYER);
		player_health->setSpritePos(pos_x, pos_y, i);
		player_health->setSpriteSize(PLAYER_WIDTH, PLAYER_HEIGHT, i);
	}
	return true;
}



void PlayerManager::drawLives()
{
	for (int i = 0; i < PLAYER_LIVES; i++)
	{ 
		player_health->draw(i);
	}
}
