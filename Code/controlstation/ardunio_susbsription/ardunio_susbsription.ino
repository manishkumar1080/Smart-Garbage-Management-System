#include <SoftwareSerial.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd (13,12,11,10,9,8);

String ssid="Falcon";
String password="marvel10";
String temp;
const int buzzer = 7; 
int i = 0;
int j = 0;
int k = 0;


SoftwareSerial  ARD(2, 3);

int delayTime2 = 350; // Delay between shifts

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
  scrollInFromLeft(1, " Control Station");
  lcd.clear();
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
  ARD.print("*");
 if(ARD.available())
{
 while(ARD.read()!='#');
 char ch1,ch2;
 ch1=ARD.read();
 switch(ch1)
          {
            case '1':
                        ch2=ARD.read();
                        switch(ch2)
                        {
                                  case '1':
                                          noTone(buzzer);
                                          lcd.setCursor(0,0);
                                          lcd.print("Bin1= B 50%    ");
                                          break;
                    
                                  case '2':
                                          noTone(buzzer);
                                          lcd.setCursor(0,0);
                                          lcd.print("Bin1= A 50%     ");
                                          break;
                   
                                  case '3':
                                          lcd.setCursor(0,0);
                                          lcd.print("Bin1= F 100%");
                                          tone(buzzer, 1000);
                                          break;
                          
                        }
                        break;
             case '2':
                        ch2=ARD.read();
                        switch(ch2)
                        {
               
                                  case '1':
                                        noTone(buzzer);
                                        lcd.setCursor(0,1);
                                        lcd.print("Bin2= B 50%      ");
                                        break;

                    
                                 case '2':
                                        noTone(buzzer);
                                        lcd.setCursor(0,1);
                                        lcd.print("Bin2= A 50%      ");
                                        break;
                    
                                case '3':
                                        lcd.setCursor(0,1);
                                        lcd.print("Bin2= F 100%");
                                        tone(buzzer, 1000);
                                        break;
                          }
                          break;
          }
}
}
