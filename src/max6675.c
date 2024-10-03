#include "max6675.h"

// Configuracion de MAX6675
max6675_config_t max6675_config = {0};

/**
 * @brief Inicializa el SPI para el MAX6675
 * @param config configuracion del MAX6675
 */
void max6675_init(max6675_config_t config) {
    // Guarda los datos de configuracion
    max6675_config = config;
    // Inicializa SPI
    spi_init(max6675_config.spi_bus, max6675_config.frequency);
    // Inicializa GPIOs
    gpio_set_function(max6675_config.sck, GPIO_FUNC_SPI);
    gpio_set_function(max6675_config.so, GPIO_FUNC_SPI);

    gpio_init(max6675_config.cs);
    gpio_set_dir(max6675_config.cs, GPIO_OUT);
}

/**
 * @brief Devuelve configuracion por defecto para el MAX6675
 * @return estructura de configuracion con SPI0, 4MHz, 
 * SCK = 18, RX = 16, CS = 17
 */
max6675_config_t max6675_get_default_config(void) {

    return (max6675_config_t) {
        .spi_bus = spi0,
        .frequency = 4000000,
        .sck = PICO_DEFAULT_SPI_SCK_PIN,
        .so = PICO_DEFAULT_SPI_RX_PIN,
        .cs = PICO_DEFAULT_SPI_CSN_PIN
    };
}

/**
 * @brief Pone el CS en low
 */
static void spi_cs_low(void) {
    asm volatile("nop \n nop \n nop");
    gpio_put(max6675_config.cs, false);
    asm volatile("nop \n nop \n nop");
}

/**
 * @brief Pone el CS en high
 */
static void spi_cs_high(void) {
    asm volatile("nop \n nop \n nop");
    gpio_put(max6675_config.cs, true);
    asm volatile("nop \n nop \n nop");
}

/**
 * @brief Hace una lectura de temperatura
 * @return temperatura en C
 */
static float max6675_get_temp(void) {
    // Buffer para leer
	uint8_t buffer[2] = {0};
    // Tiro abajo CS
    spi_cs_low();
    // Hace una lectura del bus
    spi_read_blocking(max6675_config.spi_bus, 0, buffer, 2);
    // Deshabilito CS
    spi_cs_high();
    // Armo los 16 bits
	uint16_t reading = (buffer[0] << 8) + buffer[1];
    // Los primeros tres bits no sirven
	reading >>= 3;
    // Devuelvo temperatura
	return reading * 0.25;
}

/**
 * @brief Obtiene la temperatura de la termocupla
 * @return temperatura en C
 */
float max6675_get_temp_c(void) {
    return max6675_get_temp();
}

/**
 * @brief Obtiene la temperatura de la termocupla
 * @return temperatura en K
 */
float max6675_get_temp_k(void) {
	return max6675_get_temp() + 273.15;
}

/**
 * @brief Obtiene la temperatura de la termocupla
 * @return temperatura en F
 */
float max6675_get_temp_f(void) {
	return (max6675_get_temp() * 1.8) + 32.0;
}
