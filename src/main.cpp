#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
byte BTData;

// GPIOs DC motor
int DCmotorInput1 = 21;               // IN1
int DCmotorInput2 = 22;               // IN2
int DCmotorInput3 = 25;               // IN3
int DCmotorInput4 = 27;               // IN4

void setup() {

  Serial.begin(115200);
  delay(1000);

  // Configuring the output GPIOs
  pinMode(DCmotorInput1, OUTPUT);
  pinMode(DCmotorInput2, OUTPUT);
  pinMode(DCmotorInput3, OUTPUT);
  pinMode(DCmotorInput4, OUTPUT);
 
  // Starts the Bluetooth device
  SerialBT.begin();
  Serial.println("Bluetooth Started! Ready to pair...");
}

void loop() {
  if (SerialBT.available()) {
    BTData = SerialBT.read();

    if (BTData == 'S') {
      // Stops the DC motor
      Serial.println("Motor stopped");
      digitalWrite(DCmotorInput1, LOW);
      digitalWrite(DCmotorInput2, LOW);
      digitalWrite(DCmotorInput3, LOW);
      digitalWrite(DCmotorInput4, LOW); 
      delay(1000);
    } else if (BTData == 'F') {
      // Moves the DC motor forward with speed according to PWM duty cycle
      Serial.println("Moving Forward");
      digitalWrite(DCmotorInput3, LOW);
      digitalWrite(DCmotorInput4, HIGH); 
      digitalWrite(DCmotorInput1, LOW);
      digitalWrite(DCmotorInput2, HIGH); 
      delay(1000);
    } else if (BTData == 'B') {
        // Moves the DC motor backwards with speed according to PWM duty cycle
        Serial.println("Moving Backwards");
        digitalWrite(DCmotorInput3, HIGH);
        digitalWrite(DCmotorInput4, LOW);
        digitalWrite(DCmotorInput1, HIGH);
        digitalWrite(DCmotorInput2, LOW);
        delay(1000);
    } else if (BTData == 'I') {
        digitalWrite(DCmotorInput1, LOW);
        digitalWrite(DCmotorInput2, HIGH); 
        digitalWrite(DCmotorInput3, LOW);
        digitalWrite(DCmotorInput4, LOW); 
        delay(1000);
    } else if (BTData == 'D') {
      digitalWrite(DCmotorInput1, LOW);
      digitalWrite(DCmotorInput2, LOW);
      digitalWrite(DCmotorInput3, LOW);
      digitalWrite(DCmotorInput4, HIGH);
      delay(1000);
    }

    // Reset BTData after executing the action
    BTData = 'E'; // Set it to an empty character or another value
  }
}
