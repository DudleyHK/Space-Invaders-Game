/*



*/
#pragma once

#include <string>
#include <vector>

#include <Engine/OGLGame.h>

#include "Timer.h"


enum class ShootCommands;
struct GameData;
struct GameFont;
class Collisions;
class EnemyManager;
class PlayerManager;
class Spawner;

/**
*  Invaders Game. An OpenGL Game based on ASGE.
*/

class InvadersGame:
	public ASGE::OGLGame
{
public:
	InvadersGame();
	~InvadersGame();

	// Inherited via Game
	virtual bool run() override;
	bool shouldExit() const;
	void render();

	// Inherited via OGLGame
	virtual bool init();
	virtual void drawFrame();

	const bool initGameObjects(const bool _full_reset);
	void reset(const bool _full_reset);
	void collisionDetection();
	const bool hitEnemy (const int _i);
	const bool hitPlayer(const int _i);
	const bool hitBlock (const int _i);
	const bool checkPlayerHealth();
	void drawPlayerScore();
	void createBlocks();
	void drawBlocks();


	// GAME STATES // 
	typedef  void (InvadersGame::*GameState)();
	void menuUpdate();     // This is where the player chooses where to go in the game
	void playUpdate();     // Game play from here the only option is to pause -> this can be done using a key press. 
 	void pauseUpdate();    // From here either go back to play, or quit. Game will not be restarted 
	void gameOverUpdate(); // Display different text, reset variables

	void inputMenu(const int _key, const int _action);
	void inputPlay(const int _key, const int _action);
	void inputPause(const int _key, const int _action);
	void inputGameOver(const int _key, const int _action);
	void inputExitGame(const int _key, const int _action);


private:
	GameState current_state = &InvadersGame::menuUpdate;

	std::vector<ShootCommands> enemy_shoot_cmds;

	void processGameActions(); 
	void input(int _key, int _action);
	void enemyCommands();

	int  callback_id = -1;                 /**< Input Callback ID. The callback
										   ID assigned by the game engine. */
	bool exit = false;        
	bool init_game_objs = false;
	bool first_iter = false;
	bool game_won = false;
	float wait_time = 1.f;

	std::unique_ptr<Spawner>       block_spawner   = nullptr;
	std::unique_ptr<PlayerManager> player_manager  = nullptr;
	std::unique_ptr<EnemyManager>  enemy_manager   = nullptr;
	std::unique_ptr<Collisions>    col             = nullptr;
	std::unique_ptr<Timer>         timer           = nullptr;

	GameData* game_data = nullptr;
};