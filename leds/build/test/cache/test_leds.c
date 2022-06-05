#include "src/errores.h"
#include "src/leds.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


static uint16_t ledsVirtuales;

static gravedad_t gravedad_informada;









void RegistrarError (gravedad_t gravedad, const char * funcion, int linea, const char * mensaje, ...)

{

    gravedad_informada = gravedad;

}





void setUp (void)

{

    LedsInit(&ledsVirtuales, RegistrarError);

}





void tearDown (void)

{

    gravedad_informada = 0xFFFF;

}







void test_LedsOffAfterCreate (void)

{

   uint16_t ledsVirtuales = 0xFFFF;

   LedsInit(&ledsVirtuales, RegistrarError);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_HEX16);

}









void test_TurnOnOneLed(void)

{

    LedTurnOn(5);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1<<4)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_HEX16);

}









void test_TurnOffOneLed(void)

{

    LedTurnOn(5);

    LedTurnOff(5);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_HEX16);

}









void test_TurnOnAndOffManyLed(void)

{

    LedTurnOn(5);

    LedTurnOn(11);

    LedTurnOff(3);

    LedTurnOff(11);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1<<4)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_HEX16);

}









void test_InvaalidUpperLimitTurnOnLed (void)

{

    LedTurnOn (17);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((ALERTA)), (UNITY_INT)(UNITY_INT16)((gravedad_informada)), (

   ((void *)0)

   ), (UNITY_UINT)(82), UNITY_DISPLAY_STYLE_HEX16);

}









void test_TurnAllOn(void)

{

   LedsAllOn();

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(91), UNITY_DISPLAY_STYLE_HEX16);

}









void test_TurnAllOff(void)

{

   LedsAllOn();

   LedsAllOff();

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(101), UNITY_DISPLAY_STYLE_HEX16);

}









void test_LedStateOff(void)

{

   UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((LedState(4))), (

  ((void *)0)

  ), (UNITY_UINT)(109), UNITY_DISPLAY_STYLE_INT);

}









void test_LedStateOn(void)

{

   LedTurnOn(3);

   UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((LedState(3))), (

  ((void *)0)

  ), (UNITY_UINT)(118), UNITY_DISPLAY_STYLE_INT);

}
