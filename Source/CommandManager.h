/*




*/
#pragma once
#include <memory>

#include "Command.h"


enum class Direction;
enum class ShootCommands;

class CommandManager
{
public:
	CommandManager() = default;
	~CommandManager() = default;

	std::unique_ptr<Command> getMoveCommand(const Direction) const;
	std::unique_ptr<Command> getShootCommand(const ShootCommands) const;

private:
};