/*




*/
#pragma once
#include <memory>
#include <vector>

#include "GameObject.h"
#include "ObjectType.h"


namespace ASGE 
{
	class Renderer;
};


class Spawner
{
public:
	Spawner() = delete;
	Spawner(std::shared_ptr<ASGE::Renderer>);
	~Spawner() = default;


	GameObject* getSpriteAt(const int _idx);
	const int getListSize() const;
	
	void setSpriteAt(const int _idx, GameObject*);
	void setSpriteType(const ObjectType _type);
	void setSpritePos(const int _x, const int _y, const int _idx);
	void setSpriteSize(const int _w, const int _h, const int _idx);
	void draw(const int _idx);

	void removeAllObjects();

	void pushToAllObjects(GameObject*);
	void deactivateObj(const int _idx, bool _is_kill);

	void incrementTotalBullets();

private:

	static int total_bullets;


	//static std::vector<GameObject*> all_game_objects;

	std::vector<std::unique_ptr<GameObject>> object_list;

	std::shared_ptr<ASGE::Renderer> renderer = nullptr;
	std::unique_ptr<GameObject>     temp_obj = nullptr;
};