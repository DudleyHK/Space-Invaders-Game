/*





*/
//#include "Actor.h"
//#include "Player.h"
//#include "Enemy.h"
//#include "EnemyManager.h"
//#include "PlayerManager.h"
//#include "ObjectType.h"
#include "Collisions.h"
#include "GameObject.h"




//void Collisions::checkCollision(Actor* _shooter, Actor* _shot_at)
//{
//	//if (_shooter->getBullet() && _shooter->getBullet()->getIsAlive())
//	//{
//		if ((_shooter->getBullet()->getPosX() + _shooter->getBullet()->getWidth())
//			>= _shot_at->getPosX() &&
//			(_shooter->getBullet()->getPosX())
//			<= (_shot_at->getPosX() + _shot_at->getWidth()) &&
//			(_shooter->getBullet()->getPosY() + _shooter->getBullet()->getHeight())
//			>= _shot_at->getPosY() &&
//			(_shooter->getBullet()->getPosY()
//			 <= (_shot_at->getPosY() + _shot_at->getHeight())))
//		{
//			//_shot_at->setIsAlive(false);
//			//_shooter->getBullet()->setIsAlive(false);
//		}
//	//}
//}



//void Collisions::update(ObjectType _type)
//{
//	switch (_type)
//	{
//		case ObjectType::PLAYER:
//			break;
//
//		case ObjectType::ENEMY_B:
//		case ObjectType::ENEMY_M:
//		case ObjectType::ENEMY_T:
//			get
//			break;
//	}
//}
//


// Are the two objects overlapping?
bool Collisions::checkCollision(GameObject* _collider, GameObject* _other)
{
	if(_collider->getParent() == _other->getType())
	{
		return false;
	}

	if ((_collider->getPosX() + _collider->getWidth()) >= _other->getPosX() &&
		(_collider->getPosX()) <= (_other->getPosX() + _other->getWidth()) &&
		(_collider->getPosY() + _collider->getHeight()) >= _other->getPosY() &&
		(_collider->getPosY() <= (_other->getPosY() + _other->getHeight())))
	{
		return true;
	}
	return false;
}
