#include <stdio.h>
#include "pico/stdlib.h"

#include "max6675.h"

/**
 * @brief Programa principal
 */
int main(void) {  
    // Inicializacion de USB
    stdio_init_all();
    // Inicializo SPI para el MAX6675
    max6675_init(max6675_get_default_config());

    while (true) {
        // Leo temperatura y muestro
        printf("La temperatura es %.2f\n", max6675_get_temp_c());
        sleep_ms(500);
    }
}
