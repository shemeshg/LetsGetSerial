// ShellWe v0.0.251024
int getIntPart(String input, int index);
String getStrPart(String input, int index);

class ShellWeItmItf
{
public:
  ShellWeItmItf(String cmdIdentifier, String cmdUsage) : cmdIdentifier{cmdIdentifier}, cmdUsage{cmdUsage}
  {
  }

  const String getCmdIdentifier() const
  {
    return cmdIdentifier;
  }

  const String getCmdUsage() const
  {
    return cmdUsage;
  }

  virtual void cmdAction(String line) = 0;

  virtual ~ShellWeItmItf() {};

private:
  String cmdIdentifier;
  String cmdUsage;
};

class HelpCmd : public ShellWeItmItf
{
public:
  HelpCmd() : ShellWeItmItf("?", "Displays available commands") {}

  void cmdAction(String line) override
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
    Serial.write("followMode int int int - <pin> <0/1 to follow input> <followAnalogTolerance>  <int millis interval 0=false>\n");
    Serial.write("heartbeat <int heartbeatIntervalCounter start 0=false> <int millis interval>\n");
  }

  ~HelpCmd() override {}
};



const int MAX_ShellWeItmItf = 20;
class ShellWe
{
public:
  void append(ShellWeItmItf *itm)
  {
    shellWeItmItfArray[shellWeItmItfCount++] = itm;
  }

  bool runCmds(String inputLine)
  {
    String inputLineCmdIdentifier = getStrPart(inputLine, 0);
    for (int i = 0; i < shellWeItmItfCount; i++)
    {
      if (shellWeItmItfArray[i]->getCmdIdentifier() == inputLineCmdIdentifier)
      {
        shellWeItmItfArray[i]->cmdAction(inputLine);
        return true;
      }
    }
    return false;
  }

  void printHelp()
  {
    Serial.println("***** For My Debug ***********");
    for (int i = 0; i < shellWeItmItfCount; i++)
    {
      Serial.println("Cmd: " + shellWeItmItfArray[i]->getCmdIdentifier() + " - " + shellWeItmItfArray[i]->getCmdUsage());
    }
  }

private:
  ShellWeItmItf *shellWeItmItfArray[MAX_ShellWeItmItf];
  int shellWeItmItfCount = 0;
};
ShellWe shellWe{};

class PinStatus
{
public:
  int pinNumber;
  String mode;      // "INPUT", "OUTPUT", "INPUT_PULLUP"
  String writeType; // "digital", "analog"
  bool isFollow = false;
  int followAnalogTolerance = 0;
  int millisInterval = 0;

  PinStatus(int pin, String m, String wType, int val)
  {
    pinNumber = pin;
    mode = m;
    writeType = wType;
    setLastVal(val);
  }

  String getStatusString()
  {
    return "Pin " + String(pinNumber) + ": Mode=" + mode + ", WriteType=" + writeType + ", LastValue=" + String(lastValue) + " FollowMode:" + isFollow;
  }

  void setLastVal(int v)
  {
    lastValue = v;
    lastMilis = millis();
  }

  int getLastVal()
  {
    return lastValue;
  }

  bool isIntervalPassed()
  {
    return (millis() - lastMilis >= millisInterval);
  }

private:
  int lastValue;
  unsigned long lastMilis;
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
    existing->setLastVal(value);
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
    existing->setLastVal(value);
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
  pinStatus->setLastVal(val);
  Serial.println("READ: " + String(pin) + " " + String(val));
}

void setAnalogRead(String inputLine)
{
  int pin = getIntPart(inputLine, 1);
  int val = analogRead(pin);
  PinStatus *pinStatus = getPinStatus(pin);
  pinStatus->writeType = "Analog";
  pinStatus->setLastVal(val);
  Serial.println("READ: " + String(pin) + " " + String(val));
}

void setFollowMode(String inputLine)
{
  int pin = getIntPart(inputLine, 1);
  PinStatus *pinStatus = getPinStatus(pin);
  pinStatus->isFollow = getIntPart(inputLine, 2);
  pinStatus->followAnalogTolerance = getIntPart(inputLine, 3);
  pinStatus->millisInterval = getIntPart(inputLine, 4);
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

class StatusCmd : public ShellWeItmItf
{
public:
  StatusCmd() : ShellWeItmItf("STATUS", "Displays PIN status") {}

  void cmdAction(String line) override
  {
    for (int i = 0; i < pinCount; i++)
    {
      Serial.println(pinArray[i]->getStatusString());
    }
  }

  ~StatusCmd() override {}
};

void setup()
{

  Serial.begin(115200);
  while (!Serial)
  {
    // Wait for Serial to initialize
  }

  shellWe.append(new HelpCmd{});
  shellWe.append(new StatusCmd{});
  shellWe.printHelp();
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

      String inputLineCmdIdentifier = getStrPart(inputLine, 0);

      if (shellWe.runCmds(inputLine))
      {
        // yes we found cmd and run it
      }
      else if (inputLineCmdIdentifier == "pinMode")
      {
        setPinMode(inputLine);
      }
      else if (inputLineCmdIdentifier == "digitalWrite")
      {
        setDigitalWrite(inputLine);
      }
      else if (inputLineCmdIdentifier == "analogWrite")
      {
        setAnalogWrite(inputLine);
      }
      else if (inputLineCmdIdentifier == "digitalRead")
      {
        setDigitalRead(inputLine);
      }
      else if (inputLineCmdIdentifier == "analogRead")
      {
        setAnalogRead(inputLine);
      }
      else if (inputLineCmdIdentifier == "followMode")
      {
        setFollowMode(inputLine);
      }
      else if (inputLineCmdIdentifier == "ECHO")
      {
        setEcho(inputLine);
      }
      else if (inputLineCmdIdentifier == "heartbeat")
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
        if (abs(pinArray[i]->getLastVal() - valRed) > pinArray[i]->followAnalogTolerance && pinArray[i]->isIntervalPassed())
        {
          pinArray[i]->setLastVal(valRed);
          Serial.println("CHANGED: " + String(pinArray[i]->pinNumber) + " " + String(pinArray[i]->getLastVal()));
        }
      }
      else
      {
        int valRed = digitalRead(pinArray[i]->pinNumber);
        if (valRed != pinArray[i]->getLastVal() && pinArray[i]->isIntervalPassed())
        {
          pinArray[i]->setLastVal(valRed);
          Serial.println("CHANGED: " + String(pinArray[i]->pinNumber) + " " + String(pinArray[i]->getLastVal()));
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