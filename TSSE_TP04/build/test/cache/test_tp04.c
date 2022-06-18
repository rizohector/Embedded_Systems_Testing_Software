#include "src/tp04.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
actualMeasurement_t actMeasurement;







void UploadTestCase (int testCase)

{

 switch (testCase)

 {

  case 0:



   {

   actMeasurement.actualTemperature=61;

   actMeasurement.actualHumidity=95;

   actMeasurement.actualVoltage=13.5;

   actMeasurement.actualCurrent=45;

   actMeasurement.stateSystem=1;

   }

   break;



  case 1:



   {

   actMeasurement.actualTemperature=42;

      actMeasurement.actualHumidity=85;

      actMeasurement.actualVoltage=12.3;

      actMeasurement.actualCurrent=16;

   actMeasurement.stateSystem=1;

   }

   break;



  case 2:

   {



   actMeasurement.actualTemperature=52;

      actMeasurement.actualHumidity=98;

      actMeasurement.actualVoltage=14.1;

      actMeasurement.actualCurrent=1.4;

   actMeasurement.stateSystem=1;

   }

   break;



  case 3:

   {



   actMeasurement.actualTemperature=49;

      actMeasurement.actualHumidity=91;

      actMeasurement.actualVoltage=8;

      actMeasurement.actualCurrent=100.1;

   actMeasurement.stateSystem=1;

   }

   break;



  case 4:

   {



   actMeasurement.actualTemperature=60.4;

      actMeasurement.actualHumidity=92;

      actMeasurement.actualVoltage=14.1;

      actMeasurement.actualCurrent=2.5;

   actMeasurement.stateSystem=1;

   }

   break;



  case 5:

   {



   actMeasurement.actualTemperature=59;

      actMeasurement.actualHumidity=84.1;

      actMeasurement.actualVoltage=14.1;

      actMeasurement.actualCurrent=100.1;

   actMeasurement.stateSystem=1;

   }

   break;



  case 6:

   {



   actMeasurement.actualTemperature=60.1;

      actMeasurement.actualHumidity=53.8;

      actMeasurement.actualVoltage=14.1;

      actMeasurement.actualCurrent=100.1;

   actMeasurement.stateSystem=1;

   }

   break;



  case 7:

   {



   actMeasurement.actualTemperature=47.2;

      actMeasurement.actualHumidity=98.3;

      actMeasurement.actualVoltage=12.5;

      actMeasurement.actualCurrent=15;

   actMeasurement.stateSystem=1;

   }

   break;

 }

}







void test_SystemInit (void)

{

    SystemInit (&actMeasurement);



 UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((0))), (UNITY_FLOAT)((UNITY_FLOAT)((actMeasurement.actualTemperature))), ((

((void *)0)

)), (UNITY_UINT)((UNITY_UINT)(117)));

 UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((0))), (UNITY_FLOAT)((UNITY_FLOAT)((actMeasurement.actualHumidity))), ((

((void *)0)

)), (UNITY_UINT)((UNITY_UINT)(118)));

 UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((0))), (UNITY_FLOAT)((UNITY_FLOAT)((actMeasurement.actualVoltage))), ((

((void *)0)

)), (UNITY_UINT)((UNITY_UINT)(119)));

 UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((0))), (UNITY_FLOAT)((UNITY_FLOAT)((actMeasurement.actualCurrent))), ((

((void *)0)

)), (UNITY_UINT)((UNITY_UINT)(120)));

 UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((actMeasurement.stateSystem)), (

((void *)0)

), (UNITY_UINT)(121), UNITY_DISPLAY_STYLE_INT);

}







void test_MaxTempAccum (void)

{

 UploadTestCase (( 0 ));



 if(OverheatedSystem(&actMeasurement))

 {

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((actMeasurement.stateSystem)), (

 ((void *)0)

 ), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_INT);

 }

}







void test_MinHumAccum (void)

{

 UploadTestCase (( 0 ));



 if(Dry_System(&actMeasurement))

 {

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((actMeasurement.stateSystem)), (

 ((void *)0)

 ), (UNITY_UINT)(144), UNITY_DISPLAY_STYLE_INT);

 }

}







void test_MaxVoltAccum (void)

{

 UploadTestCase (( 0 ));



 if(Overvoltage_System(&actMeasurement))

 {

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((actMeasurement.stateSystem)), (

 ((void *)0)

 ), (UNITY_UINT)(156), UNITY_DISPLAY_STYLE_INT);

 }

}







void test_MaxCorrAccum (void)

{

 UploadTestCase (( 0 ));



 if(Overcurrent_System(&actMeasurement))

 {

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((actMeasurement.stateSystem)), (

 ((void *)0)

 ), (UNITY_UINT)(168), UNITY_DISPLAY_STYLE_INT);

 }

}
