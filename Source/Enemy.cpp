/*




*/

#include "Enemy.h"





// SET STATIC DIRECTION VARIABLES
Direction Enemy::move_dir = Direction::LEFT;





Enemy::Enemy(const int _points, const std::shared_ptr<ASGE::Renderer>_r, 
			 int _num_of_frames)
	: Actor(_r)
{
	createSprites(_num_of_frames);
	setIsAlive(true);
	setShootDir(Direction::DOWN);
}



void Enemy::setCurrentDirection(Direction _dir)
{
	move_dir = _dir;
}



void Enemy::setShootCommand(ShootCommands command)
{
	shoot_command = command;
}



const int Enemy::getPoints() const
{
	return points;
}



const Direction Enemy::getCurrentDirection()
{
	return move_dir;
}
	
