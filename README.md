# LetsGetSerial

A lightweight, extensible Qt QML-based serial terminal and graphing app designed for Arduino projects. 
LetsGetSerial provides a clean foundation for developers to build custom interfaces, 
visualize data, and interact with their microcontrollers.


```c++
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // Wait for Serial to initialize
  }

  String line = "";
  while (line.length() == 0) {
    if (Serial.available()) {
      line = Serial.readStringUntil('\n');
    }
  }

  Serial.write("Starting Loop\n");
}


void loop() {
  // put your main code here, to run repeatedly:
  int bytesSent = Serial.write("hello World\n"); 
  delay(1000);
}
```

