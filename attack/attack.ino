#include<PS2X_lib.h>
#include<Servo.h>



double move_f(int x)//手柄的输入转换曲线（也可以是直线）x是0~127的数字
{
  if(x<20) return x/2.0;
  if(x>=20&&x<=80) return (x-20)*5.0/6.0+10;//(20,10) (80,60)
  if(x>80) return (x-80)*40.0/47.0+60;//(80,60) (127,100)

}

void up(int x);//向前单位
void down(int x);//向后单位
void left(int x);//左转
void right(int x);//右转
void gofront(int x);//炮台向前
void gotial(int x);//炮台向后
void shoot();
void motor1(int x);//单独控制电机模块
void motor2(int x);
void motor3(int x);
void motor4(int x);
//舵机的180~输入的100
void printIn()
void setup() {
  // put your setup code here, to run once:
  s2x.config_gamepad(A5,A3,A4,A2, true, true);
  delay(300);

  pinMode(4, OUTPUT);//A电机正反转
  pinMode(5, OUTPUT);//A电机转速
  pinMode(7, OUTPUT);//B电机转速
  pinMode(6, OUTPUT);//B电机正反转
  servo_9.attach(9);//上下移动的舵机
  pinMode(11, OUTPUT);//
  servo_10.attach(10);

  item = 180;
  // 100-180
  servo_9.write(item);
  // 90-180
  servo_10.write(180);
}

void loop() {
  // put your main code here, to run repeatedly:

}
