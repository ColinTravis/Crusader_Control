#include "Keyboard.h"
#include "keymap.h"

#define SHIELD_BACK_PIN 5
#define SHIELD_FRONT_PIN 6
#define POWER_PIN 7
#define ENG_PIN 8
#define SHLD_PIN 9
#define WEAP_PIN 10
#define LNDG_PIN 11
#define LIGHT_PIN 12
#define DOOR_PIN 14
#define ATC_PIN 19
#define QT_PIN 18
#define SPOOL_PIN 15
#define PWR_WEAP_PIN 16
//#define PWR_SHLD_PIN 15
//#define PWR_ENG_PIN 14
#define PWR_RST_PIN 13

bool lastStatePwr = HIGH;
bool lastStateShld = HIGH;
bool lastStateEngine = HIGH;
bool lastStateWeap = HIGH;
// bool lastStateAtc = HIGH;
// bool lastStateAcc = HIGH;
// bool lastStateDecl = HIGH;
// bool lastStateGear = HIGH;
// bool lastStateLights = HIGH;
bool lastStateQuant = HIGH;
// bool lastStateGmbl1 = HIGH;
bool lastStateSpool = HIGH;
// bool lastStateFire = HIGH;
bool lastStateDoor = HIGH;
// bool lastStateLock = HIGH;
// bool lastStateShldFrt = HIGH;
// bool lastStateShldBack = HIGH;
// byte gimbalState = 1;

// Quantum
unsigned long pressedTime = 0;
bool quantPressing = false;
bool quantLongDetected = false;
const int LONG_PRESS_TIME = 600; // 600 milliseconds - Quantum hold time

void setup()
{
  // pinMode(SHIELD_BACK_PIN, INPUT_PULLUP);
  // pinMode(SHIELD_FRONT_PIN, INPUT_PULLUP);
  pinMode(POWER_PIN, INPUT);
  pinMode(ENG_PIN, INPUT);
  //  pinMode(SHLD_PIN, INPUT);
  //  pinMode(WEAP_PIN, INPUT);
  // pinMode(LNDG_PIN, INPUT_PULLUP);
  // pinMode(LIGHT_PIN, INPUT_PULLUP);
  pinMode(DOOR_PIN, INPUT_PULLUP);
  // pinMode(ATC_PIN, INPUT_PULLUP);
  pinMode(QT_PIN, INPUT_PULLUP);
  pinMode(SPOOL_PIN, INPUT);
  // pinMode(PWR_WEAP_PIN, INPUT_PULLUP);
  // pinMode(PWR_SHLD_PIN, INPUT_PULLUP);
  // pinMode(PWR_ENG_PIN, INPUT_PULLUP);
  // pinMode(PWR_RST_PIN, INPUT_PULLUP);

  // Checking the flip switch state to prevent rogue keypresses when the logic starts.
  // lastStateLights = digitalRead(21);
  // lastStateGear = digitalRead(6);
  lastStatePwr = digitalRead(POWER_PIN);
  lastStateEngine = digitalRead(ENG_PIN);
  //  lastStateShld = digitalRead(SHLD_PIN);
  //  lastStateWeap = digitalRead(WEAP_PIN);
  // lastStateAtc = digitalRead(8);
  // lastStateSpool = digitalRead(9);
  // lastStateFire = digitalRead(10);
  lastStateDoor = digitalRead(DOOR_PIN);
  // lastStateLock = digitalRead(15);
  // lastStateShldFrt = digitalRead(3);
  // lastStateShldBack = digitalRead(2);

  Keyboard.begin();
  Serial.begin(115200);
  Serial.println("Serial Started!");
}
// void loop()
// {

//   // Test
//   int buttonStateAtc = digitalRead(8);
//   if ((buttonStateAtc != lastStateAtc) && (buttonStateAtc == LOW))
//   {
//     //    Keyboard.press(KEY_LEFT_ALT);
//     //    delay(10);
//     Keyboard.press('n');
//     delay(10);
//     Keyboard.releaseAll();
//     delay(200);
//   }
//   lastStateAtc = buttonStateAtc;

//  if (digitalRead(8) != lastStateGmbl1)
//  {
//    Serial.println(lastStateGmbl1);
//    Keyboard.press('g');
//    delay(10);
//    Keyboard.releaseAll();
//    lastStateGmbl1 = !lastStateGmbl1;
//  }
// }

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

    Serial.println(digitalRead(SPOOL_PIN));
    Keyboard.press(SPOOL_BIND);
    delay(10);
    Keyboard.releaseAll();
    delay(200);
  }
  lastStateSpool = buttonStateSpool;

  // // ATC
  // int buttonStateAtc = digitalRead(15);
  // if ((buttonStateAtc != lastStateAtc) && (buttonStateAtc == LOW))
  // {
  //   Keyboard.press(KEY_LEFT_ALT);
  //   delay(10);
  //   Keyboard.press(ATC_BIND);
  //   delay(10);
  //   Keyboard.releaseAll();
  //   delay(200);
  // }
  // lastStateAtc = buttonStateAtc;


  // // Accept
  // int buttonStateAcc = digitalRead(18);
  // if ((buttonStateAcc != lastStateAcc) && (buttonStateAcc == LOW))
  // {
  //   Keyboard.press((136 + 0x2f));
  //   delay(10);
  //   Keyboard.releaseAll();
  //   delay(200);
  // }
  // lastStateAcc = buttonStateAcc;

  // // Decline
  // int buttonStateDecl = digitalRead(19);
  // if ((buttonStateDecl != lastStateDecl) && (buttonStateDecl == LOW))
  // {
  //   Keyboard.press('+');
  //   delay(10);
  //   Keyboard.releaseAll();
  //   delay(200);
  // }
  // lastStateDecl = buttonStateDecl;

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


  //
  //  // Shields
  //  if (digitalRead(SHLD_PIN) != lastStateShld)
  //  {
  //    Keyboard.press(SHIELD_BIND);
  //    delay(10);
  //    Keyboard.releaseAll();
  //    lastStateShld = !lastStateShld;
  //  }
  //

  //
  //  // Weapons
  //  if (digitalRead(WEAP_PIN) != lastStateWeap)
  //  {
  //    Keyboard.press(WEAPONS_BIND);
  //    delay(10);
  //    Keyboard.releaseAll();
  //    lastStateWeap = !lastStateWeap;
  //  }

  // // Landing gear
  // if (digitalRead(6) != lastStateGear)
  // {
  //   Keyboard.press(LANDING_BIND);
  //   delay(10);
  //   Keyboard.releaseAll();
  //   lastStateGear = !lastStateGear;
  // }

  // // Lights
  // if (digitalRead(7) != lastStateLights)
  // {
  //   Keyboard.press(LIGHTS_BIND);
  //   delay(10);
  //   Keyboard.releaseAll();
  //   lastStateLights = !lastStateLights;
  // }


  // // Fire mode
  // if (digitalRead(10) != lastStateFire)
  // {
  //   Keyboard.press(KEY_RIGHT_ALT);
  //   delay(10);
  //   Keyboard.press(KEY_INSERT);
  //   delay(10);
  //   Keyboard.releaseAll();
  //   lastStateFire = !lastStateFire;
  // }


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

  //   // Doors open
  //   if (digitalRead(DOOR_PIN) != lastStateDoor && digitalRead(DOOR_PIN) == LOW)
  //   {
  //     Keyboard.press('k');
  //     delay(10);
  ////     Keyboard.press('o');
  ////     delay(10);
  //     Keyboard.releaseAll();
  //     lastStateDoor = !lastStateDoor;
  //   }

  // // Doors close
  // if (digitalRead(16) != lastStateDoor && digitalRead(16) == HIGH)
  // {
  //   // Keyboard.press(KEY_LEFT_ALT);
  //   // delay(10);
  //   Keyboard.press(DOORS_BIND);
  //   delay(10);
  //   Keyboard.releaseAll();
  //   lastStateDoor = !lastStateDoor;
  // }

  // // Door unlock
  // if (digitalRead(14) != lastStateLock && digitalRead(14) == HIGH)
  // {
  //   Keyboard.press(KEY_LEFT_ALT);
  //   delay(10);
  //   Keyboard.press('u');
  //   delay(10);
  //   Keyboard.releaseAll();
  //   lastStateLock = !lastStateLock;
  // }
}
