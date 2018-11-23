/*




*/
#pragma once

#include "GameObject.h"


class Bullet : public GameObject
{
public:
	Bullet() = delete;
	Bullet(std::shared_ptr<ASGE::Renderer>, int _num_of_frames);
	virtual ~Bullet() = default;

	const float getSpeed() const;
	void setSpeed(const float _speed);

	void destroy();
	void hitEnd();

	bool checkCollision(GameObject* _other);

private:
	Direction dir = Direction::NONE;
	float speed = 0.f;
};