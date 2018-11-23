/*




*/
#include "MoveRight.h"




void MoveRight::execute(GameObject* _object, GameData* _gd)
{
	_object->setPos(_object->getPosX() + (_gd->x_speed * _gd->dt),
					_object->getPosY());
}