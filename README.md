# LetsGetSerial

A lightweight, extensible Qt QML-based serial terminal and graphing app designed for Arduino projects. 
LetsGetSerial provides a clean foundation for developers to build custom interfaces, 
visualize data, and interact with their microcontrollers.

## Arduino serial example

```c++
const int LEDOUT_13 = 13;

void setup() {

   Serial.begin(9600);
   while (!Serial) {
     // Wait for Serial to initialize
   }

   Serial.write("Available commands:\n");
   Serial.write("STATUS\n");
   Serial.write("LED_13\n");
   Serial.write("ECHO\n");
       
   pinMode(LEDOUT_13, OUTPUT);
}

bool previous_LEDOUT_13= LOW;
bool isECHO = false;
void printLedStatus(){
 if (previous_LEDOUT_13 == HIGH) {
   Serial.println("LED_13 STATUS: HIGH");
 } else {
   Serial.println("LED_13 STATUS: LOW");
 }
 if (isECHO) {
   Serial.println("ECHO STATUS: ON");
 } else {
   Serial.println("ECHO STATUS: OFF");
 }
}

String inputLine = "";
void loop() {
 while (Serial.available() > 0) {
   char c = Serial.read();
   
   if (c == '\n' || c == '\r') {
     if (isECHO) {
       Serial.write(c);
     }
     // Line complete, process it     
     if (inputLine == "STATUS") {
       printLedStatus();
     } else if (inputLine == "LED_13") {
       previous_LEDOUT_13 = !previous_LEDOUT_13;
       digitalWrite(LEDOUT_13, previous_LEDOUT_13);
     } else if (inputLine == "ECHO") {
       isECHO = !isECHO;
     }
     else {
        Serial.println("Received: " + inputLine);
       Serial.println("COMMAND DOES NOT EXISTS");
     }

     inputLine = ""; // Clear for next line
   } else {
     inputLine += c;
     if (isECHO) {
       Serial.write(c);
     }
   }
 }
}

```

## Playground scatch window

https://github.com/shemeshg/LetsGetSerial/blob/main/Design/Playground/PlaygroundComponent.qml

<img width="735" height="529" alt="image" src="https://github.com/user-attachments/assets/7d5d3b15-7c4f-41b7-a62e-53f9d6c02fe1" />


<img width="729" height="535" alt="image" src="https://github.com/user-attachments/assets/a352e83b-9cde-4029-942e-9a2cc1356cb7" />
