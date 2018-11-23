#pragma once

/*! \file Constants.h
@brief   Constants that are used throughout the game. 
@details Add any new constants to this file. 
*/

constexpr int WINDOW_WIDTH  = 1280;  /**< The window width. Defines how wide the 
									game window is. */
constexpr int WINDOW_HEIGHT = 720;  /**< The window height. Defines the height 
									of the game window */


constexpr int BOUNDARY_L = 80;
constexpr int BOUNDARY_R = 1200;

constexpr int TOTAL_ENEMIES      = 55;   /**< Total number of enemies to spawn */
constexpr int MAX_PLAYER_BULLETS = 5;
constexpr int ENEMY_POS_X       = 100;
constexpr int ENEMY_POS_Y       = 50;
constexpr int ENEMY_DIST_X      = 32;
constexpr int ENEMY_DIST_Y      = 32;
constexpr int ENEMY_X_SPEED     = 100;
constexpr int ENEMY_Y_SPEED     = 75;
constexpr int ENEMY_WIDTH       = 32;
constexpr int ENEMY_HEIGHT      = 28;
constexpr int DIFFICULTY        = 10000;
constexpr int ENEMY_WAIT_TIME   = 15;

constexpr int TOTAL_PLAYERS = 1;
constexpr int PLAYER_LIVES  = 3;
constexpr int PLAYER_WIDTH  = 64;
constexpr int PLAYER_HEIGHT = 32;

constexpr int BULLET_WIDTH  = 5;
constexpr int BULLET_HEIGHT = 20;
constexpr int BULLET_OFFSET = 25;
constexpr int BULLET_SPEED  = 50;

constexpr int TOTAL_BLOCKS = 4;
constexpr int BLOCK_LIVES  = 3;
constexpr int BLOCK_WIDTH  = 150;
constexpr int BLOCK_HEIGHT = 100;