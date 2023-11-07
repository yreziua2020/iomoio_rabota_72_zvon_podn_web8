void ds1820_z(const uint16_t opros) {
        if (millis() - timer > opros) {
        timer = millis();
        sensorsDs18b20();

        
        //Serial.println(tempDs18b20) ; //для поиска
         //Serial.println("Опрос датчика") ; 
    }
       
}
//------------------------------
void sensorsDs18b20(void) {  
  static unsigned long timer1_t = millis();
  static bool cherDal;     //чередовать на два этапа запрос на изменрение и через 750 на чтение температуры

   // Serial.print(addr2[1][1]);
  if (!cherDal)  {   //250 что бы не дал било постоянно если вызывают без задежки
    if (millis()-timer1_t >250) {
      timer1_t = millis();

 /*   
      if (!ds.search(addr)) {                               // Стартуємо функцію пошук першого або наступного датчика в addr-возвращаем ответ датчика
        ds.reset_search();    // при повторном в ходе ищет следующий есл доходет до конца то сбрасывает именно сдесь что бы находило и другие датчики Якщо добігли кінця адресного простору, то скидуємо адрес на початок простору                                 
        tempDs18b20 = 999;
        return ;                                             // Виходимо з підпрограми
      }
      for(int i =0 ; i<8; i++){Serial.print(addr[i]);Serial.print(",");}
      Serial.println("");
 //*/   

  
   
   if(_D18b20) {Serial.print("первый влет "); Serial.print(" Дачик номер "); Serial.println(nom_dat); }
   
    if (OneWire::crc8(TempDs18[nom_dat].addr, 7) != TempDs18[nom_dat].addr[7]) {TempDs18[nom_dat].tDs = 50; if (nom_dat++>=K_dat) {nom_dat=0;}  if(_D18b20) { Serial.print("ретурн из первого влета "); }return ; }         // перевіряємо 7 байт в addr - он содержит crc8 
     ds.reset();                                             //present = ds.reset(); вроде всегда возвращает 1 если присутвует хоть один датчик
     ds.select(TempDs18[nom_dat].addr);
     ds.write(0x44, 1);
    cherDal=1;  //именно в незу что во вторую влетало токо после полного прохода что при повторном входе прочитать данные с датчикка температуры
    } 
  } else {
    if (millis()-timer1_t >750){ //даже если милис переполниться то просто быстрее пройдет интрвал так безнаковое при вычитании будет переброшено через ноль но к большему числу
      cherDal=0;  //сделать паузу между измирениями при постоянном повторе
      byte data[12];  
      ds.reset();
      ds.select(TempDs18[nom_dat].addr);
      ds.write(0xBE);
      for (byte i = 0; i < 9; i++) {    data[i] = ds.read();  }
      int16_t raw = (data[1] << 8) | data[0];
      byte cfg = (data[4] & 0x60);
      if (cfg == 0x00) raw = raw & ~7;
      else if (cfg == 0x20) raw = raw & ~3;
      else if (cfg == 0x40) raw = raw & ~1;
      
      if (nom_dat==1) {TempDs18[nom_dat].tDs = ((float)raw / 16.00)-3;} else {TempDs18[nom_dat].tDs = (float)raw / 16.00;}
     
     //if(TempDs18[nom_dat].tDs>50) {TempDs18[nom_dat].tDs=tDs_pred[nom_dat]; tDs_pred[nom_dat]=50;  }
     //if(TempDs18[nom_dat].tDs<40)TempDs18[nom_dat].tDs=40;
     //if(TempDs18[nom_dat].tDs<-20){ TempDs18[nom_dat].tDs=tDs_pred[nom_dat]; } else { tDs_pred[nom_dat]= TempDs18[nom_dat].tDs;}
      // if(TempDs18[3].tDs<=0){TempDs18[3].tDs=tDs_pred[3];} else { tDs_pred[3]= TempDs18[3].tDs;}
/*        if(nom_dat!=1){ 
       if(TempDs18[nom_dat].tDs<4){TempDs18[nom_dat].tDs=tDs_pred[nom_dat];} else { tDs_pred[nom_dat]= TempDs18[nom_dat].tDs;}
       }

       if(nom_dat==1){ 
       if(TempDs18[nom_dat].tDs<-20){TempDs18[nom_dat].tDs=tDs_pred[nom_dat];} else { tDs_pred[nom_dat]= TempDs18[nom_dat].tDs;}
       } */
       
      timer1_t = millis();
      
     if(_D18b20) { Serial.print("второй влет ");Serial.print(" Дачик номер "); Serial.println(nom_dat);      Serial.print("Температура ");Serial.println(TempDs18[nom_dat].tDs); }
         
      
      if (nom_dat++>=K_dat) {nom_dat=0;} // считаем  датчики с нулевого а почемуто при большем значении портило пременую случайным мусором , поэтому поставил >= а было >
      //Serial.print("nom_dat=");  Serial.println(nom_dat);      Serial.print("K_dat=");  Serial.println(K_dat);
      } 
  }
}//-----------------
