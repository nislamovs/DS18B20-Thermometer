#include <DS18B20.h>

#define posValuePin 11
#define negValuePin 10
#define DS18B20Pin 9

#define calcConst 8.3

DS18B20 ds(DS18B20Pin);
int curVal;
boolean curTempSign;

void setup() {
  Serial.begin(9600);
  curVal = 0;
  curTempSign = false;    //false -> negative; true positive or zero
}

void loop() {
  ds.doConversion();
  float temp = ds.getTempC();
  int val = abs((int)(calcConst * temp));

  if (val > 255) val = 255;

//Necessary to except thermometer glitch values

  if (curVal == 0) {
    curTempSign = (int)temp >= 0;
    curVal = val;
  } else {
    if (abs(curVal - val) < 5)
      curVal = val;
  }
////////////////////////////////////////////////

  if ( !( ((int)temp >= 0) != curTempSign && curVal >= 20) ) { // Necessary to except thermometer glitch values as well
    if ((int)temp < 0) {
      analogWrite(negValuePin, curVal);
      analogWrite(posValuePin, 0);
    } else {
      analogWrite(posValuePin, curVal);
      analogWrite(negValuePin, 0);
    }
    curTempSign = (int)temp >= 0;
  }
  
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.print("Value: ");
  Serial.print(val);
  Serial.println("\n");

  delay(200);
}
