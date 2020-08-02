void Controller(TBMessage msg)
{
    if (msg.text.equals("/start")) 
    { 
      isStart = true;
      String reply;        
      reply +=  "Готов следить за вашей аквафермой";   
      reply +=  "\n";
      reply +=  "Текущие настройки:";   
      reply +=  "\n"; 
      reply +=  "\n";   

      reply +=  "Время ВКЛ освещения: ";
      reply +=  lightingOnTime;
      reply +=  ":00 часов";
      reply +=  "\n";

      reply +=  "Время ВЫКЛ освещения: ";
      reply +=  lightingOffTime;
      reply +=  ":00 часов";
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

      reply +=  "Время: ";
      reply +=  currentHour;
      reply +=  ":";
      reply +=  currentMinute;
      reply +=  ":";
      reply +=  currentSecond;
      reply +=  "\n"; 
      reply +=  "\n";
       
      reply +=  "Автоконтроль: ";
      reply +=  getAutoControlStatus(isStart);
    
      myBot.sendMessage(msg, reply);
      resetAllSettings();  
    }
    else if (msg.text.equals("/stop")) 
    { 
      isStart = false;
      String reply;      
      reply +=  "Перестаю следить за временем освещения и температурой";   
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
      allLedsON(msg);
      resetAllSettings();
    }
    else if (msg.text.equals("/all_lights_off")) 
    { 
      allLedsOFF(msg);
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
      reply +=  "Пример --> 20";                                          
      myBot.sendMessage(msg, reply);       
    }
      else if (msg.text.equals("/set_max_temp")) 
    {    
      resetAllSettings();    
      isSettingMaxTemp  = true;  
      
      String reply = "Задайте максимальное значение температуры";       
      reply +=  "\n";
      reply +=  "\n";      
      reply +=  "Пример --> 30";                                          
      myBot.sendMessage(msg, reply);         
    }
      else if (msg.text.equals("/set_start_time_lighting")) 
    {  
      resetAllSettings();
      isSettingLedON  = true; 

      String reply = "Задайте время ВКЛ освещения в диапазоне от 0-23";       
      reply +=  "\n";
      reply +=  "\n";      
      reply +=  "Пример --> 10";                                          
      myBot.sendMessage(msg, reply);       
    }
      else if (msg.text.equals("/set_end_time_all_lighting")) 
    {     
      resetAllSettings();   
      isSettingLedOFF  = true; 

      String reply = "Задайте время ВЫКЛ освещения в диапазоне от 0-23";       
      reply +=  "\n";
      reply +=  "\n";      
      reply +=  "Пример --> 20";                                          
      myBot.sendMessage(msg, reply);         
    }
      else if (msg.text.equals("/get_settings")) 
    {   
      resetAllSettings();
           
      String reply = "#Settings: ";       
      reply +=  "\n";
      reply +=  "\n";  
          
      reply +=  "Время ВКЛ освещения: ";
      reply +=  lightingOnTime;
      reply +=  ":00 ч";
      reply +=  "\n";

      reply +=  "Время ВЫКЛ освещения: ";
      reply +=  lightingOffTime;
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
      
      reply +=  "Время: ";
      reply +=  currentHour;
      reply +=  ":";
      reply +=  currentMinute;
      reply +=  ":";
      reply +=  currentSecond;
      reply +=  "\n"; 
      reply +=  "\n";
      
      reply +=  "Автоконтроль: ";
      reply +=  getAutoControlStatus(isStart);
      myBot.sendMessage(msg, reply);       
    }
    else 
    {  
      if (isSettingMinTemp)
      {
        setMinTemp(msg);
      }
      else if(isSettingMaxTemp)
      {
        setMaxTemp(msg);
      }
      else if(isSettingLedON)
      {
        resetAllSettings();
        isSettingLedON  = true;
        setLightingOnTime(msg);
 
      } 
      else if(isSettingLedOFF)
      {
        resetAllSettings();
        isSettingLedOFF = true; 
        setLightingOffTime(msg);
      } 
      else
      {
       String reply = "Извини, но я не знаю о чем ты... =((";
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
}

String getAutoControlStatus (bool s)
{
  switch(s)
  {
    case 0: return "OFF"; break;
    case 1: return "ON"; break;
  }
}
