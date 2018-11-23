/*




*/
#include "Player.h"
#include "Enemy.h"
#include "Shoot.h"



void Shoot::execute(GameObject* _object, GameData* _gd)
{
	_object->update(this, _gd);
}