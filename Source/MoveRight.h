/*



*/
#pragma once
#include "Command.h"


class MoveRight : public Command
{
public:
	MoveRight() = default;
	~MoveRight() = default;

	void execute(GameObject*, GameData*) override final;

private:
};