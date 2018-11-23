/*




*/
#include <Engine/Input.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>

#include "Actions.h"
#include "Collisions.h"
#include "Constants.h"
#include "EnemyManager.h"
#include "Game.h"
#include "GameData.h"
#include "GameFont.h"
#include "PlayerManager.h"
#include "Spawner.h"



// HIT ENEMY JUST AS HITS THE EDGE


/**
*   @brief   Default Constructor.
*/
InvadersGame::InvadersGame() :
	game_won(true)
{

}


/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
InvadersGame::~InvadersGame()
{
	this->inputs->unregisterCallback(callback_id);

	if(game_data)
	{
		delete game_data;
		game_data = nullptr;
	}
}



/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The input callback should also
			 be set in the initialise function. 
*   @return  True if the game initialised correctly.
*/
bool InvadersGame::init()
{
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	if (!initAPI())
	{
		return false;
	}
	renderer->setWindowTitle("BEST GAME IN THE WORLD");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	toggleFPS();


	// init game objects
	block_spawner   = std::make_unique<Spawner>(renderer);
	enemy_manager   = std::make_unique<EnemyManager>(renderer);
	player_manager  = std::make_unique<PlayerManager>(renderer);
	timer           = std::make_unique<Timer>();
	col             = std::make_unique<Collisions>();

	game_data = new GameData();
	

	// load fonts we need
	GameFont::fonts[0] = new GameFont(
		renderer->loadFont("..\\..\\Resources\\Fonts\\Comic.ttf", 42), "default", 42);

	if (GameFont::fonts[0]->id == -1)
	{
		return false;
	};

	callback_id = 
		this->inputs->addCallbackFnc(&InvadersGame::input, this);

	return true;
}

/**
*   @brief   The main game loop. 
*   @details The main loop should be responsible for updating the game
			 and rendering the current scene. Runs until the shouldExit
			 signal is received.
*   @return  True if the game ran correctly. 
*/
bool InvadersGame::run()
{
	while (!shouldExit())
	{
		timer->startTimer();
		
		processGameActions();
		render();

		timer->stopTimer();
		game_data->dt = timer->getTime();
	}
	return true;
}


/**
*   @brief   Should the game exit?
*   @details Has the renderer terminated or the game requesting to exit?
*   @return  True if the game should exit
*/
bool InvadersGame::shouldExit() const
{
	return (renderer->exit() || this->exit);
}


/**
*   @brief   Renders the scene
*   @details Prepares the renderer subsystem before drawing the 
			 current frame. Once the current frame is has finished
			 the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void InvadersGame::render()
{
	beginFrame();
	drawFrame(); // replace this with gamestate pointer. 
	endFrame();
}


/*
*   For all the bullets check to see if:
*		a) Any of them have hit any enemies 
*		b) Check to see if any have hit the player,.
*/
//void InvadersGame::collisionDetection()
//{
//	for (int i = 0; i < game_data->bullets.size(); i++)
//	{
//		// a)
//		for (int j = 0; j < TOTAL_ENEMIES; j++)
//		{
//			if (enemy_manager->getSpriteAt(j)->getIsAlive())
//			{
//				if (col->checkCollision(
//					game_data->bullets[i], enemy_manager->getSpriteAt(j)))
//				{
//					enemy_manager->getSpriteAt(j)->setIsAlive(false);
//					player_manager->getPlayer()->setBulletState(false);
//					player_manager->setScore(ObjectType::ENEMY);
//					game_data->bullets[i]->setIsAlive(false);
//					return;
//				}
//			}
//		}
//
//		// b)
//		if (player_manager->getPlayer()->getIsAlive())
//		{
//			if (col->checkCollision(
//				game_data->bullets[i], player_manager->getPlayer()))
//			{
//				// check the players health situation
//				if(player_manager->getTotalLives() <= 1)
//				{
//					current_state = &InvadersGame::gameOverUpdate;
//				}
//				else
//				{
//					player_manager->setTotalLives(
//						player_manager->getTotalLives() - 1);
//					reset(false);
//				}
//				return;
//			}
//		}
//
//		// c)
//		for(int j = 0; j < TOTAL_ENEMIES; j++)
//		{
//			for (int k = 0; k < TOTAL_BLOCKS; k++)
//			{
//				if (block_spawner->getSpriteAt(k)->getIsAlive())
//				{
//					// if the bullet hits the block
//					if (col->checkCollision(
//						game_data->bullets[i], block_spawner->getSpriteAt(k)))
//					{
//						game_data->bullets[i]->setIsAlive(false);
//						block_spawner->getSpriteAt(k)->setIsAlive(false);
//
//						switch (game_data->bullets[i]->getParent())
//						{
//							case ObjectType::ENEMY:
//								enemy_manager->getSpriteAt(j)->setBulletState(false);
//								break;
//							case ObjectType::PLAYER:
//								player_manager->getPlayer()->setBulletState(false);
//								break;
//						}
//						//could lower block health here. 
//						return;
//					}
//					if (enemy_manager->getSpriteAt(j)->getIsAlive())
//					{
//						if (col->checkCollision(
//							enemy_manager->getSpriteAt(j), block_spawner->getSpriteAt(k)))
//						{
//							if (player_manager->getTotalLives() <= 1)
//							{
//								current_state = &InvadersGame::gameOverUpdate; /////////////////////REPEATED CODE
//							}
//							else
//							{
//								player_manager->setTotalLives(
//									player_manager->getTotalLives() - 1);
//								reset(false);
//							}
//							return;
//						}
//					}
//				}
//			}
//		}
//	}
//}
void InvadersGame::collisionDetection()
{
	for (unsigned int i = 0; i < game_data->bullets.size(); i++)
	{
		if (!hitEnemy(i))
		{
			if (!hitPlayer(i))
			{
				if (!hitBlock(i))
				{
					continue;
				}
			}
		}
		return;
	}
}


const bool InvadersGame::hitEnemy(const int _i)
{
	for (int j = 0; j < TOTAL_ENEMIES; j++)
	{
		if (enemy_manager->getSpriteAt(j)->getIsAlive())
		{
			if (col->checkCollision(
				game_data->bullets[_i], enemy_manager->getSpriteAt(j)))
			{
				enemy_manager->getSpriteAt(j)->setIsAlive(false);
				player_manager->getPlayer()->setBulletState(false);
				player_manager->setScore(ObjectType::ENEMY);
				game_data->bullets[_i]->setIsAlive(false);
				return true;
			}
		}
	}
	return false;
}



const bool InvadersGame::hitPlayer(const int _i)
{
	if (player_manager->getPlayer()->getIsAlive())
	{
		if (col->checkCollision(
			game_data->bullets[_i], player_manager->getPlayer()))
		{
			return checkPlayerHealth();
		}
	}
	return false;
}
											
											
											
const bool InvadersGame::hitBlock(const int _i)
{
	for (int j = 0; j < TOTAL_ENEMIES; j++)
	{
		for (int k = 0; k < TOTAL_BLOCKS; k++)
		{
			if (block_spawner->getSpriteAt(k)->getIsAlive())
			{
				if (col->checkCollision(
					game_data->bullets[_i], block_spawner->getSpriteAt(k)))
				{
					game_data->bullets[_i]->setIsAlive(false);
					block_spawner->getSpriteAt(k)->setIsAlive(false);

					switch (game_data->bullets[_i]->getParent())
					{
						case ObjectType::ENEMY:
							enemy_manager->getSpriteAt(j)->setBulletState(false);
							break;
						case ObjectType::PLAYER:
							player_manager->getPlayer()->setBulletState(false);
							break;
					}
					return true;
				}
				if (enemy_manager->getSpriteAt(j)->getIsAlive())
				{
					if (col->checkCollision(
						enemy_manager->getSpriteAt(j), block_spawner->getSpriteAt(k)))
					{
						return checkPlayerHealth();
					}
				}
			}
		}
	}
	return false;
}


const bool InvadersGame::checkPlayerHealth()
{
	if (player_manager->getTotalLives() <= 1)
	{
		current_state = &InvadersGame::gameOverUpdate;
	}
	else
	{
		player_manager->setTotalLives(
			player_manager->getTotalLives() - 1);
		reset(false);
	}
	return true;
}



void InvadersGame::drawPlayerScore()
{
	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText("Score: ", 1000, 40, 1.0,
						 ASGE::COLOURS::DARKORANGE);

	renderer->renderText(std::to_string(player_manager->getScore()).c_str(),
						 1150, 40, 1.0, ASGE::COLOURS::DARKORANGE);
}



void InvadersGame::createBlocks()
{
	int pos_x = 0;
	int pos_y = 0;

	for (int i = 0; i < TOTAL_BLOCKS; i++)
	{
		if (i == 0)
		{
			pos_x = 200;
			pos_y += 500;
		}
		else
		{
			pos_x += 250;
		}
		block_spawner->setSpriteType(ObjectType::BLOCK);
		block_spawner->setSpritePos(pos_x, pos_y, i);
		block_spawner->setSpriteSize(BLOCK_WIDTH, BLOCK_HEIGHT, i);
	}
}



void InvadersGame::drawBlocks()
{
	for(int i = 0; i < TOTAL_BLOCKS; i++)
	{
		block_spawner->draw(i);
	}
}


/**
*   @brief   Renderers the contents for this frame 
*   @details All game objects that need rendering should be done
			 in this function, as it ensures they are completed
			 before the buffers are swapped.
*   @return  void
*/
void InvadersGame::drawFrame()
{
	(this->*current_state)();
}



const bool InvadersGame::initGameObjects(const bool _full_reset) // this depends on if the game has been won or not
{
	if (_full_reset)
	{
		enemy_manager->createEnemies();
		player_manager->createPlayer();
		game_data->bullets.reserve(250);
		createBlocks();
	}
	else
	{
		enemy_manager->createEnemies();
		game_data->bullets.reserve(250);
		createBlocks();
	}
	return true;
}



void InvadersGame::reset(const bool _full_reset)
{
	game_won = _full_reset;

	if (_full_reset)
	{
		enemy_manager->clearObjects();
		player_manager->resetPlayer();
		block_spawner->removeAllObjects();
		game_data->bullets.clear();
	}
	else
	{
		enemy_manager->clearObjects();
		game_data->bullets.clear();
	}
	init_game_objs = false;
}



void InvadersGame::menuUpdate()
{
	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText("Press 'Enter' key to PLAY", 375, 325, 1.0, 
	 ASGE::COLOURS::DARKORANGE);

	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText("Press 'Esc' key to EXIT", 400, 400, 1.0,
						 ASGE::COLOURS::DARKORANGE);
}



void InvadersGame::playUpdate()
{
	if(!init_game_objs)
	{
		first_iter = true;
		init_game_objs = initGameObjects(game_won);
	}
	
	player_manager->update(game_data);
	enemy_manager->update(game_data);



	if (first_iter)
	{
		first_iter = false;
		return;
	}
	if(enemy_manager->getListSize() <= 0)
	{
 		reset(false);
  		return;
	}

	drawPlayerScore();
	drawBlocks();
	collisionDetection();

	// Check if enemy has hit bottom of the screen
	for (int i = 0; i < TOTAL_ENEMIES; i++)
	{
		if (enemy_manager->getSpriteAt(i) &&
			enemy_manager->getSpriteAt(i)->getPosY() >(WINDOW_HEIGHT - 150))
		{
			current_state = &InvadersGame::gameOverUpdate;
			return;
		}
	}
}



void InvadersGame::pauseUpdate()
{
	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText("PRESS 'BACKSPACE' KEY TO PLAY", 375, 325, 1.0,
						 ASGE::COLOURS::DARKORANGE);

	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText("PRESS 'ESC' KEY FOR MAINMENU", 400, 400, 1.0,
						 ASGE::COLOURS::DARKORANGE);
}



void InvadersGame::gameOverUpdate()
{
	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText("GAMEOVER", 550, 350, 1.0,
						 ASGE::COLOURS::DARKORANGE);

	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText("PRESS 'ESC' TO RETURN", 450, 400, 1.0,
						 ASGE::COLOURS::DARKORANGE);

	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText("SCORE: ", 550, 500, 1.0,
						 ASGE::COLOURS::DARKORANGE);

	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText(std::to_string(player_manager->getScore()).c_str(), 
						 700, 500, 1.0, ASGE::COLOURS::WHITESMOKE);
}



void InvadersGame::inputMenu(const int _key, const int _action)
{
	if (_action == ASGE::KEYS::KEY_PRESSED)
	{
		if (_key == ASGE::KEYS::KEY_ESCAPE)
		{
			game_action = GameAction::EXIT;
		}
	}

	if (ASGE::KEYS::KEY_PRESSED)
	{
		if (_key == ASGE::KEYS::KEY_ENTER)
		{
			current_state = &InvadersGame::playUpdate;
		}
	}
}



void InvadersGame::inputPlay(const int _key, const int _action)
{
	// KEY PRESSED
	if (_action == ASGE::KEYS::KEY_PRESSED)
	{
		if (_key == ASGE::KEYS::KEY_A)
		{
			move_command = Direction::LEFT;
		}
		if (_key == ASGE::KEYS::KEY_D)
		{
			move_command = Direction::RIGHT;
		}
		if (_key == ASGE::KEYS::KEY_SPACE)
		{
			shoot_command = ShootCommands::SHOOTING;
		}
		if(_key == ASGE::KEYS::KEY_P)
		{
			current_state = &InvadersGame::pauseUpdate;
		}
	}

	// KEY RELEASED
	if (_action == ASGE::KEYS::KEY_RELEASED)
	{
		if (_key == ASGE::KEYS::KEY_A)
		{
			move_command = Direction::NONE;
		}
		if (_key == ASGE::KEYS::KEY_D)
		{
			move_command = Direction::NONE;
		}
		if (_key == ASGE::KEYS::KEY_SPACE)
		{
			shoot_command = ShootCommands::NONE;
		}
	}
}



void InvadersGame::inputPause(const int _key, const int _action)
{
	if (_action == ASGE::KEYS::KEY_PRESSED)
	{
		if (_key == ASGE::KEYS::KEY_BACKSPACE)
		{
			current_state = &InvadersGame::playUpdate;
		}
	}

	if (_action == ASGE::KEYS::KEY_PRESSED)
	{
		if (_key == ASGE::KEYS::KEY_ESCAPE)
		{
			current_state = &InvadersGame::menuUpdate;
			reset(true);
		}
	}
}



void InvadersGame::inputGameOver(const int _key, const int _action)
{
	if (_action == ASGE::KEYS::KEY_PRESSED)
	{
		if (_key == ASGE::KEYS::KEY_ESCAPE)
		{
			current_state = &InvadersGame::menuUpdate;
			reset(true);
		}
	}
}


/**
*   @brief   Processes any key inputs and translates them to a GameAction
*   @details This function is added as a callback to handle the game's 
			 input. Key presseses are translated in to GameActions which 
			 are then processed by the main game loop.
*   @param   key is the key the action relates to
*   @param   action whether the key was released or pressed
*   @return  void
*/
void InvadersGame::input(const int _key, const int _action)
{
	// create different input functions based the current game state
	if(current_state == &InvadersGame::menuUpdate)
	{
		inputMenu(_key, _action);
	}
	else if(current_state == &InvadersGame::playUpdate)
	{
		inputPlay(_key, _action);
	}
	else if(current_state == &InvadersGame::pauseUpdate)
	{
		inputPause(_key, _action);
	}
	else if(current_state == &InvadersGame::gameOverUpdate)
	{
		inputGameOver(_key, _action);
	}
}



/**
*   @brief   Processes the next game action
*   @details Uses the game action that was a direct result of 
*            user input. It allows input to processed in a different
             thread and the game actions performed in the main thread. 
*   @return  void
*/
void InvadersGame::processGameActions()
{
	if (current_state == &InvadersGame::menuUpdate)
	{
		if (game_action == GameAction::EXIT)
		{
			this->exit = true;
		}
	}
	else if (current_state == &InvadersGame::playUpdate)
	{
		if (init_game_objs)
		{
			player_manager->handleMove(move_command);
			player_manager->handleShoot(shoot_command);
		}
	}
	else if (current_state == &InvadersGame::pauseUpdate)
	{
		// ..
	}
	else if (current_state == &InvadersGame::gameOverUpdate)
	{
		move_command = Direction::NONE;
		shoot_command = ShootCommands::NONE;
	}
}