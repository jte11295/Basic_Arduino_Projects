#include <HCSR04.h> // Driver Library for Hypersonic Sensor - see included folder for author and copyrights, etc.


int trigger_pin = 13;
int echo_pin = 12;
int led = 9;
int led_fade_value = 0;
UltraSonicDistanceSensor distanceSensor(trigger_pin, echo_pin);  // Initialize sensor that uses digital pins 13 and 12.

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
    pinMode(led, OUTPUT);
}

void loop () {

    double distance_in_cm = distanceSensor.measureDistanceCm();
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    //Serial.println(distance_in_cm);

    // Do fading function on LED based on measured distance
    // Need to scale value and round to nearest int
    // LED valid values (0-255; PWM duty cycle) and the HC-SR04 (2cm to 400 cm)

    //TODO: It would be nice to add a low pass filter to smooth some of the transistions and filter out noise
    
    if (distance_in_cm == -1.0)
    {
      led_fade_value = 0;
    }
    else
    {
      led_fade_value = (((distance_in_cm - 2) * 255) / 50);
      Serial.println(led_fade_value);
    }
    analogWrite(led, led_fade_value);
    
    delay(100);
}
