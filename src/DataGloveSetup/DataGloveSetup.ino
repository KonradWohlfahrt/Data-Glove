#include <Adafruit_TinyUSB.h> // for serial communication

#include "preferences.h"

#define LDR_PIN A5
#define VIBRATION_MOTOR_PIN D8
#define LED_PIN D10
#define IR_RECEIVER_PIN D9

#define TOP_BTN_PIN D7
#define BOTTOM_BTN_PIN D6


bool topButton() { return digitalRead(TOP_BTN_PIN) == 0; }
bool bottomButton() { return digitalRead(BOTTOM_BTN_PIN) == 0; }
bool anyButton() { return topButton() || bottomButton(); }


void setup() 
{
  Serial.begin(115200);

  while(!Serial) delay(5);

  pinMode(VIBRATION_MOTOR_PIN, OUTPUT);
  digitalWrite(VIBRATION_MOTOR_PIN, LOW);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  pinMode(LDR_PIN, INPUT);
  pinMode(IR_RECEIVER_PIN, INPUT);

  pinMode(TOP_BTN_PIN, INPUT);
  pinMode(BOTTOM_BTN_PIN, INPUT);

  pinMode(HALL_THUMB, INPUT);
  pinMode(HALL_INDEX, INPUT);
  pinMode(HALL_MIDDLE, INPUT);
  pinMode(HALL_RING, INPUT);
  pinMode(HALL_PINKY, INPUT);
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);


  Serial.println("initialization complete!");
  Serial.println("press any button to continue...");
  while (!anyButton()) delay(5);
  

  // EXTENDED VALUES
  Serial.println();
  Serial.println("Open your hand!");
  delay(3000);
  readHallSensors(50);
  int thumb_extended = _sensorData[0];
  int index_extended = _sensorData[1];
  int middle_extended = _sensorData[2];
  int ring_extended = _sensorData[3];
  int pinky_extended = _sensorData[4];
  for (int i = 0; i < 5; i++)
    extendedValues[i] = _sensorData[i];

  // CONTRACTED VALUES
  Serial.println();
  Serial.println("Form a fist!");
  delay(3000);
  readHallSensors(50);
  int thumb_contracted = _sensorData[0];
  int index_contracted = _sensorData[1];
  int middle_contracted = _sensorData[2];
  int ring_contracted = _sensorData[3];
  int pinky_contracted = _sensorData[4];
  for (int i = 0; i < 5; i++)
    contractedValues[i] = _sensorData[i];

  
  Serial.println();
  Serial.println("--- Replace the values in preferences.h with the following ---");

  Serial.print("int extendedValues[5] = { ");
  Serial.print(thumb_extended);
  Serial.print(", ");
  Serial.print(index_extended);
  Serial.print(", ");
  Serial.print(middle_extended);
  Serial.print(", ");
  Serial.print(ring_extended);
  Serial.print(", ");
  Serial.print(pinky_extended);
  Serial.println(" };");

  Serial.print("int contractedValues[5] = { ");
  Serial.print(thumb_contracted);
  Serial.print(", ");
  Serial.print(index_contracted);
  Serial.print(", ");
  Serial.print(middle_contracted);
  Serial.print(", ");
  Serial.print(ring_contracted);
  Serial.print(", ");
  Serial.print(pinky_contracted);
  Serial.println(" };");

  initializeGlove();

  Serial.println();
  Serial.println("press any button to test...");

  while (!anyButton()) delay(5);
}

void loop() 
{
  readHallSensors();
  Serial.print(fingersExtended[(int)finger_thumb]);
  Serial.print('\t');
  Serial.print(fingersExtended[(int)finger_index]);
  Serial.print('\t');
  Serial.print(fingersExtended[(int)finger_middle]);
  Serial.print('\t');
  Serial.print(fingersExtended[(int)finger_ring]);
  Serial.print('\t');
  Serial.println(fingersExtended[(int)finger_pinky]);
}

