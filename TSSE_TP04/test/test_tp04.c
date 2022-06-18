#include "unity.h"
#include "tp04.h"
//#include "errores.h"

/* MAX_TEMP_ACCUM     60  // MAXIMA TEMPERATURA PERMITIDA EN EL ACUMULADOR (en grados centigrados)
   MAX_HUM_ACCUM      90  // MINIMA HUMEDAD PERMITIDA EN EL ACUMULADOR (en porcentaje)
   MAX_VOLT_ACCUM     14  // MAXIMA TENSIÓN PERMITIDA EN EL ACUMULADOR (en voltios)
   MAX_CURRENT_ACCUM 100  // MAXIMA CORRIENTE PERMITIDA EN EL ACUMULADOR (en amperes)
   STATE_ON            1  // SISTEMA ENCENDIDO
   STATE_OFF           0  // SISTEMA APAGADO
*/

actualMeasurement_t actMeasurement;

#define TEST_CASE_X ( 0 ) // SE ELIJE EL CASO DE PRUEBA DESEADO DEL 0 AL 7 QUE MAS ABAJO SE DETALLA

void UploadTestCase (int testCase)
{
	switch (testCase)
	{
		case 0:
			/* Valores de casos de prueba por sobretemperatura */
			{
			actMeasurement.actualTemperature=61;   // TEMPERATURA DE PRUEBA
			actMeasurement.actualHumidity=95;      // HUMEDAD DE PRUEBA
			actMeasurement.actualVoltage=13.5;     // TENSIÓN DE PRUEBA
			actMeasurement.actualCurrent=45;       // CORRIENTE DE PRUEBA
			actMeasurement.stateSystem=STATE_ON;   // ESTADO DEL SISTEMA ENCENDIDO
			}
			break;

		case 1:
			/* Valores de casos de prueba por baja humedad*/
			{
			actMeasurement.actualTemperature=42;   // TEMPERATURA DE PRUEBA
    		actMeasurement.actualHumidity=85;      // HUMEDAD DE PRUEBA
   			actMeasurement.actualVoltage=12.3;     // TENSIÓN DE PRUEBA
   			actMeasurement.actualCurrent=16;       // CORRIENTE DE PRUEBA
			actMeasurement.stateSystem=STATE_ON;   // ESTADO DEL SISTEMA ENCENDIDO
			}
			break;

		case 2:
			{
			/* Valores de casos de prueba por sobretensión*/
			actMeasurement.actualTemperature=52;   // TEMPERATURA DE PRUEBA
    		actMeasurement.actualHumidity=98;      // HUMEDAD DE PRUEBA
    		actMeasurement.actualVoltage=14.1;     // TENSIÓN DE PRUEBA
    		actMeasurement.actualCurrent=1.4;      // CORRIENTE DE PRUEBA
			actMeasurement.stateSystem=STATE_ON;   // ESTADO DEL SISTEMA ENCENDIDO
			}
			break;

		case 3:
			{
			/* Valores de casos de prueba con sobrecorriente */
			actMeasurement.actualTemperature=49;   // TEMPERATURA DE PRUEBA
    		actMeasurement.actualHumidity=91;      // HUMEDAD DE PRUEBA
    		actMeasurement.actualVoltage=8;        // TENSIÓN DE PRUEBA
    		actMeasurement.actualCurrent=100.1;    // CORRIENTE DE PRUEBA
			actMeasurement.stateSystem=STATE_ON;   // ESTADO DEL SISTEMA ENCENDIDO
			}
			break;

		case 4:
			{
			/* Valores de casos de prueba con dos casos eventos fuera de limites*/
			actMeasurement.actualTemperature=60.4;   // TEMPERATURA DE PRUEBA
    		actMeasurement.actualHumidity=92;        // HUMEDAD DE PRUEBA
    		actMeasurement.actualVoltage=14.1;       // TENSIÓN DE PRUEBA
    		actMeasurement.actualCurrent=2.5;        // CORRIENTE DE PRUEBA
			actMeasurement.stateSystem=STATE_ON;     // ESTADO DEL SISTEMA ENCENDIDO
			}
			break;

		case 5:
			{
			// Valores de casos de prueba con tres eventos fuera de limite //
			actMeasurement.actualTemperature=59;     // TEMPERATURA DE PRUEBA
    		actMeasurement.actualHumidity=84.1;      // HUMEDAD DE PRUEBA
    		actMeasurement.actualVoltage=14.1;       // TENSIÓN DE PRUEBA
    		actMeasurement.actualCurrent=100.1;      // CORRIENTE DE PRUEBA
			actMeasurement.stateSystem=STATE_ON;     // ESTADO DEL SISTEMA ENCENDIDO
			}
			break;

		case 6:
			{
			// Valores de casos de prueba con cuatro eventos fuera de limite//
			actMeasurement.actualTemperature=60.1;   // TEMPERATURA DE PRUEBA
    		actMeasurement.actualHumidity=53.8;      // HUMEDAD DE PRUEBA
    		actMeasurement.actualVoltage=14.1;       // TENSIÓN DE PRUEBA
    		actMeasurement.actualCurrent=100.1;      // CORRIENTE DE PRUEBA
			actMeasurement.stateSystem=STATE_ON;     // ESTADO DEL SISTEMA ENCENDIDO
			}
			break;

		case 7:
			{
			// Valores de casos de prueba con eventos dentro de los limites//
			actMeasurement.actualTemperature=47.2;   // TEMPERATURA DE PRUEBA
    		actMeasurement.actualHumidity=98.3;      // HUMEDAD DE PRUEBA
    		actMeasurement.actualVoltage=12.5;       // TENSIÓN DE PRUEBA
    		actMeasurement.actualCurrent=15;         // CORRIENTE DE PRUEBA
			actMeasurement.stateSystem=STATE_ON;     // ESTADO DEL SISTEMA ENCENDIDO
			}
			break;
	}
}

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
// El sensor de temperatura genera dato valido entre -10 a 80 C.
void test_MaxTempAccum (void)
{
	UploadTestCase (TEST_CASE_X);

	if(OverheatedSystem(&actMeasurement))
	{
		TEST_ASSERT_EQUAL(STATE_OFF,actMeasurement.stateSystem);        
	}
}

// Sistema de control mide la humedad en el acumulador y saca de servicio el SMCBAE cuando sea inferior al 90ºC.
// El sensor de humedad genera dato valido entre 0% a 100%.
void test_MinHumAccum (void)
{
	UploadTestCase (TEST_CASE_X);

	if(Dry_System(&actMeasurement))
	{
		TEST_ASSERT_EQUAL(STATE_OFF,actMeasurement.stateSystem);         
	}
}

// Sistema de control mide la tensión en el acumulador y saca de servicio el SMCBAE cuando sea superior a 14 V.
// Se medirá entre un rango de 0 V a 15 V.
void test_MaxVoltAccum (void)
{
	UploadTestCase (TEST_CASE_X);

	if(Overvoltage_System(&actMeasurement))
	{
		TEST_ASSERT_EQUAL(STATE_OFF,actMeasurement.stateSystem);        
	}
}

// Sistema de control mide la corriente eléctrica en el acumulador y saca de servicio el SMCBAE cuando sea superior a 100 A.
// Se medirá entre un rango de 0 A a 120 A.
void test_MaxCorrAccum (void)
{
	UploadTestCase (TEST_CASE_X);

	if(Overcurrent_System(&actMeasurement))
	{
		TEST_ASSERT_EQUAL(STATE_OFF,actMeasurement.stateSystem);         
	}
}