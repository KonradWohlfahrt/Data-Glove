#include "Adafruit_TinyUSB.h" // for serial communication

#define LDR_PIN A5
#define VIBRATION_MOTOR_PIN D8
#define LED_PIN D10
#define IR_RECEIVER_PIN D9

#define TOP_BTN_PIN D7
#define BOTTOM_BTN_PIN D6

#define HALL_THUMB A0
#define HALL_INDEX A1
#define HALL_MIDDLE A2
#define HALL_RING A3
#define HALL_PINKY A4



void setup() 
{
  Serial.begin(115200);

  // test vibration motor
  pinMode(VIBRATION_MOTOR_PIN, OUTPUT);
  digitalWrite(VIBRATION_MOTOR_PIN, HIGH);
  delay(500);
  digitalWrite(VIBRATION_MOTOR_PIN, LOW);

  // test led
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);

  // set input pins
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

  // test onboard leds
  digitalWrite(LED_RED, LOW);
  delay(250);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
  delay(250);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, LOW);
  delay(500);
  digitalWrite(LED_BLUE, HIGH);
}

void loop() 
{
  Serial.print(analogRead(HALL_THUMB));
  Serial.print('\t');
  Serial.print(analogRead(HALL_INDEX));
  Serial.print('\t');
  Serial.print(analogRead(HALL_MIDDLE));
  Serial.print('\t');
  Serial.print(analogRead(HALL_RING));
  Serial.print('\t');
  Serial.print(analogRead(HALL_PINKY));
  Serial.print('\t');
  Serial.print(analogRead(LDR_PIN));
  Serial.print('\t');
  Serial.print(digitalRead(IR_RECEIVER_PIN));
  Serial.print('\t');
  Serial.print(digitalRead(TOP_BTN_PIN));
  Serial.print('\t');
  Serial.println(digitalRead(BOTTOM_BTN_PIN));
  delay(5);
}
