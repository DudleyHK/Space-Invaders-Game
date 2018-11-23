#pragma once
#include <string>
#include <atomic>

/** @file Actions.h
    @brief   Actions file defines a thread safe game action
    @details GameActions are stored here as well as a thread safe  
             GameAction variable, which has external linkage. 
*/


/** @enum GameAction
*   @brief is a strongly typed enum class representing the next game action
*/
enum class GameAction : int
{
	INVALID = -1,  /**< is a non-valid game action */
	NONE    =  0,  /**< means no outstanding action to process */
	CHANGE_STATE,
	EXIT          /**< signals the intention to exit the game */
};



enum class Direction : int
{
	LEFT,
	RIGHT,
	DOWN,
	UP,
	NONE
};



enum class ShootCommands : int
{
	SHOOTING,
	NONE
};



extern std::atomic<Direction>     move_command;
extern std::atomic<GameAction>    game_action;
extern std::atomic<ShootCommands> shoot_command;
extern std::atomic<ShootCommands> enemy_shoot;