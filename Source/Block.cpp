/*







*/
#include "Block.h"
#include "Constants.h"

Block::Block(std::shared_ptr<ASGE::Renderer> _r, int _num_of_frames) :
	GameObject(_r), total_lives(BLOCK_LIVES)
{
	createSprites(_num_of_frames);
	setIsAlive(true);
}



const int Block::getLives() const
{
	return total_lives;
}



void Block::setLives(const int _lives)
{
	total_lives = _lives;
}
