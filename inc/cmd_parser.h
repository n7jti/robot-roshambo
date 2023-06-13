#pragma once 

// (C) Alan Ludwig, All rights reserved. 

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/util/queue.h"

/*
enum{
    PLAY: PL
    YES: YE
    ROCK: R
    PAPER : PA
    SCISSORS: SC
    YOU WIN: YO
    I WIN: I
    TIE: T
}
*/

int init_cmd_parser();
int push_character(char ch);
int process_input(); 

