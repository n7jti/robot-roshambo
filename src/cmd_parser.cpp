// (C) Alan Ludwig, All rights reserved

#include "pico/stdlib.h"
#include "pico/util/queue.h"

#include "error.h"
#include "cmd_parser.h"
#include "game.h"
#include "uart.h"

queue_t char_fifo;
Parser_State parser_state;
Parser_State parser_state_before_skip;

int init_cmd_parser()
{
    queue_init(&char_fifo, sizeof(char), PARSER_FIFO_LENGTH);
    parser_state = PARSER_STATE_IDLE;
    return 0;
}

int cmd_parser_push_character(char ch)
{
    bool ret = false;
    ret = queue_try_add(&char_fifo, &ch);

    // Return 0 on success or
    return ret ? ERROR_SUCCESS : ERROR_CHARACTER_QUEUE_FULL;
}

int process_input()
{
    int ret = ERROR_SUCCESS;
    char ch = '\0';
    while (queue_try_remove(&char_fifo, &ch))
    {
        // echo characters to the screen
        // this is only for interaction with Humans for debugging.  
        // must be removed or it will confuse the robots
        //uart_putc(UART_ID, ch);
        //if ('\r' == ch){
        //    uart_putc(UART_ID, '\n');
        //}


        switch (parser_state)
        {
        case PARSER_STATE_IDLE:
            switch (ch)
            {
            case 'P':
                parser_state = PARSER_STATE_P;
                break;
            case 'Y':
                parser_state = PARSER_STATE_Y;
                break;
            case 'R':
                parser_state = PARSER_STATE_ROCK;
                parser_state_before_skip = parser_state;
                parser_state = PARSER_STATE_SKIP;
                break;
            case 'S':
                parser_state = PARSER_STATE_SCISSORS;
                parser_state_before_skip = parser_state;
                parser_state = PARSER_STATE_SKIP;
                break;
            case 'T':
                parser_state = PARSER_STATE_TIE;
                parser_state_before_skip = parser_state;
                parser_state = PARSER_STATE_SKIP;
                break;
            case 'I':
                parser_state = PARSER_STATE_I_WIN;
                parser_state_before_skip = parser_state;
                parser_state = PARSER_STATE_SKIP;
                break;
            case '\r':
            case '\n':
            case ' ':
            case '\t':
                break;
            default:
                parser_state_before_skip = PARSER_STATE_IDLE;
                parser_state = PARSER_STATE_SKIP;
            };
            break;
        case PARSER_STATE_P:
            switch (ch)
            {
            case 'L':
                parser_state = PARSER_STATE_PLAY;
                parser_state_before_skip = parser_state;
                parser_state = PARSER_STATE_SKIP;
                break;
            case 'A':
                parser_state = PARSER_STATE_PAPER;
                parser_state_before_skip = parser_state;
                parser_state = PARSER_STATE_SKIP;
                break;
            default:
                parser_state_before_skip = PARSER_STATE_IDLE;
                parser_state = PARSER_STATE_SKIP;
            }
            break;
        case PARSER_STATE_Y:
            switch (ch)
            {
            case 'E':
                parser_state = PARSER_STATE_YES;
                parser_state_before_skip = parser_state;
                parser_state = PARSER_STATE_SKIP;
                break;
            case 'O':
                parser_state = PARSER_STATE_YOU_WIN;
                parser_state_before_skip = parser_state;
                parser_state = PARSER_STATE_SKIP;
            default:
                parser_state_before_skip = PARSER_STATE_IDLE;
                parser_state = PARSER_STATE_SKIP;
            }
        case PARSER_STATE_SKIP:
            switch (ch)
            {
            case '\r':
            case '\n':
                // on '\r' or '\n' go back to Idle state
                parser_state = PARSER_STATE_IDLE;
                switch (parser_state_before_skip)
                {
                case PARSER_STATE_PLAY:
                    ret = parser_on_play();
                    break;
                case PARSER_STATE_ROCK:
                    ret = parser_on_rock();
                    break;
                case PARSER_STATE_SCISSORS:
                    ret = parser_on_scissors();
                    break;
                case PARSER_STATE_TIE:
                    ret = parser_on_tie();
                    break;
                case PARSER_STATE_I_WIN:
                    ret = parser_on_i_win();
                    break;
                case PARSER_STATE_PAPER:
                    ret = parser_on_paper();
                    break;
                case PARSER_STATE_YES:
                    ret = parser_on_yes();
                    break;
                case PARSER_STATE_YOU_WIN:
                    ret = parser_on_you_win();
                    break;
                case PARSER_STATE_IDLE:
                    // Nothing more to do here!
                    break; 
                default:
                    // we should never have gotten here!!
                    ret = ERROR_UNEXPECTED_PARSER_STATE_BEFORE_SKIP;
                    break;
                }
                parser_state_before_skip = PARSER_STATE_I_WIN;
                break;
            default:
                // stay in this state till we see \n
                break;
            }
            break;
        // We should never hit the default case.  We are in an unexpected state
        default:
        // log some sort of error!!
        // After that, try to recover by going to the skip state.
        ret:
            ERROR_UNEXPECTED_CMD_PARSER_STATE;
            parser_state_before_skip = PARSER_STATE_IDLE;
            parser_state = PARSER_STATE_SKIP;
            break;
        }

        // stop command parsing if we have hit an error.
        if (ERROR_SUCCESS != ret)
        {
            break;
        }
    }

    return ret;
}

int parser_on_play()
{
    int ret = ERROR_SUCCESS;
    ret = game_push_move(MOVE_PLAY);
    return ret;
}

int parser_on_paper()
{
    int ret = ERROR_SUCCESS;
    ret = game_push_move(MOVE_PAPER);
    return ret;
}

int parser_on_yes()
{
    int ret = ERROR_SUCCESS;
    ret = game_push_move(MOVE_YES);
    return ret;
}

int parser_on_you_win()
{
    int ret = ERROR_SUCCESS;
    ret = game_push_move(MOVE_YOU_WIN);
    return ret;
}

int parser_on_rock()
{
    int ret = ERROR_SUCCESS;
    ret = game_push_move(MOVE_ROCK);
    return ret;
}

int parser_on_scissors()
{
    int ret = ERROR_SUCCESS;
    ret = game_push_move(MOVE_SCISSORS);
    return ret;
}

int parser_on_tie()
{
    int ret = ERROR_SUCCESS;
    ret = game_push_move(MOVE_TIE);
    return ret;
}

int parser_on_i_win()
{
    int ret = ERROR_SUCCESS;
    ret = game_push_move(MOVE_I_WIN);
    return ret;
}