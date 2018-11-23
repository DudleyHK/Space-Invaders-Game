/*



*/
#pragma once
#include "GameData.h"
#include "Player.h"


class GameObject;
class Command
{
public:
	Command() = default;
	virtual ~Command() = default;

	virtual void execute(GameObject*, GameData*) = 0;

private:

};