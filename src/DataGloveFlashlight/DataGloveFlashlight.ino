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

  initializeGlove();
}

void loop() 
{
  readHallSensors();
  // fist
  if (!fingersExtended[0] && !fingersExtended[1] && !fingersExtended[2] && !fingersExtended[3] && !fingersExtended[4])
    digitalWrite(LED_PIN, HIGH);
  // open hand
  else if (fingersExtended[0] && fingersExtended[1] && fingersExtended[2] && fingersExtended[3] && fingersExtended[4])
    digitalWrite(LED_PIN, LOW);
  delay(5);
}

