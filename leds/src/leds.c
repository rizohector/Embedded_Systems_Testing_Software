#include "leds.h"

//Definiciones y macros
#define LED_TO_BIT_OFFSET  1
#define BIT_MASK           1
#define LEDS_ALL_OFF       0x0000
#define LEDS_ALL_ON        0xFFFF
#define LSB                1
#define LED_OFF            0
#define LED_ON             1

//Definición de variables privadas
static uint16_t *puerto;
static uint16_t state;
static registro_errores_t RegistroErrores;


//Definición de funciones

static void LedsHardwareUpdate(void) {
   *puerto = state;
}

uint16_t Led_To_Mask (uint8_t led)
{
    return (BIT_MASK << (led - LED_TO_BIT_OFFSET));
}


void LedsInit(uint16_t *direccion, registro_errores_t FuncionRegistro)
{
    puerto = direccion;
    RegistroErrores = FuncionRegistro;
    *puerto = LEDS_ALL_OFF;
}


void LedTurnOn(uint8_t led)
{
    if (led>16) { RegistroErrores (ALERTA, __FUNCTION__,__LINE__, "Numero de led invalido");}
    else        {*puerto |= Led_To_Mask(led);} //con 1<<4 pasa
}


void LedTurnOff(uint8_t led)
{
    *puerto &= ~Led_To_Mask(led);
}



void LedsAllOff(void)
{
   state = LEDS_ALL_OFF;
   LedsHardwareUpdate();   
};



void LedsAllOn(void)
{
   state = LEDS_ALL_ON;
   LedsHardwareUpdate();   
}



bool LedState(uint8_t led)
{
    if(*puerto == (LSB << (led-LED_TO_BIT_OFFSET)))
    {
        return LED_ON;
    }
    else
    {
        return LED_OFF;
    }
}