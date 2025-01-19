// Anibal Maldonado: Código Menú  - https://github.com/PhD-Anibal
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/watchdog.h"

#define led_pin_green 11      // porta do pino 11 LED RGB Verde
#define led_pin_blue 12       // porta do pino 12 LED RGB Azul
#define led_pin_red 13        // porta do pino 13 LED RGB Vermelho
#define BUZZER 21             // porta do pino 21 Buzzer


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
    // Inicialização do Buzzer
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);

    // Desligar os LEDs ao iniciar
    //***** codigo  *****

  
    // Inicialização do terminal
    stdio_init_all();

    char buffer[30]; // Buffer para entrada de texto

    // Aguarda até que o terminal esteja conectado
    while (!stdio_usb_connected()) {
        sleep_ms(100); // Aguarda 100ms antes de verificar novamente
    }

    while (true) {
        printf("****** Menu ******\n");
        printf("Escreva: VERMELHO, AZUL, VERDE, BRANCO para Ascender o LED nessa cor\n");
        printf("Escreva: DESLIGAR para desligar os LEDS\n");
        printf("Escreva: SOM para Tocar a nota Lá\n");
        printf("Escreva: REBOOT para habilitar o modo gravação\n");
        scanf("%30s", buffer); // Limitar entrada para evitar overflow
        printf("ESCRITO: %s!\n", buffer);
        sleep_ms(500);    // Debounce

        // Comparação de strings
        if (strcmp(buffer, "VERMELHO") == 0) {
            printf("LIGA VERMELHO\n");
        //***** codigo  *****
        } else if (strcmp(buffer, "AZUL") == 0) {
            printf("LIGA AZUL\n");
        //***** codigo  *****
        } else if (strcmp(buffer, "VERDE") == 0) {
            printf("LIGA VERDE\n");
        //***** codigo  *****
        } else if (strcmp(buffer, "BRANCO") == 0) {
            printf("LIGA BRANCO\n");
            //codigo
        } else if (strcmp(buffer, "DESLIGAR") == 0) {
            printf("DESLIGANDO LEDS\n");
        //***** codigo  *****
        } else if (strcmp(buffer, "SOM") == 0) {
            printf("TOCANDO POR 2 SEGUNDOS\n");
        //***** codigo  *****
        } else if (strcmp(buffer, "REBOOT") == 0) {
            printf("HABILITANDO O MODO DE GRAVAÇÃO\n");
        //***** codigo  *****
        } else {
            printf("Comando não reconhecido. Tente novamente.\n");
        }
    }

    return 0;
}
