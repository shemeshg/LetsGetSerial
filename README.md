# LetsGetSerial

A lightweight, extensible Qt QML-based serial terminal and graphing app designed for Arduino projects. 
LetsGetSerial provides a clean foundation for developers to build custom interfaces, 
visualize data, and interact with their microcontrollers.

## Arduino serial example

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

## Playground scatch window

https://github.com/shemeshg/LetsGetSerial/blob/main/Design/Playground/PlaygroundComponent.qml

<img width="735" height="529" alt="image" src="https://github.com/user-attachments/assets/7d5d3b15-7c4f-41b7-a62e-53f9d6c02fe1" />


<img width="729" height="535" alt="image" src="https://github.com/user-attachments/assets/a352e83b-9cde-4029-942e-9a2cc1356cb7" />
