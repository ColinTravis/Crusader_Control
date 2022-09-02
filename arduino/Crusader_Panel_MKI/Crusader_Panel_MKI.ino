#include "Keyboard.h"
#include "keymap.h"
bool lastStateAtc = HIGH;
bool lastStateAcc = HIGH;
bool lastStateDecl = HIGH;
bool lastStatePwr = HIGH;
bool lastStateShld = HIGH;
bool lastStateThrst = HIGH;
bool lastStateWep = HIGH;
bool lastStateGear = HIGH;
bool lastStateLights = HIGH;
bool lastStateQuant = HIGH;
bool lastStateGmbl1 = HIGH;
bool lastStateSpool = HIGH;
bool lastStateFire = HIGH;
bool lastStateDoor = HIGH;
bool lastStateLock = HIGH;
byte gimbalState = 1;

// Quantum
unsigned long pressedTime = 0;
bool quantPressing = false;
bool quantLongDetected = false;
const int LONG_PRESS_TIME = 600; // 600 milliseconds - Quantum hold time

void setup()
{
  pinMode(21, INPUT);
  pinMode(20, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);

  // Checking the flip switch state to prevent rogue keypresses when the logic starts.
  lastStatePwr = digitalRead(21);
  lastStateShld = digitalRead(20);
  lastStateThrst = digitalRead(4);
  lastStateWep = digitalRead(5);
  lastStateGear = digitalRead(6);
  lastStateLights = digitalRead(7);
  lastStateAtc = digitalRead(8);
  lastStateSpool = digitalRead(9);
  lastStateFire = digitalRead(10);
  lastStateDoor = digitalRead(14);
  lastStateLock = digitalRead(15);

  Keyboard.begin();
  Serial.begin(115200);
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
  int buttonStateQuant = digitalRead(15);

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
  int buttonStateSpool = digitalRead(9);
  if ((buttonStateSpool != lastStateSpool) && (buttonStateSpool == LOW))
  {
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


  // Accept
  int buttonStateAcc = digitalRead(18);
  if ((buttonStateAcc != lastStateAcc) && (buttonStateAcc == LOW))
  {
    Keyboard.press((136 + 0x2f));
    delay(10);
    Keyboard.releaseAll();
    delay(200);
  }
  lastStateAcc = buttonStateAcc;

  // Decline
  int buttonStateDecl = digitalRead(19);
  if ((buttonStateDecl != lastStateDecl) && (buttonStateDecl == LOW))
  {
    Keyboard.press('+');
    delay(10);
    Keyboard.releaseAll();
    delay(200);
  }
  lastStateDecl = buttonStateDecl;

  // Power
  if (digitalRead(2) != lastStatePwr)
  {
    Keyboard.press(POWER_BIND);
    delay(10);
    Keyboard.releaseAll();
    lastStatePwr = !lastStatePwr;
  }

  // Shields
  if (digitalRead(3) != lastStateShld)
  {
    Keyboard.press(SHIELD_BIND);
    delay(10);
    Keyboard.releaseAll();
    lastStateShld = !lastStateShld;
  }

  // Thrusters
  if (digitalRead(4) != lastStateThrst)
  {
    Keyboard.press(ENGINE_BIND);
    delay(10);
    Keyboard.releaseAll();
    lastStateThrst = !lastStateThrst;
  }

  // Weapons
  if (digitalRead(5) != lastStateWep)
  {
    Keyboard.press(WEAPONS_BIND);
    delay(10);
    Keyboard.releaseAll();
    lastStateWep = !lastStateWep;
  }

  // Landing gear
  if (digitalRead(6) != lastStateGear)
  {
    Keyboard.press(LANDING_BIND);
    delay(10);
    Keyboard.releaseAll();
    lastStateGear = !lastStateGear;
  }

  // Lights
  if (digitalRead(7) != lastStateLights)
  {
    Keyboard.press(LIGHTS_BIND);
    delay(10);
    Keyboard.releaseAll();
    lastStateLights = !lastStateLights;
  }


  // Fire mode
  if (digitalRead(10) != lastStateFire)
  {
    Keyboard.press(KEY_RIGHT_ALT);
    delay(10);
    Keyboard.press(KEY_INSERT);
    delay(10);
    Keyboard.releaseAll();
    lastStateFire = !lastStateFire;
  }

  // // Doors open
  // if (digitalRead(16) != lastStateDoor && digitalRead(16) == LOW)
  // {
  //   Keyboard.press(KEY_LEFT_ALT);
  //   delay(10);
  //   Keyboard.press('o');
  //   delay(10);
  //   Keyboard.releaseAll();
  //   lastStateDoor = !lastStateDoor;
  // }

  // Doors close
  if (digitalRead(16) != lastStateDoor && digitalRead(16) == HIGH)
  {
    // Keyboard.press(KEY_LEFT_ALT);
    // delay(10);
    Keyboard.press(DOORS_BIND);
    delay(10);
    Keyboard.releaseAll();
    lastStateDoor = !lastStateDoor;
  }

  // Door unlock
  if (digitalRead(14) != lastStateLock && digitalRead(14) == HIGH)
  {
    Keyboard.press(KEY_LEFT_ALT);
    delay(10);
    Keyboard.press('u');
    delay(10);
    Keyboard.releaseAll();
    lastStateLock = !lastStateLock;
  }
}
