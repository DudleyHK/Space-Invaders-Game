/*



*/
#pragma once
#include "Actor.h"
#include "CommandManager.h"
#include "ObjectType.h"



class Actor;

class Enemy : public Actor
{
public:

	Enemy() = delete;
	Enemy(const int _points, const std::shared_ptr<ASGE::Renderer>, 
		  int _num_of_frames);
	~Enemy() = default;

	const int getPoints() const;
	static const Direction getCurrentDirection();

	static void setCurrentDirection(Direction);
	void setShootCommand(ShootCommands);

	void reloadBullets();
	bool initBulletList();

private:
	int points = 0;
	//int ID = -1;
	//bool init_bullet = false;

	static Direction move_dir;

	ShootCommands shoot_command = ShootCommands::NONE;

	//std::unique_ptr<Spawner> bullet_spawner = nullptr;
	//std::vector<std::unique_ptr<GameObject>> bullet_list;
};