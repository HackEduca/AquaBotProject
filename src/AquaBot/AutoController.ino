void AutoController (AsyncTelegram myBot, TBMessage msg, int currentHour, int currentMinute, int currentSecond, float currentTemp[])
{
  if (currentHour == lightingOnHour && currentMinute == lightingOnMinute && !isLedsON() && !isSendMsgLedON)
  {
    isSendMsgLedON = true;
    isSendMsgLedOFF = false;

    String reply = "#message Освещение ВКЛ автоматически";
    allLedsON(msg, reply);
  }
  else if ((currentHour == lightingOffHour && currentMinute == lightingOffMinute && isLedsON()) && !isSendMsgLedOFF)
  {
    isSendMsgLedON = false;
    isSendMsgLedOFF = true;

    String reply = "#message Освещение ВЫКЛ автоматически";
    allLedsOFF(msg, reply);
  }


  if (currentTemp[0] < minTemp && currentTemp[0] >= 0 && (isSendMsgCriticalMinTemp1 == false || isSendMsgCriticalMinTemp1 == true && sendHoutMsg1 == currentHour))
  {
    String reply = "#alarm Температура ";
    reply +=  getTempName(0);
    reply +=  " достигла минимальной критической отметки: ";
    reply +=  currentTemp[0];
    reply +=  " °C";
    myBot.sendMessage(msg, reply);

    sendHoutMsg1 = currentHour;
    sendHoutMsg1++;
    if (sendHoutMsg1 == 24)
    {
      sendHoutMsg1 = 0;
    }

    isSendMsgCriticalMinTemp1 = true;
    isSendMsgCriticalMaxTemp1 = false;
  }
  else if (currentTemp[0] > maxTemp && currentTemp[0] <= 100 && (isSendMsgCriticalMaxTemp1 == false || isSendMsgCriticalMaxTemp1 == true && sendHoutMsg1 == currentHour))
  {
    String reply = "#alarm Температура ";
    reply +=  getTempName(0);
    reply +=  " достигла максимальной критической отметки: ";
    reply +=  currentTemp[0];
    reply +=  " °C";
    myBot.sendMessage(msg, reply);

    sendHoutMsg1 = currentHour;
    sendHoutMsg1++;
    if (sendHoutMsg1 == 24)
    {
      sendHoutMsg1 = 0;
    }

    isSendMsgCriticalMaxTemp1 = true;
    isSendMsgCriticalMinTemp1 = false;
  }

  else if (currentTemp[0] <= maxTemp && currentTemp[0] >= minTemp)
  {
    isSendMsgCriticalMaxTemp1 = false;
    isSendMsgCriticalMinTemp1 = false;
  }

  if (currentTemp[1] < minTemp  && currentTemp[1] >= 0 && (isSendMsgCriticalMinTemp2 == false || isSendMsgCriticalMinTemp2 == true && sendHoutMsg2 == currentHour))
  {
    String reply = "#alarm Температура ";
    reply +=  getTempName(1);
    reply +=  " достигла минимальной критической отметки: ";
    reply +=  currentTemp[1];
    reply +=  " °C";
    myBot.sendMessage(msg, reply);

    sendHoutMsg2 = currentHour;
    sendHoutMsg2++;
    if (sendHoutMsg2 == 24)
    {
      sendHoutMsg2 = 0;
    }

    isSendMsgCriticalMinTemp2 = true;
    isSendMsgCriticalMaxTemp2 = false;
  }
  else if (currentTemp[1] > maxTemp && currentTemp[1] <= 100 && (isSendMsgCriticalMaxTemp2 == false || isSendMsgCriticalMaxTemp2 == true && sendHoutMsg2 == currentHour))
  {
    String reply = "#alarm Температура ";
    reply +=  getTempName(1);
    reply +=  " достигла максимальной критической отметки: ";
    reply +=  currentTemp[1];
    reply +=  " °C";
    myBot.sendMessage(msg, reply);

    sendHoutMsg2 = currentHour;
    sendHoutMsg2++;
    if (sendHoutMsg2 == 24)
    {
      sendHoutMsg2 = 0;
    }

    isSendMsgCriticalMaxTemp2 = true;
    isSendMsgCriticalMinTemp2 = false;
  }

  else if (currentTemp[1] <= maxTemp && currentTemp[1] >= minTemp)
  {
    isSendMsgCriticalMaxTemp2 = false;
    isSendMsgCriticalMinTemp2 = false;
  }

  if (currentTemp[0] < minTemp1ForReport && currentTemp[0] >= 0)
  {
    minTemp1ForReport = currentTemp[0];
    minTemp1HourForReport = currentHour;
    minTemp1MinuteForReport = currentMinute;
  }

  if (currentTemp[0] > maxTemp1ForReport && currentTemp[0] <= 100)
  {
    maxTemp1ForReport = currentTemp[0];
    maxTemp1HourForReport = currentHour;
    maxTemp1MinuteForReport = currentMinute;
  }

  if (currentTemp[1] < minTemp2ForReport && currentTemp[1] >= 0)
  {
    minTemp2ForReport = currentTemp[1];
    minTemp2HourForReport = currentHour;
    minTemp2MinuteForReport = currentMinute;
  }
  if (currentTemp[1] > maxTemp2ForReport && currentTemp[1] <= 100)
  {
    maxTemp2ForReport = currentTemp[1];
    maxTemp2HourForReport = currentHour;
    maxTemp2MinuteForReport = currentMinute;
  }

  if (currentHour == hourForReport && currentMinute == minuteForReport && currentSecond == 0 && !isSendMsgReport)
  {
    autoSetTime(myBot,msg);
    isSendMsgReport = true;
    sendReport(msg);
  }
  else if (currentHour == 0 && currentMinute == 0 && currentSecond == 1)
  {
    isSendMsgReport = false;

    minTemp1ForReport = 100;
    maxTemp1ForReport = 0;

    minTemp2ForReport = 100;
    maxTemp2ForReport = 0;

    hourLed1On = 0;
    minuteLed1On = 0;
    secondLed1On = 0;

    hourLed2On = 0;
    minuteLed2On = 0;
    secondLed2On = 0;
  }

  if (!digitalRead(Led1) && tempSecond1 != currentSecond)
  {
    tempSecond1 = currentSecond;
    secondLed1On++;
    if (secondLed1On == 60)
    {
      secondLed1On = 0;
      minuteLed1On++;
    }
    if (minuteLed1On == 60)
    {
      minuteLed1On = 0;
      hourLed1On++;
    }
  }


  if (!digitalRead(Led2) && tempSecond2 != currentSecond)
  {
    tempSecond2 = currentSecond;
    secondLed2On++;
    if (secondLed2On == 60)
    {
      secondLed2On = 0;
      minuteLed2On++;
    }
    if (minuteLed2On == 60)
    {
      minuteLed2On = 0;
      hourLed2On++;
    }
  }
}


bool isLedsON()
{
  bool Led1State = digitalRead(Led1);
  bool Led2State = digitalRead(Led2);

  return Led1State == false && Led2State == false ? true : false;
}

String getTempName (int index)
{
  switch (index)
  {
    case 0: return "№1"; break;
    case 1: return "№2"; break;
  }
}

void autoSetTime(AsyncTelegram myBot, TBMessage msg)
{
  HTTPClient http;

  http.begin("http://worldtimeapi.org/api/ip");
  int httpCode = http.GET();

  if (httpCode == 200) {
    DynamicJsonDocument doc(1024);
    String payload = http.getString();
    deserializeJson(doc, payload);
    JsonObject obj = doc.as<JsonObject>();
    String dateTimeJson = obj[String("datetime")];
    int index = dateTimeJson.indexOf("T");
    String dataJson = dateTimeJson.substring(0, index);
    String timeJson = dateTimeJson.substring(index + 1, dateTimeJson.indexOf("."));

    int indexH = timeJson.indexOf(":");
    int indexM = timeJson.indexOf(":", indexH + 1);

    String hourJson = timeJson.substring(0, indexH);
    String minuteJson = timeJson.substring(indexH + 1, indexM);
    String secondJson = timeJson.substring(indexM + 1);

    int indexY = dataJson.indexOf("-");
    int indexMon = dataJson.indexOf("-", indexY + 1);

    String yearJson = dateTimeJson.substring(0, indexY);
    String monthJson = dateTimeJson.substring(indexY + 1, indexMon);
    String dayJson = dateTimeJson.substring(indexMon + 1);

    String dayOfWeek = obj[String("day_of_week")];

    int S = secondJson.toInt();
    int M = minuteJson.toInt();
    int H = hourJson.toInt();
    int D = dayJson.toInt();
    int MON = monthJson.toInt();
    int Y = yearJson.toInt();
    int W = dayOfWeek.toInt();

    watch.settime(S, M, H, D, MON, Y, W);
  } else {
    String reply = "#httpError ";
    reply +=  "\n";
    reply +=  "http://worldtimeapi.org/api/ip";
    reply +=  "\n";
    reply +=  "httpCode: " + httpCode;
    myBot.sendMessage(msg, reply);
  }

  http.end();
}
