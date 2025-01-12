
#include <PS2X_lib.h>
#include <Servo.h>

PS2X ps2x;
Servo servo_9;
Servo servo_10;
volatile int item;

void setup(){
  ps2x.config_gamepad(3,A5,2,A4, true, true);
  delay(300);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  servo_9.attach(9);
  pinMode(11, OUTPUT);
  servo_10.attach(10);

  item = 180;
  // 100-180
  servo_9.write(item);
  // 90-180
  servo_10.write(180);
}

void loop(){
  ps2x.read_gamepad(false, 0);
    delay(30);
  if ( ps2x.Analog(PSS_LY) < 125) {
    digitalWrite(4,LOW);
    analogWrite(5, (map(ps2x.Analog(PSS_LY), 0, 125, 255, 0)));
    digitalWrite(7,LOW);
    analogWrite(6, (map(ps2x.Analog(PSS_LY), 0, 125, 255, 0)));

  } else if ( ps2x.Analog(PSS_LY) > 130) {
    digitalWrite(4,HIGH);
    analogWrite(5, (map(ps2x.Analog(PSS_LY), 130, 255, 255, 0)));
    digitalWrite(7,HIGH);
    analogWrite(6, (map(ps2x.Analog(PSS_LY), 130, 255, 255, 0)));
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
  } else if ( ps2x.Analog(PSS_RY) < 125) {
    item = item + 5;
    // 100-180
    servo_9.write(item);
    if (item > 180) {
      item = 180;

    }
  } else if ( ps2x.Analog(PSS_RY) > 130) {
    item = item - 5;
    // 100-180
    servo_9.write(item);
    if (item < 100) {
      item = 100;
    }
  } else if (ps2x.Button(PSB_R1)) {
    digitalWrite(11,HIGH);
    delay(1000);
    // 90-180
    servo_10.write(100);
  } else {
    digitalWrite(4,LOW);
    analogWrite(5, 0);
    digitalWrite(7,LOW);
    analogWrite(6, 0);
    // 90-180
    servo_10.write(180);
    digitalWrite(11,LOW);

  }

}