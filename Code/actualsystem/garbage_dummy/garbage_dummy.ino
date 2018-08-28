#include <SoftwareSerial.h>
#include<LiquidCrystal.h>


LiquidCrystal lcd (10,11,12,13,6,5);

int obstaclePin50 = 3;  // This is our input pin
int obstaclePin100 = 7;  // This is our input pin
int Obstacle50 = HIGH;  // HIGH MEANS NO OBSTACLE
int Obstacle100 = HIGH;  // HIGH MEANS NO OBSTACLE

int obstaclePin50_2 = A1;  // This is our input pin
int obstaclePin100_2 = A5;  // This is our input pin
int Obstacle50_2 = HIGH;  // HIGH MEANS NO OBSTACLE
int Obstacle100_2 = HIGH;  // HIGH MEANS NO OBSTACLE
const int buzzer = A2; 
const int sensor = A3;
const int sensor1 = A0;
int state,state1,state2; // 0 close - 1 open wwitch

String ssid="Falcon";
String password="marvel10";
int i = 0;
int j = 0;
int k = 0;

int delayTime2 = 350; // Delay between shifts

SoftwareSerial ARD(8, 9);

void scrollInFromRight (int line, char str1[]) {
  i = strlen(str1);
  for (j = 16; j >= 0; j--) {
    lcd.setCursor(0, line);
    for (k = 0; k <= 15; k++) {
      lcd.print(" "); // Clear line
    }
    lcd.setCursor(j, line);
    lcd.print(str1);
    delay(delayTime2);
  }
}


void scrollInFromLeft (int line, char str1[]) {
  i = 40 - strlen(str1);
  line = line - 1;
  for (j = i; j <= i + 16; j++) {
    for (k = 0; k <= 15; k++) {
      lcd.print(" "); // Clear line
      }
      lcd.setCursor(j, line);
      lcd.print(str1);
      delay(delayTime2);
   }
}

void setup()
{
  Serial.begin(115200);
  ARD.begin(115200);
  lcd.begin(16, 2);
  scrollInFromRight(0, " Welcome to the");
  scrollInFromLeft(1, "     System");
  delay(100);
  lcd.clear();
  pinMode(sensor, INPUT);
  pinMode(obstaclePin50, INPUT);
  pinMode(obstaclePin100, INPUT); 
  delay(500);
  ARD.print("u");
  ARD.print(ssid);
  ARD.print("\n");
  delay(100);
  ARD.print("p");
  ARD.print(password);
  ARD.print("\n");
  delay(200);
}

void loop()
{
  char bin1,bin2;
if(ARD.available())
{
  while(ARD.read()!='*');
  bin1 = bin_1();
  bin2 = bin_2();
  lcd.setCursor(0,0);
  lcd.print(" Bin1=");
  lcd.print(bin1);

lcd.setCursor(0,1);
lcd.print(" Bin2=");
lcd.print(bin2);
if(bin1=='F' || bin2=='F')
{  
 if (state == LOW && bin1=='F' )
  {
     tone(buzzer, 1000);
     delay(1000);
  }
   if (state1 == LOW && bin2=='F')
   {
     tone(buzzer, 1000);
     delay(1000);
   }
  else{
    noTone(buzzer);
  }
    }
}
}


 char bin_1()
 {
   char chr;
  Obstacle50 = digitalRead(obstaclePin50); //Reads the output of the obstacle sensor from the 7th PIN of the Digital section of the arduino
  Obstacle100 = digitalRead(obstaclePin100); //Reads the output of the obstacle sensor from the 7th PIN of the Digital section of the arduino
  state = digitalRead(sensor);
  if (Obstacle50 == HIGH && Obstacle100 == HIGH) //LOW means something is ahead, so illuminates the 13th Port connected LED
  {
    noTone(buzzer);
    ARD.print("!");
    ARD.print("B1 50%");
    ARD.print("\a");
    chr='B';
  }
  else if (Obstacle50 == LOW && Obstacle100 == HIGH) //LOW means something is ahead, so illuminates the 13th Port connected LED
  {
    noTone(buzzer);
    ARD.print("!");
    ARD.print("A1 50%");
    ARD.print("\a");
    chr='A';
  }
  else if (Obstacle50 == LOW && Obstacle100 == LOW) //LOW means something is ahead, so illuminates the 13th Port connected LED
  {
    ARD.print("!");
    ARD.print("F1 100%");
    ARD.print("\a");
    chr='F';
  }
  else
  {
    ARD.print("!");
    ARD.print("F1 100%");
    ARD.print("\a");
    chr='F'; 
  }
  return chr;
 }

 char bin_2()
 {
   char chr;
  Obstacle50_2 = digitalRead(obstaclePin50_2); //Reads the output of the obstacle sensor from the 7th PIN of the Digital section of the arduino
  Obstacle100_2 = digitalRead(obstaclePin100_2); //Reads the output of the obstacle sensor from the 7th PIN of the Digital section of the arduino
  state = digitalRead(sensor1);
  if (Obstacle50_2 == HIGH && Obstacle100_2 == HIGH) //LOW means something is ahead, so illuminates the 13th Port connected LED
  {
    noTone(buzzer);
    ARD.print("#");
    ARD.print("B2 50%");
    ARD.print("\a");
    chr='B';
  }
  else if (Obstacle50_2 == LOW && Obstacle100_2 == HIGH) //LOW means something is ahead, so illuminates the 13th Port connected LED
  {
    noTone(buzzer);
    ARD.print("#");
    ARD.print("A2 50%");
    ARD.print("\a");
    chr='A';
  }
  else if (Obstacle50_2 == LOW && Obstacle100_2 == LOW) //LOW means something is ahead, so illuminates the 13th Port connected LED
  {
    ARD.print("#");
    ARD.print("F2 100%");
    ARD.print("\a");
    chr='F';
  }
  else
  {
    ARD.print("#");
    ARD.print("F2 100%");
    ARD.print("\a");
    chr='F';
    
  }
  return chr;
 }


