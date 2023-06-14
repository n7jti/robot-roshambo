#pragma once 

// (C) Alan Ludwig, All rights reserved. 

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/util/queue.h"

constexpr uint PARSER_FIFO_LENGTH = 32; 

typedef enum e_Parser_State
{
    PARSER_STATE_START      = 0, 
    PARSER_STATE_IDLE       = 1,
    PARSER_STATE_P          = 2,
    PARSER_STATE_Y          = 3,
    PARSER_STATE_PLAY       = 4,
    PARSER_STATE_PAPER      = 5,
    PARSER_STATE_YES        = 6,
    PARSER_STATE_YOU_WIN    = 7,
    PARSER_STATE_ROCK       = 8,
    PARSER_STATE_SCISSORS   = 9,
    PARSER_STATE_TIE        = 10,
    PARSER_STATE_I_WIN      = 11,
    PARSER_STATE_SKIP       = 12,
    PARSER_STATE_END        = 13  
} Parser_State; 


int init_cmd_parser();
int cmd_parser_push_character(char ch);
int process_input(); 

// MOVE events
int parser_on_play();
int parser_on_paper();
int parser_on_yes();
int parser_on_you_win(); 
int parser_on_rock();
int parser_on_scissors();
int parser_on_tie();
int parser_on_i_win();

