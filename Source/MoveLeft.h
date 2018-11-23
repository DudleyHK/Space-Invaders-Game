/*



*/
#pragma once
#include "Command.h"


class MoveLeft : public Command
{
public:
	MoveLeft() = default;
	~MoveLeft() = default;

	void execute(GameObject*, GameData*) override final;

private:
};