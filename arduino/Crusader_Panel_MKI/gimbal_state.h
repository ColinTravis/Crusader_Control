// // Gimbal mode 1
// if (digitalRead(8) != lastStateGmbl1)
// {
//     Keyboard.press('g');
//     delay(10);
//     Keyboard.releaseAll();
//     lastStateGmbl1 = !lastStateGmbl1;
// }

// // Gimbal mode 2
// if (digitalRead(9) != lastStateGmbl2)
// {
//     Keyboard.press('g');
//     delay(10);
//     Keyboard.releaseAll();
//     lastStateGmbl2 = !lastStateGmbl2;
// }

// // Gimbal mode pro
// if (digitalRead(8) == LOW && digitalRead(9) == HIGH && gimbalState == 2)
// {
//     Keyboard.press('g');
//     delay(10);
//     Keyboard.releaseAll();
//     gimbalState = 1;
// }
// else if (digitalRead(8) == LOW && digitalRead(9) == HIGH && gimbalState == 3)
// {
//     Keyboard.write('g');
//     delay(10);
//     Keyboard.write('g');
//     delay(10);
//     gimbalState = 1;
// }
// else if (digitalRead(8) == HIGH && digitalRead(9) == HIGH && gimbalState == 1)
// {
//     Keyboard.write('g');
//     delay(10);
//     Keyboard.write('g');
//     delay(10);
//     gimbalState = 2;
// }
// else if (digitalRead(8) == HIGH && digitalRead(9) == HIGH && gimbalState == 3)
// {
//     Keyboard.write('g');
//     delay(10);
//     gimbalState = 2;
// }
// else if (digitalRead(8) == HIGH && digitalRead(9) == LOW && gimbalState == 1)
// {
//     Keyboard.write('g');
//     delay(10);
//     gimbalState = 3;
// }
// else if (digitalRead(8) == HIGH && digitalRead(9) == LOW && gimbalState == 2)
// {
//     Keyboard.write('g');
//     delay(10);
//     Keyboard.write('g');
//     delay(10);
//     gimbalState = 3;
// }
