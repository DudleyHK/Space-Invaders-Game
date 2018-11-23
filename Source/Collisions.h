/*





*/
#pragma once

//
//class Actor;
//class EnemyManager;
//class PlayerManager;
//enum class ObjectType;
//

class GameObject;

class Collisions
{
public:/*
	friend class EnemyManager;
	friend class PlayerManager;*/

	Collisions() = default;
	~Collisions() = default;

	//void checkCollision(Actor* _shooter, Actor* _shot_at);
	bool checkCollision(GameObject* _collider, GameObject* _other);
};