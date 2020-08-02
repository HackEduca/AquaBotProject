void AutoController (AsyncTelegram myBot, TBMessage msg,int currentHour, float currentTemp)
{
  if (currentHour >= lightingOnTime && currentHour < lightingOffTime && !isDay)
  {
    isDay = !isDay;
    digitalWrite(Led1, HIGH); 
    digitalWrite(Led2, HIGH);    
    String reply = "#message Все светильники ВКЛ автоматически";   
                           
    myBot.sendMessage(msg, reply); 
  }
  else if ((currentHour >= lightingOffTime || currentHour < lightingOnTime) && isDay)
  {
    isDay = !isDay;
    digitalWrite(Led1, LOW); 
    digitalWrite(Led2, LOW);    
    String reply = "#message Все светильники ВЫКЛ автоматически";
                              
    myBot.sendMessage(msg, reply); 
  }

  if (currentTemp < minTemp && isSendMsgCriticalMinTemp == false && currentTemp >= 0)
  {  
    String reply = "#message Температура достигла минимальной критической отметки: ";  
    reply +=  currentTemp;
    reply +=  "°C";                      
    myBot.sendMessage(msg, reply); 

    isSendMsgCriticalMinTemp = true;
    isSendMsgCriticalMaxTemp = false;
  }
  else if (currentTemp > maxTemp && isSendMsgCriticalMaxTemp == false && currentTemp <= 100)
  {   
    String reply = "#message Температура достигла максимальной критической отметки: ";  
    reply +=  currentTemp;
    reply +=  "°C";                      
    myBot.sendMessage(msg, reply); 

    isSendMsgCriticalMaxTemp = true;
    isSendMsgCriticalMinTemp = false;
  }

  else if (currentTemp <= maxTemp && currentTemp >= minTemp)
  {   
    isSendMsgCriticalMaxTemp = false;
    isSendMsgCriticalMinTemp = false;
  }
}
