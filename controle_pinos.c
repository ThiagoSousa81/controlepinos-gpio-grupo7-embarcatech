#include <stdio.h>
#include "pico/stdlib.h"

#define led_pin_green 11
#define led_pin_blue 12
#define led_pin_red 13


void inicializaRGB(){
    gpio_init(led_pin_red);
    gpio_init(led_pin_green);
    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_red, GPIO_OUT);
    gpio_set_dir(led_pin_green, GPIO_OUT);
    gpio_set_dir(led_pin_blue, GPIO_OUT);
}

void acendeRGB(int r, int g, int b){
    // Desliga todos os leds
    gpio_put(led_pin_red, 0);
    gpio_put(led_pin_green, 0);
    gpio_put(led_pin_blue, 0);

    // Acende os leds de acordo com os valores passados
    gpio_put(led_pin_red, r);
    gpio_put(led_pin_green, g);
    gpio_put(led_pin_blue, b);
}


int main()
{
    inicializaRGB();
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
