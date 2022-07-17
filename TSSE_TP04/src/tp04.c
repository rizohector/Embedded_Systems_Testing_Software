#include "tp04.h"
#include "hardware.h"


actualMeasurement_t *getADC_Values;
/*
    getADC_Value->actualTemperature     // ESTE CAMPO SE CONECTA AL GPIO/ADC
    getADC_Value->actualHumidity        // ESTE CAMPO SE CONECTA AL GPIO/ADC
    getADC_Value->actualVoltage         // ESTE CAMPO SE CONECTA AL GPIO/ADC
    getADC_Value->actualCurrent         // ESTE CAMPO SE CONECTA AL GPIO/ADC
    getADC_Value->stateSystem=STATE_ON; // ESTE CAMPO SE CONECTA AL GPIO DE SALIDA
*/

void SystemInit (actualMeasurement_t *actMeasurement)
{
    getADC_Values=actMeasurement;
    getADC_Values->actualTemperature=INITIALIZE;   // INICIALIZA TEMPERATURA
    getADC_Values->actualHumidity=INITIALIZE;      // INICIALIZA HUMEDAD
    getADC_Values->actualVoltage=INITIALIZE;       // INICIALIZA TENSIÓN
    getADC_Values->actualCurrent=INITIALIZE;       // INICIALIZA CORRIENTE
    getADC_Values->stateSystem=STATE_ON;           // INICIALIZA ESTADO DEL SISTEMA

}

uint16_t Read_Value(void)
{
    uint16_t rawValue;

    rawValue = getADC_value();
    return rawValue;
}


bool OverheatedSystem(actualMeasurement_t *actMeasurement)
{
    getADC_Values=actMeasurement;

    if ((getADC_Values->actualTemperature) > MAX_TEMP_ACCUM)
    {
        getADC_Values->stateSystem=STATE_OFF;
        return(true);
    }
    else return(false);
}


bool Dry_System(actualMeasurement_t *actMeasurement)
{
     getADC_Values=actMeasurement;

    if ((getADC_Values->actualHumidity) < MIN_HUM_ACCUM)
    {
        getADC_Values->stateSystem=STATE_OFF;
        return(true);
    }
    else return(false);
}



bool Overvoltage_System(actualMeasurement_t *actMeasurement)
{   
    getADC_Values=actMeasurement;
    
    if ((getADC_Values->actualVoltage) > MAX_VOLT_ACCUM)
    {
        getADC_Values->stateSystem=STATE_OFF;
        return(true);
    }
    else return(false);
}



bool Overcurrent_System(actualMeasurement_t *actMeasurement)
{
    getADC_Values=actMeasurement;
    
    if ((actMeasurement->actualCurrent) > MAX_CURRENT_ACCUM)
    {
        actMeasurement->stateSystem=STATE_OFF;
        return(true);
    }
    else return(false);
}