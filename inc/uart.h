#pragma once

// (C) Alan Ludwig, All rights reserved

// uart functions

constexpr uart_parity_t PARITY = UART_PARITY_NONE; 
constexpr uint DATA_BITS = 8;
constexpr uint STOP_BITS = 1;
constexpr uint BAUD_RATE = 115200;
constexpr uint UART_TX_PIN = 4;
constexpr uint UART_RX_PIN = 5;

// our Game UART
#define UART_ID uart1

void setup_uart();