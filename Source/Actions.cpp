/*



*/
#include "Actions.h"


/**< Queued Game Action. The next action to be processed as determined by user input. */
std::atomic<GameAction>    game_action    = GameAction::NONE;
std::atomic<Direction>     move_command   = Direction::NONE;
std::atomic<ShootCommands> shoot_command  = ShootCommands::NONE;
std::atomic<ShootCommands> enemy_shoot    = ShootCommands::NONE;