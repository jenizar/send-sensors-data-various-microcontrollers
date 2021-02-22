#include <VirtualWire.h> //Load the library
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2    // pin D2 - Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int i;

int Sensor1Data;
int Sensor2Data;
unsigned int Ldr;
char Sensor1CharMsg[4]; 
char Sensor2CharMsg[4];
char LdrMsg[4];

void setup()
{ 
    Serial.begin(9600);    // Debugging only
    Serial.println(F("DHTxx test!"));
    dht.begin();     
    vw_set_tx_pin(12);          // Sets pin D12 as the TX pin
    vw_setup(2000);          // Bits per sec         
    lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
    lcd.backlight();          
}
void loop()
{
  Sensor1Data = dht.readHumidity();
  // Read temperature as Celsius (the default)
  Sensor2Data = dht.readTemperature();     
   Ldr = analogRead(A0);
   
  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.setCursor(7, 0);
  lcd.print(Sensor2Data);
  lcd.setCursor(10, 0);
  lcd.print((char)223);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("R.H  : ");
  lcd.setCursor(7, 1);
  lcd.print(Sensor1Data);
  lcd.setCursor(10, 1);
  lcd.print("%");  

  lcd.setCursor(0, 2);
  lcd.print("LDR  : ");
  lcd.setCursor(7, 2);
  lcd.print(Ldr); 
         
    // Convert integer data to Char array directly 
      itoa(Sensor2Data,Sensor1CharMsg,10);
      itoa(Sensor1Data,Sensor2CharMsg,10);
      itoa(Ldr,LdrMsg,10);
  //char envioXY[ 24 ]="";    //for 2 sensors
  char envioXYZ[ 36 ]="";      //for 3 sensors 
  sprintf(envioXYZ,"%d,%d,%d",Sensor2Data,Sensor1Data,Ldr); 
//  Serial.println(envioXY); //for 2 sensors
  Serial.println(envioXYZ); //for 3 sensors
//        vw_send((byte *)DHT.temperature, strlen(DHT.temperature));  
      //  vw_send((uint8_t *)envioXY, strlen(envioXY)); //for 2 sensors
        vw_send((uint8_t *)envioXYZ, strlen(envioXYZ));   //for 3 sensors
     //    vw_send((uint8_t *)Sensor2CharMsg, strlen(Sensor2CharMsg));
         vw_wait_tx(); // Wait until the whole message is gone 
      
    delay(400);

}
    
