/*


*/
#pragma once

#include "Actions.h"
#include "Bullet.h"
#include "Constants.h"
#include "GameObject.h"
#include "Spawner.h"


struct GameData;

class Actor : public GameObject
{
public:
	Actor() = delete;
	Actor(std::shared_ptr<ASGE::Renderer>);
	~Actor() = default;

	GameObject* getBullet() const;
	void setShootDir(const Direction);
	virtual void setBulletState(const bool _state) override;


protected:
	virtual void update(Command*, GameData*) override final;
	//virtual void updateCollisions(GameObject*, GameObject*);

	void initBullet(GameData*);
	void updateBullet(GameData*);
	void updateEnemyBullet(GameData*);
	void updatePlayerBullet(GameData*);
	void updatePos(GameData*, const int _idx);
	bool checkBounds(const int _idx);

private:
	bool bullet_alive = false;
	std::vector<bool> player_buls_alive;

	Direction bullet_dir = Direction::NONE;

	std::unique_ptr<Spawner> bullet_spawner = nullptr;
	std::vector<std::unique_ptr<Bullet>> bullet_list;
};