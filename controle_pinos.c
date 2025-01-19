// Anibal Maldonado: Código Menú  - https://github.com/PhD-Anibal
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
// Thiago Sousa: Reboot para bootloader - https://github.com/ThiagoSousa81
#include "pico/bootrom.h"
#include "hardware/watchdog.h"
#include "hardware/pwm.h"

#define led_pin_green 11      // porta do pino 11 LED RGB Verde
#define led_pin_blue 12       // porta do pino 12 LED RGB Azul
#define led_pin_red 13        // porta do pino 13 LED RGB Vermelho
#define BUZZER 21             // porta do pino 21 Buzzer

void init_pwm(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM); // Configura o GPIO como PWM
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_clkdiv(slice_num, 125.0f);     // Define o divisor do clock para 1 MHz
    pwm_set_wrap(slice_num, 1000);        // Define o TOP para frequência de 1 kHz
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), 0); // Razão cíclica inicial
    pwm_set_enabled(slice_num, true);     // Habilita o PWM
}

void set_buzzer_tone(uint gpio, uint freq) {
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint top = 1000000 / freq;            // Calcula o TOP para a frequência desejada
    pwm_set_wrap(slice_num, top);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), top / 2); // 50% duty cycle
}

void stop_buzzer(uint gpio) {
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), 0); // Desliga o PWM
}


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
    // Inicialização do RGB
    inicializaRGB();
    // Inicialização do Buzzer
    init_pwm(BUZZER);  // Inicializa o buzzer com PWM

  
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
            acendeRGB(1, 0, 0);
        } else if (strcmp(buffer, "AZUL") == 0) {
            printf("LIGA AZUL\n");
            acendeRGB(0, 0, 1);
        } else if (strcmp(buffer, "VERDE") == 0) {
            printf("LIGA VERDE\n");
            acendeRGB(0, 1, 0);
        } else if (strcmp(buffer, "BRANCO") == 0) {
            printf("LIGA BRANCO\n");
            acendeRGB(1, 1, 1);
        } else if (strcmp(buffer, "DESLIGAR") == 0) {
            printf("DESLIGANDO LEDS\n");
            acendeRGB(0, 0, 0);
        } else if (strcmp(buffer, "SOM") == 0) {
            printf("TOCANDO POR 2 SEGUNDOS\n");
            set_buzzer_tone(BUZZER, 440); // Frequência 440 Hz (Nota Lá)
                sleep_ms(2000);
                stop_buzzer(BUZZER);
        } else if (strcmp(buffer, "REBOOT") == 0) {            
            printf("HABILITANDO O MODO DE GRAVAÇÃO\n");
            watchdog_reboot(0, 0, 0);
            /* Códigos para bootsel
            // Habilita o modo de gravação
            printf("Em 3 ");
            sleep_ms(1000);
            printf("2 ");
            sleep_ms(1000);
            printf("1...");
            sleep_ms(1000);
            // Desabilita o Watchdog, se estiver ativado
            watchdog_enable(0, 1);
            // Escreve a sequência mágica no endereço especial
            reset_usb_boot(0, 0);*/            

        } else {
            printf("Comando não reconhecido. Tente novamente.\n");
        }
    }

    return 0;
}
