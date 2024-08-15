#ifndef _MAX6675_H_
#define _MAX6675_H_

#include "pico/stdlib.h"
#include "hardware/spi.h"

/**
 * @brief Estructura para MAX6675
*/
typedef struct {
    spi_inst_t *spi_bus;
    uint32_t frequency;
    uint8_t so;
    uint8_t sck;
    uint8_t cs;
} max6675_config_t;

// Prototipos de funciones

void max6675_init(max6675_config_t config);
max6675_config_t max6675_get_default_config(void);
float max6675_get_temp_c(void);
float max6675_get_temp_f(void);
float max6675_get_temp_k(void);

#endif
