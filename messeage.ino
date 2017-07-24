void SendMessage(int count[100][2])
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  //mySerial.println("AT+CMGS=\"+917064428282\"\r");
  mySerial.println("AT+CMGS=\"+919437477499\"\r");// Replace x with mobile number
  delay(1000);
  for(int i=0;i<1;i++)
  {
  for(int l=0;l<2;l++)
  { 
  mySerial.print(count[i][l]);
  delay(50);
  //Serial.print(count[i][l]);
  if(l<1)
 { mySerial.print(":");
  // The SMS text you want to send
  //Serial.print(":");
  }
  
  }
  mySerial.print(",");
  Serial.print(",");
  }
  mySerial.println(date);
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  
}

