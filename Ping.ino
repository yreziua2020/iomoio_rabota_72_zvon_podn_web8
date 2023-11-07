void pingg (uint16_t opros){
    if (millis() - t_ping > opros) {   //5000 -5 секунд
        if(pin_ip_caun<kol_kom){  
            if (devices[pin_ip_caun].f_ping) {   //если не надо пинговоать то не обнуляем тамер , а сразу при повторном  и сразу при повторном вызове проверяем следующий
                t_ping = millis(); 
                if(_Dping) {Serial.print("Запуск пинга");Serial.print(devices[pin_ip_caun].web_ip);}                
                sendUserPing(devices[pin_ip_caun].pingH, 2, 500);  
                pin_ip_caun++;
            } else {pin_ip_caun++;}  
        } else  {pin_ip_caun=0;}
        
      } //millis() 
}

// отправляем пинг-запрос на конкретный хост. IP-адрес может быть URL-адресом или IP-адресом
void sendUserPing(const char* ipaddress, u8_t count = 3, u32_t timeout = 1000) {
     IPAddress ip;
      if (WiFi.hostByName(ipaddress, ip)) {
       if(_Dping) {Serial.printf("Отправка пинга на %s (%s)\n",  ipaddress, ip.toString().c_str());}
       userPinger.begin(ipaddress, count, timeout);  // // 3 пинга, тайм-аут 1000 это значения по умолчанию
     } else {             
       if(_Dping) {Serial.printf("Не удалось создать действительный IP-адрес для  %s\n",  ipaddress);}
     }    
}


 // функция, которая вызывается, когда приходит ответ на пинг с указанного 
// когда истикает время  точно
bool userPingerRecvCallback(const AsyncPingResponse& response) {

     IPAddress addr(response.addr); // для предотвращения без const toString() в 2.3.0
     if (response.answer)
        {
        ping_ok[pin_ip_caun-1]=1;
        rele[pin_ip_caun-1] =ping_ok[pin_ip_caun-1];
        //Serial.print("+");
        if(_Dping){Serial.printf("%d байт из %s: icmp_seq=%d ttl=%d time=%lu ms\n", response.size, addr.toString().c_str(), response.icmp_seq, response.ttl, response.time);}
        }
     else
      {
        ping_ok[pin_ip_caun-1]=0;
        rele[pin_ip_caun-1] =ping_ok[pin_ip_caun-1];
       if(_Dping){Serial.printf("еще нет ответа от %s icmp_seq=%d\n", addr.toString().c_str(), response.icmp_seq); }
        //Serial.print("-");
      }
     return false; //// не останавливаться
}


//  функция, которая вызывается, когда истекает время ожидания запроса ping пользователя 
//вызыветься полсе поледнего пинга указано при запуске пингов 
bool userPingerFinalCallback(const AsyncPingResponse& response) {
     IPAddress addr(response.addr); /// для предотвращения без const toString() в 2.3.0 
    // if(_debag){Serial.printf("%d запросов отправлено на %s, %d получено, время: %lu ms\n", response.total_sent, addr.toString().c_str(), response.total_recv, response.total_time);}
    if (response.total_recv) {
        if(_Dping){ Serial.println("ответ получен");Serial.println("");}
    } else {
        if(_Dping) {Serial.print("Ответ не был получен");Serial.println("");}
    }
     return true;  //выполнено (не имеет значения)
}
