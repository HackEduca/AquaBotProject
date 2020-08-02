void getData(TBMessage msg)
{
    String reply = "Температура: ";  
    reply +=  currentTemp;  
    reply +=  "\n"; 
           
    reply +=  "Светильник №1: ";   
    reply +=  getStatus(digitalRead(Led1));  
    reply +=  "\n";  

    reply +=  "Светильник №2: ";   
    reply +=  getStatus(digitalRead(Led2));
    reply +=  "\n";     
    
    myBot.sendMessage(msg, reply);  
}

void allLedsON(TBMessage msg)
{
    digitalWrite(Led1, HIGH); 
    digitalWrite(Led2, HIGH);    
    String reply = "Все светильники ВКЛ";                          
    myBot.sendMessage(msg, reply);  
}

void allLedsOFF(TBMessage msg)
{
    digitalWrite(Led1, LOW); 
    digitalWrite(Led2, LOW);    
    String reply = "Все светильники ВЫКЛ";                          
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
    digitalWrite(Led1, LOW);    
    String reply = "Светильник №1 ВЫКЛ";                          
    myBot.sendMessage(msg, reply);  
}

void Led2ON(TBMessage msg)
{
    digitalWrite(Led2, HIGH); 
    String reply = "Светильник №2 ВКЛ";                          
    myBot.sendMessage(msg, reply);  
}

void Led2OFF(TBMessage msg)
{
    digitalWrite(Led2, LOW);    
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
   String setHour =  msg.text;

    if (isDigital(setHour))
    {
      if (setHour.toInt() <= 23 && setHour.toInt() >= 0 && setHour.toInt() < lightingOffTime)
      {
        lightingOnTime  = setHour.toInt();
        isSettingLedON  = false; 
        String reply;      
        reply +=  "Время ВКЛ освещения: ";   
        reply +=  lightingOnTime;  
        reply +=  ":00:00";   
        reply +=  "\n";                      
        myBot.sendMessage(msg, reply);  
      }
      else
      {
        if (setHour.toInt() >= lightingOffTime)
        {
          String reply;      
          reply +=  "Время ВКЛ не может быть больше или равно чем время ВЫКЛ ";
          reply +=  "\n";                      
          myBot.sendMessage(msg, reply); 
        }
        else 
        {
          String reply;      
          reply +=  "Задайте время в диапазоне от 0..23";
          reply +=  "\n";                      
          myBot.sendMessage(msg, reply);  
        } 
      }
    }
    else
    {
      isSettingLedON  = false;      
      String reply;      
      reply +=  "Не удачная установка значения: ";   
      reply +=  setHour;  
      reply +=  "\n";   
      reply +=  "Начни все заново и будь внимательнее!";                    
      myBot.sendMessage(msg, reply); 
    }
}

void setLightingOffTime (TBMessage msg)
{
   String setHour =  msg.text;

    if (isDigital(setHour))
    {
      if (setHour.toInt() <= 23 && setHour.toInt() >= 0 && setHour.toInt() > lightingOnTime)
      {
        lightingOffTime  = setHour.toInt();
        isSettingLedOFF  = false; 
        String reply;      
        reply +=  "Время ВЫКЛ освещения: ";   
        reply +=  lightingOffTime;  
        reply +=  ":00:00";   
        reply +=  "\n";                      
        myBot.sendMessage(msg, reply);  
      }
      else
      {
        if ( setHour.toInt() <= lightingOnTime)
        {
          String reply;      
          reply +=  "Время ВЫКЛ не может быть больше или равно чем время ВКЛ ";
          reply +=  "\n";                      
          myBot.sendMessage(msg, reply);  
        }
        else 
        {
          String reply;      
          reply +=  "Задайте время в диапазоне от 0..23: ";
          reply +=  "\n";                      
          myBot.sendMessage(msg, reply);    
        }
      }
    }
    else
    {
      isSettingLedOFF  = false;      
      String reply;      
      reply +=  "Не удачная установка значения: ";   
      reply +=  setHour;  
      reply +=  "\n";   
      reply +=  "Начни все заново и будь внимательнее!";                    
      myBot.sendMessage(msg, reply); 
    }
}

bool isDigital (String s)
{
    int str_len = s.length() + 1; 
    char char_array[str_len];
    s.toCharArray(char_array, str_len);
    
    char numbers[] = "0123456789";
    int count = 0;
    for(int i = 0; i < s.length(); i++)
    {
       count = 0;
      for(int j = 0; j < sizeof(numbers)-1; j++)
      {
          if(char_array[i] != numbers[j])
          {
              count ++; 
          }
          
          if (count == sizeof(numbers)-1)
          {
            return false;
          }
       }
    }

    return true;
}

String getStatus (int s)
{
  switch(s)
  {
    case 0: return "OFF"; break;
    case 1: return "ON"; break;
  }
}
