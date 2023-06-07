// (C) Alan Ludwig All rights reserved

#include <stdio.h>
#include "pico/stdlib.h"

// constants
constexpr uint LED_PIN = PICO_DEFAULT_LED_PIN;

// All setup goes here 
void setup(){
    // Standard Pico
    setup_default_uart();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    return;
}


// This loop function will be called forever
void loop(){
    gpio_put(LED_PIN, 1);
    printf("Hello, world!\n");
    sleep_ms(250);
    gpio_put(LED_PIN, 0);
    sleep_ms(250);
    return; 
}


// Use a super loop pattern 
int main() {
    setup();
    while (true) {
        loop(); 
    }

}