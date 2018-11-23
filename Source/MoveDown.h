/*



*/
#pragma once
#include "Command.h"


class MoveDown : public Command
{
public:
	MoveDown() = default;
	~MoveDown() = default;

	void execute(GameObject*, GameData*) override final;

private:
};