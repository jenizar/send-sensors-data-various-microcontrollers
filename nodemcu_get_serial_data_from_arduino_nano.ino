#include <SoftwareSerial.h>

//#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
  
  LiquidCrystal_I2C lcd(0x27,20,4); 

//create variable for software serial (Tx, Rx)
SoftwareSerial DataSerial(12, 13);   //D6, D7
//data from arduino nano
//arduino nano pin tx -> D6 esp8266/nodemcu 
//arduino nano pin rx -> D7 esp8266/nodemcu

//variabel array for data parsing 
//String arrData[2];    //total sensor = 2 
String arrData[3];    //total sensor = 3 (temp,rh,ldr)

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 
 DataSerial.begin(9600);
   lcd.init();                     
   lcd.backlight();     
}

void loop() {
  delay(2000);
  // put your main code here, to run repeatedly:

   //read serial data
   String data = "";
   while(DataSerial.available()>0)
   {
    data += char(DataSerial.read());
   }
   //remove space/blank
   data.trim();
   Serial.println(data);
   // test the data
   if(data != "")
   {
      //format data "29#70#429" = array (after parsing)
      //parsing data (data split)
      int index = 0;
      for(int i=0; i<=data.length(); i++)
      {
        char delimiter = 'H';
        if(data[i] != delimiter)
          arrData[index] += data[i];
        else
          index++;     //variabel index bertambah 1
      }
      
     //make sure the data is completed (LDR, Temp, Humidity)
     //sequence: 0, 1, 2  
     if(index == 2)
     {
        //tampilkan nilai sensor ke serial monitor
      //  Serial.println("LDR : " + arrData[0]);   //LDR
    //    Serial.println("Temperature : " + arrData[0].substring(0,3));   //Temp
    //    Serial.println("Humidity : " + arrData[1]);   //Hum   
    //    Serial.println("LDR : " + arrData[2]);   //LDR  
    //    Serial.println();
     //}   
   lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.setCursor(7, 0);
  lcd.print(arrData[0]);
  lcd.setCursor(9, 0);
  lcd.print(" ");  
  lcd.setCursor(10, 0);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(12, 0);
  lcd.print("        ");   
  
  lcd.setCursor(0, 1);
  lcd.print("R.H  : ");
  lcd.setCursor(7, 1);
  lcd.print(arrData[1]);
  lcd.setCursor(10, 1);
  lcd.print("%");    

  lcd.setCursor(0, 2);
  lcd.print("LDR  : ");
  lcd.setCursor(7, 2);
  lcd.print(arrData[2]);
  lcd.setCursor(10, 2);
  lcd.print("    ");   
      
     } 

     arrData[0] = "";
     arrData[1] = "";
     arrData[2] = "";
   }
 
}
