#include <SoftwareSerial.h>
#include <Sleep_n0m1.h>
#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>

 void SendMessage(int count[100][3]);
Sleep sleep;

int calibrationTime = 30;        

//Mario main theme melody
int c=0,c1=0;
unsigned int address = 0;
unsigned int addr = 0;
byte value,value1;
int z=0,date,last_day,last_year,last_date; 
int count[100][2]={},curr_time[2]={},count2[100][2]={},last_hour=0,last_minute=0,actual_hour=0,actual_minute=0;

int pirPin = 2;    //the digital pin connected to the PIR sensor's output
int gsmpwr = 5;
int pir=0;
int l=0;
SoftwareSerial mySerial(10, 11);

RTC_DS1307 rtc;

void setup()
{
   
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  pinMode(gsmpwr, OUTPUT);//buzzer
    pinMode(pirPin, INPUT);

  delay(200);
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(100);
      }
    Serial.println(" done");
   
    delay(50);

 
  
     if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
   // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2016, 5, 15, 5, 47, 0));
  }

 digitalWrite(gsmpwr, HIGH);
 
 delay(200);

value1 = EEPROM.read(52);
addr=value1;
date=EEPROM.read(62);
last_date=date;
Serial.println(date);

}



void loop()
{
  if(date!=last_date)
  {
    Serial.print("send msg1");
    ///digitalWrite(gsmpwr, HIGH);
    //delay(40000);   
    addr=0;
    c1=0;
    eeprom_read();
    SendMessage(count2);
    eeprom_clear();
    address=0;
    last_date=date;
   // delay(70000);
    //digitalWrite(gsmpwr, LOW);
  delay(100); //delay to allow serial to fully print before sleep   
  sleep.pwrDownMode();
    
  }
  
  
  if(addr==2)
  {
    Serial.print("send msg");
    //digitalWrite(gsmpwr, HIGH);
    //delay(40000);   
    addr=0;
    c1=0;
    eeprom_read();
    SendMessage(count2);
    eeprom_clear();
    address=0;
    //delay(70000);
    //digitalWrite(gsmpwr, LOW);
    last_date=date;
  delay(100); //delay to allow serial to fully print before sleep   
  sleep.pwrDownMode(); //set sleep mode 
  }


  
  Serial.println(addr);
  DateTime now = rtc.now();
   int z=pir_sensor();
  clock_time();
    
    
    if (z==1)
         {   
          //melody1();
          z=0;
          pir=0;
          Serial.print("z=");
          Serial.println(z);
          delay(100);
        }  
  
  
    if(curr_time[1]!=last_minute)
      {
       int z=pir_sensor();
       Serial.print("zzzzzzzz=");
       Serial.println(z);
       Serial.println("c=");
          Serial.println(c); 
        
          if((curr_time[1]>(last_minute+1))||(curr_time[0]!=last_hour))
             {      
                actual_minute=last_minute-(c-1);
                Serial.print("actual_minute5=");
                Serial.println(actual_minute);
                Serial.print("c=");
                Serial.println(c);
                actual_hour=last_hour;
                
                if(actual_minute<0)
                  {
                  actual_minute=60+actual_minute;
                  actual_hour=last_hour-1;
                  }
                
                
                if(actual_hour<0)
                 {
                  actual_hour=24+actual_hour;
                 }
      
            
         
       
         for(int k=0;k<2;k++)
         {
    
                if(k==0)
                {count[c1][k]=actual_hour;
                Serial.println(count[c1][0]);
                }
                
                if(k==1)
                {
                count[c1][k]=actual_minute;
                Serial.println(count[c1][1]);
                }
        
           c=0;
           Serial.println("c1=");
           Serial.println(c1);
        }
      Serial.println("eeprom write");
      eeprom_write(count[c1][0],count[c1][1]);
      c1++;
      
    }
  c++;
 last_hour= curr_time[0];
 last_minute=curr_time[1];

  
  }
  
  
    

  Serial.print("Sleeping Till Interrupt");
  delay(100); //delay to allow serial to fully print before sleep   
  sleep.pwrDownMode(); //set sleep mode 
  //Sleep till interrupt pin equals a particular state. 
  //In this case "falling" change from 1 to 0.
  sleep.sleepInterrupt(0,RISING); //(interrupt Number, interrupt State)
   //sleep.sleepInterrupt(1,RISING);

}
 
 

 
