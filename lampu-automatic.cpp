#include <IRremote.h>
#include <DHT.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(2, DHT11);

const byte IR_RECEIVE_PIN = 11;
const int replay1 = 3,replay2 = 4;

void setup()
{
   Serial.begin(115200);
   IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
   pinMode(replay1, OUTPUT);
   pinMode(replay2, OUTPUT);
   digitalWrite(replay1, LOW);
   digitalWrite(replay2, LOW);
   dht.begin();
   lcd.init();
   lcd.backlight();
   lcd.clear();
}

void loop()
{
   if (IrReceiver.decode())
   {
      Serial.println(IrReceiver.decodedIRData.command, HEX);
      delay(200);
      if(IrReceiver.decodedIRData.command == 1)
        {
          Serial.println("masuk 1");
          digitalWrite(replay1, HIGH);
          }
      if(IrReceiver.decodedIRData.command == 2)
        {
          Serial.println("masuk 2");
          digitalWrite(replay1, LOW);
          }
      if(IrReceiver.decodedIRData.command == 3)
        {
          Serial.println("masuk 3");
          digitalWrite(replay2, HIGH);
          }
      if(IrReceiver.decodedIRData.command == 4)
        {
          Serial.println("masuk 4");
          digitalWrite(replay2, LOW);
          }
      IrReceiver.resume();
   }
 float kelembaban = dht.readHumidity();
 float suhu = dht.readTemperature();
 lcd.clear();
 delay(1000);
 lcd.setCursor(0, 0);
 lcd.print("suhu: ");
 lcd.print(suhu);
 lcd.print("C");
 lcd.setCursor(0, 1);
 lcd.print("kelembaban: ");
 lcd.print(kelembaban);
 lcd.print("%RH");
 delay(1000);
}
