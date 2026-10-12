```cpp
const int trigPin = 3;
const int echoPin = 2;
const int ledPin = 8;

const unsigned long sensorInterval = 200;
const unsigned long statusInterval = 1000;
const unsigned long triggerPulseTime = 10;
const unsigned long echoTimeout = 30000;

unsigned long previousSensorTime = 0;
unsigned long previousStatusTime = 0;
unsigned long triggerStartTime = 0;
unsigned long echoStartTime = 0;

unsigned long echoDuration = 0;
float distance = 0;

bool waitingForEcho = false;
bool waitingForRise = false;
bool validReading = false;
bool objectDetected = false;

enum SensorState
{
  IDLE,
  TRIGGER_HIGH,
  WAIT_FOR_ECHO
};

SensorState sensorState = IDLE;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(trigPin, LOW);
  Serial.begin(9600);
}

void loop()
{
  unsigned long now = micros();
  unsigned long nowMs = millis();

  // Start a measurement every 200 ms.
  if (sensorState == IDLE &&
      nowMs - previousSensorTime >= sensorInterval)
  {
    previousSensorTime = nowMs;
    digitalWrite(trigPin, HIGH);
    triggerStartTime = now;
    sensorState = TRIGGER_HIGH;
    waitingForRise = false;
  }

  // Finish the 10-microsecond trigger pulse.
  if (sensorState == TRIGGER_HIGH &&
      now - triggerStartTime >= triggerPulseTime)
  {
    digitalWrite(trigPin, LOW);
    echoStartTime = now;
    sensorState = WAIT_FOR_ECHO;
    waitingForEcho = true;
    waitingForRise = false;
  }

  // Read the echo pin without pulseIn().
  if (sensorState == WAIT_FOR_ECHO)
  {
    bool echoHigh = digitalRead(echoPin);

    if (!waitingForRise && echoHigh)
    {
      echoStartTime = now;
      waitingForRise = true;
    }

    if (waitingForRise && !echoHigh)
    {
      echoDuration = now - echoStartTime;
      distance = echoDuration * 0.0343 / 2.0;
      validReading = true;
      objectDetected = (distance <= 20);
      sensorState = IDLE;
      waitingForEcho = false;
    }
    else if (now - echoStartTime >= echoTimeout)
    {
      validReading = false;
      objectDetected = false;
      sensorState = IDLE;
      waitingForEcho = false;
    }
  }

  // Update the LED from the latest reading.
  digitalWrite(ledPin,
               (validReading && objectDetected) ? HIGH : LOW);

  // Print status every 1000 ms.
  if (nowMs - previousStatusTime >= statusInterval)
  {
    previousStatusTime = nowMs;

    if (validReading)
    {
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
    }
    else
    {
      Serial.println("No valid distance reading");
    }

    Serial.println(objectDetected && validReading
                       ? "Object Nearby - LED ON"
                       : "Object Far - LED OFF");
  }
}
```
