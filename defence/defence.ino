#include<PS2X_lib.h>
#include<Servo.h>


PS2X ps2x;
Servo servo_9;
volatile int item;

double move_f(int x)//手柄的输入转换曲线（也可以是直线）x是0~127的数字
{
  if(x<10) return 0;
  if(x<20) return x-10;
  if(x>=20&&x<=80) return (x-20)*5.0/6.0+10;//(20,10) (80,60)
  if(x>80) return (x-80)*40.0/47.0+60;//(80,60) (127,100)

}
void init()
{
  digitalWrite(4,LOW);
  analogWrite(5, 0);
  digitalWrite(7,LOW);
  analogWrite(6, 0);
}
/*
void up(int x)//向前单位
{
  digitalWrite(4,HIGH);
  analogWrite(5,x);
  digitalWrite(7,HIGH);
  analogWrite(6,x);
}
void down(int x)//向后单位
{
  digitalWrite(4,LOW);
  analogWrite(5,x);
  digitalWrite(7,LOW);
  analogWrite(6,x);
}
void left(int x)//左转 a后b前
{
  digitalWrite(4,LOW);
  analogWrite(5,x);
  digitalWrite(7,HIGH);
  analogWrite(6,x);
}
void right(int x)//右转 a前b后
{
  digitalWrite(4,HIGH);
  analogWrite(5,x);
  digitalWrite(7,LOW);
  analogWrite(6,x);
}
*/
void move(int A,int B)//移动上下左右总和
{
  if(A>=0)
  {
    digitalWrite(4,HIGH);
    analogWrite(5,A);
  }
  else
  {
    digitalWrite(4,LOW);
    analogWrite(5,-A);
  }
  if(A>=0)
  {
    digitalWrite(4,HIGH);
    analogWrite(5,B);
  }
  else
  {
    digitalWrite(4,LOW);
    analogWrite(5,-B);
  }
}
void gofront()//炮台向前
{
  if(x<10) return;
  item=item+5<150? item+5:150;
  servo_9.write(item);
}
void goback()//炮台向后
{
  if(x<10) return;
  item=item-5>50? item-5:50;
  servo_9.write(item);
}
void shoot();
void motor1(int x);//单独控制电机模块
void motor2(int x);
void motor3(int x);
void motor4(int x);
//舵机的180~输入的100
void setup() {
  // put your setup code here, to run once:
  ps2x.config_gamepad(A5,A3,A4,A2, true, true);
  delay(300);

  pinMode(4, OUTPUT);//A电机正反转
  pinMode(5, OUTPUT);//A电机转速
  pinMode(7, OUTPUT);//B电机转速
  pinMode(6, OUTPUT);//B电机正反转
  servo_9.attach(9);//上下移动的舵机
  pinMode(10,OUTPUT);//激光灯 测试用
  //50~150 舵机角度 50竖直 135水平
  item=135;
  servo_9.write(item);//初始化防御位置
  init();
  Serial.println("初始条件完成");

}

void loop() {
  // put your main code here, to run repeatedly:
  //激光灯测试代码
  digitalWrite(10,HIGH);
  delay(1000);
  digitalWrite(10,LOW);
  delay(1000);
  //------
  ps2x.read_gamepad(false, 0);
    delay(30);
  Serial.println(ps2x.Analog(PSS_LX));
  Serial.println(ps2x.Analog(PSS_LY));
  double A,B;
  /*if(ps2x.Analog(PSS_LY)>=128)
  {
    up(int(move_f(ps2x.Analog(PSS_LY)-128)));
  }
  else if(ps2x.Analog(PSS_LY)<125)
  {
    down(int(move_f(128-ps2x.Analog(PSS_LY))));
  }
  else if(ps2x.Analog(PSS_LX)>=128)
  {
    right(int(move_f(ps2x.Analog(PSS_LX)-128)));
  }
  else
  {
    left(int(move-f(128-ps2x.Analog(PSS_LX))));
  }*/
  A=move_f(ps2x.Analog(PSS_LY)-128)+move_f(ps2x.Analog(PSS_LX)-128);
  B=move_f(ps2x.Analog(PSS_LY)-128)-move_f(ps2x.Analog(PSS_LX)-128);
  move(int (A),int (B));
  if(ps2x.Analog(PSS_RY) > 130)
  {
    gofront();
  }
  else if(ps2x.Analog(PSS_RY)<125)
  {
    goback();
  }
  
}
