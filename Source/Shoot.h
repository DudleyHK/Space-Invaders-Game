/*



*/
#pragma once
#include "Command.h"


class Shoot : public Command
{
public:
	Shoot() = default;
	~Shoot() = default;

	void execute(GameObject*, GameData*) override final;

private:
};