// (C) Alan Ludwig, All rights reserved

#include "pico/stdlib.h"
#include "ai.h"

static Move my_moves[MOVES_PER_GAME];
static Move their_moves[MOVES_PER_GAME];
static int current_move;

void init_ai()
{
    for (int i = 0; i < MOVES_PER_GAME; ++i)
    {
        my_moves[i] = MOVE_INVALID;
        their_moves[i] = MOVE_INVALID;
    }
    current_move = 0;
}

Move ai_get_move()
{
    Move my_move;
    my_move = MOVE_ROCK;
    my_moves[current_move % MOVES_PER_GAME] = my_move;
    return my_move;
}

void ai_their_last_move(const Move move)
{
    their_moves[current_move % MOVES_PER_GAME] = move;
    return;
}

void ai_move_complete(){
    current_move++;
    current_move %= MOVES_PER_GAME;
}