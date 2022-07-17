#include <stdint.h>
#include <stdbool.h>

// la funcion de ADC estara definida por el hardware final.
// Aqui solo se define la cabecera para que se genere un mock.
// El GPIO/ADC se multiplexa para obtener las 4 mediciones deseadas

uint16_t getADC_value(void);
