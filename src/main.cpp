#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
byte BTData;

// GPIOs DC motor
int DCmotorInput1 = 26;               // IN1
int DCmotorInput2 = 27;               // IN2
int DCmotorInput3 = 25;               // IN3
int DCmotorInput4 = 33;               // IN5
int EnableDCmotor1 = 5;
int EnableDCmotor2 = 2;

// Configuring the PWM values
const int PWM_Frequency = 5000;
const int PWM_Channel = 0;
const int PWM_Resolution = 8;
int dutyCycle = 200;

void setup() {

  Serial.begin(115200);
  delay(2000);

  // Configuring the output GPIOs
  pinMode(DCmotorInput1, OUTPUT);
  pinMode(DCmotorInput2, OUTPUT);
  pinMode(DCmotorInput3, OUTPUT);
  pinMode(DCmotorInput4, OUTPUT);
  pinMode(EnableDCmotor1, OUTPUT);
  pinMode(EnableDCmotor2, OUTPUT);
  
  // Configuring the PWM output
  ledcSetup(PWM_Channel, PWM_Frequency, PWM_Resolution);
  
  // Connecting the PWM channel
  ledcAttachPin(EnableDCmotor1, PWM_Channel);
  ledcAttachPin(EnableDCmotor2, PWM_Channel);
 
  // Starts the Bluetooth device
  SerialBT.begin();
  Serial.println("Bluetooth Started! Ready to pair...");
}

void loop() {


  if(SerialBT.available())
  {
    BTData = SerialBT.read();
  }

  if(BTData == 'S')
  {
    // Stops the DC motor
    Serial.println("Motor stopped");
    digitalWrite(DCmotorInput1, LOW);
    digitalWrite(DCmotorInput2, LOW);
    digitalWrite(DCmotorInput3, LOW);
    digitalWrite(DCmotorInput4, LOW); 
    delay(1000);
  }


  if(BTData == 'F')
  {
    // Moves the DC motor forward with speed according to PWM duty cycle
    Serial.println("Moving Forward");
    digitalWrite(DCmotorInput1, LOW);
    digitalWrite(DCmotorInput2, HIGH); 
    digitalWrite(DCmotorInput3, LOW);
    digitalWrite(DCmotorInput4, HIGH); 
    ledcWrite(PWM_Channel, dutyCycle); 
    delay(2000);
  }

  if(BTData == 'B')
  {
    // Moves the DC motor backwards with speed according to PWM duty cycle
    Serial.println("Moving Backwards");
    digitalWrite(DCmotorInput1, HIGH);
    digitalWrite(DCmotorInput2, LOW);
    digitalWrite(DCmotorInput3, HIGH);
    digitalWrite(DCmotorInput4, LOW);
    ledcWrite(PWM_Channel, dutyCycle);
    delay(2000);

  }

  if(BTData == 'I')
  {
    /*/ Increments the PWM duty cycle by 10
    dutyCycle = dutyCycle + 10;

    // Limits the PWM duty cycle value to a maximum of 250
    if(dutyCycle >= 250)
    {
      dutyCycle = 250;
    }

    Serial.print("I ");
    Serial.println(dutyCycle);
    ledcWrite(PWM_Channel, dutyCycle);*/
    digitalWrite(DCmotorInput1, LOW);
    digitalWrite(DCmotorInput2, HIGH); 
    digitalWrite(DCmotorInput3, HIGH);
    digitalWrite(DCmotorInput4, LOW); 
    ledcWrite(PWM_Channel, dutyCycle); 
    delay(2000);
  }

  if(BTData == 'D')
  {
    /*/ Decrements the PWM duty cycle by 10
    dutyCycle = dutyCycle - 10;

    // Limits the PWM duty cycle value to a minimum of 170
    if(dutyCycle <= 170)
    {
      dutyCycle = 170;
    }
    
    Serial.print("D ");
    Serial.println(dutyCycle);
    ledcWrite(PWM_Channel, dutyCycle);*/
    digitalWrite(DCmotorInput1, HIGH);
    digitalWrite(DCmotorInput2, LOW);
    digitalWrite(DCmotorInput3, LOW);
    digitalWrite(DCmotorInput4, HIGH);
    ledcWrite(PWM_Channel, dutyCycle);
    delay(2000);
  }
}