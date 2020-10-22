void Controller(TBMessage msg)
{
  if (msg.text.equals("/start"))
  {
    autoSetTime(myBot,msg);
    isStart = true;
    String reply;
    reply +=  "Автоконтроль включен";
    reply +=  "\n";
   
    myBot.sendMessage(msg, reply);
    resetAllSettings();
  }
  else if (msg.text.equals("/stop"))
  {
    isStart = false;
    String reply;
    reply +=  "Автоконтроль выключен";
    reply +=  "\n";

    myBot.sendMessage(msg, reply);
    resetAllSettings();
  }
  else if (msg.text.equals("/get_data"))
  {
    getData(msg);
    resetAllSettings();
  }
  else if (msg.text.equals("/all_lights_on"))
  {
    String reply = "Все светильники ВКЛ";
    allLedsON(msg, reply);
    resetAllSettings();
  }
  else if (msg.text.equals("/all_lights_off"))
  {
    String reply = "Все светильники ВЫКЛ";
    allLedsOFF(msg, reply);
    resetAllSettings();
  }
  else if (msg.text.equals("/light_1_on"))
  {
    Led1ON(msg);
    resetAllSettings();
  }
  else if (msg.text.equals("/light_1_off"))
  {
    Led1OFF(msg);
    resetAllSettings();
  }
  else if (msg.text.equals("/light_2_on"))
  {
    Led2ON(msg);
    resetAllSettings();
  }
  else if (msg.text.equals("/light_2_off"))
  {
    Led2OFF(msg);
    resetAllSettings();
  }
  else if (msg.text.equals("/set_min_temp"))
  {
    resetAllSettings();
    isSettingMinTemp  = true;

    String reply = "Задайте минимальное значение температуры";
    reply +=  "\n";
    reply +=  "\n";
    reply +=  "#Пример:  20";
    myBot.sendMessage(msg, reply);
  }
  else if (msg.text.equals("/set_max_temp"))
  {
    resetAllSettings();
    isSettingMaxTemp  = true;

    String reply = "Задайте максимальное значение температуры";
    reply +=  "\n";
    reply +=  "\n";
    reply +=  "#Пример: 30";
    myBot.sendMessage(msg, reply);
  }
  else if (msg.text.equals("/set_start_time_lighting"))
  {
    resetAllSettings();
    isSettingLedON  = true;

    String reply = "Задайте время ВКЛ освещения";
    reply +=  "\n";
    reply +=  "\n";
    reply +=  "#Пример: hh:mm";
    myBot.sendMessage(msg, reply);
  }
  else if (msg.text.equals("/set_end_time_all_lighting"))
  {
    resetAllSettings();
    isSettingLedOFF  = true;

    String reply = "Задайте время ВЫКЛ освещения";
    reply +=  "\n";
    reply +=  "\n";
    reply +=  "#Пример --> hh:mm";
    myBot.sendMessage(msg, reply);
  }
  else if (msg.text.equals("/set_time_send_report"))
  {
    resetAllSettings();
    isSettingTimeForReport  = true;

    String reply = "Задайте время отправки отчета";
    reply +=  "\n";
    reply +=  "\n";
    reply +=  "#Пример --> hh:mm";
    myBot.sendMessage(msg, reply);
  }
  else if (msg.text.equals("/get_settings"))
  {
    resetAllSettings();
    sendSettings(msg);
  }
  else if (msg.text.equals("/get_report"))
  {
    autoSetTime(myBot,msg);
    resetAllSettings();
    sendReport(msg);
  }
  else if (msg.text.equals("/add_user"))
  {
    resetAllSettings();
    isSettingAddUser = true;
    String reply = "#Add Введите username";
    myBot.sendMessage(msg, reply);
  }
  else if (msg.text.equals("/delete_user"))
  {
    resetAllSettings();
    isSettingDeleteUser = true;
    String reply = "#Delete Введите username";

    reply += "\n";
    reply += "\n";
    reply += "#Список:";
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
  else
  {
    if (isSettingMinTemp)
    {
      setMinTemp(msg);
    }
    else if (isSettingMaxTemp)
    {
      setMaxTemp(msg);
    }
    else if (isSettingLedON)
    {
      resetAllSettings();
      isSettingLedON  = true;
      setLightingOnTime(msg);

    }
    else if (isSettingLedOFF)
    {
      resetAllSettings();
      isSettingLedOFF = true;
      setLightingOffTime(msg);
    }
    else if (isSettingTimeForReport)
    {
      resetAllSettings();
      isSettingTimeForReport = true;
      setTimeForReport(msg);
    }
    else if (isSettingAddUser)
    {
      addUser(msg);

    }
    else if (isSettingDeleteUser)
    {
      deleteUser(msg);
    }
    else
    {
      String reply = "Error";
      myBot.sendMessage(msg, reply);

      resetAllSettings();
    }
  }
}

void resetAllSettings()
{
  isSettingMinTemp  = false;
  isSettingMaxTemp  = false;
  isSettingLedON  = false;
  isSettingLedOFF = false;
  isSettingTimeForReport = false;
  isSettingAddUser = false;
  isSettingDeleteUser = false;
}

void addUser(TBMessage msg)
{
  String reply = "";
  isSettingAddUser = false;
  String username = msg.text;
  username.trim();

  int index = 0;
  int arraySize = sizeof(users) / sizeof(String);
  for (int i = 0; i < arraySize; i++)
  {
    if (users[i].equals("???"))
    {
      break;
    }
    index++;
    if (username.equals(users[i]))
    {
      reply = "username: " + username;
      reply += " уже существует!";
      myBot.sendMessage(msg, reply);
      return;
    }

    if (index == arraySize)
    {
      reply = "Нет свободного места для добавления: " + username;
      reply += " , придется кого то удалить...";
      myBot.sendMessage(msg, reply);
      return;
    }
  }

  users[index] = username;

  reply = "#Список:";
  reply += "\n";
  reply += "\n";

  for (int i = 0; i < index + 1; i++) {
    reply += i + 1;
    reply += ") " + users[i];
    reply += "\n";
  }

  myBot.sendMessage(msg, reply);
}

void deleteUser(TBMessage msg)
{
  String reply = "";
  String username = msg.text;
  username.trim();

  int arraySize = sizeof(users) / sizeof(String);

  for (int i = 0; i < arraySize; i++)
  {
    if (username.equals(users[i]) && !username.equals("???"))
    {
      if (username.equals(users[0]))
      {
        reply = "username: " + username;
        reply += " не может быть удален!";
        myBot.sendMessage(msg, reply);
        return;
      } else {
        isSettingDeleteUser = false;
        for (int j = i; j < arraySize; j++) {
          int nextElement = j + 1;
          int index = j + 1 == arraySize ? arraySize - 1 : j + 1;
          users[j] = users[index];
        }
        users[arraySize - 1] = "???";
        reply = "username : " + username;
        reply += " удален!";
        reply += "\n";
        reply += "\n";
        reply += "#Список:";
        reply += "\n";
        for (int j = 0; j < arraySize; j++) {
          if (!users[j].equals("???")) {
            reply += j + 1;
            reply += ") " + users[j];
            reply += "\n";
          }
        }
        myBot.sendMessage(msg, reply);
        return;
      }
    }
  }

  reply += "username : " + username;
  reply += " не найден!";
  myBot.sendMessage(msg, reply);
  return;
}

String getAutoControlStatus (bool s)
{
  switch (s)
  {
    case 0: return "ВЫКЛ"; break;
    case 1: return "ВКЛ"; break;
  }
}

String getTimeVal(int val)
{
  if (val <= 9)
  {
    String s;
    s += "0";
    s += val;
    return s;
  }

  return String(val);
}
