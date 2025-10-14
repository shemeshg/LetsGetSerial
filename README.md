# LetsGetSerial

A lightweight, extensible Qt QML-based serial terminal and graphing app designed for Arduino projects. 
LetsGetSerial provides a clean foundation for developers to build custom interfaces, 
visualize data, and interact with their microcontrollers.

## Arduino serial example

```c++

// v0.0.1410

class PinStatus
{
public:
  int pinNumber;
  String mode;      // "INPUT", "OUTPUT", "INPUT_PULLUP"
  String writeType; // "digital", "analog"
  int lastValue;
  bool isFollow = false;
  int followAnalogTolerance = 0;

  PinStatus(int pin, String m, String wType, int val)
  {
    pinNumber = pin;
    mode = m;
    writeType = wType;
    lastValue = val;
  }

  String getStatusString()
  {
    return "Pin " + String(pinNumber) + ": Mode=" + mode + ", WriteType=" + writeType + ", LastValue=" + String(lastValue) + " FollowMode:" + isFollow;
  }
};

const int MAX_PINS = 20;
PinStatus *pinArray[MAX_PINS]; // Array of pointers to PinStatus
int pinCount = 0;

PinStatus *getPinStatus(int pin)
{
  for (int i = 0; i < pinCount; i++)
  {
    if (pinArray[i]->pinNumber == pin)
    {
      return pinArray[i];
    }
  }
  return nullptr; // Not found
}

void updatePinStatus(int pin, String mode, String writeType, int value)
{
  PinStatus *existing = getPinStatus(pin);
  if (existing != nullptr)
  {
    existing->mode = mode;
    existing->writeType = writeType;
    existing->lastValue = value;
  }
  else if (pinCount < MAX_PINS)
  {
    pinArray[pinCount++] = new PinStatus(pin, mode, writeType, value);
  }
}

void updatePinVal(int pin, String writeType, int value)
{
  PinStatus *existing = getPinStatus(pin);
  if (existing != nullptr)
  {
    existing->writeType = writeType;
    existing->lastValue = value;
  }
  else if (pinCount < MAX_PINS)
  {
    pinArray[pinCount++] = new PinStatus(pin, "", writeType, value);
  }
}

String getStrPart(String input, int index)
{
  input.trim(); // Remove leading/trailing whitespace
  int count = 0;
  int start = 0;

  // Split by space and ignore empty parts
  for (int i = 0; i < input.length(); i++)
  {
    if (input.charAt(i) == ' ')
    {
      if (start < i)
      { // Non-empty segment
        if (count == index)
        {
          return input.substring(start, i);
        }
        count++;
      }
      start = i + 1;
    }
  }

  // Last word
  if (start < input.length() && count == index)
  {
    return input.substring(start);
  }

  return "";
}

int getIntPart(String input, int index)
{
  String part = getStrPart(input, index);
  return part.toInt();
}

void setPinMode(String inputLine)
{
  int mode = OUTPUT;
  int pin = getIntPart(inputLine, 1);
  String strMode = getStrPart(inputLine, 2);
  if (strMode == "INPUT")
  {
    mode = INPUT;
  }
  else if (strMode == "INPUT_PULLUP")
  {
    mode = INPUT_PULLUP;
  }
  pinMode(pin, mode);
  updatePinStatus(pin, strMode, "", 0);
}

void setDigitalWrite(String inputLine)
{
  int mode = HIGH;
  int pin = getIntPart(inputLine, 1);
  if (getStrPart(inputLine, 2) == "LOW")
  {
    mode = LOW;
  }
  digitalWrite(pin, mode);
  updatePinVal(pin, "Digital", mode);
}

void setAnalogWrite(String inputLine)
{
  int pin = getIntPart(inputLine, 1);
  int val = getIntPart(inputLine, 2);
  analogWrite(pin, val);
  updatePinVal(pin, "Analog", val);
}

void setDigitalRead(String inputLine)
{
  int pin = getIntPart(inputLine, 1);
  int val = digitalRead(pin);
  PinStatus *pinStatus = getPinStatus(pin);
  pinStatus->writeType = "Digital";
  pinStatus->lastValue = val;
  Serial.println("READ: " + String(pin) + " " + String(val));
}

void setAnalogRead(String inputLine)
{
  int pin = getIntPart(inputLine, 1);
  int val = analogRead(pin);
  PinStatus *pinStatus = getPinStatus(pin);
  pinStatus->writeType = "Analog";
  pinStatus->lastValue = val;
  Serial.println("READ: " + String(pin) + " " + String(val));
}

void setFollowMode(String inputLine)
{
  int pin = getIntPart(inputLine, 1);
  PinStatus *pinStatus = getPinStatus(pin);
  pinStatus->isFollow = getIntPart(inputLine, 2);
  pinStatus->followAnalogTolerance = getIntPart(inputLine, 3);
}

bool isECHO = false;
void setEcho(String inputLine)
{
  isECHO = getIntPart(inputLine, 1);
}

unsigned long heartbeatPreviousMillis = 0;
unsigned long heartbeatInterval = 1000; // 1 second
unsigned int heartbeatIntervalCounter = 0;
void setHeartbeat(String inputLine)
{
  heartbeatIntervalCounter = getIntPart(inputLine, 1);
  heartbeatInterval = getIntPart(inputLine, 2);
}

void printHelp()
{
  Serial.write("Available commands:\n");
  Serial.write("? - help\n");
  Serial.write("STATUS\n");
  Serial.write("ECHO <int bool>\n");
  Serial.write("pinMode int <OUTPUT|INPUT|INPUT_PULLUP>\n");
  Serial.write("digitalWrite int <HIGH|LOW>\n");
  Serial.write("analogWrite int <int 1..255>\n");
  Serial.write("digitalRead int \n");
  Serial.write("analogRead int \n");
  Serial.write("followMode int int int - <pin> <0/1 to follow input> <followAnalogTolerance>\n");
  Serial.write("heartbeat <int heartbeatIntervalCounter start 0=false> <int millis interval>\n");
}

void heartBeat()
{
  if (heartbeatIntervalCounter == 0)
  {
    return;
  }
  unsigned long currentMillis = millis();
  if (currentMillis - heartbeatPreviousMillis >= heartbeatInterval)
  {
    heartbeatPreviousMillis = currentMillis;
    heartbeatIntervalCounter++;
    Serial.println("Heartbit: " + String(heartbeatIntervalCounter));
  }
}

void setup()
{

  Serial.begin(115200);
  while (!Serial)
  {
    // Wait for Serial to initialize
  }
  printHelp();
}

void printLedStatus()
{

  for (int i = 0; i < pinCount; i++)
  {
    Serial.println(pinArray[i]->getStatusString());
  }
}

String inputLine = "";

void cliInterperter()
{
  while (Serial.available() > 0)
  {
    char c = Serial.read();

    if (c == '\n' || c == '\r')
    {
      if (isECHO)
      {
        Serial.write(c);
      }
      // Line complete, process it
      if (inputLine == "?")
      {
        printHelp();
      }
      else if (inputLine == "STATUS")
      {
        printLedStatus();
      }
      else if (inputLine.startsWith("pinMode"))
      {
        setPinMode(inputLine);
      }
      else if (inputLine.startsWith("digitalWrite"))
      {
        setDigitalWrite(inputLine);
      }
      else if (inputLine.startsWith("analogWrite"))
      {
        setAnalogWrite(inputLine);
      }
      else if (inputLine.startsWith("digitalRead"))
      {
        setDigitalRead(inputLine);
      }
      else if (inputLine.startsWith("analogRead"))
      {
        setAnalogRead(inputLine);
      }
      else if (inputLine.startsWith("followMode"))
      {
        setFollowMode(inputLine);
      }
      else if (inputLine.startsWith("ECHO"))
      {
        setEcho(inputLine);
      }
      else if (inputLine.startsWith("heartbeat"))
      {
        setHeartbeat(inputLine);
      }
      else
      {
        Serial.println("Received: " + inputLine);
        Serial.println("COMMAND DOES NOT EXISTS");
      }

      inputLine = ""; // Clear for next line
    }
    else
    {
      inputLine += c;
      if (isECHO)
      {
        Serial.write(c);
      }
    }
  }
}

void followNotification()
{
  for (int i = 0; i < pinCount; i++)
  {
    if (pinArray[i]->mode == "INPUT" && pinArray[i]->isFollow)
    {
      if (pinArray[i]->writeType == "Analog")
      {
        int valRed = analogRead(pinArray[i]->pinNumber);
        if (abs(pinArray[i]->lastValue - valRed) > pinArray[i]->followAnalogTolerance)
        {
          pinArray[i]->lastValue = valRed;
          Serial.println("CHANGED: " + String(pinArray[i]->pinNumber) + " " + String(pinArray[i]->lastValue));
        }
      }
      else
      {
        int valRed = digitalRead(pinArray[i]->pinNumber);
        if (valRed != pinArray[i]->lastValue)
        {
          pinArray[i]->lastValue = valRed;
          Serial.println("CHANGED: " + String(pinArray[i]->pinNumber) + " " + String(pinArray[i]->lastValue));
        }
      }
    }
  }
}

void loop()
{
  heartBeat();
  cliInterperter();
  followNotification();
}

```

```text
Available commands:
? - help
STATUS
ECHO
pinMode int <OUTPUT|INPUT|INPUT_PULLUP>
digitalWrite int <HIGH|LOW>
analogWrite int <int 1..255>
digitalRead int 
analogRead int 
followMode int int int - <pin> <0/1 to follow input> <followAnalogTolerance>
```

For example
```
pinMode 14 INPUT
analogRead 14
followMode 14 1 4
```

## Playground scatch window

https://github.com/shemeshg/LetsGetSerial/blob/main/Design/Playground/PlaygroundComponent.qml

<img width="410" height="474" alt="image" src="https://github.com/user-attachments/assets/5fc4ad08-cc1f-4ee1-9ae0-da809400ec27" />




<img width="729" height="535" alt="image" src="https://github.com/user-attachments/assets/a352e83b-9cde-4029-942e-9a2cc1356cb7" />
