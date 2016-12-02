
#include <Servo.h>

Servo myservo; // Tower Pro MicroServo gg - SG90

int nodeMcu_Pin = 5;
bool isLightOn = false;

void setup()
{
  myservo.attach(9); //attachs servo on pin 9
  myservo.write(55); //position to 55 degrees
  delay(1000); //wait for a second

  pinMode(nodeMcu_Pin, INPUT); // Input from nodeMcu
}

void loop()
{
  if(digitalRead(nodeMcu_Pin) && false == isLightOn){
    lightOn();
    isLightOn = true;
    delay(2000);
  }

  if(false == digitalRead(nodeMcu_Pin) && isLightOn){
    lightOff();
    isLightOn = false;
    delay(2000);
  }
}


void lightOn()
{
  myservo.write(90); // in my case 90 degrees
  delay(200); // i have to trigger the switch HARD :D
  myservo.write(55); // and back
}

void lightOff()
{
  myservo.write(10); // here 10 degrees
  delay(200);
  myservo.write(55); // and back
}
