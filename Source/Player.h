/*



*/
#pragma once

#include "Actor.h"
#include "Bullet.h"


class Player : public Actor
{
public:
	Player() = delete;
	Player(std::shared_ptr<ASGE::Renderer>, int _num_of_frames);
	~Player() = default;

private:
//	bool init_bullet = false;
};
