void clock_time()
{
  DateTime now = rtc.now();
     Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    Serial.print(now.year(), DEC);
    Serial.println();
    if(now.day()!=last_day)
    {
      date=now.day()+((now.month()-1)*30);
 
      EEPROM.write(62, date);
    
    }
    last_day=now.day();
    for(int j=0;j<2;j++)
    {
      if(j==0)
      {curr_time[j]=now.hour();
      Serial.println("curr_hour");
      Serial.println(curr_time[j]);
      }
      else if(j==1)
      {curr_time[j]=now.minute();
      Serial.println("curr_minute=");
      Serial.println(curr_time[j]);
      }
    }
}



int pir_sensor()
{
  if(digitalRead(pirPin) == HIGH&&pir==0)
  {
       pir=1;
       Serial.println("pirrr");
  }

 return pir;
}

