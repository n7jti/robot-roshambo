#pragma once

// (C) Alan Ludwig, All rights reserved

constexpr uint MOVE_FIFO_LENGTH = 32;
constexpr int MOVES_PER_GAME = 100;

typedef enum e_Move
{
    MOVE_INVALID = 0,
    MOVE_START = 1,
    MOVE_PLAY = 2,
    MOVE_YES = 3,
    MOVE_ROCK = 4,
    MOVE_PAPER = 5,
    MOVE_SCISSORS = 6,
    MOVE_YOU_WIN = 7,
    MOVE_I_WIN = 8,
    MOVE_TIE = 9,
    MOVE_ERROR = 10
} Move;

typedef enum e_Game_State
{
    GAME_STATE_IDLE = 1,
    GAME_STATE_INVITE = 2,
    GAME_STATE_MOVE = 3,
    GAME_STATE_RESULT = 4
} Game_State;

int init_game_engine();
int game_push_move(Move move);
int game_process_moves();
Game_State game_get_state(); 
