#include <DS18B20.h>

#define posValuePin 11
#define negValuePin 10
#define DS18B20Pin 9

#define calcConst 8.3

DS18B20 ds(DS18B20Pin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  ds.doConversion();
  float temp = ds.getTempC();
  int val = (int)(calcConst * temp);
  if (val > 255 || val < -255) val = 255;

if ((int)temp < 0) {
  analogWrite(negValuePin, val);
  analogWrite(posValuePin, 0);
} else {
  analogWrite(posValuePin, val);
  analogWrite(negValuePin, 0);
}
  
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.print("Value: ");
  Serial.print(val);
  Serial.println("\n");

  delay(200);
}
