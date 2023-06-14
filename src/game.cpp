// (C) Alan Ludwig, All Rights Reserved.

#include "pico/stdlib.h"
#include "pico/util/queue.h"

#include "error.h"
#include "game.h"
#include "uart.h"

queue_t move_fifo;

int init_game_engine()
{
    queue_init(&move_fifo, sizeof(Move), MOVE_FIFO_LENGTH);
    return 0;
}

int game_push_move(Move move)
{
    bool ret = false;
    ret = queue_try_add(&move_fifo, &move);

    // Return 0 on success or
    return ret ? ERROR_SUCCESS : MOVE_QUEUE_FULL;
}

int game_process_moves()
{
    int ret = ERROR_SUCCESS;
    Move move; 
    while (queue_try_remove(&move_fifo, &move))
    {
        switch(move){
            case MOVE_PLAY:
                uart_puts(UART_ID, "PLAY\n");
                break; 
            case MOVE_YES:
                uart_puts(UART_ID, "YES\n");
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
                uart_puts(UART_ID, "Unrecognized Move!!!\n");
                break;
        }
    }
    return ret; 
}