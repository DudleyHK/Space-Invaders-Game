/*





*/
#include "MoveDown.h"



void MoveDown::execute(GameObject* _object, GameData* _gd)
{
	_object->setPos(_object->getPosX(), 
					_object->getPosY() + (_gd->y_speed * _gd->dt));
}