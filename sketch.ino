```cpp
const int trigPin = 3;
const int echoPin = 2;
const int ledPin = 8;

unsigned long previousSensorTime = 0;
unsigned long previousStatusTime = 0;

const unsigned long sensorInterval = 200;
const unsigned long statusInterval = 1000;

float distance = 0;
bool objectDetected = false;
bool validReading = false;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  unsigned long currentTime = millis();

  // Task 1: Read the sensor every 200 ms
  if (currentTime - previousSensorTime >= sensorInterval)
  {
    previousSensorTime = currentTime;

    digitalWrite(trigPin, LOW);
    digitalWrite(trigPin, HIGH);
    digitalWrite(trigPin, LOW);

    // Generate the ultrasonic trigger pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    unsigned long duration = pulseIn(echoPin, HIGH, 30000);

    validReading = (duration > 0);

    if (validReading)
    {
      distance = duration * 0.0343 / 2;
      objectDetected = (distance <= 20);
    }
    else
    {
      objectDetected = false;
    }

    digitalWrite(ledPin,
                 (validReading && objectDetected) ? HIGH : LOW);
  }

  // Task 2: Print status every 1000 ms
  if (currentTime - previousStatusTime >= statusInterval)
  {
    previousStatusTime = currentTime;

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
