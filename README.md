# LetsGetSerial

A lightweight, extensible Qt QML-based serial terminal and graphing app designed for Arduino projects. 
LetsGetSerial provides a clean foundation for developers to build custom interfaces, 
visualize data, and interact with their microcontrollers.

## Arduino serial example

```c++
class PinStatus {
public:
  int pinNumber;
  String mode;         // "INPUT", "OUTPUT", "INPUT_PULLUP"
  String writeType;    // "digital", "analog"
  int lastValue;

  PinStatus(int pin, String m, String wType, int val) {
    pinNumber = pin;
    mode = m;
    writeType = wType;
    lastValue = val;
  }

  String getStatusString() {
    return "Pin " + String(pinNumber) + ": Mode=" + mode + ", WriteType=" + writeType + ", LastValue=" + String(lastValue);
  }
};

const int MAX_PINS = 20;
PinStatus* pinArray[MAX_PINS]; // Array of pointers to PinStatus
int pinCount = 0;

PinStatus* getPinStatus(int pin) {
  for (int i = 0; i < pinCount; i++) {
    if (pinArray[i]->pinNumber == pin) {
      return pinArray[i];
    }
  }
  return nullptr; // Not found
}

void updatePinStatus(int pin, String mode, String writeType, int value) {
  PinStatus* existing = getPinStatus(pin);
  if (existing != nullptr) {
    existing->mode = mode;
    existing->writeType = writeType;
    existing->lastValue = value;
  } else if (pinCount < MAX_PINS) {
    pinArray[pinCount++] = new PinStatus(pin, mode, writeType, value);
  }
}

void updatePinVal(int pin, String writeType, int value) {
  PinStatus* existing = getPinStatus(pin);
  if (existing != nullptr) {
    existing->writeType = writeType;
    existing->lastValue = value;
  } else if (pinCount < MAX_PINS) {
    pinArray[pinCount++] = new PinStatus(pin, "", writeType, value);
  }
}

String getStrPart(String input, int index) {
  input.trim(); // Remove leading/trailing whitespace
  int count = 0;
  int start = 0;

  // Split by space and ignore empty parts
  for (int i = 0; i < input.length(); i++) {
    if (input.charAt(i) == ' ') {
      if (start < i) { // Non-empty segment
        if (count == index) {
          return input.substring(start, i);
        }
        count++;
      }
      start = i + 1;
    }
  }

  // Last word
  if (start < input.length() && count == index) {
    return input.substring(start);
  }

  return "";
}


int getIntPart(String input, int index) {
  String part = getStrPart(input, index);
  return part.toInt();
}


void setPinMode(String inputLine){
  int mode = OUTPUT;
  int pin = getIntPart(inputLine,1);
  String strMode =  getStrPart(inputLine,2);
  if (strMode == "INPUT") {
    mode = INPUT;
  } else if (strMode == "INPUT_PULLUP") {
    mode = INPUT_PULLUP;
  }
  pinMode(pin, mode);
  updatePinStatus(pin, strMode, "", 0);
}

void setDigitalWrite(String inputLine){
  int mode = HIGH;
  int pin = getIntPart(inputLine,1);
  if (getStrPart(inputLine,2) == "LOW") {
    mode = LOW;
  } 
  digitalWrite(pin, mode);  
  updatePinVal(pin, "Digital", mode); 
}


void setAnalogWrite(String inputLine){  
  int pin = getIntPart(inputLine,1);
  int val = getIntPart(inputLine,2);
  analogWrite(pin, val);
  updatePinVal(pin, "Analog", val);
}

void setDigitalRead(String inputLine){
  int pin = getIntPart(inputLine,1);


  Serial.println("READ: " + String(pin) + " " + String(digitalRead(pin)));
}

void setAnalogRead(String inputLine){
  int pin = getIntPart(inputLine,1);
  Serial.println("READ: " + String(pin) + " " + String(analogRead(pin)));
}



void setup() {

   Serial.begin(9600);
   while (!Serial) {
     // Wait for Serial to initialize
   }

   Serial.write("Available commands:\n");
   Serial.write("STATUS\n");
   Serial.write("ECHO\n");
   Serial.write("pinMode int <OUTPUT|INPUT|INPUT_PULLUP>\n");
   Serial.write("digitalWrite int <HIGH|LOW>\n");
   Serial.write("analogWrite int <int 1..255>\n");
   Serial.write("digitalRead int \n");
   Serial.write("analogRead int \n");
}

bool isECHO = false;
void printLedStatus(){

  for (int i = 0; i < pinCount; i++) {
    Serial.println(pinArray[i]->getStatusString());
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
     } else if (inputLine.startsWith("pinMode")) {
        setPinMode(inputLine);
     } else if (inputLine.startsWith("digitalWrite")) {
        setDigitalWrite(inputLine);
     } else if (inputLine.startsWith("analogWrite")) {
        setAnalogWrite(inputLine);
     } else if (inputLine.startsWith("digitalRead")) {
        setDigitalRead(inputLine);
     } else if (inputLine.startsWith("analogRead")) {
        setAnalogRead(inputLine);
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

<img width="410" height="474" alt="image" src="https://github.com/user-attachments/assets/5fc4ad08-cc1f-4ee1-9ae0-da809400ec27" />




<img width="729" height="535" alt="image" src="https://github.com/user-attachments/assets/a352e83b-9cde-4029-942e-9a2cc1356cb7" />
