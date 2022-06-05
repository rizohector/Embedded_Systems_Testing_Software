
#include "unity.h"
#include "leds.h"
#include "errores.h"

//Definiciones y macros
#define LEDS_ALL_OFF    0x0000
#define LEDS_ALL_ON     0xFFFF
#define LED_OFF         0
#define LED_ON          1

//Variables globales
static uint16_t ledsVirtuales;
static gravedad_t gravedad_informada;


//Definición de funciones

void RegistrarError (gravedad_t gravedad, const char * funcion, int linea, const char * mensaje, ...) //Registrarerror es un puntero a la función
{
    gravedad_informada = gravedad;
}


void setUp (void) //esto se ejecutará antes de cada prueba
{
    LedsInit(&ledsVirtuales, RegistrarError);
}


void tearDown (void) // se ejecutará al final de cada prueba, en este caso no será necesaria
{
    gravedad_informada = 0xFFFF;
}


//• Después de la inicialización todos los LEDs deben quedar apagados.
void test_LedsOffAfterCreate (void)
{
   uint16_t ledsVirtuales = 0xFFFF; // declaramos una variable de 16 bits al ser el puerto virtual de 16 bits
   LedsInit(&ledsVirtuales, RegistrarError);
   TEST_ASSERT_EQUAL_HEX16(0x0000,ledsVirtuales);
}



//• Se puede prender un LED individual.
void test_TurnOnOneLed(void)
{
    LedTurnOn(5); //Prendo led 5
    TEST_ASSERT_EQUAL_HEX16(1<<4,ledsVirtuales); //0x10 es igual a 1<<4
}



//• Se puede apagar un LED individual.
void test_TurnOffOneLed(void)
{
    LedTurnOn(5);
    LedTurnOff(5); //Apago led 5
    TEST_ASSERT_EQUAL_HEX16(0x0000,ledsVirtuales); //0x20 es igaul a 1<<5
}



//• Se pueden prender y apagar múltiples LED’s.
void test_TurnOnAndOffManyLed(void)
{
    LedTurnOn(5);
    LedTurnOn(11);
    LedTurnOff(3);
    LedTurnOff(11);
    TEST_ASSERT_EQUAL_HEX16(1<<4,ledsVirtuales); //0x10 es igual a 1<<4
}



//• Revisar parámetros fuera de los limites.
void test_InvaalidUpperLimitTurnOnLed (void)
{
    LedTurnOn (17);
    TEST_ASSERT_EQUAL_HEX16(ALERTA, gravedad_informada);
}



//• Se pueden prender todos los LEDs de una vez.
void test_TurnAllOn(void)
{
   LedsAllOn();
   TEST_ASSERT_EQUAL_HEX16(LEDS_ALL_ON, ledsVirtuales);   
}



//• Se pueden apagar todos los LEDs de una vez.
void test_TurnAllOff(void)
{
   LedsAllOn();
   LedsAllOff();
   TEST_ASSERT_EQUAL_HEX16(LEDS_ALL_OFF, ledsVirtuales);
}



//• Se puede consultar el estado de un LED apagado.
void test_LedStateOff(void)
{
   TEST_ASSERT_EQUAL(LED_OFF, LedState(4));
}



//• Se puede consultar el estado de un LED prendido.
void test_LedStateOn(void)
{
   LedTurnOn(3);
   TEST_ASSERT_EQUAL(LED_ON, LedState(3));
}