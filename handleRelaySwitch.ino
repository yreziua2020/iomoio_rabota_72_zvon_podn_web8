String handleRelaySwitch() {
  String id = HTTP.arg("id");
  String on = HTTP.arg("on");

 /* Serial.print(F("/switch("));
  Serial.print(id);
  Serial.print(F(", "));
  Serial.print(on);
  Serial.println(F(")"));*/
  
  switchRelay(id.toInt(), on == "true");
  
  /*if (on == "true")  digitalWrite(relayPin0, false);
  else digitalWrite(relayPin0,true );*/
  String message = "OK";
  //String message = "";
  return message;
 
}

void switchRelay(int8_t id, bool on) {
 /// if (((id < 0) || (id >= maxRelays)) || (relayPin[id] == -1))    return;
  if (rele[id] != on) { rele[id]= on;} 
      if (rele[id]) {sendWOL_X(id);}
  
   Serial.print("id=");Serial.print(id);Serial.print("Значение реле");Serial.println( rele[id]);
 //// bool relay = digitalRead(relayPin[id]);
    
   //if (relay)  digitalWrite(relayPin[id], false); else digitalWrite(relayPin[id], true);
  //if (! relayLevel[id])    relay = ! relay;
  //if (relay != on) { digitalWrite(relayPin[id], relayLevel[id] == on);
////  if (relay != on) { digitalWrite(relayPin[id], on);  } 
 
 //Serial.print("_ReadrelayPin[id]=");
 // Serial.println(digitalRead(relayPin[id]));
  //delay(50);
}

String KondSwitch() {
  String id = HTTP.arg("id");
  String on = HTTP.arg("on");

  switchKond(id.toInt(), on == "true");
  
  String message = "OK";
  return message;
 
}

void switchKond(int8_t id, bool on) {
 /// if (((id < 0) || (id >= maxRelays)) || (relayPin[id] == -1))    return;
  if (kond[id] != on) { kond[id]= on;} 
       if ( kond[id]) {        
        if (id==0) {    Serial.print("посылаем команду Включить холод");  irsend.sendRaw(rawData_on, 439, 38);  delay(100);}  
        if (id==1) {    Serial.print("посылаем команду выключить холод"); irsend.sendRaw(rawData_Off, 439, 38); delay(100); }
        if (id==2) {    Serial.print("посылаем команду Включить фан");    irsend.sendRaw(rawData_on_f, 439, 38);delay(100); }
        if (id==3) {    Serial.print("посылаем команду выключить фан");   irsend.sendRaw(rawData_Off_f, 439, 38); delay(100); }
       }
   Serial.print("id=");Serial.print(id);Serial.print("Значение реле");Serial.println( kond[id]);
}
