#include<PS2X_lib.h>
#include<Servo.h>


PS2X ps2x;
Servo servo_9;
volatile int item;

double move_f(int x)//手柄的输入转换曲线（也可以是直线）x是0~127的数字
{
  return map(x, 0, 127, 0, 255);
  if(x<10) return 0;
  else return (x-10)*127.0/117.0;
/*
  if(x<10) return 0;
  if(x<20) return x-10;
  if(x>=20&&x<=80) return (x-20)*5.0/6.0+10;//(20,10) (80,60)
  if(x>80) return (x-80)*40.0/47.0+60;//(80,60) (127,100)
*/

}
void up(int x)//向前单位 255最快
{
  digitalWrite(4,LOW);
  analogWrite(5,x);
  digitalWrite(7,LOW);
  analogWrite(6,x);
}
void down(int x)//向后单位 0最快
{
  digitalWrite(4,HIGH);
  analogWrite(5,x);
  digitalWrite(7,HIGH);
  analogWrite(6,x);
}
void left(int x)//左转 a后b前 255最快
{
  digitalWrite(4,HIGH);
  analogWrite(5,255-x);
  digitalWrite(7,LOW);
  analogWrite(6,x);
}
void right(int x)//右转 a前b后 255最快
{
  digitalWrite(4,LOW);
  analogWrite(5,x);
  digitalWrite(7,HIGH);
  analogWrite(6,255-x);
}

void gofront()//炮台向前
{
  item=item+5<110? item+5:110;
  servo_9.write(item);
}
void goback()//炮台向后
{
  item=item-5>0? item-5:0;
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
  ps2x.config_gamepad(3,A5,2,A4, true, true);
  delay(300);
  Serial.begin(9600);
  pinMode(4, OUTPUT);//A电机正反转
  pinMode(5, OUTPUT);//A电机转速
  pinMode(7, OUTPUT);//B电机转速
  pinMode(6, OUTPUT);//B电机正反转
  servo_9.attach(9);//上下移动的舵机
 // pinMode(10,OUTPUT);//激光灯 测试用
  //50~150 舵机角度 50竖直 135水平
  item=0;
  servo_9.write(item);//初始化防御位置
    digitalWrite(4,LOW);
  analogWrite(5, 0);
  digitalWrite(7,LOW);
  analogWrite(6, 0);
  Serial.println("初始条件完成");
  item=110;
  servo_9.write(item);
  up(255);delay(100);
  left(255);delay(425);
  up(255);delay(1500);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //激光灯测试代码
  /*
  digitalWrite(10,HIGH);
  delay(1000);
  digitalWrite(10,LOW);
  delay(1000);
  */
  //------
  ps2x.read_gamepad(false, 0);
    delay(30);
  
  // Serial.println("手柄");
  // Serial.println(ps2x.Analog(PSS_LX));
  // Serial.println(ps2x.Analog(PSS_LY));
  digitalWrite(4,LOW);
  analogWrite(5, 0);
  digitalWrite(7,LOW);
  analogWrite(6, 0);
  // double A=0,B=0;
  if (ps2x.Button(PSAB_PAD_UP))
  {
    up(255);
  }
  else if (ps2x.Button(PSAB_PAD_DOWN))
  {
    down(0);
  }
  else if (ps2x.Button(PSAB_PAD_RIGHT))
  {
    right(255);
  }
  else if (ps2x.Button(PSAB_PAD_LEFT))
  {
    left(255);
  }
  else if(ps2x.Analog(PSS_LY)>130 && abs(ps2x.Analog(PSS_LY)-128)>=abs(ps2x.Analog(PSS_LX)-128))
  {
    // A+=move_f(ps2x.Analog(PSS_LY)-128);
    // B+=move_f(ps2x.Analog(PSS_LY)-128);
    down(map(ps2x.Analog(PSS_LY), 0, 125, 0, 255));
  }
  else if(ps2x.Analog(PSS_LY)<125&& abs(ps2x.Analog(PSS_LY)-128)>=abs(ps2x.Analog(PSS_LX)-128))
  {
    // A-=move_f(128-ps2x.Analog(PSS_LY));
    // B-=move_f(128-ps2x.Analog(PSS_LY));
    up(map(ps2x.Analog(PSS_LY), 130, 255, 0, 255));
  }
  else if(ps2x.Analog(PSS_LX)>130)
  {
    // A-=move_f(ps2x.Analog(PSS_LX)-128);
    // B+=move_f(ps2x.Analog(PSS_LX)-128);
      right(map(ps2x.Analog(PSS_LX), 130, 255, 0, 255));
  }
  else if(ps2x.Analog(PSS_LX)<125)
  {
    // A+=move_f(128-ps2x.Analog(PSS_LX));
    // B-=move_f(128-ps2x.Analog(PSS_LX));
    left(255-map(ps2x.Analog(PSS_LX), 0, 125, 0, 255));
  }
  // A=move_f(ps2x.Analog(PSS_LY)-128)+move_f(ps2x.Analog(PSS_LX)-128);
  // B=move_f(ps2x.Analog(PSS_LY)-128)-move_f(ps2x.Analog(PSS_LX)-128);
  
//  Serial.println("AB");
//  Serial.println(A);
// Serial.println(B);
  // move(int (A/(abs(A)+abs(B))*100),int (B/(abs(A)+abs(B))*100));
  if(ps2x.Analog(PSS_RY) > 130)
  {
    gofront();
  }
  else if(ps2x.Analog(PSS_RY)<125)
  {
    goback();
  }
  
}
/*
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
    digitalWrite(7,HIGH);
    analogWrite(6,B);
  }
  else
  {
    digitalWrite(7,LOW);
    analogWrite(6,-B);
  }
}
*/