/*






*/
#include "Block.h"
#include "Bullet.h"
#include "Constants.h"
#include "Enemy.h"
#include "Spawner.h"



int Spawner::total_bullets = -1;/////////////////////IS THIS NEEDED


Spawner::Spawner(std::shared_ptr<ASGE::Renderer> _r)
	: renderer(_r)
{
	//all_game_objects.reserve(100);
	object_list.reserve(100);
}



GameObject* Spawner::getSpriteAt(const int _idx)
{
	return object_list[_idx].get();
}



const int Spawner::getListSize() const
{
	int counter = 0;
	for(int i = 0; i < object_list.size(); i++)
	{
		if(object_list[i]->getIsAlive())
		{
			counter++;
		}
	}
	return counter;
}



void Spawner::setSpriteAt(const int _idx, GameObject* _obj)
{
	object_list[_idx].reset(std::move(_obj));
}



void Spawner::setSpriteType(const ObjectType _type)
{
	switch (_type)
	{
		case ObjectType::ENEMY_T:
			temp_obj = std::make_unique<Enemy>(75, renderer, 2);
			temp_obj->setSpriteAt(
				"..\\..\\Resources\\Textures\\Top_Alien_1.png", 1);
			temp_obj->setSpriteAt(
				"..\\..\\Resources\\Textures\\Top_Alien_2.png", 2);
			temp_obj->setType(ObjectType::ENEMY);
			break;

		case ObjectType::ENEMY_M:
			temp_obj = std::make_unique<Enemy>(50, renderer, 2);
			temp_obj->setSpriteAt(
				"..\\..\\Resources\\Textures\\Mid_Alien_1.png", 1);
			temp_obj->setSpriteAt(
				"..\\..\\Resources\\Textures\\Mid_Alien_2.png", 2);
			temp_obj->setType(ObjectType::ENEMY);
			break;

		case ObjectType::ENEMY_B:
			temp_obj = std::make_unique<Enemy>(25, renderer, 2);
			temp_obj->setSpriteAt(
				"..\\..\\Resources\\Textures\\Bot_Alien_1.png", 1);
			temp_obj->setSpriteAt(
				"..\\..\\Resources\\Textures\\Bot_Alien_2.png", 2);
			temp_obj->setType(ObjectType::ENEMY);
			break;

		case ObjectType::PLAYER:
			temp_obj = std::make_unique<Player>(renderer, 1);
			temp_obj->setSpriteAt(
				"..\\..\\Resources\\Textures\\Player.png", 1);
			temp_obj->setType(ObjectType::PLAYER);
			break;

		case ObjectType::BULLET:
			temp_obj = std::make_unique<Bullet>(renderer, 1);
			temp_obj->setSpriteAt(
				"..\\..\\Resources\\Textures\\Bullet.png", 1);
			temp_obj->setType(ObjectType::BULLET);
			temp_obj->setID(total_bullets);//////////////////////////////////////////////////ARE THESE NEEDED
			incrementTotalBullets();       //////////////////////////////////////////////////ARE THESE NEEDED
			break;

		case ObjectType::BLOCK:
			temp_obj = std::make_unique<Block>(renderer, 1);
			temp_obj->setSpriteAt(
				"..\\..\\Resources\\Textures\\Barrier.png", 1);
			temp_obj->setType(ObjectType::BLOCK);
		default:
			break;
	}
	object_list.push_back(std::move(temp_obj));
	temp_obj.reset(nullptr);
}



void Spawner::setSpritePos(const int _x, const int _y, const int _idx)
{
	object_list[_idx]->setPos(_x, _y);
}



void Spawner::setSpriteSize(const int _w, const int _h, const int _idx)
{
	object_list[_idx]->setSize(_w, _h);
}



void Spawner::draw(const int _idx)
{
	if (object_list[_idx]->getIsAlive())
	{
		object_list[_idx]->getSpriteAt(object_list[_idx]->getCurrentFrame())->
			render(renderer);
	}
}



void Spawner::removeAllObjects()
{
	object_list.clear();
}



void Spawner::incrementTotalBullets()
{
	total_bullets++;
}
