/*


*/
#pragma once

#include <memory>
#include <vector>

#include <Engine\Sprite.h>
#include <Engine\Renderer.h>

#include "Actions.h"
#include "ObjectType.h"

class Command;
class Enemy;
class Player;
struct GameData;


class GameObject
{
public:
	GameObject() = delete;
	GameObject(std::shared_ptr<ASGE::Renderer>);
	virtual ~GameObject() = default;


	ASGE::Sprite* getSpriteAt(const int _idx);
	const int getPosX() const;
	const int getPosY() const;
	const int getWidth() const;
	const int getHeight() const;
	const int getCurrentFrame() const;
	const int getID() const;
	const bool getIsAlive() const;
	const ObjectType getParent() const;
	const ObjectType getType() const;

	void setIsAlive(const bool _is_alive);
	void setPos(const int _x, const int _y);
	void setSize(const int _x, const int _y);
	void setSpriteAt(const char* _file, const int _idx);
	void setCurrentFrame(const int _current_frame);
	void setType(ObjectType);
	void setParent(ObjectType);
	void setID(const int _ID);

	void calcNewIdx(const int _idx);
	void createSprites(const int _total);

	virtual void update(Command*, GameData*);//{};
	virtual void setBulletState(const bool _state);
	//virtual void updateCollisions();


protected:
	std::vector<std::unique_ptr<ASGE::Sprite>> sprite_list;
	std::shared_ptr<ASGE::Renderer> renderer = nullptr;

private:
	int pos_x = 0;
	int pos_y = 0;
	int width = 0;
	int height = 0;
	int sprite_idx = -1;
	bool is_alive = false;

	int ID = -1;

	ObjectType type = ObjectType::NONE;
	ObjectType parent = ObjectType::NONE;
	int current_frame;
};







//const IMaths::Vector2 getPos() const;
//void setSize(IMaths::Vector2 _size);


//std::unique_ptr<ASGE::Sprite> getSpriteImg(int _frame) const;
//const int getFrameIndex() const;
//const char* getFileName(int _frame) const;

//void setFileName(const char* _file, int _frame);
//void setPos(float _x, float _y);
//void setSize(float _x, float _y);
//void setSpriteImg(std::unique_ptr<ASGE::Sprite>);
//void setFrameIndex(int _i);



/*
IMaths::Vector2 pos;
IMaths::Vector2 size;

std::unique_ptr<IVector> spr_frames = nullptr;
std::unique_ptr<ASGE::Sprite> sprite = nullptr;
std::unique_ptr<std::string[]> file_name_array = nullptr;*/