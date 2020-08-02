#include <Arduino.h>
#include "AsyncTelegram.h"
AsyncTelegram myBot;

#include <OneWire.h>
#include <DallasTemperature.h>

const char* ssid = "xxx";
const char* pass = "xxx";     
const char* token = "xxx";
const String users = "xxx";

#define Led1 3
#define Led2 1
#define inputTemp 0

OneWire oneWire(inputTemp);
DallasTemperature sensor(&oneWire);

#include <iarduino_RTC.h>                                             
iarduino_RTC watch(RTC_DS1307);  

bool isLed1On = false;
bool isLed2On = false;

int lightingOnTime = 11;
int lightingOffTime = 18;
int currentHour, currentMinute, currentSecond;

bool isDay = false;
                                                                             
float minTemp = 20.0;
float maxTemp = 27.0;
float currentTemp;

bool isSendMsgCriticalMinTemp = false;
bool isSendMsgCriticalMaxTemp = false;

bool isSettingMinTemp  = false;
bool isSettingMaxTemp  = false;

bool isSettingLedON  = false;
bool isSettingLedOFF = false;

bool isStart = false;

void setup() 
{
	Serial.begin(115200);
	Serial.println("Starting TelegramBot...");

	WiFi.setAutoConnect(true);   
	WiFi.mode(WIFI_STA);
 	
	WiFi.begin(ssid, pass);
	delay(500);
	while (WiFi.status() != WL_CONNECTED) 
	{
		Serial.print('.');
		delay(500);
	}

	myBot.setUpdateTime(1000);
	myBot.setTelegramToken(token);
	
	Serial.print("\nTest Telegram connection... ");
	myBot.begin() ? Serial.println("OK") : Serial.println("NOK");

  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);

  sensor.begin();
  sensor.setResolution(12);

  delay(300); 
  watch.begin();  
}

 static bool login(const char* username, const String users)
 {
   String usernameStr = username;
   bool res = usernameStr.equals(users);
   return res;
 }
  
void loop() 
{
	TBMessage msg;
  sensor.requestTemperatures();
  
  currentTemp = sensor.getTempCByIndex(0);
                                            
  watch.gettime();                                                  
  currentHour = watch.Hours;                                                  
  currentMinute = watch.minutes;                                                
  currentSecond = watch.seconds;                                                

  if (isStart)
  {
     AutoController(myBot, msg, currentHour, currentTemp);
  }
  
	if (myBot.getNewMessage(msg)) 
	{
     if(login(msg.sender.username, users))
     {
        Controller(msg);
     }
     else
     {
        myBot.sendMessage(msg, "А ну, канай отсюда! A то я тебе рога поотшибаю, пасть порву, моргалы выколю! Всю жизнь работать на лекарства будешь!!!");  
     }      
  }
}
