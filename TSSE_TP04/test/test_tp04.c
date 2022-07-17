#include "unity.h"
#include "tp04.h"
#include "mock_hardware.h"

/* MAX_TEMP_ACCUM     60  // MAXIMA TEMPERATURA PERMITIDA EN EL ACUMULADOR (en grados centigrados)
   MAX_HUM_ACCUM      90  // MINIMA HUMEDAD PERMITIDA EN EL ACUMULADOR (en porcentaje)
   MAX_VOLT_ACCUM     14  // MAXIMA TENSIÓN PERMITIDA EN EL ACUMULADOR (en voltios)
   MAX_CURRENT_ACCUM 100  // MAXIMA CORRIENTE PERMITIDA EN EL ACUMULADOR (en amperes)
   STATE_ON            1  // SISTEMA ENCENDIDO
   STATE_OFF           0  // SISTEMA APAGADO
*/

actualMeasurement_t actMeasurement;

// El sistema debe inicializar encendido para la realización de las pruebas.
// El sistema debe inicializar con las variables en 0.
void test_SystemInit (void)
{
    SystemInit (&actMeasurement);

	TEST_ASSERT_EQUAL_FLOAT(INITIALIZE,actMeasurement.actualTemperature);
	TEST_ASSERT_EQUAL_FLOAT(INITIALIZE,actMeasurement.actualHumidity);
	TEST_ASSERT_EQUAL_FLOAT(INITIALIZE,actMeasurement.actualVoltage);
	TEST_ASSERT_EQUAL_FLOAT(INITIALIZE,actMeasurement.actualCurrent);
	TEST_ASSERT_EQUAL(STATE_ON,actMeasurement.stateSystem);
}

// Sistema de control mide la temperatura en el acumulador y saca de servicio el SMCBAE cuando supere los 60ºC.
// La prueba se realizará con una temperatura de 61.
// El sensor de temperatura genera dato valido entre -10 a 80 C.
void test_MaxTempAccum (void)
{
	actMeasurement.stateSystem=STATE_ON;	//Recordar que el sistema debe estar encendido para las pruebas.
	getADC_value_ExpectAndReturn(61);
	actMeasurement.actualTemperature= (float)Read_Value();
	TEST_ASSERT_EQUAL(ACTIVE_FUNCTION,OverheatedSystem(&actMeasurement));
	TEST_ASSERT_EQUAL(STATE_OFF,actMeasurement.stateSystem);
}

// Sistema de control mide la temperatura en el acumulador y continua en servicio el SMCBAE sino se supera los 60ºC.
// La prueba se realizará con una temperatura de 59.
// El sensor de temperatura genera dato valido entre -10 a 80 C.
void test_NormalTempAccum (void)
{
	actMeasurement.stateSystem=STATE_OFF;
	actMeasurement.stateSystem=STATE_ON;	//Recordar que el sistema debe estar encendido para las pruebas.
	getADC_value_ExpectAndReturn(59);
	actMeasurement.actualTemperature= (float)Read_Value();
	TEST_ASSERT_EQUAL(OFF_FUNCTION,OverheatedSystem(&actMeasurement));
	TEST_ASSERT_EQUAL(STATE_ON,actMeasurement.stateSystem);
}

// Sistema de control mide la humedad en el acumulador y saca de servicio el SMCBAE cuando sea inferior al 90ºC.
// La prueba se realizará con una humedad de 89%.
// El sensor de humedad genera dato valido entre 0% a 100%.
void test_MinHumAccum (void)
{
	getADC_value_ExpectAndReturn(89);
	actMeasurement.actualHumidity= (float)Read_Value();
	TEST_ASSERT_EQUAL(ACTIVE_FUNCTION,Dry_System(&actMeasurement));
	TEST_ASSERT_EQUAL(STATE_OFF,actMeasurement.stateSystem); 
}

// Sistema de control mide la humedad en el acumulador y continua en servicio el SMCBAE cuando sea superior o igual a 90%.
// La prueba se realizará con una humedad de 91%.
// El sensor de humedad genera dato valido entre 0% a 100%.
void test_NormalHumAccum (void)
{
	actMeasurement.stateSystem=STATE_OFF;
	actMeasurement.stateSystem=STATE_ON;	//Recordar que el sistema debe estar encendido para las pruebas.
	getADC_value_ExpectAndReturn(91);
	actMeasurement.actualHumidity= (float)Read_Value();
	TEST_ASSERT_EQUAL(OFF_FUNCTION,Dry_System(&actMeasurement));
	TEST_ASSERT_EQUAL(STATE_ON,actMeasurement.stateSystem); 
}

// Sistema de control mide la tensión en el acumulador y saca de servicio el SMCBAE cuando sea superior a 14 V.
// La prueba se realizará con una tensión de 15V.
// Se medirá entre un rango de 0 V a 15 V.
void test_MaxVoltAccum (void)
{
	actMeasurement.stateSystem=STATE_ON;	//Recordar que el sistema debe estar encendido para las pruebas.
	getADC_value_ExpectAndReturn(15);
	actMeasurement.actualVoltage= (float)Read_Value();
	TEST_ASSERT_EQUAL(ACTIVE_FUNCTION,Overvoltage_System(&actMeasurement));
	TEST_ASSERT_EQUAL(STATE_OFF,actMeasurement.stateSystem);        

}

// Sistema de control mide la tensión en el acumulador y continua en servicio el SMCBAE cuando sea menor o igual a 14 V.
// La prueba se realizará con una tensión de 13,9V.
// Se medirá entre un rango de 0 V a 15 V.
void test_NormalVoltAccum (void)
{
	actMeasurement.stateSystem=STATE_OFF;
	actMeasurement.stateSystem=STATE_ON;	//Recordar que el sistema debe estar encendido para las pruebas.
	getADC_value_ExpectAndReturn(13.9);
	actMeasurement.actualVoltage= (float)Read_Value();
	TEST_ASSERT_EQUAL(OFF_FUNCTION,Overvoltage_System(&actMeasurement));
	TEST_ASSERT_EQUAL(STATE_ON,actMeasurement.stateSystem);        

}

// Sistema de control mide la corriente eléctrica en el acumulador y saca de servicio el SMCBAE cuando sea superior a 100 A.
// La prueba se realizará con una corriente eléctrica de 101V.
// Se medirá entre un rango de 0 A a 120 A.
void test_MaxCorrAccum (void)
{
	actMeasurement.stateSystem=STATE_ON;	//Recordar que el sistema debe estar encendido para las pruebas.
	getADC_value_ExpectAndReturn(101);
	actMeasurement.actualCurrent= (float)Read_Value();
	TEST_ASSERT_EQUAL(ACTIVE_FUNCTION,Overcurrent_System(&actMeasurement));
	TEST_ASSERT_EQUAL(STATE_OFF,actMeasurement.stateSystem); 
}


// Sistema de control mide la corriente eléctrica en el acumulador y continua en servicio el SMCBAE cuando sea inferior o igual a 100 A.
// La prueba se realizará con una corriente eléctrica de 101V.
// Se medirá entre un rango de 0 A a 120 A.
void test_NormalCorrAccum (void)
{
	actMeasurement.stateSystem=STATE_OFF;
	actMeasurement.stateSystem=STATE_ON;	//Recordar que el sistema debe estar encendido para las pruebas.
	getADC_value_ExpectAndReturn(99);
	actMeasurement.actualCurrent= (float)Read_Value();
	TEST_ASSERT_EQUAL(OFF_FUNCTION,Overcurrent_System(&actMeasurement));
	TEST_ASSERT_EQUAL(STATE_ON,actMeasurement.stateSystem); 
}