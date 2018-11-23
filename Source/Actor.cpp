/*



*/
#include "Actor.h"
#include "GameData.h"



Actor::Actor(std::shared_ptr<ASGE::Renderer> _r)
	: GameObject(_r), bullet_spawner(std::make_unique<Spawner>(_r))
{
	bullet_list.reserve(5);
}



void Actor::setShootDir(const Direction _dir)
{
	bullet_dir = _dir;
}



GameObject* Actor::getBullet()const
{
	return bullet_spawner->getSpriteAt(0);
}


void Actor::setBulletState(const bool _state)
{
	bullet_alive = _state;
}



void Actor::update(Command* _command, GameData* _gd)
{
	if (_command)
	{
		initBullet(_gd);
	}
	else
	{
		updateBullet(_gd);
	}
}


void Actor::initBullet(GameData* _gd)
{
	if (!bullet_alive)
	{
		bullet_spawner->setSpriteType(ObjectType::BULLET);
		bullet_spawner->setSpritePos(getPosX() + BULLET_OFFSET, getPosY(), 0);
		bullet_spawner->setSpriteSize(BULLET_WIDTH, BULLET_HEIGHT, 0);

		bullet_spawner->getSpriteAt(0)->setParent(this->getType());
		_gd->bullets.push_back(bullet_spawner->getSpriteAt(0));
		_gd->bullets.back()->setIsAlive(true);
		bullet_alive = true;
	}
}



//void Actor::initPlayerBullet(GameData* _gd)
//{
//	for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
//	{
//		if(!player_buls_alive[i])
//		{
//			bullet_spawner->setSpriteType(ObjectType::BULLET);
//			bullet_spawner->setSpritePos(getPosX(), getPosY(),i);
//			bullet_spawner->setSpriteSize(BULLET_WIDTH, BULLET_HEIGHT,i);
//
//			bullet_spawner->getSpriteAt(i)->setParent(this->getType());
//			_gd->bullets.push_back(bullet_spawner->getSpriteAt(i));
//			_gd->bullets.back()->setIsAlive(true);
//			player_buls_alive[i] = true;
//		}
//	}
//}



// If the bullet is alive check if its out of bounds or should be rendered?
void Actor::updateBullet(GameData* _gd)
{
	if(bullet_alive)
	{
		if (!checkBounds(0))
		{
			bullet_alive = false;
		}
		else
		{
			updatePos(_gd, 0);
			bullet_spawner->draw(0);
		}
	}
}



//void Actor::updatePlayerBullet(GameData* _gd)
//{
//	for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
//	{
//		if (player_buls_alive[i])
//		{
//			if (!checkBounds(i))
//			{
//				player_buls_alive[i] = false;
//			}
//			else
//			{
//				updatePos(_gd, i);
//				bullet_spawner->draw(i);
//			}
//		}
//	}
//}



void Actor::updatePos(GameData* _gd, const int _idx)
{
	switch (bullet_dir)
	{
		case Direction::UP:
			bullet_spawner->getSpriteAt(_idx)->
				setPos(bullet_spawner->getSpriteAt(_idx)->getPosX(),
					   bullet_spawner->getSpriteAt(_idx)->getPosY() -
					   (BULLET_SPEED * _gd->dt));
			break;

		case Direction::DOWN:
			bullet_spawner->getSpriteAt(_idx)->
				setPos(bullet_spawner->getSpriteAt(_idx)->getPosX(),
					   bullet_spawner->getSpriteAt(_idx)->getPosY() +
					   (BULLET_SPEED * _gd->dt));
			break;
	}
}



bool Actor::checkBounds(const int _idx)
{
	if ((bullet_spawner->getSpriteAt(_idx)->getPosY() < 10) ||
		(bullet_spawner->getSpriteAt(_idx)->getPosY() > (WINDOW_HEIGHT - 10)))
	{		
		return false;
	}
	return true;
}
