#ifndef _LEDS_H // guarda para que si se incluye dos veces el archivo no dé error
#define _LEDS_H

//Inclusiones de archivos y librerías
#include <stdint.h>
#include <stdbool.h>
#include "errores.h"

//Tipos de datos y de funciones
uint16_t Led_To_Mask (uint8_t led);

//Prototipo de funciones

/**
 * @brief Configura biblioteca y apaga todos los leds.
 * 
 * @param direccion Dirección del puerto GPIO que controla los leds.
 */
void LedsInit(uint16_t *direccion, registro_errores_t FuncionRegistro); // lo ultimo es un puntero a una función


/**
 * @brief Prende un led.
 * 
 * @param led Numero de led a prender (1 al 16).
 */
void LedTurnOn (uint8_t led); //con uint8_t nos alcanza para contaar hasta 16


/**
 * @brief Apaga un led.
 * 
 * @param led Numero de led a apagar (1 al 16).
 */
void LedTurnOff (uint8_t led);


/**
 * @brief Función para modicar todos los leds a la vez
 * 
 */
static void LedsHardwareUpdate(void);


/**
 * @brief Funcion para prender todos los leds
 * 
 */
void LedsAllOn(void);


/**
 * @brief Funcion para apagar todos los leds
 * 
 */
void LedsAllOff(void);


/**
 * @brief Funcion para leer el estado de un led
 * 
 * @param led Numero de led para leer estado (1 al 16)
 * @return true 
 * @return false 
 */
bool LedState(uint8_t led);

#endif