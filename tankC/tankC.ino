#include <PS2X_lib.h>//attack
#include <Servo.h>

PS2X ps2x;
Servo servo_9;
volatile int item;

void setup(){
  ps2x.config_gamepad(A5,A3,A4,A2, true, true);
  delay(300);

  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  servo_9.attach(9);
  item = 50;
  // 100-180
  servo_9.write(item);
}

void loop(){
  ps2x.read_gamepad(false, 0);
    delay(30);
  Serial.println(ps2x.Analog(PSS_LX));
  if ( ps2x.Analog(PSS_LY) < 125) {
    digitalWrite(4,HIGH);
    analogWrite(5, (map(ps2x.Analog(PSS_LY), 0, 125, 0, 255)));
    digitalWrite(7,HIGH);
    analogWrite(6, (map(ps2x.Analog(PSS_LY), 0, 125, 0, 255)));

  } else if ( ps2x.Analog(PSS_LY) > 130) {
    digitalWrite(4,LOW);
    analogWrite(5, (map(ps2x.Analog(PSS_LY), 130, 255, 0, 255)));
    digitalWrite(7,LOW);
    analogWrite(6, (map(ps2x.Analog(PSS_LY), 130, 255, 0, 255)));
  } else if ( ps2x.Analog(PSS_LX) < 125) {
    digitalWrite(4,HIGH);
    analogWrite(5, (map(ps2x.Analog(PSS_LX), 0, 125, 0, 255)));
    digitalWrite(7,LOW);
    analogWrite(6, (map(ps2x.Analog(PSS_LX), 0, 125, 255, 0)));
  } else if ( ps2x.Analog(PSS_LX) > 130) {
    digitalWrite(4,LOW);
    analogWrite(5, (map(ps2x.Analog(PSS_LX), 130, 255, 0, 255)));
    digitalWrite(7,HIGH);
    analogWrite(6, (map(ps2x.Analog(PSS_LX), 130, 255, 255, 0)));
  } else if ( ps2x.Analog(PSS_RY) > 130) {
    item = item + 5;
    // 100-180
    servo_9.write(item);
    if (item > 180) {
      item = 180;

    }
  } else if ( ps2x.Analog(PSS_RY) < 125) {
    item = item - 5;
    // 100-180
    servo_9.write(item);
    if (item < 50) {
      item = 50;

    }
  } else {
    digitalWrite(4,LOW);
    analogWrite(5, 0);
    digitalWrite(7,LOW);
    analogWrite(6, 0);

  }

}