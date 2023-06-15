// (C) Alan Ludwig, All Rights Reserved.

#include "pico/stdlib.h"
#include "pico/util/queue.h"

#include "error.h"
#include "game.h"
#include "uart.h"

queue_t move_fifo;
Game_State game_state;

Move my_move;
Move their_move;

Move get_result(const Move &them, const Move &me)
{

    Move ret;

    if (MOVE_ROCK == them)
    {
        if (MOVE_PAPER == me)
        {
            ret = MOVE_I_WIN;
        }
        else if (MOVE_SCISSORS == me)
        {
            ret = MOVE_YOU_WIN;
        }
        else
        {
            ret = MOVE_TIE;
        }
    }
    else if (MOVE_PAPER == them)
    {
        if (MOVE_SCISSORS == me)
        {
            ret = MOVE_I_WIN;
        }
        else if (MOVE_ROCK == me)
        {
            ret = MOVE_YOU_WIN;
        }
        else
        {
            ret = MOVE_TIE;
        }
    }
    else // scissors
    {
        if (MOVE_ROCK == me)
        {
            ret = MOVE_I_WIN;
        }
        else if (MOVE_PAPER == me)
        {
            ret = MOVE_YOU_WIN;
        }
        else
        {
            ret = MOVE_TIE;
        }
    }

    return ret; 
}

int init_game_engine()
{
    queue_init(&move_fifo, sizeof(Move), MOVE_FIFO_LENGTH);
    game_state = GAME_STATE_IDLE;
    return 0;
}

int game_push_move(Move move)
{
    bool ret = false;
    ret = queue_try_add(&move_fifo, &move);

    // Return 0 on success or
    return ret ? ERROR_SUCCESS : MOVE_QUEUE_FULL;
}

void send_move(const Move &move)
{
    switch (move)
    {
    case MOVE_PLAY:
        uart_puts(UART_ID, "PLAY?\n");
        break;
    case MOVE_YES:
        uart_puts(UART_ID, "YES!\n");
        break;
    case MOVE_ROCK:
        uart_puts(UART_ID, "ROCK\n");
        break;
    case MOVE_PAPER:
        uart_puts(UART_ID, "PAPER\n");
        break;
    case MOVE_SCISSORS:
        uart_puts(UART_ID, "SCISSORS\n");
        break;
    case MOVE_YOU_WIN:
        uart_puts(UART_ID, "YOU WIN\n");
        break;
    case MOVE_I_WIN:
        uart_puts(UART_ID, "I WIN\n");
        break;
    case MOVE_TIE:
        uart_puts(UART_ID, "TIE\n");
        break;
    default:
        uart_puts(UART_ID, "ERROR\n");
        break;
    }
    return;
}

int game_process_moves()
{
    int ret = ERROR_SUCCESS;
    Move move;
    while (queue_try_remove(&move_fifo, &move))
    {
        send_move(move);
        switch (game_state)
        {
        case GAME_STATE_IDLE:
            switch (move)
            {
            case MOVE_START:
                send_move(MOVE_PLAY);
                game_state = GAME_STATE_INVITE;
                break;
            case MOVE_PLAY:
                send_move(MOVE_YES);
                // TODO: Call the AI here and get a move
                // In the mean time. always choose ROCK
                my_move = MOVE_ROCK;
                send_move(my_move);
                game_state = GAME_STATE_MOVE;
                break;
            default:
                send_move(MOVE_ERROR);
                // we're already in the idle state.
                break;
            }
            break;
        case GAME_STATE_INVITE:
            switch (move)
            {
            case MOVE_YES:
                // TODO: Call the AI here and get a move
                // In the mean time. always choose ROCK
                my_move = MOVE_ROCK;
                send_move(my_move);
                game_state = GAME_STATE_MOVE;
                break;
            default:
                send_move(MOVE_ERROR);
                game_state = GAME_STATE_IDLE;
                break;
            }
            break;
        case GAME_STATE_MOVE:
            switch (move)
            {
            case MOVE_ROCK:
            case MOVE_PAPER:
            case MOVE_SCISSORS:
                their_move = move;
                send_move(get_result(their_move, my_move)); 
                game_state = GAME_STATE_RESULT; 
                break;
            default:
                send_move(MOVE_ERROR);
                game_state = GAME_STATE_IDLE;
                break;
            }
            break;
        case GAME_STATE_RESULT:
            switch (move)
            {
            case MOVE_YOU_WIN:
            case MOVE_I_WIN:
            case MOVE_TIE:
                game_state = GAME_STATE_IDLE;
                break;
            default:
                send_move(MOVE_ERROR);
                game_state = GAME_STATE_IDLE;
                break;
            }
            break;
        default:
            // We should never get here
            ret = ERROR_UNEXPECTED_GAME_ENGINE_STATE;
            game_state = GAME_STATE_IDLE;
            break;
        }
    }
    return ret;
}