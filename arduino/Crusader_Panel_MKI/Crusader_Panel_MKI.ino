#include "Keyboard.h"
#include "keymap.h"

#define DEBUG false
#define DEBUG_SERIAL if (DEBUG) Serial

#define SHIELD_BACK_PIN 2
#define SHIELD_FRONT_PIN 3
#define POWER_PIN 4
#define ENG_PIN 5
#define SHLD_PIN 6
#define WEAP_PIN 7
#define LNDG_PIN 8
#define LIGHT_PIN 9
#define DOOR_PIN 21
#define ATC_PIN 20
#define QT_PIN 19
#define SPOOL_PIN 18
#define PWR_WEAP_PIN 15
#define PWR_SHLD_PIN 14
#define PWR_ENG_PIN 16
#define PWR_RST_PIN 10

bool lastStatePwr = HIGH;
bool lastStateShld = HIGH;
bool lastStateEngine = HIGH;
bool lastStateWeap = HIGH;
bool lastStateAtc = HIGH;
bool lastStateGear = HIGH;
bool lastStateLights = HIGH;
bool lastStateDoor = HIGH;
bool lastStateQuant = HIGH;
bool lastStateSpool = HIGH;
bool lastStateShldFrt = HIGH;
bool lastStateShldBack = HIGH;
bool lastStatePwrRst = HIGH;
bool lastStatePwrShld = HIGH;
bool lastStatePwrEng = HIGH;
bool lastStatePwrWeap = HIGH;
// byte gimbalState = 1;

// Quantum
unsigned long pressedTime = 0;
bool quantPressing = false;
bool quantLongDetected = false;
const int LONG_PRESS_TIME = 600; // 600 milliseconds - Quantum hold time

void setup()
{
  pinMode(SHIELD_BACK_PIN, INPUT_PULLUP);
  pinMode(SHIELD_FRONT_PIN, INPUT_PULLUP);
  pinMode(POWER_PIN, INPUT);
  pinMode(ENG_PIN, INPUT);
  pinMode(SHLD_PIN, INPUT);
  pinMode(WEAP_PIN, INPUT);
  pinMode(LNDG_PIN, INPUT_PULLUP);
  pinMode(LIGHT_PIN, INPUT_PULLUP);
  pinMode(DOOR_PIN, INPUT_PULLUP);
  pinMode(ATC_PIN, INPUT_PULLUP);
  pinMode(QT_PIN, INPUT_PULLUP);
  pinMode(SPOOL_PIN, INPUT);
  pinMode(PWR_WEAP_PIN, INPUT_PULLUP);
  pinMode(PWR_SHLD_PIN, INPUT_PULLUP);
  pinMode(PWR_ENG_PIN, INPUT_PULLUP);
  pinMode(PWR_RST_PIN, INPUT);

  // Checking the flip switch state to prevent rogue keypresses when the logic starts.
  lastStateLights = digitalRead(LIGHT_PIN);
  lastStateGear = digitalRead(LNDG_PIN);
  lastStatePwr = digitalRead(POWER_PIN);
  lastStateEngine = digitalRead(ENG_PIN);
  lastStateShld = digitalRead(SHLD_PIN);
  lastStateWeap = digitalRead(WEAP_PIN);
  lastStateAtc = digitalRead(ATC_PIN);
  lastStateSpool = digitalRead(SPOOL_PIN);
  lastStateDoor = digitalRead(DOOR_PIN);
  lastStatePwrWeap = digitalRead(PWR_WEAP_PIN);
  lastStatePwrShld = digitalRead(PWR_SHLD_PIN);
  lastStatePwrEng = digitalRead(PWR_ENG_PIN);
  lastStatePwrRst = digitalRead(PWR_RST_PIN);
  lastStateShldFrt = digitalRead(SHIELD_FRONT_PIN);
  lastStateShldBack = digitalRead(SHIELD_BACK_PIN);

  Keyboard.begin();
  DEBUG_SERIAL.begin(115200);
  DEBUG_SERIAL.println("Serial Debugging Started.");
}

void loop()
{
  // Quant
  int buttonStateQuant = digitalRead(QT_PIN);

  if ((buttonStateQuant != lastStateQuant) && (buttonStateQuant == LOW))
  // initial button press
  {
    pressedTime = millis();
    quantPressing = true;
    quantLongDetected = false;
  }
  else if ((buttonStateQuant != lastStateQuant) && (buttonStateQuant == HIGH))
  { // button is released
    quantPressing = false;
    delay(10);
    Keyboard.releaseAll();
  }

  if (quantPressing == true && quantLongDetected == false)
  {
    long pressDuration = millis() - pressedTime;

    if (pressDuration > LONG_PRESS_TIME)
    {
      Keyboard.press(QUANTUM_BIND);
      quantLongDetected = true;
    }
  }

  // save the the last state
  lastStateQuant = buttonStateQuant;

  // Quantum Spool
  int buttonStateSpool = digitalRead(SPOOL_PIN);
  if ((buttonStateSpool != lastStateSpool) && (buttonStateSpool == LOW))
  {
    DEBUG_SERIAL.println(digitalRead(SPOOL_PIN));
    Keyboard.press(SPOOL_BIND);
    delay(10);
    Keyboard.releaseAll();
    delay(200);
  }
  lastStateSpool = buttonStateSpool;

  // ATC
  int buttonStateAtc = digitalRead(15);
  if ((buttonStateAtc != lastStateAtc) && (buttonStateAtc == LOW))
  {
    Keyboard.press(KEY_LEFT_ALT);
    delay(10);
    Keyboard.press(ATC_BIND);
    delay(10);
    Keyboard.releaseAll();
    delay(200);
  }
  lastStateAtc = buttonStateAtc;

  //   Power
  if (digitalRead(POWER_PIN) != lastStatePwr)
  {
    Keyboard.press('u');
    delay(10);
    Keyboard.releaseAll();
    lastStatePwr = !lastStatePwr;
  }

  //   Engines
  if (digitalRead(ENG_PIN) != lastStateEngine)
  {
    Keyboard.press(ENGINE_BIND);
    delay(10);
    Keyboard.releaseAll();
    lastStateEngine = !lastStateEngine;
  }

  // Shields
  if (digitalRead(SHLD_PIN) != lastStateShld)
  {
    Keyboard.press(SHIELD_BIND);
    delay(10);
    Keyboard.releaseAll();
    lastStateShld = !lastStateShld;
  }

  // Weapons
  if (digitalRead(WEAP_PIN) != lastStateWeap)
  {
    Keyboard.press(WEAPONS_BIND);
    delay(10);
    Keyboard.releaseAll();
    lastStateWeap = !lastStateWeap;
  }

  // Landing gear
  //  int buttonStateLanding = digitalRead(LNDG_PIN);
  //  if ((buttonStateLanding != lastStateGear) && (buttonStateLanding == LOW))
  //  {

  //    Keyboard.press(LANDING_BIND);
  //    delay(10);
  //    Keyboard.releaseAll();
  //    delay(200);
  //  }
  //  lastStateGear = buttonStateLanding;

  // Landing gear
  if (digitalRead(LNDG_PIN) != lastStateGear)
  {
    Keyboard.press(LANDING_BIND);
    delay(10);
    Keyboard.releaseAll();
    delay(200);
    lastStateGear = !lastStateGear;
  }

  // Lights
  if (digitalRead(LIGHT_PIN) != lastStateLights)
  {
    Keyboard.press(LIGHTS_BIND);
    delay(10);
    Keyboard.releaseAll();
    lastStateLights = !lastStateLights;
  }

  // Doors Toggle
  int buttonStateDoors = digitalRead(DOOR_PIN);
  if ((buttonStateDoors != lastStateDoor) && (buttonStateDoors == LOW))
  {

    Keyboard.press(DOORS_BIND);
    delay(10);
    Keyboard.releaseAll();
    delay(200);
  }
  lastStateDoor = buttonStateDoors;

  // Shield Front
  int buttonStateShldFront = digitalRead(SHIELD_FRONT_PIN);
  if ((buttonStateShldFront != lastStateShldFrt) && (buttonStateShldFront == LOW))
  {

    Keyboard.press(SHLD_FRONT_BIND);
    delay(10);
    Keyboard.releaseAll();
    delay(200);
  }
  lastStateShldFrt = buttonStateShldFront;

  // Shield Back
  int buttonStateShldBack = digitalRead(SHIELD_BACK_PIN);
  if ((buttonStateShldBack != lastStateShldBack) && (buttonStateShldBack == LOW))
  {

    Keyboard.press(SHLD_BACK_BIND);
    delay(10);
    Keyboard.releaseAll();
    delay(200);
  }
  lastStateShldBack = buttonStateShldBack;

  // Power Triangle
  /////

  // Power Weapon Priority
  int buttonStatePwrWeap = digitalRead(PWR_WEAP_PIN);
  if ((buttonStatePwrWeap != lastStatePwrWeap) && (buttonStatePwrWeap == LOW))
  {
    Keyboard.press(KEY_F7);
    delay(10);
    Keyboard.releaseAll();
    delay(200);
  }
  lastStatePwrWeap = buttonStatePwrWeap;

  // Power Shields Priority
  int buttonStatePwrShld = digitalRead(PWR_SHLD_PIN);
  if ((buttonStatePwrShld != lastStatePwrShld) && (buttonStatePwrShld == LOW))
  {
    Keyboard.press(KEY_F6);
    delay(10);
    Keyboard.releaseAll();
    delay(200);
  }
  lastStatePwrShld = buttonStatePwrShld;

  // Power Engine Priority
  int buttonStatePwrEng = digitalRead(PWR_ENG_PIN);
  if ((buttonStatePwrEng != lastStatePwrEng) && (buttonStatePwrEng == LOW))
  {

    Keyboard.press(KEY_F5);
    delay(10);
    Keyboard.releaseAll();
    delay(200);
  }
  lastStatePwrEng = buttonStatePwrEng;

  // Power Reset Priority
  int buttonStatePwrRst = digitalRead(PWR_RST_PIN);
  if ((buttonStatePwrRst != lastStatePwrRst) && (buttonStatePwrRst == LOW))
  {

    Keyboard.press(KEY_F8);
    delay(10);
    Keyboard.releaseAll();
    delay(200);
  }
  lastStatePwrRst = buttonStatePwrRst;
}
