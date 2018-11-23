/*



*/
#include "Actions.h"
#include "CommandManager.h"
#include "MoveLeft.h"
#include "MoveRight.h"
#include "MoveDown.h"
#include "Shoot.h"



std::unique_ptr<Command>
CommandManager::getMoveCommand(const Direction _action) const
{
	switch (_action)
	{
		case Direction::LEFT:
			return (std::make_unique<MoveLeft>());
			break;

		case Direction::RIGHT:
			return (std::make_unique<MoveRight>());
			break;
		case Direction::DOWN:
			return (std::make_unique<MoveDown>());

		case Direction::NONE:
			return nullptr;
			break;
	}
	return nullptr;
}



std::unique_ptr<Command> 
CommandManager::getShootCommand(const ShootCommands _action) const
{
	switch (_action)
	{
		case ShootCommands::SHOOTING:
			return (std::make_unique<Shoot>());
			break;

		case ShootCommands::NONE:
			return nullptr;
			break;
	}
	return nullptr;
}
