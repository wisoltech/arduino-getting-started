#include <Arduino.h>

// LED connected to digital pin 13
const int led_pin =  13;
// Blink interval in milliseconds
const unsigned long interval = 1000;

unsigned long prev_time = 0;
int led_state = LOW;

void setup()   {                
  // Initialize the digital pin as an output:
  pinMode(led_pin, OUTPUT);
}

void loop()                     
{
	const unsigned long cur_time = millis();

	if(cur_time - prev_time > interval)
	{
		prev_time = cur_time;
		led_state = led_state == LOW ? HIGH : LOW;
		// Write output
		digitalWrite(led_pin, led_state);
	}
}

