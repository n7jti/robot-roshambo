#pragma once

// (C) Alan Ludwig, All rights reserved

constexpr uint MOVE_FIFO_LENGTH = 32;

typedef enum e_Move
{
    MOVE_INVALID_MOVE = 0,
    MOVE_PLAY = 1,
    MOVE_YES = 2,
    MOVE_ROCK = 3,
    MOVE_PAPER = 4,
    MOVE_SCISSORS = 5,
    MOVE_YOU_WIN = 6,
    MOVE_I_WIN = 7,
    MOVE_TIE = 8
} Move;

int init_game_engine();
int game_push_move(Move move);
int game_process_moves();
