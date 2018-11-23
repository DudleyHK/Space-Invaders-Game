/*




*/
#pragma once
#include "Enemy.h"
#include "Spawner.h"



struct GameData;

class EnemyManager
{
public:
	EnemyManager() = delete;
	EnemyManager(std::shared_ptr<ASGE::Renderer>);
	~EnemyManager() = default;

	GameObject* getSpriteAt(const int _idx);
	const int getDifficulty() const;
	const int getListSize() const;
	void resetParameters();

	void createEnemies();
	void update(GameData*);

	void clearObjects();

	void handleShoot(const int _idx, ShootCommands _command);


protected:
	const ObjectType getEnemyType(const int _row) const;
	void speedUp();
	void setCommand();
	void exeCommand();
	void changeSpriteFrame();
	void updateDirection();
	void shooting();
	bool checkEnemiesPos(const int _idx);
	void drawEnemies();
	bool isTimeUp();


private:
	float timer       = 0;
	float wait_time   = 0;
	int enemy_x_speed = 0;
	int enemy_y_speed = 0;
	int diff          = 0;   /**< How often do the enemies shoot */
	bool half_diff    = false;
	bool quater_diff  = false;
	
	std::vector<Direction>  command_list;
	std::vector<GameObject*> bullet_list;

	std::unique_ptr<CommandManager> command_manager = nullptr;
	std::unique_ptr<Command>        current_command = nullptr;
	std::unique_ptr<Spawner>        enemy_spawner   = nullptr;
	std::shared_ptr<ASGE::Renderer> renderer        = nullptr;

	ObjectType current_type = ObjectType::NONE;
	GameData* game_data = nullptr;
};