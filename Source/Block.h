/*/





*/
#pragma once
#include "GameObject.h"



class Block : public GameObject
{
public:
	Block() = delete;
	Block(std::shared_ptr<ASGE::Renderer>, int _num_of_frames);
	virtual ~Block() = default;

	const int getLives() const;
	void setLives(const int _lives);


private:
	int total_lives = 0;
};
