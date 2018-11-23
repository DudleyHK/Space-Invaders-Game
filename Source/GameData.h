/*




*/
#pragma once
#include <vector>

class GameObject;

struct GameData
{
	float dt = 0.f;

	int x_speed = 0;
	int y_speed = 0;
	int total_bullets = 0;
	std::vector<GameObject*> bullets;
};