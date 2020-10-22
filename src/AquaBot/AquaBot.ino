
#include <Arduino.h>
#include "AsyncTelegram.h"
#include "ArduinoJson.h"
#include "ESP8266HTTPClient.h"
AsyncTelegram myBot;

#include <OneWire.h>
#include <DallasTemperature.h>

const char* ssid = "WiFi_NAME";
const char* pass = "WiFi_PASS";
const char* token = "BOT_TOKEN"
String users[] = {"???", "???", "???", "???", "???", "???", "???", "???", "???", "???"};
int notification[] = {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0};

#define Led1 3
#define Led2 1
#define inputTemp 0

OneWire oneWire(inputTemp);
DallasTemperature sensors(&oneWire);

DeviceAddress *sensorsUnique;
int countSensors;


void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

#include <iarduino_RTC.h>
iarduino_RTC watch(RTC_DS1307);

bool isLed1On = false;
bool isLed2On = false;

int lightingOnHour = 10;
int lightingOffHour = 18;

int hourLed1On = 0;
int minuteLed1On = 0;
int secondLed1On = 0;
int tempSecond1 = -1;

int hourLed2On = 0;
int minuteLed2On = 0;
int secondLed2On = 0;
int tempSecond2 = -1;

int lightingOnMinute = 0;
int lightingOffMinute = 0;

bool isSendMsgLedON = false;
bool isSendMsgLedOFF = false;

int currentHour, currentMinute, currentSecond;

float minTemp = 20.0;
float maxTemp = 27.0;
float currentTemp[2];

float minTemp1ForReport = 100;
float maxTemp1ForReport = 0;

int minTemp1HourForReport;
int minTemp1MinuteForReport;
int maxTemp1HourForReport;
int maxTemp1MinuteForReport;

float minTemp2ForReport = 100;
float maxTemp2ForReport = 0;

int minTemp2HourForReport;
int minTemp2MinuteForReport;
int maxTemp2HourForReport;
int maxTemp2MinuteForReport;

int hourForReport = 23;
int minuteForReport = 0;

bool isSendMsgCriticalMinTemp1 = false;
bool isSendMsgCriticalMaxTemp1 = false;
bool isSendMsgCriticalMinTemp2 = false;
bool isSendMsgCriticalMaxTemp2 = false;
int sendHoutMsg1;
int sendHoutMsg2;

bool isSettingTimeForReport  = false;
bool isSendMsgReport  = false;

bool isSettingMinTemp  = false;
bool isSettingMaxTemp  = false;

bool isSettingLedON  = false;
bool isSettingLedOFF = false;

bool isSettingAddUser = false;
bool isSettingDeleteUser = false;

bool isStart = true;
bool isRestart = true;
String rebootTime  = "";

TBMessage msgReal;

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

  while (!Serial);
  sensors.begin();
  countSensors = sensors.getDeviceCount();
  Serial.print("Found sensors: ");
  Serial.println(countSensors);

  sensorsUnique = new DeviceAddress[countSensors];

  if (sensors.isParasitePowerMode()) {
    Serial.println("Mode power is Parasite");
  } else {
    Serial.println("Mode power is Normal");
  }

  for (int i = 0; i < countSensors; i++) {
    sensors.getAddress(sensorsUnique[i], i);
  }

  for (int i = 0; i < countSensors; i++) {
    Serial.print("Device ");
    Serial.print(i);
    Serial.print(" Address: ");
    printAddress(sensorsUnique[i]);
    Serial.println();
  }
  Serial.println();
  for (int i = 0; i < countSensors; i++) {
    sensors.setResolution(sensorsUnique[i], 12);
  }

  delay(300);
  watch.begin();
}

static bool login(const char* username, String users [])
{
  bool result = false;
  String usernameStr = username;
  int usersCount = sizeof(users);
  for (int i = 0; i < usersCount + 1; i++)
  {
    if (users[i].equals("???"))
    {
      break;
    }
    if (usernameStr.equals(users[i]))
    {
      result = true;
    }
  }

  return result;
}

void loop()
{


  TBMessage msg;

  sensors.requestTemperatures();
  for (int i = 0; i < countSensors; i++) {
    currentTemp[i] = sensors.getTempCByIndex(i);
  }

  watch.gettime();
  currentHour = watch.Hours;
  currentMinute = watch.minutes;
  currentSecond = watch.seconds;

  if (isRestart)
  {
    msgReal.sender.id = notification[0];
    Serial.println("Restart");
    digitalWrite(Led1, HIGH);
    digitalWrite(Led2, HIGH);
    secondLed1On = 0;
    secondLed2On = 0;

    autoSetTime(myBot,msg);

    rebootTime = watch.gettime("d");;
    rebootTime += "-";
    rebootTime += watch.gettime("m");;
    rebootTime += "-";
    rebootTime += watch.gettime("Y");;
    rebootTime += "\n";
    rebootTime  += watch.gettime("H");;
    rebootTime += ":";
    rebootTime += watch.gettime("i");;
    rebootTime += ":";
    rebootTime += watch.gettime("s");;

    String reply = "#RestartBot";
    reply +=  "\n";
    reply +=  rebootTime;

    isRestart = false;
    myBot.sendMessage(msgReal, reply);
  }

  if (isStart)
  {
    AutoController(myBot, msgReal, currentHour, currentMinute, currentSecond, currentTemp);
  }

  if (myBot.getNewMessage(msg))
  {

    if (login(msg.sender.username, users))
    {
      Controller(msg);
    }
    else
    {
      String text;
      text += "#Атака!";
      text +=  "\n";
      text +=  "\n";
      text += "id: ";
      text += String(msg.sender.id);
      text +=  "\n";
      text += "firstName: ";
      text += String(msg.sender.firstName);
      text +=  "\n";
      text += "lastName: ";
      text += String(msg.sender.lastName);
      text +=  "\n";
      text += "username: ";
      text += String(msg.sender.username);

      text +=  "\n";
      text += "text: ";
      text +=  "\n";
      text += String(msg.text);
      
      myBot.sendMessage(msgReal, text);
      myBot.sendMessage(msg, "Давай, до свидания!");
    }
  }
}
