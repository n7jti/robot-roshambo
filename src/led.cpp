// (C) Alan Ludwig All rights reserved

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "game.h"
#include "led.h"
#include "uart.h"

// Lets setup the pins!

static uint16_t led_value = 0;

void init_led()
{
    gpio_init(data_pin);
    gpio_init(clock_pin);
    gpio_init(latch_pin);
    gpio_init(oe_pin);

    gpio_set_dir(data_pin, GPIO_OUT);
    gpio_set_dir(clock_pin, GPIO_OUT);
    gpio_set_dir(latch_pin, GPIO_OUT);
    gpio_set_dir(oe_pin, GPIO_OUT);

    gpio_pull_down(data_pin);
    gpio_pull_down(clock_pin);
    gpio_pull_down(latch_pin);
    gpio_pull_down(oe_pin);

    gpio_put(data_pin, false);
    gpio_put(clock_pin, false);
    gpio_put(latch_pin, false);
    gpio_put(oe_pin, false);

    led_value = 0;
}

static void write_value(uint16_t value)
{

    // uart_puts(UART_ID, "writing value!\n");
    //  shift out the values
    gpio_put(clock_pin, 0);
    gpio_put(latch_pin, 0);

    for (uint i = 0; i < 16; ++i)
    {
        // uart_puts(UART_ID, ((value >> i) & 0x0001) ? "1" : "0");
        gpio_put(data_pin, (value >> i) & 0x0001);
        gpio_put(clock_pin, true);
        sleep_us(CLOCK_DELAY_US);
        gpio_put(clock_pin, false);
        sleep_us(CLOCK_DELAY_US);
    }

    // uart_puts(UART_ID, "\n");

    // latch out the values
    gpio_put(latch_pin, true);
    sleep_us(CLOCK_DELAY_US);
    gpio_put(latch_pin, false);
    sleep_us(CLOCK_DELAY_US);
}

void led_clear()
{
    // uart_puts(UART_ID, "clear!\n");
    write_value(0x0000);
}

void led_set_my_move(Move my_move)
{
    led_value &= (uint16_t)0x0FFF;

    if (my_move == MOVE_ROCK)
    {
        led_value |= (uint16_t)0x8000;
    }
    else if (my_move == MOVE_PAPER)
    {
        led_value |= (uint16_t)0x4000;
    }
    else if (my_move == MOVE_SCISSORS)
    {
        led_value |= (uint16_t)0x2000;
    }

    write_value(led_value);
}

void led_set_their_move(Move their_move)
{
    led_value &= (uint16_t)0xF0FF;

    if (their_move == MOVE_ROCK)
    {
        led_value |= (uint16_t)0x0800;
    }
    else if (their_move == MOVE_PAPER)
    {
        led_value |= (uint16_t)0x0400;
    }
    else if (their_move == MOVE_SCISSORS)
    {
        led_value |= (uint16_t)0x0200;
    }

    write_value(led_value);
}

void led_set_result(Move result)
{
    led_value &= (uint16_t)0xFF0F;

    if (result == MOVE_YOU_WIN)
    {
        led_value |= (uint16_t)0x0080;
    }
    else if (result == MOVE_I_WIN)
    {
        led_value |= (uint16_t)0x0040;
    }
    else if (result == MOVE_TIE)
    {
        led_value |= (uint16_t)0x0010;
    }

    write_value(led_value);
}