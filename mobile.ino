//----------------------------------------------------------------
String sendATCommand(String cmd, bool waiting) {
  String _resp = "";   if(_com_tel){Serial.println(cmd); }
  SIM800.println(cmd);     
  if (waiting) {                                // Если необходимо дождаться ответа...
    _resp = waitResponse();                     // ... ждем  ответ от модуля
    if (_resp.startsWith(cmd)) //startsWith проверяем ответ не начинается ли на название команды если исина 
    { int8_t dlina =cmd.length();         
      int8_t inndex=_resp.indexOf("\r");               // indexOf(Осуществляет поиск символа или подстроки в строке (String),с которой необходимо начать поиск) 
      _resp = _resp.substring( inndex+ 2); }          //substring Возвращает подстроку в строке (String), substring(начальный индекс в строке);  
    
    }
    if (_com_tel){Serial.println(_resp);}  //ответ печатаем . 
  return _resp;                                 // Возвращаем результат. Пусто, если проблема
}
//--------------------------------------------------------------------------
void sendSMS(String phone, String message)
{  
  sendATCommand("AT+CMGS=\"" + phone + "\"", 1);                          // Переходим в режим ввода текстового сообщения
  sendATCommand(message + "\r\n" + (String)((char)26),1);   // После текста отправляем перенос строки и Ctrl+Z
}
//--------------------------------------------------------------------------
String waitResponse() {                        
  String _resp = "";                           
  long _timeout = millis() + 10000;             // Переменная для отслеживания таймаута (10 секунд)
  while (!SIM800.available() && millis() < _timeout)  {}; // Ждем ответа 10 секунд, если пришел ответ или наступил таймаут, то...
  if (SIM800.available()) {   _resp = SIM800.readString(); }   // Если пришел ответ
  else {    if(_com_tel){Serial.println("Timeout...");}  }                 // Если пришел таймаут, то...
  return _resp;                                 // ... возвращаем результат. Пусто, если проблема
}
