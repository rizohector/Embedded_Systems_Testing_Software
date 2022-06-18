#include "tp04.h"


actualMeasurement_t *getADC_Value;
/*
    getADC_Value->actualTemperature     // ESTE CAMPO SE CONECTA AL GPIO/ADC_0
    getADC_Value->actualHumidity        // ESTE CAMPO SE CONECTA AL GPIO/ADC_1
    getADC_Value->actualVoltage         // ESTE CAMPO SE CONECTA AL GPIO/ADC_2
    getADC_Value->actualCurrent         // ESTE CAMPO SE CONECTA AL GPIO/ADC_3
    getADC_Value->stateSystem=STATE_ON; // ESTE CAMPO SE CONECTA AL GPIO DE SALIDA
*/

void SystemInit (actualMeasurement_t *actMeasurement)
{
    getADC_Value=actMeasurement;
    getADC_Value->actualTemperature=INITIALIZE;   // INICIALIZA TEMPERATURA
    getADC_Value->actualHumidity=INITIALIZE;      // INICIALIZA HUMEDAD
    getADC_Value->actualVoltage=INITIALIZE;       // INICIALIZA TENSIÓN
    getADC_Value->actualCurrent=INITIALIZE;       // INICIALIZA CORRIENTE
    getADC_Value->stateSystem=STATE_ON;           // INICIALIZA ESTADO DEL SISTEMA

}



bool OverheatedSystem(actualMeasurement_t *actMeasurement)
{
    getADC_Value=actMeasurement;

    if ((getADC_Value->actualTemperature) > MAX_TEMP_ACCUM)
    {
        getADC_Value->stateSystem=STATE_OFF;
        return(true);
    }
    else return(false);
}


bool Dry_System(actualMeasurement_t *actMeasurement)
{
     getADC_Value=actMeasurement;

    if ((getADC_Value->actualHumidity) < MIN_HUM_ACCUM)
    {
        getADC_Value->stateSystem=STATE_OFF;
        return(true);
    }
    else return(false);
}



bool Overvoltage_System(actualMeasurement_t *actMeasurement)
{   
    getADC_Value=actMeasurement;
    
    if ((getADC_Value->actualVoltage) > MAX_VOLT_ACCUM)
    {
        getADC_Value->stateSystem=STATE_OFF;
        return(true);
    }
    else return(false);
}



bool Overcurrent_System(actualMeasurement_t *actMeasurement)
{
    getADC_Value=actMeasurement;
    
    if ((actMeasurement->actualCurrent) > MAX_CURRENT_ACCUM)
    {
        actMeasurement->stateSystem=STATE_OFF;
        return(true);
    }
    else return(false);
}