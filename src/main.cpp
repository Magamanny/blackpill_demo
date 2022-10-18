#include <Arduino.h>
#include <STM32FreeRTOS.h>
//#include "tomcrypt.h"
// TX = PA9
// RX = PA10
static portTASK_FUNCTION_PROTO(vTest, pvParameters);
static portTASK_FUNCTION_PROTO(vEcho, pvParameters);
void vTestTaskCreate()
{
  xTaskCreate(vTest,
              "TestTask",
              configMINIMAL_STACK_SIZE,
              NULL,
              tskIDLE_PRIORITY,
              NULL);
}
void vEchoTaskCreate()
{
  xTaskCreate(vEcho,
              "EchoTask",
              configMINIMAL_STACK_SIZE,
              NULL,
              tskIDLE_PRIORITY,
              NULL);
}
// Working ok
void setup()
{
  Serial.begin(115200, SERIAL_8E1);
  vTestTaskCreate();
  vEchoTaskCreate();
  pinMode(LED_BUILTIN, OUTPUT);
  // put your setup code here, to run once:
  //printf("Hello printf, used by littlefs, minimium stack %d", configMINIMAL_STACK_SIZE);
  vTaskStartScheduler();
}

void loop()
{
}
static portTASK_FUNCTION(vEcho, pvParameters)
{
  for (;;)
  {
    if (Serial.available())
    {
      Serial.write(Serial.read());
    }
  }
}
static portTASK_FUNCTION(vTest, pvParameters)
{
  for (;;)
  {
    Serial.println("Hello Serial 1");
    // put your main code here, to run repeatedly:
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}
// Full assert
void assert_failed(uint8_t *file, uint32_t line)
{
	printf("----------------\r\n");
	printf("assertion failed: %s %d \r\n", file, line);
	printf("----------------\r\n");
	while (1)
	{
		;
	}
}