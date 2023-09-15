// (C) Alan Ludwig All rights reserved

#include <stdio.h>
#include "pico/stdlib.h"
#include "uart.h"
#include "game.h"
#include "cmd_parser.h"
#include "ai.h"
#include "led.h"
#include "button.h"

// constants
constexpr uint LED_PIN = PICO_DEFAULT_LED_PIN;

// All setup goes here
void setup()
{
    // Standard Pico
    stdio_init_all();

    // Setup the UART we'll play the game with
    setup_uart();

    init_cmd_parser();
    init_game_engine();
    init_led();
    init_ai();

    return;
}

// This loop function will be called forever
void loop()
{

    Game_State game_state = game_get_state();
    if (GAME_STATE_IDLE == game_state && true == get_bootsel_button())
    {
        game_push_move(MOVE_START);
    }
    else
    {
        process_input();
    }
    game_process_moves();
    return;
}

// Use a super loop pattern
int main()
{
    setup();
    while (true)
    {
        loop();
    }
}