

bool handleFileRead(String path){                                       // Функция работы с файловой системой
  if(path.endsWith("/")) path += "index.html";                          // Если устройство вызывается по корневому адресу, то должен вызываться файл index.html (добавляем его в конец адреса)
  String contentType = getContentType(path);                            // С помощью функции getContentType (описана ниже) определяем по типу файла (в адресе обращения) какой заголовок необходимо возвращать по его вызову
  if(SPIFFS.exists(path)){                                              // Если в файловой системе существует файл по адресу обращения
    File file = SPIFFS.open(path, "r");                                 //  Открываем файл для чтения
    size_t sent = HTTP.streamFile(file, contentType);                   //  Выводим содержимое файла по HTTP, указывая заголовок типа содержимого contentType
    file.close();                                                       //  Закрываем файл
    return true;                                                        //  Завершаем выполнение функции, возвращая результатом ее исполнения true (истина)
  }
  return false;                                                         // Завершаем выполнение функции, возвращая результатом ее исполнения false (если не обработалось предыдущее условие)
}

String getContentType(String filename){                                 // Функция, возвращающая необходимый заголовок типа содержимого в зависимости от расширения файла
  if (filename.endsWith(".html")) return "text/html";                   // Если файл заканчивается на ".html", то возвращаем заголовок "text/html" и завершаем выполнение функции
  else if (filename.endsWith(".css")) return "text/css";                // Если файл заканчивается на ".css", то возвращаем заголовок "text/css" и завершаем выполнение функции
  else if (filename.endsWith(".js")) return "application/javascript";   // Если файл заканчивается на ".js", то возвращаем заголовок "application/javascript" и завершаем выполнение функции
  else if (filename.endsWith(".png")) return "image/png";               // Если файл заканчивается на ".png", то возвращаем заголовок "image/png" и завершаем выполнение функции
  else if (filename.endsWith(".jpg")) return "image/jpeg";              // Если файл заканчивается на ".jpg", то возвращаем заголовок "image/jpg" и завершаем выполнение функции
  else if (filename.endsWith(".gif")) return "image/gif";               // Если файл заканчивается на ".gif", то возвращаем заголовок "image/gif" и завершаем выполнение функции
  else if (filename.endsWith(".ico")) return "image/x-icon";            // Если файл заканчивается на ".ico", то возвращаем заголовок "image/x-icon" и завершаем выполнение функции
  return "text/plain";                                                  // Если ни один из типов файла не совпал, то считаем что содержимое файла текстовое, отдаем соответствующий заголовок и завершаем выполнение функции
}







String handleData() {
  String message = "{\"";
   message += "temp";
   message += "\":[";
   message += TempDs18[0].tDs;  
   message += ","; 
   message += TempDs18[1].tDs;
   message += ","; 
   message += TempDs18[2].tDs;
   message += ","; 
   message += TempDs18[3].tDs;
   message += ","; 
   message += TempDs18[4].tDs;
   message += "]"; 
     
 
  message += ",\"";
  message += "uptime";
  message += "\":";
  message += String(millis() / 1000);
  //message += String(per_zn-1);
  message += ",\"";
  message+="time";
 ////message += "\":\"";
 
  message += "\":";
 message += ntp_time;
 
 /// message+= (String)h+":";
 /// message+= (String)m+":"; 
 /// message+= (String)s+"-"; 
 /// message+= (String)dn;
 /// message += "\",\"";
  
  message += ",\"";
    message+="ip";
    message += "\":\"";
    message+=(String)devices[pin_ip_caun-1].web_ip;  
    message += "\",\"";
  message += "relay";
  message += "\":[";
 if (rele[0]) message += "true"; else message += "false";
 for(uint8_t i=1; i<kol_kom ; i++) {
  message += ",";
  if (rele[i]) message += "true"; else message += "false";
  }
 
 
  message += "],\"";
  message += "ping";
  message += "\":[";
 if (ping_ok[0]) message += "true"; else message += "false";
 for(uint8_t i=1; i<kol_kom ; i++) {
  message += ",";
  if (ping_ok[i]) message += "true"; else message += "false";
  }


/*
 for(uint8_t i=0; i<kol_kom ; i++) {
  message += ",\"relay"+(String)i;
  message += "\":";
  if (ping_ok[i]) message += "true"; else message += "false";
  }
 */
  message += "]";

  message += ",\"";
  message += "konde";
  message += "\":[";
 if (kond[0]) message += "true"; else message += "false";
 message +=",";
 if (kond[1]) message += "true"; else message += "false";
 message +=",";
 if (kond[2]) message += "true"; else message += "false";
 message +=",";
 if (kond[3]) message += "true"; else message += "false";
  message += "]";
  message += "}";
  
  //httpServer.send(200, F("text/html"), message);
  //Serial.print("message=");Serial.println(message);
  return message;
}


String StartData() {
//  per_zn=0; //заставляем преррисовать графиик при обновлении страницы
  String message = "{";
   message +="\"web_ip\":[\""+devices[0].web_ip+"\"";
  for (uint8_t i=1; i<kol_kom; i++)   {message +=",\""+ devices[i].web_ip+"\""; }
  message += "],\"deviceName\":[\""+devices[0].deviceName+"\"";
  for (uint8_t i=1; i<kol_kom; i++)   {message +=",\""+ devices[i].deviceName+"\""; }
  message += "]";
  message += "}";
  
  //Serial.print("message=");Serial.println(message);  
  return message;
}  
