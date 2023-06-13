#pragma once 

// (C) Alan Ludwig, All rights reserved. 

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/util/queue.h"

typedef e_Command
enum{
    COMMAND_PLAY        = 1,
    COMMAND_YES         = 2,
    COMMAND_ROCK        = 3,
    COMMAND_PAPER       = 4,
    COMMAND_SCISSORS    = 5,
    COMMAND_YOUWWIN     = 6,
    COMMAND_I_WIN       = 7,
    COMMAND_TIE         = 8
} Command; 


typedef e_Parser_State
enum {
    PARSER_STATE_P = 1,
    PARSER_STATE_L = 2, 
    PARSER_STATE_A = 3, 
    PARSER_STATE_Y = 4, 
    PARSER_STATE_E = 5, 
    PARSER_STATE_O = 6, 
    PARSER_STATE_R = 7, 
    PARSER_STATE_S = 8, 
    PARSER_STATE_I = 9, 
    PARSER_STATE_T = 10,
    PARSER_STATE_SKIP = 11 
} Parser_State; 


int init_cmd_parser();
int push_character(char ch);
int process_input(); 

