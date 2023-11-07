
/*

void red_analog(){  //просто пример чтение аналогового выхода
  String ADCData;
  int adcvalue=analogRead(A0);  //Read Analog value of LDR
  ADCData = String(adcvalue);   //String to interger conversio
}

*/


/*
void WeatherDisplay(){  
  //char * out = strtok(devices[0].pingH,".");        // Выделяем первую часть из строки до символа '-'
   char * out = strtok(icon,"-");        // Выделяем первую часть из строки до символа '-'
   Serial.println(out);


/*    Со стринга преобразуем в нужный формат
  String ntpServerName = "ntp.time.in.ua";
  WiFi.hostByName(ntpServerName.c_str(), timeServerIP);   //определяет по именм айпи в timeServerIP может возвращать ошибку
*/
  
/*
  while (out != NULL) {                 // Выделяем последующие части строки в цикле, пока значение out не станет нулевым (пустым)
      if (String(out) == "skc")         // Перебираем в условиях все возможные варианты, зашифрованные в названии иконки
        Serial.println("Yasno");
      else if (String(out) == "ovc")
        Serial.println("Pasmurno");
      else if (String(out) == "bkn")
        Serial.println("Oblachno");
      else if (String(out) == "ra")
        Serial.println("Dozhd'");
      else if (String(out) == "ts")
        Serial.println("Groza");
      else if (String(out) == "sn")
        Serial.println("Sneg");
      else if (String(out) == "bl")
        Serial.println("Metel'");
      else if (String(out) == "fg")
        Serial.println("Tuman");
      else if (String(out) == "n")
        Serial.println("\nTemnoe vremya sutok");
      else if (String(out) == "d")
        Serial.println("\nSvetloe vremya sutok");
      
      out = strtok(NULL,"-");              // Выделяем очередную часть
   }
   */

}

*/

/*
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   unsigned long StringToULong(String Str) {                     // Эта функция преобразует String в unsigned long
  unsigned long ULong = 0;
  for (int i = 0; i < Str.length(); i++) {                    // В цикле посимвольно переводим строку в unsigned long
     char c = Str.charAt(i);
     if (c < '0' || c > '9') break;
     ULong *= 10;
     ULong += (c - '0');
  }
  return ULong;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
String leadNull(int digits){                                    // Функция добавляет ведущий ноль
  String out = "";
  if(digits < 10)
    out += "0";                                               
  return out + String(digits);
}

*/

/*









///////////////////////////////////////////////////////////////
  if (ESPclient.connect(weatherHost0.c_str(), 80)) {
  String weatherHost0 = "158.69.116.36";
/////////////////////////////////////////////////////////////////


WiFiClient ESPclient;   //зачемто конект реализован с сайтом так
 if (ESPclient.connect(weatherHost0.c_str(), 80)) { 
 HTTPClient http;
  if (http.begin(ESPclient, reqline))  //а отправка запроса так





















  if (ESPclient.connect(weatherHost0.c_str(), 80)) {
  
  //static byte addr[] = { 40,210,113,72,2,0,0,167}; 
  //40,50,191,229,5,0,0,64  //третий датчик
  //static byte addr[8];    //адрес не должен обнуляться пр выход с функции
  //static byte addr[] = {40,206,26,168,1,0,0,77};   //40 206 26 168 1 0 0 77
  //static byte addr[] = { 40,210,113,72,2,0,0,167};    //плохо рабочий для теста
 // static byte addr2[] = {40,3,163,185,5,0,0,13};  //улица второй



 
void ESPWebMQTTRelay::switchRelay(int8_t id, bool on) {
  if (((id < 0) || (id >= maxRelays)) || (relayPin[id] == -1))
    return;

  bool relay = digitalRead(relayPin[id]);

  if (! relayLevel[id])
    relay = ! relay;
  if (relay != on) {
    digitalWrite(relayPin[id], relayLevel[id] == on);

    if (pubSubClient->connected()) {
      String topic;

      if (_mqttClient != strEmpty) {
        topic += charSlash;
        topic += _mqttClient;
      }
      topic += FPSTR(mqttTopic);
      topic += charSlash;
      topic += String(id + 1);
      mqttPublish(topic, String(on));
    }
  }
}


  Serial.print(F("/switch("));
  Serial.print(id);
  Serial.print(F(", "));
  Serial.print(on);
  Serial.println(F(")"));
#endif

  switchRelay(id.toInt(), on == "true");


void ESPWebMQTTRelay::switchRelay(int8_t id, bool on) {
  if (((id < 0) || (id >= maxRelays)) || (relayPin[id] == -1))
    return;

  bool relay = digitalRead(relayPin[id]);

  if (! relayLevel[id])
    relay = ! relay;
  if (relay != on) {
    digitalWrite(relayPin[id], relayLevel[id] == on);


  }
}

void ESPWebMQTTRelay::handleRelaySwitch() {
  String id = httpServer->arg("id");
  String on = httpServer->arg("on");

#ifndef NOSERIAL
  Serial.print(F("/switch("));
  Serial.print(id);
  Serial.print(F(", "));
  Serial.print(on);
  Serial.println(F(")"));
#endif

  switchRelay(id.toInt(), on == "true");

  httpServer->send(200, FPSTR(textHtml), strEmpty);
}


void ESPWebMQTTRelay::switchRelay(int8_t id, bool on) {
  if (((id < 0) || (id >= maxRelays)) || (relayPin[id] == -1))
    return;

  bool relay = digitalRead(relayPin[id]);

  if (! relayLevel[id])
    relay = ! relay;
  if (relay != on) {
    digitalWrite(relayPin[id], relayLevel[id] == on);

    if (pubSubClient->connected()) {
      String topic;

      if (_mqttClient != strEmpty) {
        topic += charSlash;
        topic += _mqttClient;
      }
      topic += FPSTR(mqttTopic);
      topic += charSlash;
      topic += String(id + 1);
      mqttPublish(topic, String(on));
    }
  }
}

*/
