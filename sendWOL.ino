
void WOL() {
  //h=8;
//if()  
  if(((dn==1)||(dn==2)||(dn==3)||(dn==4)||(dn==5))){
      if (h==7){
          if ((m==45)&&(s<20)) { if (!f_otpr_wr_S){f_otpr_wr_S=1;f_paket_b_S=1;}}  else { f_otpr_wr_S=0;}
          if ((m==56)&&(s<20)) { if (!f_otpr_wr){f_otpr_wr=1;f_paket_b=1;}} else  { f_otpr_wr=0;}    //
         
      }
      if (h==8){
          
          if ((m==25)&&(s<20)){ if (!f_otpr_wr_K){f_otpr_wr_K=1;f_paket_b_K=1;}} else { f_otpr_wr_K=0;} //
      }
  }

 
  //for (int i=0; i < kol_kom; i++)    {     if(f_paket[i]) {Serial.print("Send-");Serial.println(i);f_paket[i]=0;sendWOL_X(i);}   }


        if (millis() - t_w_vse > 1000) {  
        t_w_vse = millis();
         if (f_paket_b) {
              if(devices[coun_W_pk].f_wek==1) { sendWOL_X(coun_W_pk);} else {Serial.print("не отправить wek только на 1 ");Serial.println(devices[coun_W_pk].deviceName);}
              if (coun_W_pk++>=kol_kom) {coun_W_pk=0;f_paket_b=0;}
         }
         if (f_paket_b_S) {
              if(devices[coun_W_pk].f_wek==2) { sendWOL_X(coun_W_pk);} else {Serial.print("не отправить wek только на 2 ");Serial.println(devices[coun_W_pk].deviceName);}
              if (coun_W_pk++>=kol_kom) {coun_W_pk=0;f_paket_b_S=0;}
         }
         if (f_paket_b_K) {
              if(devices[coun_W_pk].f_wek==3) { sendWOL_X(coun_W_pk);} else {Serial.print("не отправить wek только на 3 ");Serial.println(devices[coun_W_pk].deviceName);}
              if (coun_W_pk++>=kol_kom) {coun_W_pk=0;f_paket_b_K=0;}
         }
         
        }

}// WOL()

void sendWOL_X(int nomer) {
  const int magicPacketLength = 102; 
  byte magicPacket[magicPacketLength] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
   Serial.print("sendWOL_X_ ");  Serial.print(nomer);  Serial.print(" ");Serial.println( devices[nomer].deviceName); //Serial.print("=");     Serial.println( devices[nomer].mac[0] ,HEX);
  for (int ix=6; ix < magicPacketLength; ix++)    {  magicPacket[ix] = devices[nomer].mac[ix % 6] ; Serial.print(magicPacket[ix],HEX); Serial.print("");}      //7
  Serial.println("");
 // udp.begin(localUdpPort);
  udp.begin(localPort);
  udp.beginPacket(targetIPAddress, targetWOLPort);
  udp.write(magicPacket, magicPacketLength);
  udp.endPacket();
  udp.stop();

}
