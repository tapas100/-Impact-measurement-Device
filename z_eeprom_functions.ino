void eeprom_clear()
{
   for ( unsigned int i = 0 ; i < 51 ; i++ )
    EEPROM.write(i, 0);
}
int eeprom_write(int g,int h)
{
  
  Serial.println("actual_hour3=");
      Serial.println(g);
      
  Serial.println("actual_minute3=");
      Serial.println(h);
  EEPROM.write(addr, g);
   Serial.println("addr=");
  Serial.println(addr);
 addr=addr+1;
 EEPROM.write(addr, h);
 Serial.println("addr=");
  Serial.println(addr);
 addr=addr+1;
 Serial.println("addr=");
  Serial.println(addr);
 EEPROM.write(52, addr);
  
  if(addr == EEPROM.length())
    addr = 0;

}
void eeprom_read()
{
  for(int v=0;v<1;v++)
  {
   for(int b=0;b<2;b++)
   {
  value = EEPROM.read(address);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();
  count2[v][b]=value;
  Serial.println(count2[v][b]);
  address = address + 1;
  if(address == EEPROM.length())
    address = 0;
   }
  }
}

