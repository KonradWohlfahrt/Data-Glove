#include <bluefruit.h>

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


BLEDis bledis;
BLEHidAdafruit blehid;

#define DOUBLE_PRESS_DEADZONE 750
#define DEBOUNCE_TIME 100
unsigned long lastGrip;
bool awaitingDoublePress = false;


void setup() 
{
  pinMode(VIBRATION_MOTOR_PIN, OUTPUT);
  digitalWrite(VIBRATION_MOTOR_PIN, LOW);

  pinMode(TOP_BTN_PIN, INPUT);
  pinMode(BOTTOM_BTN_PIN, INPUT);

  pinMode(HALL_THUMB, INPUT);
  pinMode(HALL_INDEX, INPUT);
  pinMode(HALL_MIDDLE, INPUT);
  pinMode(HALL_RING, INPUT);
  pinMode(HALL_PINKY, INPUT);

  pinMode(LED_RED, OUTPUT);
  

  Bluefruit.begin();
  Bluefruit.setTxPower(4);

  bledis.setManufacturer("Seeed Studio");
  bledis.setModel("XIAO nRF52840");
  bledis.begin();

  blehid.begin();
  startAdv();

  initializeGlove();
}

void loop() 
{
  // wait for connection
  if (Bluefruit.connected() > 0)
  {
    if (handClosed() && millis() - lastGrip > DEBOUNCE_TIME)
    {
      unsigned long timestamp = millis();
      while (!handOpened()) delay(5);
      
      if (millis() - timestamp < DOUBLE_PRESS_DEADZONE && millis() - timestamp > DEBOUNCE_TIME)
      {
        if (!awaitingDoublePress)
          awaitingDoublePress = true;
        else
        {
          blehid.consumerKeyPress(HID_USAGE_CONSUMER_VOLUME_DECREMENT);
          delay(5);
          blehid.consumerKeyRelease();

          digitalWrite(VIBRATION_MOTOR_PIN, HIGH);
          delay(200);
          digitalWrite(VIBRATION_MOTOR_PIN, LOW);

          awaitingDoublePress = false;
        }
      }
      else
        awaitingDoublePress = false;

      lastGrip = millis();
    }
    if (awaitingDoublePress && millis() - lastGrip > DOUBLE_PRESS_DEADZONE)
      awaitingDoublePress = false;

    digitalWrite(LED_RED, !awaitingDoublePress);
  }
}

bool handOpened() { readHallSensors(); return fingersExtended[0] && fingersExtended[1] && fingersExtended[2] && fingersExtended[3] && fingersExtended[4]; }
bool handClosed() { readHallSensors(); return !fingersExtended[0] && !fingersExtended[1] && !fingersExtended[2] && !fingersExtended[3] && !fingersExtended[4]; }

void startAdv(void)
{  
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  // Include BLE HID service
  Bluefruit.Advertising.addService(blehid);

  // There is enough room for the dev name in the advertising packet
  Bluefruit.Advertising.addName();
  
  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   * 
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html   
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}