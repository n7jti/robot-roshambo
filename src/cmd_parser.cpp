// (C) Alan Ludwig, All rights reserved

#include "pico/stdlib.h"
#include "pico/util/queue.h"


#include "error.h"
#include "cmd_parser.h"
#include "game.h"


queue_t char_fifo;
Parser_State parser_state;

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
                ret = parser_on_rock();
                parser_state = PARSER_STATE_SKIP;
                break;
            case 'S':
                parser_state = PARSER_STATE_SCISSORS;
                ret = parser_on_scissors();
                parser_state = PARSER_STATE_SKIP;
                break;
            case 'T':
                parser_state = PARSER_STATE_TIE;
                ret = parser_on_tie();
                parser_state = PARSER_STATE_SKIP;
                break;
            case 'I':
                parser_state = PARSER_STATE_I_WIN;
                ret = parser_on_i_win();
                parser_state = PARSER_STATE_SKIP;
                break;
            case '\r':
            case ' ':
            case '\t':
            case '\n':
                break;
            default:
                parser_state = PARSER_STATE_SKIP;
            };
            break;
        case PARSER_STATE_P:
            switch (ch)
            {
            case 'L':
                parser_state = PARSER_STATE_PLAY;
                ret = parser_on_play();
                parser_state = PARSER_STATE_SKIP;
                break;
            case 'A':
                parser_state = PARSER_STATE_PAPER;
                ret = parser_on_paper();
                parser_state = PARSER_STATE_SKIP;
                break;
            default:
                parser_state = PARSER_STATE_SKIP;
            }
            break;
        case PARSER_STATE_Y:
            switch (ch)
            {
            case 'E':
                parser_state = PARSER_STATE_YES;
                ret = parser_on_yes();
                parser_state = PARSER_STATE_SKIP;
                break;
            case 'O':
                parser_state = PARSER_STATE_YOU_WIN;
                ret = parser_on_you_win();
                parser_state = PARSER_STATE_SKIP;
            default:
                parser_state = PARSER_STATE_SKIP;
            }
        case PARSER_STATE_SKIP:
        
            switch (ch)
            {
                case '\n':
                    // on '\n' go back to Idle state
                    parser_state = PARSER_STATE_IDLE;
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