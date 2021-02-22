#include <WiFi.h>
#include <WebServer.h>
#define RXD2 16  //Rx pin  -> Tx pin arduino nano
#define TXD2 17  //Tx pin  -> Rx pin arduino nano

//arduino nano pin tx -> D6 esp32 
//arduino nano pin rx -> D7 esp32

//variabel array untuk data parsing
//String arrData[2];    //jumlah sensor = 2
String arrData[3];    //jumlah sensor = 3

const char* ssid = "PULPSTONE"; //wifi ssid / wifi name
const char* password = "internet"; //wifi password

WebServer server(80);

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 
 Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); //DataSerial.begin(9600);

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {  
  server.handleClient();
}

void handle_OnConnect()
{  
  //24#87#423
  //012345678
  //Serial.println(Serial2.readString());
  float float1, float2, float3;
  
  String data = "";
  while (Serial2.available() > 0) {
    data = Serial2.readStringUntil('\n');   // Until CR (Carriage Return)
  }
  data.trim();
  if(data != "")
  {
    int index = 0;
    for(int i=0; i<=data.length(); i++)
    {
      char delimiter = 'H';
      if(data[i] != delimiter)
        arrData[index] += data[i];
      else
      index++;  
    }
    if (index == 2)
    {
      char char1[8];
      arrData[0].toCharArray(char1, arrData[0].length() +1);   
      float1 = atof(char1);

      char char2[8];
      arrData[1].toCharArray(char2, arrData[1].length() +1);   
      float2 = atof(char2);

      char char3[8];      
      arrData[2].toCharArray(char3, arrData[2].length() +1);   
      float3 = atof(char3);      
    }
    arrData[0] = "";
    arrData[1] = "";
    arrData[2] = "";
  }

server.send(200, "text/html", SendHTML(float1,float2,float3));   
}


 
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat,float Humiditystat,float Ldr){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta http-equiv=\"refresh\" content=\"3\">\n";
  ptr +="<title>ESP32 Read Sensors Display</title>\n";  
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n"; 
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP32 Read Sensors Display</h1>\n";
  
  ptr +="<p>Temperature: ";
  ptr +=(int)Temperaturestat;
  ptr +="*C</p>";
  ptr +="<p>Humidity: ";
  ptr +=(int)Humiditystat;
  ptr +="%</p>";
  ptr +="<p>Brightness: ";
  ptr +=(int)Ldr;
  ptr +="</p>";  
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
