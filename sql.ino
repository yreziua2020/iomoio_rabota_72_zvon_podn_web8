void bd_sql() {
 // Serial.print("f_pina_energy=");  Serial.println(f_pina_energy);
 //if( TempDs18[0].tDs!=-0.6 && TempDs18[1].tDs!=-0.6 && TempDs18[2].tDs!=-0.6 && TempDs18[3].tDs!=-0.6 &&  TempDs18[0].tDs!=0 /*&& TempDs18[2].tDs!=0*/ && TempDs18[3].tDs!=0 )
 //{
if (!client.connect(DB_host,Port)) {
    if (_com_sql) { Serial.print(DB_host);}
    if (_com_sql) { Serial.println(" - Connection failed.");}
    client.stop();
  }
  
    if (client.connect(DB_host, Port))
    {
    if (_com_sql) { Serial.println("database connection established (соединение с базой данных установлено)");  }
    client.print( "GET /php/wp-scale.php?A=Vp3wDWbP&ID=");
    client.print(UserID);
    client.print("&T1=");
    client.print(TempDs18[0].tDs); //data
    client.print("&T2=");
    client.print(TempDs18[1].tDs);
    client.print("&T3=");
    client.print(TempDs18[2].tDs);
    client.print("&T4=");
    client.print(TempDs18[3].tDs);
    client.print("&T5=0");  //при значению большему заданому(3 так датчиков 4 но с нуля) тоже менялась переменная f_pina_energy на ноль с 1 //при значению большему заданому(3 так датчиков 4 но с нуля) тоже менялась переменная f_pina_energy на ноль с 1
    //TempDs18[4].tDs=0;   //при значению большему заданому(3 так датчиков 4 но с нуля) тоже менялась переменная f_pina_energy на ноль с 1
    //client.print(TempDs18[4].tDs);
    client.print("&P=");
     client.print(database_pass);
    client.println( " HTTP/1.1");
    client.print( "Host:" );
    client.println(DB_host);
    client.println( "Connection: close" );
    client.println();
    client.println();
    client.stop();
    }

 //}
  
}
