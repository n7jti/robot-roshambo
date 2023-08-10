#pragma once

// (C) Alan Ludwig, All rights reserved

constexpr int data_pin = 6;
constexpr int clock_pin = 7;
constexpr int latch_pin = 8;
constexpr int oe_pin = 9;
constexpr int CLOCK_DELAY_US = 5;

void init_led();
void led_clear();
void led_set_my_move(Move my_move);
void led_set_their_move(Move their_move);
void led_set_result(Move result);
