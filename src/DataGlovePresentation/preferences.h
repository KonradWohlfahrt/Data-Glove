#ifndef PREFERENCES_h
#define PREFERENCES_h



// ---  YOUR SENSOR VALUES GO HERE ---
int extendedValues[5] = { 512, 512, 512, 512, 512 };
int contractedValues[5] = { 512, 512, 512, 512, 512 };
// ---  YOUR SENSOR VALUES GO HERE ---



#define HALL_THUMB A0
#define HALL_INDEX A1
#define HALL_MIDDLE A2
#define HALL_RING A3
#define HALL_PINKY A4

#define SAMPLES 10
#define SAMPLE_TIME 1

enum Fingers {
  finger_thumb = 0,
  finger_index = 1,
  finger_middle = 2,
  finger_ring = 3,
  finger_pinky = 4
};

int _medianValues[5];
int _deadzoneValues[5];
void initializeGlove()
{
  for (int i = 0; i < 5; i++) 
  {
    _medianValues[i] = (extendedValues[i] + contractedValues[i]) / 2;
    if (extendedValues[i] < contractedValues[i])
      _deadzoneValues[i] = (contractedValues[i] - extendedValues[i]) / 4;
    else
      _deadzoneValues[i] = (extendedValues[i] - contractedValues[i]) / 4;
  }
}

int readHallSensorSingle(Fingers finger, int samples = SAMPLES);
int readHallSensorSingle(Fingers finger, int samples)
{
  int pin;
  switch (finger)
  {
    case finger_thumb:
      pin = HALL_THUMB;
      break;
    case finger_index:
      pin = HALL_INDEX;
      break;
    case finger_middle:
      pin = HALL_MIDDLE;
      break;
    case finger_ring:
      pin = HALL_RING;
      break;
    case finger_pinky:
      pin = HALL_PINKY;
      break;
  }

  long avg = 0;
  for(int i = 0; i < samples; i++)
  {
    avg += analogRead(pin);
    delay(SAMPLE_TIME);
  }
  return (int)(avg / samples);
}
bool isExtended(Fingers finger)
{
  int val = readHallSensorSingle(finger);
  int extended = extendedValues[(int)finger];
  int contracted = contractedValues[(int)finger];

  int m = (extended + contracted) / 2;

  if (extended > contracted)
    return val >= m;
  return val <= m;
}

long _sensorData[5];
bool fingersExtended[5];
void readHallSensors(int samples = SAMPLES);
void readHallSensors(int samples)
{
  memset(_sensorData, 0, sizeof(_sensorData));
  for (int i = 0; i < samples; i++)
  {
    _sensorData[0] += analogRead(HALL_THUMB);
    _sensorData[1] += analogRead(HALL_INDEX);
    _sensorData[2] += analogRead(HALL_MIDDLE);
    _sensorData[3] += analogRead(HALL_RING);
    _sensorData[4] += analogRead(HALL_PINKY);
    delay(SAMPLE_TIME);
  }
  for (int i = 0; i < 5; i++) 
  {
    _sensorData[i] = _sensorData[i] / samples;

    int v = fingersExtended[i] ? -_deadzoneValues[i] : _deadzoneValues[i];
    
    if (extendedValues[i] > contractedValues[i])
      fingersExtended[i] = _sensorData[i] >= _medianValues[i] + v;
    else
      fingersExtended[i] = _sensorData[i] <= _medianValues[i] - v;
  }
}

#endif