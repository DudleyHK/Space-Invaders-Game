/*




*/
#pragma once
#include "Command.h"
#include "CommandManager.h"
#include "Player.h"


struct GameData;

class PlayerManager
{
public:
	PlayerManager() = delete;
	PlayerManager(std::shared_ptr<ASGE::Renderer>);
	~PlayerManager() = default;

	GameObject* getPlayer()      const;
	const bool  getPlayerState() const;
	const int   getTotalLives()  const;
	const int   getScore()       const; 

	GameObject* getBulletAt(const int _idx);
	void setPlayerState(const bool _state);
	void setTotalLives(const int _lives);
	void setScore(ObjectType);

	void update(GameData*);
	bool createPlayer();
	void resetPlayer();
	void handleMove(const Direction);
	void handleShoot(const ShootCommands);

protected:
	void executeAndReset();
	bool initLivesGUI();
	void drawLives();


private:
	int num_of_frames   = 1;
	int player_x_speed  = 50;
	int total_lives     = -1;
	int current_score   = 0; 
	bool has_init_lives = false;
	bool player_dead    = false;

	std::unique_ptr<CommandManager> input_handler   = nullptr;
	std::unique_ptr<Command>        current_command = nullptr;
	std::unique_ptr<Spawner>        player_spawner  = nullptr;
	std::unique_ptr<Spawner>        player_health   = nullptr;
	std::shared_ptr<ASGE::Renderer> renderer        = nullptr;

	GameData* game_data = nullptr;
};