/*



*/
#include "Player.h"




Player::Player(std::shared_ptr<ASGE::Renderer> _r, int _num_of_frames)
	: Actor(_r)
{
	createSprites(_num_of_frames);
	setIsAlive(true);
	setShootDir(Direction::UP);
}