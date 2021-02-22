# send-sensors-data-various-microcontrollers
send sensors data with various micro-controllers : rf 433 MHz, serial, and wifi.

arduino nano --> arduino nano --> nodemcu --> esp32

1. arduino nano send data to arduino nano (wireless rf 433 MHz)
2. arduino nano send data to nodemcu (serial transmission)
3. nodemcu send data to esp32 (serial transmission)
4. esp32 display data on web browser (WiFi) 

every change in sensor value will update the data on Arduino nano, nodemcu and esp32

demo:
youtube

references:
1. https://stackoverflow.com/questions/34054070/arduino-string-to-multiple-variables
2. https://youtu.be/Zv6VVg0yYcE
