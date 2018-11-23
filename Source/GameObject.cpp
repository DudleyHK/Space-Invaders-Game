/*




*/
#include "GameObject.h"



//int GameObject::current_frame = -1;



GameObject::GameObject(std::shared_ptr<ASGE::Renderer> _r)
	: renderer(_r)
{
	sprite_list.reserve(2);
}



ASGE::Sprite* GameObject::getSpriteAt(const int _idx)
{
	calcNewIdx(_idx);
	switch (sprite_idx)
	{
		case 0:
			return sprite_list[sprite_idx].get();
			break;
		case 1:
			return sprite_list[sprite_idx].get();
			break;
	}
	return nullptr;
}



const int GameObject::getPosX() const
{
	return pos_x;
}



const int GameObject::getPosY() const
{
	return pos_y;
}



const int GameObject::getWidth() const
{
	return width;
}



const int GameObject::getHeight() const
{
	return height;
}



const int GameObject::getCurrentFrame() const
{
	return current_frame;
}



const int GameObject::getID() const
{
	return ID;
}



const bool GameObject::getIsAlive() const
{
	return is_alive;
}



const ObjectType GameObject::getParent() const
{
	return parent;
}



const ObjectType GameObject::getType() const
{
	return type;
}



void GameObject::setIsAlive(const bool _is_alive)
{
	is_alive = _is_alive;
}



void GameObject::setPos(const int _x, const int _y)
{
	pos_x = _x;
	pos_y = _y;

	for(const auto& sprite : sprite_list)
	{
		if(sprite)
		{
			sprite->position[0] = _x;
			sprite->position[1] = _y;
		}
	}
}



void GameObject::setSize(const int _w, const int _h)
{
	width = _w;
	height = _h;

	for (const auto& sprite : sprite_list)
	{
		if (sprite)
		{
			sprite->size[0] = _w;
			sprite->size[1] = _h;
		}
	}
}



void GameObject::setSpriteAt(const char* _file, const int _idx)
{
	calcNewIdx(_idx);
	switch (sprite_idx)
	{
		case 0:
			current_frame = _idx;
			sprite_list[sprite_idx]->loadTexture(_file);
			break;

		case 1:
			current_frame = _idx;
			sprite_list[sprite_idx]->loadTexture(_file);
			break;
	}
}



void GameObject::setCurrentFrame(const int _current_frame)
{
	current_frame = _current_frame;
}



void GameObject::setType(ObjectType _type)
{
	type = _type;
}



void GameObject::setParent(ObjectType _type)
{
	parent = _type;
}



void GameObject::setID(const int _ID)
{
	ID = _ID;
}



/**
*   @brief   Calculates sprite frame from human version to computer version. 
*   @param  The index being checked
*   @return  void
*/
void GameObject::calcNewIdx(const int _idx)
{
	sprite_idx = _idx - 1;
}



/**
*   @brief   Create sprite list with sanity check. 
*   @details Takes the number of sprites being pushed back, 
				checks it does not exceed what the program expects. 

*   @param  total number of sprites to add to the object
*   @param  Renderer. 
*   @return  void
*/
void GameObject::createSprites(const int _total)
{
	if (_total > sprite_list.capacity())
	{
		return;
	}
	else
	{
		for (int i = 0; i < _total; i++)
		{
			sprite_list.push_back(nullptr);
			sprite_list[i] = renderer->createSprite();
		}
	}
}



void GameObject::update(Command*, GameData*)
{
	// see derived class
}



void GameObject::setBulletState(const bool _state)
{
	// see derived
};



//void GameObject::updateCollisions()
//{
	// see derived
//}







































































//GameObject::GameObject()
//	: spr_frames(std::make_unique<IVector>()),
//	file_name_array(new std::string[2])
//{
//
//}
//
//
//std::unique_ptr<ASGE::Sprite> GameObject::getSpriteImg(int _frame) const
//{
//	return spr_frames->getElement(_frame);
//}
//
//
//
//const int GameObject::getFrameIndex() const
//{
//	return frame_index;
//}
//
//
//
//const char* GameObject::getFileName(int _frame) const
//{
//	return file_name_array[_frame].c_str();
//}
//
//
//
//void GameObject::setFileName(const char* _file, int _frame)
//{
//	file_name_array[_frame] = _file;
//}
//
//
//
//void GameObject::setPos(float _x, float _y)
//{
//	if(spr_frames->getElement(0))
//	{
//		spr_frames->getElement(0)->position[0] = _x;
//		spr_frames->getElement(0)->position[1] = _y;
//	}
//
//	if(spr_frames->getElement(1))
//	{
//		spr_frames->getElement(1)->position[0] = _x;
//		spr_frames->getElement(1)->position[1] = _y;
//	}
//}
//
//
//
//void GameObject::setSize(float _x, float _y)
//{
//	if (spr_frames->getElement(0))
//	{
//		spr_frames->getElement(0)->size[0] = _x;
//		spr_frames->getElement(0)->size[1] = _y;
//	}
//
//	if (spr_frames->getElement(1))
//	{
//		spr_frames->getElement(1)->size[0] = _x;
//		spr_frames->getElement(1)->size[1] = _y;
//	}
//}
//
//
//
//void GameObject::setSpriteImg(std::unique_ptr<ASGE::Sprite> _spr)
//{
//	spr_frames->pushBack(_spr);
//}
//
//
//
//void GameObject::setFrameIndex(int _i)
//{
//	frame_index = _i;
//}
//
//
////
////temp_spr = _r->createSprite();
////	temp_spr->loadTexture(_file_name.c_str());
////	temp_spr->size[0] = _size.x;
////	temp_spr->size[1] = _size.y;
////
////	spr_frames->pushBack(temp_spr.get());


