/*
  MCP7941x.cpp - Arduino Library for using the MCP7941x IC.

  Ian Chilton <ian@ichilton.co.uk>
  November 2011

  Only currently supports 24hr clock and doesn't do any validation.
*/

#if (ARDUINO >= 100)
#include <Arduino.h>
#define WireSend(x) Wire1.write(x)
#define WireReceive() Wire1.read()
#else
#include <WProgram.h>
#define WireSend(x) Wire1.send(x)
#define WireReceive(x) Wire1.receive(x)
#endif

#include "Wire.h"
#include <WiFi.h>
#include "MCP7941x.h"
//============ Internet time Definition ====================//
#include "time.h"
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600*7;// GTM+7 for Bangkok Hanoi Jakata
const int   daylightOffset_sec = 0;

// Constructor:
MCP7941x::MCP7941x()
{
  Wire1.begin();
}

// Convert normal decimal numbers to binary coded decimal:
byte MCP7941x::decToBcd(byte val)
{
  return ((val / 10 * 16) + (val % 10));
}

// Convert binary coded decimal to normal decimal numbers:
byte MCP7941x::bcdToDec(byte val)
{
  return ((val / 16 * 10) + (val % 16));
}

// Function to read the mac address from the eeprom:
void MCP7941x::getMacAddress(byte *mac_address)
{
  Wire1.beginTransmission(MCP7941x_EEPROM_I2C_ADDR);
  WireSend(MAC_LOCATION);
  Wire1.endTransmission();

  Wire1.requestFrom(MCP7941x_EEPROM_I2C_ADDR, 6);

  for (int i = 0; i < 6; i++)
  {
    mac_address[i] = WireReceive();
  }
}

// Unlock the unique id area ready for writing:
void MCP7941x::unlockUniqueID()
{
  // Write 0x55 to the memory location 0x09 and stop:
  Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
  WireSend(0x09);
  WireSend(0x55);
  Wire1.endTransmission();

  // Write 0xAA to the memory location 0x09 and stop:
  Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
  WireSend(0x09);
  WireSend(0xAA);
  Wire1.endTransmission();
}

// Unlock the unique id area and write in the mac address:
void MCP7941x::writeMacAddress(byte *mac_address)
{
  Wire1.beginTransmission(MCP7941x_EEPROM_I2C_ADDR);
  WireSend(0xF2);

  for (int i = 0; i < 6; i++)
  {
    WireSend(mac_address[i]);
  }

  Wire1.endTransmission();
}

// Set the date/time, set to 24hr and enable the clock:
// (assumes you're passing in valid numbers)
void MCP7941x::setDateTime(
    byte second,     // 0-59
    byte minute,     // 0-59
    byte hour,       // 1-23
    byte dayOfWeek,  // 1-7
    byte dayOfMonth, // 1-28/29/30/31
    byte month,      // 1-12
    byte year)       // 0-99
{
  Wire1.begin(4, 5);
  Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
  WireSend(RTC_LOCATION);

  WireSend(decToBcd(second) & 0x7f);             // set seconds and disable clock (01111111)
  WireSend(decToBcd(minute) & 0x7f);             // set minutes (01111111)
  WireSend(decToBcd(hour) & 0x3f);               // set hours and to 24hr clock (00111111)
  WireSend(0x08 | (decToBcd(dayOfWeek) & 0x07)); // set the day and enable battery backup (00000111)|(00001000)
  WireSend(decToBcd(dayOfMonth) & 0x3f);         // set the date in month (00111111)
  WireSend(decToBcd(month) & 0x1f);              // set the month (00011111)
  WireSend(decToBcd(year));                      // set the year (11111111)

  Wire1.endTransmission();

  // Start Clock:
  Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
  WireSend(RTC_LOCATION);
  WireSend(decToBcd(second) | 0x80); // set seconds and enable clock (10000000)
  Wire1.endTransmission();
}

bool MCP7941x::syncTime(char *ssid,char *password,unsigned int timeout)
{
  struct tm timeinfo;  
  //configTime(gmtOffset_sec, 0, ntpServer);
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  for(int i=0;i<timeout*2;i++) 
  {
      if(WiFi.status() == WL_CONNECTED)
	  {
		//ledWIFI(1);		// ON LED Wifi status
		digitalWrite(KB_LED_WIFI,0);
		Serial.println();
		Serial.println("CONNECTED!");
		//init and get the time
		configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
		//printLocalTime();
		if(!getLocalTime(&timeinfo)){
			Serial.println("Failed to obtain time");
			return false;
		}
		uint8_t year = (timeinfo.tm_year+1900)%2000;
		uint8_t month = timeinfo.tm_mon + 1;
		uint8_t dayOfWeek = timeinfo.tm_wday;
		uint8_t dayOfMonth = timeinfo.tm_mday;
		uint8_t hour = timeinfo.tm_hour;
		uint8_t min = timeinfo.tm_min;
		uint8_t sec = timeinfo.tm_sec;
		//setDate(dayOfMonth,month,year%2000);
		//setTime(hour,min,sec);
		setDateTime(sec,min,hour,dayOfWeek,dayOfMonth,month,year);
		//disconnect WiFi as it's no longer needed
		WiFi.disconnect(true);
		WiFi.mode(WIFI_OFF);	
		digitalWrite(KB_LED_IOT,0);
		//ledIOT(1);		// ON LED IOT status
		//ledWIFI(0);		// ON LED WIFI status
		//sound(600,100);		// Alarm for Get time success!
		delay(200);
		//sound(1200,100);
		//ledIOT(0);		// OFF LED IOT status
		digitalWrite(KB_LED_IOT,1);
		digitalWrite(KB_LED_WIFI,1);
		return true;
	  }
	  digitalWrite(KB_LED_WIFI,!digitalRead(KB_LED_WIFI));	// Blink LED WIFI
	  delay(500);
	  Serial.print(".");
  }
  //ledWIFI(0);	// OFF LED Wifi status
	digitalWrite(KB_LED_IOT,1);
	digitalWrite(KB_LED_WIFI,1);
  Serial.println();
  Serial.println("Time Out!");
  return false;
}
// Get the date/time:
void MCP7941x::getDateTime(
    byte *second,
    byte *minute,
    byte *hour,
    byte *dayOfWeek,
    byte *dayOfMonth,
    byte *month,
    byte *year)
{
  Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
  WireSend(RTC_LOCATION);
  Wire1.endTransmission();

  Wire1.requestFrom(MCP7941x_RTC_I2C_ADDR, 7);

  // A few of these need masks because certain bits are control bits
  *second = bcdToDec(WireReceive() & 0x7f);     // 01111111
  *minute = bcdToDec(WireReceive() & 0x7f);     // 01111111
  *hour = bcdToDec(WireReceive() & 0x3f);       // 00111111
  *dayOfWeek = bcdToDec(WireReceive() & 0x07);  // 01111111
  *dayOfMonth = bcdToDec(WireReceive() & 0x3f); // 00111111
  *month = bcdToDec(WireReceive() & 0x1f);      // 00011111
  *year = bcdToDec(WireReceive());              // 11111111
}

// Enable the clock without changing the date/time:
void MCP7941x::enableClock()
{
  // Get the current seconds value as the enable/disable bit is in the same
  // byte of memory as the seconds value:
  Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
  WireSend(RTC_LOCATION);
  Wire1.endTransmission();

  Wire1.requestFrom(MCP7941x_RTC_I2C_ADDR, 1);

  int second = bcdToDec(WireReceive() & 0x7f); // 01111111

  // Start Clock:
  Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
  WireSend(RTC_LOCATION);
  WireSend(decToBcd(second) | 0x80); // set seconds and enable clock (10000000)
  Wire1.endTransmission();
}

// Disable the clock without changing the date/time:
void MCP7941x::disableClock()
{
  // Get the current seconds value as the enable/disable bit is in the same
  // byte of memory as the seconds value:
  Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
  WireSend(RTC_LOCATION);
  Wire1.endTransmission();

  Wire1.requestFrom(MCP7941x_RTC_I2C_ADDR, 1);

  int second = bcdToDec(WireReceive() & 0x7f); // 01111111

  // Start Clock:
  Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
  WireSend(RTC_LOCATION);
  WireSend(decToBcd(second)); // set seconds and disable clock (01111111)
  Wire1.endTransmission();
}

// Enable the battery:
void MCP7941x::enableBattery()
{
  // Get the current seconds value as the enable/disable bit is in the same
  // byte of memory as the seconds value:
  Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
  WireSend(RTC_LOCATION + 0x03);
  Wire1.endTransmission();

  Wire1.requestFrom(MCP7941x_RTC_I2C_ADDR, 1);

  int day = bcdToDec(WireReceive() & 0x07); // 00000111

  // Start Clock:
  Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
  WireSend(RTC_LOCATION + 0x03);
  WireSend(decToBcd(day) | 0x08); // set day and enable battery (00001000)
  Wire1.endTransmission();
}

// Store byte of data in SRAM:
void MCP7941x::setSramByte(byte location, byte data)
{
  if (location >= 0x20 && location <= 0x5f)
  {
    Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
    WireSend(location);
    WireSend(data);
    Wire1.endTransmission();
  }
}

// Read byte of data from SRAM:
byte MCP7941x::getSramByte(byte location)
{
  if (location >= 0x20 && location <= 0x5f)
  {
    Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
    WireSend(location);
    Wire1.endTransmission();

    Wire1.requestFrom(MCP7941x_RTC_I2C_ADDR, 1);

    return WireReceive();
  }
}
// Store Word of data in SRAM:
void  MCP7941x::setSramWord ( byte location, int data )
{
 if (location >= 0x00 && location <= 0x20)
  {
	byte location_high = 0x20 + (location * 2);
    byte location_low = location_high + 1;
	
    byte data_high = (((uint16_t)data)>>8);
	byte data_low = (((uint16_t)data)&0x00ff);
  
	Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
	WireSend(location_high);
    WireSend(data_high);
    Wire1.endTransmission();
	delay(10);
    Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
	WireSend(location_low);
    WireSend(data_low);
    Wire1.endTransmission();
	delay(10);
  }
/*
  if (location >= 0x20 && location <= 0x5f)
  {
    Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
    WireSend(location);
    WireSend(data);
    Wire1.endTransmission();
  }
*/
}
// Read word of data from SRAM:
int  MCP7941x::getSramWord ( byte location )
{
	
  if (location >= 0x00 && location <= 0x20)
  {
	byte location_high = 0x20 + (location * 2);
    byte location_low = location_high + 1;
	  
	byte data_high = 0x00;
	byte data_low = 0x00;
	
	Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
    WireSend(location_high);
    Wire1.endTransmission();
    delay(10);
    Wire1.requestFrom(MCP7941x_RTC_I2C_ADDR, 1);
	delay(10);
    data_high = WireReceive();
    delay(10);
	
	Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
    WireSend(location_low);
    Wire1.endTransmission();
    delay(10);
    Wire1.requestFrom(MCP7941x_RTC_I2C_ADDR, 1);
	delay(10);
    data_low = WireReceive();
    delay(10);
    return  ((int16_t)word(data_high,data_low));
  }
  
 /* if (location >= 0x20 && location <= 0x5f)
  {
    Wire1.beginTransmission(MCP7941x_RTC_I2C_ADDR);
    WireSend(location);
    Wire1.endTransmission();
    delay(10);
    Wire1.requestFrom(MCP7941x_RTC_I2C_ADDR, 1);

    return WireReceive();
  }
  */
}

// Store byte of data in EEPROM:
void MCP7941x::setEepromByte(byte location, byte data)
{
  if (location >=0 && location <= 127)
  {
    Wire1.beginTransmission(MCP7941x_EEPROM_I2C_ADDR);
    WireSend(location);
    WireSend(data);
    Wire1.endTransmission();
  }
  delay(10);
}

// Read byte of data from EEPROM:
byte MCP7941x::getEepromByte(byte location)
{

  if (location >=0 && location <= 127)
  {
    Wire1.beginTransmission(MCP7941x_EEPROM_I2C_ADDR);
    WireSend(location);
    Wire1.endTransmission();
    delay(10);
    Wire1.requestFrom(MCP7941x_EEPROM_I2C_ADDR, 1);

    return WireReceive();
  }
  delay(10);
}

String MCP7941x::getDateTimeString()
{
  Wire1.begin(4, 5);
  getDateTime(&_second, &_minute, &_hour, &_dayOfWeek, &_dayOfMonth, &_month, &_year);
    String h=String(_hour);
    String m=String(_minute);
	String dm=String(_dayOfMonth);
    String mo=String(_month);
	String y=String(_year);
	if(_dayOfMonth<10){
      dm="0"+dm;
    }
	if(_month<10){
      mo="0"+mo;
    }
	if(_year<10){
      y="0"+y;
    }
    if(_minute<10){
      m="0"+m;
    }
    if(_hour<10){
      h="0"+h;
    }
     
  return dm+"/"+mo+"/20"+y+" "+h+":"+m;
}

String MCP7941x::getDateString()
{
  Wire1.begin(4, 5);
  getDateTime(&_second, &_minute, &_hour, &_dayOfWeek, &_dayOfMonth, &_month, &_year);
    String h=String(_hour);
    String m=String(_minute);
	String dm=String(_dayOfMonth);
    String mo=String(_month);
	String y=String(_year);
	if(_dayOfMonth<10){
      dm="0"+dm;
    }
	if(_month<10){
      mo="0"+mo;
    }
	if(_year<10){
      y="0"+y;
    }
    if(_minute<10){
      m="0"+m;
    }
    if(_hour<10){
      h="0"+h;
    }
     
  return dm+"/"+mo+"/20"+y;
}

String MCP7941x::getTimeString()
{
  Wire1.begin(4, 5);
  getDateTime(&_second, &_minute, &_hour, &_dayOfWeek, &_dayOfMonth, &_month, &_year);
    String h=String(_hour);
    String m=String(_minute);
	String dm=String(_dayOfMonth);
    String mo=String(_month);
	String y=String(_year);
	if(_dayOfMonth<10){
      dm="0"+dm;
    }
	if(_month<10){
      mo="0"+mo;
    }
	if(_year<10){
      y="0"+y;
    }
    if(_minute<10){
      m="0"+m;
    }
    if(_hour<10){
      h="0"+h;
    }
     
  return h+":"+m;
}

byte MCP7941x::getDayofWeek()
{
  Wire1.begin(4, 5);
  getDateTime(&_second, &_minute, &_hour, &_dayOfWeek, &_dayOfMonth, &_month, &_year);
  return _dayOfWeek;
}

byte MCP7941x::getHour()
{
  Wire1.begin(4, 5);
  getDateTime(&_second, &_minute, &_hour, &_dayOfWeek, &_dayOfMonth, &_month, &_year);
  return _hour;
}

byte MCP7941x::getMinute()
{
  getDateTime(&_second, &_minute, &_hour, &_dayOfWeek, &_dayOfMonth, &_month, &_year);
  return _minute;
}

byte MCP7941x::getSecond()
{
  Wire1.begin(4, 5);
  getDateTime(&_second, &_minute, &_hour, &_dayOfWeek, &_dayOfMonth, &_month, &_year);
  return _second;
}

byte MCP7941x::getDay()
{
  Wire1.begin(4, 5);
  getDateTime(&_second, &_minute, &_hour, &_dayOfWeek, &_dayOfMonth, &_month, &_year);
  return _dayOfMonth;
}

byte MCP7941x::getMonth()
{
  Wire1.begin(4, 5);
  getDateTime(&_second, &_minute, &_hour, &_dayOfWeek, &_dayOfMonth, &_month, &_year);
  return _month;
}

byte MCP7941x::getYear()
{
  Wire1.begin(4, 5);
  getDateTime(&_second, &_minute, &_hour, &_dayOfWeek, &_dayOfMonth, &_month, &_year);
  return _year;
}