void getData(TBMessage msg)
{
  String reply = "#Данные";
  reply +=  "\n";
  reply +=  "\n";
  reply +=  "Температура №1: ";
  reply +=  currentTemp[0];
  reply +=  " °C";
  reply +=  "\n";

  reply +=  "Температура №2: ";
  reply +=  currentTemp[1];
  reply +=  " °C";
  reply +=  "\n";
  reply +=  "\n";

  reply +=  "Светильник №1: ";
  reply +=  getStatus(digitalRead(Led1));
  reply +=  "\n";

  reply +=  "Светильник №2: ";
  reply +=  getStatus(digitalRead(Led2));
  reply +=  "\n";
  reply +=  "\n";

  reply +=  "Автоконтроль: ";
  reply +=  getAutoControlStatus(isStart);
  reply +=  "\n";
  reply +=  "\n";


  myBot.sendMessage(msg, reply);
}

void allLedsON(TBMessage msg, String reply)
{
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  myBot.sendMessage(msg, reply);
}

void allLedsOFF(TBMessage msg, String reply)
{
  digitalWrite(Led1, HIGH);
  digitalWrite(Led2, HIGH);
  myBot.sendMessage(msg, reply);
}

void Led1ON(TBMessage msg)
{
  digitalWrite(Led1, LOW);
  String reply = "Светильник №1 ВКЛ";
  myBot.sendMessage(msg, reply);
}

void Led1OFF(TBMessage msg)
{
  digitalWrite(Led1, HIGH);
  String reply = "Светильник №1 ВЫКЛ";
  myBot.sendMessage(msg, reply);
}

void Led2ON(TBMessage msg)
{
  digitalWrite(Led2, LOW);
  String reply = "Светильник №2 ВКЛ";
  myBot.sendMessage(msg, reply);
}

void Led2OFF(TBMessage msg)
{
  digitalWrite(Led2, HIGH);
  String reply = "Светильник №2 ВЫКЛ";
  myBot.sendMessage(msg, reply);
}

void setMinTemp(TBMessage msg)
{
  String temp =  msg.text;

  if (isDigital(temp))
  {
    if ((float)temp.toInt() < maxTemp)
    {
      minTemp  = (float)temp.toInt();
      isSettingMinTemp  = false;
      String reply;
      reply +=  "Минимальная температура успешно установлена: ";
      reply +=  minTemp;
      reply +=  " °C";
      reply +=  "\n";
      myBot.sendMessage(msg, reply);
    }
    else
    {
      String reply;
      reply +=  "Минимальная температура не может быть болье чем максимальная: ";
      reply +=  minTemp;
      reply +=  "\n";
      myBot.sendMessage(msg, reply);
    }

  }
  else
  {
    isSettingMinTemp  = false;
    String reply;
    reply +=  "Не удачная установка значения: ";
    reply +=  temp;
    reply +=  "\n";
    reply +=  "Начни все заново и будь внимательнее!";
    myBot.sendMessage(msg, reply);
  }
}

void setMaxTemp(TBMessage msg)
{
  String temp =  msg.text;

  if (isDigital(temp))
  {
    if ((float)temp.toInt() > minTemp)
    {
      maxTemp  = (float)temp.toInt();
      isSettingMaxTemp  = false;
      String reply;
      reply +=  "Максимальная температура успешно установлена: ";
      reply +=  maxTemp;
      reply +=  " °C";
      reply +=  "\n";
      myBot.sendMessage(msg, reply);
    }
    else
    {
      String reply;
      reply +=  "Максимальная температура не может быть меньше чем минимальная: ";
      reply +=  maxTemp;
      reply +=  "\n";
      myBot.sendMessage(msg, reply);
    }
  }
  else
  {
    isSettingMaxTemp  = false;
    String reply;
    reply +=  "Не удачная установка значения: ";
    reply +=  temp;
    reply +=  "\n";
    reply +=  "Начни все заново и будь внимательнее!";
    myBot.sendMessage(msg, reply);
  }
}

void setLightingOnTime (TBMessage msg)
{
  String setHour =  parseHour(msg.text);
  String setMinute =  parseMinute(msg.text);

  if (isDigital(setHour) && isDigital(setMinute))
  {
    if (setHour.toInt() <= 23 && setHour.toInt() >= 0 && setMinute.toInt() <= 59 && setMinute.toInt() >= 0)
    {
      lightingOnHour  = setHour.toInt();
      lightingOnMinute = setMinute.toInt();

      isSettingLedON  = false;
      String reply;
      reply +=  "Время ВКЛ освещения: ";
      reply +=  getTimeVal(lightingOnHour);
      reply +=  ":";
      reply +=  getTimeVal(lightingOnMinute);
      reply +=  ":00";
      reply +=  "\n";
      myBot.sendMessage(msg, reply);
    }
    else
    {
      String reply;
      reply +=  "Задайте hh в диапазоне от 0..23";
      reply +=  "\n";
      reply +=  "Задайте mm в диапазоне от 0..59 ";
      myBot.sendMessage(msg, reply);
    }
  }
  else
  {
    isSettingLedON  = false;
    String reply;
    reply +=  "Не удачная установка значения: ";
    reply +=  msg.text;
    reply +=  "\n";
    reply +=  "Начни все заново и будь внимательнее!";
    myBot.sendMessage(msg, reply);
  }
}

void setLightingOffTime (TBMessage msg)
{
  String setHour =  parseHour(msg.text);
  String setMinute =  parseMinute(msg.text);

  if (isDigital(setHour) && isDigital(setMinute))
  {
    if (setHour.toInt() <= 23 && setHour.toInt() >= 0 && setMinute.toInt() <= 59 && setMinute.toInt() >= 0)
    {
      lightingOffHour  = setHour.toInt();
      lightingOffMinute  = setMinute.toInt();

      isSettingLedOFF  = false;
      String reply;
      reply +=  "Время ВЫКЛ освещения: ";
      reply +=  getTimeVal(lightingOffHour);
      reply +=  ":";
      reply +=  getTimeVal(lightingOffMinute);
      reply +=  ":00";
      reply +=  "\n";
      myBot.sendMessage(msg, reply);
    }
    else
    {
      String reply;
      reply +=  "Задайте hh в диапазоне от 0..23 ";
      reply +=  "\n";
      reply +=  "Задайте mm в диапазоне от 0..59 ";
      reply +=  "\n";
      myBot.sendMessage(msg, reply);
    }
  }
  else
  {
    isSettingLedOFF  = false;
    String reply;
    reply +=  "Не удачная установка времени!";
    reply +=  msg.text;
    reply +=  "\n";
    reply +=  "Начни все заново и будь внимательнее!";
    myBot.sendMessage(msg, reply);
  }
}

void setTimeForReport (TBMessage msg)
{
  String setHour =  parseHour(msg.text);
  String setMinute =  parseMinute(msg.text);

  if (isDigital(setHour) && isDigital(setMinute))
  {
    if (setHour.toInt() <= 23 && setHour.toInt() >= 0 && setMinute.toInt() <= 59 && setMinute.toInt() >= 0)
    {
      hourForReport  = setHour.toInt();
      minuteForReport = setMinute.toInt();

      isSettingTimeForReport = false;
      String reply;
      reply +=  "Время отправки отчета: ";
      reply +=  getTimeVal(hourForReport);
      reply +=  ":";
      reply +=  getTimeVal(minuteForReport);
      reply +=  ":00";
      reply +=  "\n";
      myBot.sendMessage(msg, reply);
    }
    else
    {
      String reply;
      reply +=  "Задайте hh в диапазоне от 0..23";
      reply +=  "\n";
      reply +=  "Задайте mm в диапазоне от 0..59 ";
      myBot.sendMessage(msg, reply);
    }
  }
  else
  {
    isSettingTimeForReport = false;
    String reply;
    reply +=  "Не удачная установка значения: ";
    reply +=  msg.text;
    reply +=  "\n";
    reply +=  "Начни все заново и будь внимательнее!";
    myBot.sendMessage(msg, reply);
  }
}

void sendReport (TBMessage msg)
{
  String reply = "#Отчет";
  reply +=  "\n";
  reply +=  "\n";
  reply +=  "Температура №1:";
  reply +=  "\n";
  reply +=  "-min: ";
  reply +=  getTimeVal(minTemp1HourForReport);
  reply +=  ":";
  reply +=  getTimeVal(minTemp1MinuteForReport);
  reply +=  ":00 ч --> ";
  reply +=  minTemp1ForReport;
  reply +=  " °C";
  reply +=  "\n";

  reply +=  "-max: ";
  reply +=  getTimeVal(maxTemp1HourForReport);
  reply +=  ":";
  reply +=  getTimeVal(maxTemp1MinuteForReport);
  reply +=  ":00 ч --> ";
  reply +=  maxTemp1ForReport;
  reply +=  " °C";
  reply +=  "\n";
  reply +=  "\n";

  reply +=  "Температура №2:";
  reply +=  "\n";
  reply +=  "-min: ";
  reply +=  getTimeVal(minTemp2HourForReport);
  reply +=  ":";
  reply +=  getTimeVal(minTemp2MinuteForReport);
  reply +=  ":00 ч --> ";
  reply +=  minTemp2ForReport;
  reply +=  " °C";
  reply +=  "\n";

  reply +=  "-max: ";
  reply +=  getTimeVal(maxTemp2HourForReport);
  reply +=  ":";
  reply +=  getTimeVal(maxTemp2MinuteForReport);
  reply +=  ":00 ч --> ";
  reply +=  maxTemp2ForReport;
  reply +=  " °C";
  reply +=  "\n";
  reply +=  "\n";

  reply +=  "Время освещения №1: ";
  reply +=  getTimeVal(hourLed1On);
  reply +=  ":";
  reply +=  getTimeVal(minuteLed1On);
  reply +=  ":";
  reply +=  getTimeVal(secondLed1On);
  reply +=  " ч.";
  reply +=  "\n";

  reply +=  "Время освещения №2: ";
  reply +=  getTimeVal(hourLed2On);
  reply +=  ":";
  reply +=  getTimeVal(minuteLed2On);
  reply +=  ":";
  reply +=  getTimeVal(secondLed2On);
  reply +=  " ч.";
  reply +=  "\n";

  myBot.sendMessage(msg, reply);
}

void sendSettings(TBMessage msg)
{
  String reply = "#Настройки";
  reply +=  "\n";
  reply +=  "\n";

  reply +=  "Время ВКЛ освещения: ";
  reply +=  getTimeVal(lightingOnHour);
  reply +=  ":";
  reply +=  getTimeVal(lightingOnMinute);
  reply +=  ":00 ч";
  reply +=  "\n";

  reply +=  "Время ВЫКЛ освещения: ";
  reply +=  getTimeVal(lightingOffHour);
  reply +=  ":";
  reply +=  getTimeVal(lightingOffMinute);
  reply +=  ":00 ч";
  reply +=  "\n";
  reply +=  "\n";

  reply +=  "Минимальная температура: ";
  reply +=  minTemp;
  reply +=  " °C";
  reply +=  "\n";

  reply +=  "Максимальная температура: ";
  reply +=  maxTemp;
  reply +=  " °C";
  reply +=  "\n";
  reply +=  "\n";

  reply +=  "Отправка отчета: ";
  reply +=  getTimeVal(hourForReport);
  reply +=  ":";
  reply +=  getTimeVal(minuteForReport);
  reply +=  ":00 ";
  reply +=  " ч.";
  reply +=  "\n";
  reply +=  "\n";

  reply +=  "Время: ";
  reply +=  getTimeVal(currentHour);
  reply +=  ":";
  reply +=  getTimeVal(currentMinute);
  reply +=  ":";
  reply +=  getTimeVal(currentSecond);
  reply +=  " ч.";
  reply +=  "\n";
  reply +=  "\n";

  reply +=  "Автоконтроль: ";
  reply +=  getAutoControlStatus(isStart);
  reply += "\n";
  reply += "\n";

  reply += "Список юзеров:";
  reply += "\n";
  int arraySize = sizeof(users)/sizeof(String);
  for (int j = 0; j < arraySize; j++) {
    if (!users[j].equals("???")) {
      reply += j + 1;
      reply += ") " + users[j];
      reply += "\n";
    }
  }

  myBot.sendMessage(msg, reply);
}


bool isDigital (String s)
{
  int str_len = s.length() + 1;
  char char_array[str_len];
  s.toCharArray(char_array, str_len);

  char numbers[] = "0123456789";
  int count = 0;

  int numbersCount = sizeof(numbers) / sizeof(char);
  for (int i = 0; i < s.length(); i++)
  {
    count = 0;
    for (int j = 0; j < numbersCount; j++)
    {
      if (char_array[i] != numbers[j])
      {
        count ++;
      }

      if (count == numbersCount)
      {
        return false;
      }
    }
  }

  return true;
}

String parseHour (String text)
{
  int index = text.indexOf(":");

  if (index != -1)
  {
    return text.substring(0, index);
  }

  return "h";
}

String parseMinute (String text)
{
  int index = text.indexOf(":");

  if (index != -1)
  {
    return text.substring(index + 1);
  }

  return "m";
}

String getStatus (int s)
{
  switch (s)
  {
    case 0: return "ВКЛ"; break;
    case 1: return "ВЫКЛ"; break;
  }
}
