#ifndef _TP04_H // guarda para que si se incluye dos veces el archivo no dé error
#define _TP04_H

//Inclusiones de archivos y librerías
#include <stdint.h>
#include <stdbool.h>
//#include "errores.h"

// Definiciones y macros

#define MAX_TEMP_ACCUM     60  // MAXIMA TEMPERATURA PERMITIDA EN EL ACUMULADOR (en grados centigrados)
#define MIN_HUM_ACCUM      90  // MINIMA HUMEDAD PERMITIDA EN EL ACUMULADOR (en porcentaje)
#define MAX_VOLT_ACCUM     14  // MAXIMA TENSIÓN PERMITIDA EN EL ACUMULADOR (en voltios)
#define MAX_CURRENT_ACCUM 100  // MAXIMA CORRIENTE PERMITIDA EN EL ACUMULADOR (en amperes)
#define STATE_ON            1  // SISTEMA ENCENDIDO
#define STATE_OFF           0  // SISTEMA APAGADO
#define INITIALIZE          0  // INICIALIZA VARIABLES


// Tipos de datos y de funciones
typedef struct 
{
    float actualTemperature;   // TEMPERATURA ACTUAL
    float actualHumidity;      // HUMEDAD ACTUAL
    float actualVoltage;       // TENSIÓN ACTUAL
    float actualCurrent;       // CORRIENTE ACTUAL
    bool stateSystem;          // ESTADO DEL SISTEMA

} actualMeasurement_t;



//Prototipo de funciones

/**
 * @brief CONFIGURA BIBLIOTECA, INICIALIZA TODOS LOS CAMPOS DE LA ESTRUCTURA EN 0 Y ARRANCA EL SISTEMA ENCENDIDO
 * 
 * @param actMeasurement DIRECCION DE LOS PUERTOS GPIO/ADC.
 */
void SystemInit (actualMeasurement_t *actMeasurement);

/**
 * @brief APAGA EL SISTEMA SI SE SOBRECALIENTA EL ACUMULADOR.
 * 
 * @param actMeasurement DIRECCION DE LOS PUERTOS GPIO/ADC.
 * @return true 
 * @return false 
 */
bool OverheatedSystem(actualMeasurement_t * actMeasurement);

/**
 * @brief APAGA EL SISTEMA SI LA HUMEDAD ES ESCASA EN LOS VASOS DEL ACUMULADOR.
 * 
 * @param actMeasurement DIRECCION DE LOS PUERTOS GPIO/ADC.
 * @return true 
 * @return false 
 */
bool Dry_System(actualMeasurement_t *actMeasurement);

/**
 * @brief APAGA EL SISTEMA SI EXISTE UNA SOBRETENSION EN LA CARGA DEL ACUMULADOR
 * 
 * @param actMeasurement DIRECCION DE LOS PUERTOS GPIO/ADC.
 * @return true 
 * @return false 
 */
bool Overvoltage_System(actualMeasurement_t *actMeasurement);

/**
 * @brief APAGA EL ACUMULADOR SI EXISTE UNA SOBRECORRIENTE EN LA CARGA DEL ACUMULADOR
 * 
 * @param actMeasurement 
 * @return true 
 * @return false 
 */
bool Overcurrent_System(actualMeasurement_t *actMeasurement);


#endif