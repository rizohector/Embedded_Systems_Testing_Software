# Embedded_Systems_Testing_Software
Driver de LEDs: Requisitos
• Maneja 16 leds de dos estados (encendido y apagado).
• Se puede cambiar el estado de un led sin afectar a los otros.
• Se puede cambiar el estado de todos los led’s en una sola
operación.
• Se puede recuperar el estado actual de un led.
• Los led’s están mapeados en una palabra de 16 bits en
memoria en una dirección a determinar.
• Para encender el led se debe escribir un “1” en el bit y para
apagarlo se debe escribir un “0”.
• El led 1 corresponde al lsb y el led 16 al msb.
• El reset de hardware no define un estado conocido de los
led’s, estos deben ser apagados por software.


Driver de LEDs : Test
• Después de la inicialización todos los LEDs
deben quedar apagados.
• Se puede prender un LED individual.
• Se puede apagar un LED individual.
• Se pueden prender y apagar múltiples LED’s.
• Se pueden prender todos los LEDs de una vez.
• Se pueden apagar todos los LEDs de una vez.
• Se puede consultar el estado de un LED.
• Revisar limites de los parametros.
• Revisar parámetros fuera de los limites.

Resumen
• Debemos escribir un test
• Debemos asegurarnos de que primero falle.
• Ahora debemos escribir la cantidad mínima de
código para resolver el problema.
• No caer en la tentación de escribir código de más.
• El limite entre lo que “me hace falta” y lo que podría servir lo
marca el test que escribí al inicio
• Y ahora repetimos el ciclo indefinidamente hasta
cubrir todos los requerimientos
• En un futuro con nuevos requerimientos el proceso es idéntico.
• El código obtenido es el más simple posible.
• Y por lo tanto el más robusto
