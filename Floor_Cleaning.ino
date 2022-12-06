#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position


const int trig = 6;  
const int echo = 5;    
int tien1 = 10;       //forward MOtor
int tien2 = 11;        
int lui1 = 12;      //backward Motor
int lui2 = 13;        
int dongcoservo = 9;   

int gioihan = 15;
int i;
int x = 0;
unsigned long thoigian; 
int khoangcach;          
int khoangcachtrai, khoangcachphai;
int maxspeed=30;

void dokhoangcach();
void dithang(int duongdi);
void disangtrai();
void disangphai();
void dilui();
void resetdongco();
void quaycbsangphai();
void quaycbsangtrai();
void setup() {
   

  myservo.attach(9); 
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);   

  pinMode(tien1, OUTPUT);
  pinMode(tien2, OUTPUT);
  pinMode(lui1, OUTPUT);
  pinMode(lui2, OUTPUT);
  digitalWrite(tien1, LOW);
  digitalWrite(tien2, LOW);
  digitalWrite(lui1, LOW);
  digitalWrite(lui1, LOW);
  myservo.write(90); 
  delay(500);




}

void loop()
{
  khoangcach = 0; --initial state
  dokhoangcach();
  if (khoangcach > gioihan || khoangcach == 0) //if initial state=0 or distance>15 will move (mafish 7etta odamy)
  {
      dithang();
  }
  else 
  {
    resetdongco();
    quaycbsangtrai(); //will move servo 180
    dokhoangcach();  // wa2af e trig signa el ba3ttha w eb3at signal tanya check new pos of servo
    khoangcachtrai = khoangcach;
    quaycbsangphai();
    dokhoangcach(); 
    khoangcachphai = khoangcach;
    if (khoangcachphai < 30 && khoangcachtrai < 30) {    //law 7ykhbat 7yrg la wara
      dilui();
    }
    else
    {
      if (khoangcachphai >= khoangcachtrai) //zabt zwaya shemal
      {        
        disangphai();
        delay(500);
      }
      if (khoangcachphai < khoangcachtrai) //zabt zwaya yemen
      {
        disangtrai();
        delay(500);
      }
    }
  }

}
void dithang() //7imshy forward
{

  digitalWrite(tien1, HIGH);
  digitalWrite(tien2, HIGH);


}

void disangphai()  //3gl y7wd shmal 
{
  resetdongco();
  digitalWrite(lui1, HIGH);
  delay(900);
  digitalWrite(lui1, LOW);


}
void disangtrai() //bi7wed lal ganb
{
  resetdongco();
  digitalWrite(lui2, HIGH);
  delay(900);
  digitalWrite(lui2, LOW);

}

void dilui() //backward function
{
  resetdongco();
  for (i = 0; i < 20; i++)
  digitalWrite(lui1, HIGH);
  digitalWrite(lui2, HIGH);
  delay(1000);


  digitalWrite(lui1, LOW);
  digitalWrite(lui2, LOW);
}

void resetdongco()
{
  digitalWrite(tien1, LOW);
  digitalWrite(tien2, LOW);
  digitalWrite(lui1, LOW);
  digitalWrite(lui2, LOW);
}

void dokhoangcach()
{

  digitalWrite(trig, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);  
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 


 
  thoigian = pulseIn(echo, HIGH);

  khoangcach = thoigian / 2 / 29.412;

}


void quaycbsangtrai() //khali el trig yeghyar etghao 180 w ye trig another signal
{
  myservo.write(180);              // tell servo to go to position in variable 'pos'
  delay(1000);
  dokhoangcach();
  myservo.write(90);              // tell servo to go to position in variable 'pos'
}
void quaycbsangphai()
{
  myservo.write(0);              // tell servo to go to position in variable 'pos'
  delay(1000);
  dokhoangcach();
  myservo.write(90);              // tell servo to go to position in variable 'pos'
}
void resetservo()
{
  myservo.write(90);
}
