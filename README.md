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

https://github.com/shemeshg/LetsGetSerial/blob/LED_ON_OFF_EXAMPLE/Design/Playground/PlaygroundComponent.qml


<img width="270" height="217" alt="image" src="https://github.com/user-attachments/assets/778336bf-e307-47a3-93a0-7d44cbe63517" />

<img width="192" height="257" alt="image" src="https://github.com/user-attachments/assets/18e42650-a4b9-4ed0-873d-c9e0f12ea04c" />


