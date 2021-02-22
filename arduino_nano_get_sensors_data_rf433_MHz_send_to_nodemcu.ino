#include <LiquidCrystal_I2C.h>
#include <VirtualWire.h>
#include <SPI.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

char recibo[10]="";   //for 3 sensors
//char recibo[8]="";  //for 2 sensors
int valorX; //DHT11 sensor temperature 
int valorY; //DHT11 sensor RH 
int valorZ; //LDR 

//Nano Rx -> NodemCU D6 | Nano as receiver RF433MHz and send data serial to NodeMCU
//Nano Tx -> NodeMCU D7 | Nano as receiver RF433MHz and send data serial to NodeMCU

void setup()
{
  Serial.begin(9600);
    lcd.init();
    lcd.backlight();
Serial.println("Device is ready");
// Initialize the IO and ISR
vw_set_rx_pin(11); 
vw_setup(2000); // Bits per sec
vw_rx_start(); // Start the receiver
}
void loop()
{
  delay(2000);  
    uint8_t buf[VW_MAX_MESSAGE_LEN];  
    uint8_t buflen = VW_MAX_MESSAGE_LEN;   
    
if (vw_get_message(buf, &buflen)) // Non-blocking
{
for (int i = 0; i < buflen; i++)
{
        recibo[i]=char(buf[i]);
    //    Serial.print(recibo[i]);    
}
     recibo[buflen]=NULL; 
     //String str(recibo);
     sscanf( recibo, "%d,%d,%d", &valorX, &valorY, &valorZ );
     
  Serial.println(valorX);    
  Serial.println(valorY);   
  Serial.println(valorZ);   
  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.setCursor(7, 0);
  lcd.print(valorX);
  lcd.setCursor(10, 0);
  lcd.print((char)223);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("R.H  : ");
  lcd.setCursor(7, 1);
  lcd.print(valorY);
  lcd.setCursor(10, 1);
  lcd.print("%");    

  lcd.setCursor(0, 2);
  lcd.print("LDR  : ");
  lcd.setCursor(7, 2);
  lcd.print(valorZ); 

  String datakirim = String(valorX) + String('H') + String(valorY) + String('H') + String(valorZ);
  Serial.println(datakirim);
}   
}
