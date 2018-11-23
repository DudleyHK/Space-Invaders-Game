/*




*/
#include "Bullet.h"



Bullet::Bullet(std::shared_ptr<ASGE::Renderer> _r, int _num_of_frames)
	: GameObject(_r)
{
	setIsAlive(true);
	createSprites(_num_of_frames);
}



const float Bullet::getSpeed() const
{
	return speed;
}



void Bullet::setSpeed(const float _speed)
{
	speed = _speed;
}