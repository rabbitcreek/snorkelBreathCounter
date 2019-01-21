/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/
const int numReadings = 10;
int breath = 0;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

bool ting = false;
float rateCount = 0.0;
int inhale = 0;
int exhale = 0;
int lowCount = 0;
int highCount = 0;
bool node = true;
#define PERIOD 20000  // period in us

unsigned long last_us = 0L;
unsigned long timeKeep = 0L;


unsigned long timer = 0L;
#define LongPeriod 60000
// the setup routine runs once when you press reset:
void setup() {
   // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  //if (millis() - timer > LongPeriod){
    //timer += LongPeriod;
   // outPut();
  //}
  // read the input on analog pin 0:
   if (micros () - last_us > PERIOD)
  {
    last_us += PERIOD ;
    sample () ;
  }
}
void sample ()
{
  int sensorValue = analogRead(A0);
     float voltage = sensorValue * (3300.0 / 1023.0);
     
  // print out the value you read:
  voltage = voltage - 506;
  //Serial.println(voltage);
  voltage = constrain(voltage, 0, 15);
  int inOut = map(voltage,0,15,0, 20);
  inOut = constrain(inOut,0,20);
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = inOut;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  
  //Serial.println(average);
  // send it to the computer as ASCII digits
  //Serial.print(voltage); 
  //Serial.println(inOut);
  
  if(average >1  && node == true){
    highCount += 1;
  }
    if(highCount > 5 && node == true){
      //exhale += 1;
      /*
      
      timeKeep = millis();
      */
      
      node = false;
      highCount = 0;
    }
    if( average < 2 && node == false){
      lowCount += 1;
      
  }
  if(lowCount > 5 && node == false){
    breath +=1;
    lowCount = 0;
    if((millis() - timeKeep) < 100) ting = false;
    if((millis() - timeKeep) > 4000) ting = false;
    if(ting){
        rateCount = 60.0/(( millis() - timeKeep)/1000.0);
        rateCount = constrain( rateCount, 10, 120);
        Serial.print(" Rate ");
        Serial.println(rateCount);
        ting = false;
      }
    timeKeep = millis();
    ting = true;
    node = true;
  }

  //Serial.print("Breath");
  //Serial.println(breath);
  //Serial.print("Inhale");
 // Serial.println(inhale);
 
 
  // do the sampling here 
}
 void outPut ()
 {
  inhale = inhale * 2;
  exhale = exhale * 2;
  Serial.print(" Breaths per Minute ");
  Serial.print(inhale);
  Serial.println(exhale);
  lowCount = 0;
  highCount = 0;
  inhale = 0;
  exhale = 0;
 }

