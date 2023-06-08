// (C) Alan Ludwig, All rights reserved

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "uart.h"

#define UART_ID uart1

constexpr uart_parity_t PARITY = UART_PARITY_NONE; 
constexpr uint DATA_BITS = 8;
constexpr uint STOP_BITS = 1;
constexpr uint BAUD_RATE = 115200;
constexpr uint UART_TX_PIN = 4;
constexpr uint UART_RX_PIN = 5;

static int characters_received = 0;

// Forward Declarations.  Only needed for our internal functions. Public
// functions should be declared in the public header. 
void on_uart_rx(); 

void setup_uart()
{
    // Set up our UART with the required speed.
    uart_init(UART_ID, BAUD_RATE);

     // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(UART_ID, false, false);

    // Set our data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(UART_ID, false);

    // Set up a RX interrupt
    // We need to set up the handler first
    // Select correct interrupt for the UART we are using
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);

    // Now enable the UART to send interrupts - RX only
    uart_set_irq_enables(UART_ID, true, false);

    // OK, all set up.
    // Lets send a basic string out, and then run a loop and wait for RX interrupts
    // The handler will count them, but also reflect the incoming data back with a slight change!
    uart_puts(UART_ID, "\nHello, uart interrupts\n");

}

// RX interrupt handler
void on_uart_rx() {
    while (uart_is_readable(UART_ID)) {
        uint8_t ch = uart_getc(UART_ID);
        // Can we send it back?
        if (uart_is_writable(UART_ID)) {
            // Change it slightly first!
            ch++;
            uart_putc(UART_ID, ch);
        }
        characters_received++;
    }
}