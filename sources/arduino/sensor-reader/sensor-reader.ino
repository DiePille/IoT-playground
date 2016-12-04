// Sensor-Typ: DHT11
#include <SimpleDHT.h>

// Sensor-Typ: HC-SRO4 Sensor
#include <NewPing.h>

#include <pitches.h>

#define TRIGGER_PIN  12  // trigger pin
#define ECHO_PIN     11  // echo pin
#define MAX_DISTANCE 500 // Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int tempPin = 0;


// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11;


// Sensor-Typ: HC-SR501 PIR

int PIR_ledPin = 6;                // choose the pin for the LED
int PIR_inputPin = 7;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int pirVal = 0;                    // variable for reading the pin status


// notes in the melody:
//int melody[] = {
//  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};

int init_melody[] = {NOTE_B5, NOTE_B5};
int duration = 200; 
int buzzer_pin = 8; 



void setup() {

  pinMode(PIR_ledPin, OUTPUT); // PIR motion detect LED
  pinMode(PIR_inputPin, INPUT);     // declare PIR sensor as input

  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(buzzer_pin, init_melody[thisNote], duration);
     
    // Output the voice after several minutes
    delay(500);
  }
}

void loop() 
{
  
  for(int i=0; i < 10; i++)
  {
    detectMotion(); //no delay
    
    readTemp(); //no delay
    delay(50);
  }
  
  //tone(buzzer_pin, NOTE_C6, duration);
  
  //delay(500);
  
  readTempHumi(); //no delay
  pingSonar();
  
}

void detectMotion()
{
  pirVal = digitalRead(PIR_inputPin);  // read input value
  if (pirVal == HIGH) {            // check if the input is HIGH
    digitalWrite(PIR_ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(PIR_ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}



void readTempHumi()
{
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    Serial.print("Read DHT11 failed");
    tone(buzzer_pin, NOTE_D6, duration);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" %");
}

void readTemp()
{
  // Display Temperature in C
  int tempReading = analogRead(tempPin);
  
  float tempVolts = tempReading * 5.0 / 1024.0;
  float tempC = (tempVolts - 0.5) * 10.0;
  //float tempC = (tempVolts - 0.5) / 10.0;
  float tempF = tempC * 9.0 / 5.0 + 32.0;

  if(tempC < 12.0 )
  {
    tone(buzzer_pin, NOTE_C6, 200);
    delay(1000);
  }

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" C / ");
  Serial.print(tempF);
  Serial.println(" F");
}

void pingSonar()
{
  //delay(500);  // Wait 500ms between pings (about 2 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");
}

