# Description

Led on/off example
Playground image change with Led when button pressed

## Arduino serial example

```c++
 const int ledOut = 8;
 const int buttonIn = 9;


void setup() {

    Serial.begin(9600);
    while (!Serial) {
      // Wait for Serial to initialize
    }

    Serial.write("Starting Loop\n");
        
    pinMode(ledOut, OUTPUT);
    pinMode(9, INPUT_PULLUP);
}

void printLedStatus(){
  if (digitalRead(buttonIn) == HIGH) {
    Serial.println("LED STATUS: LOW");
  } else {
    Serial.println("LED STATUS: HIGH");
  }
}

bool previousDigitalRead = HIGH;
String inputLine = "";
void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    
    if (c == '\n' || c == '\r') {
      // Line complete, process it
      Serial.println("Received: " + inputLine);
      if (inputLine == "LED") {
        printLedStatus();
      }
      inputLine = ""; // Clear for next line
    } else {
      inputLine += c;
    }
  }
  
  if (digitalRead(9) == HIGH) {
    digitalWrite(ledOut, LOW);
  } else {
    digitalWrite(ledOut, HIGH);
  }
  
  if (previousDigitalRead != digitalRead(buttonIn)){
    previousDigitalRead = digitalRead(buttonIn);
    printLedStatus();
  }
}

```

## Playground scatch window

https://github.com/shemeshg/LetsGetSerial/blob/main/Design/Design/Playground//PlaygroundComponent.qml

<img width="735" height="529" alt="image" src="https://github.com/user-attachments/assets/7d5d3b15-7c4f-41b7-a62e-53f9d6c02fe1" />


<img width="729" height="535" alt="image" src="https://github.com/user-attachments/assets/a352e83b-9cde-4029-942e-9a2cc1356cb7" />
