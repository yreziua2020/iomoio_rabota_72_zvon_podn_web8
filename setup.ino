void setup() {
                                              
  Serial.begin(9600);     SIM800.begin(9600);                                               
  WiFi.begin(ssid, password);   WiFi.config(ip, gateway, subnet, primaryDNS, secondaryDNS);
  int zad=0;
   while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print("."); if(zad++>20){break;} }  
   delay(500);
  //while (WiFi.status() != WL_CONNECTED) { delay(300);Serial.print("."); if(raz_podk++>250){ESP.reset(); }}  
  
  delay(500);                           
    
  SPIFFS.begin();                                                       // Инициализируем работу с файловой системой                          
  HTTP.begin();                                                         // Инициализируем Web-сервер
  ftpSrv.begin("admin","");                                        // Поднимаем FTP-сервер для удобства отладки работы HTML (логин: relay, пароль: relay)
  //----------------
  //timeClient.begin();   // Start the NTP UDP client
  //ClockTimer.attach(1, timerIsr);  //увеличиваем время каждую секуду
  //-------------------
  Serial.print("\n IP to connect via Web-Browser or FTP: ");          
  Serial.println(WiFi.localIP());                                      
  // Serial.println(WiFi.localIP());
  Serial.println("\n");
  Serial.println("Start6");
  httpUpdater.setup(&HTTP,  OTAUSER, OTAPASSWORD); //для обновления по вебу 

 // HTTP.on("/xml",handleXML); // формирование xml страницы для передачи данных в web интерфейс //другой способ вызова

  HTTP.on("/switch", [](){   HTTP.send(200, "text/html", handleRelaySwitch()); });
  HTTP.on("/kond", [](){   HTTP.send(200, "text/html", KondSwitch()); });
 // HTTP.on("/relay_status", [](){   HTTP.send(200, "text/plain", relay_status()); });
  HTTP.on("/start", [](){   HTTP.send(200, "text/html", StartData()); });
  HTTP.on("/data", [](){   HTTP.send(200, "text/html", handleData()); });
 // HTTP.on("/temper", [](){   HTTP.send(200, "text/html", temper()); });
    
 // HTTP.on("/temperature",  [](){   HTTP.send(200, "text/html", temperat().c_str()  ); });
 // HTTP.on("/temperature2", [](){   HTTP.send(200, "text/html", temperat2().c_str()  ); });
 // server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){ request->send_P(200, "text/plain", readBME280Humidity().c_str());  });
  HTTP.onNotFound([](){ if(!handleFileRead(HTTP.uri()))  HTTP.send(404, "text/plain", "Not Found"); });

  userPinger.on(true, userPingerRecvCallback); //будет вызываться разовый пминг с повторм 
  userPinger.on(false, userPingerFinalCallback); //вызыввается после окончания времени пинга, и без повтора

  udp.begin(localPort);
  delay(100);
  irsend.begin();
  delay(100);
  //Serial.print("TempDs18[].addr");Serial.print(TempDs18[0].addr[1]);  
  Serial.println(UserID);

 //if (_com){Serial.print("\n IP to connect via Web-Browser or FTP: ");  Serial.println(WiFi.localIP()); Serial.println("\n");  Serial.println("Start4");}
  pinMode(14,INPUT); //вход ля контроля еелектричества  
  sendATCommand("AT", true);                    // Отправили AT для настройки скорости обмена данными
  // Команды настройки модема при каждом запуске
  _response = sendATCommand("AT+CLIP=1", true);  // Включаем АОН
  //_response = sendATCommand("AT+DDET=1", true);  // Включаем DTMF
 // sendATCommand("


  
  
  }
