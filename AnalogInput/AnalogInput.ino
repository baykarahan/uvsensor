#include <LiquidCrystal.h> // LiquidCrystal kütüphanesini projemize ekliyoruz.
/*
12 RS - register select
11 E - Enable 
5-4-3-2 D4-D5-D6-D7 - 4'lü data bağlantı pinleri
*/
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // lcd nesnemizi oluşturuyoruz.
int sensorPin = A0;    // select the input pin for the potentiometer
//int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
 // pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2); // kullanacağımız lcd'nin 16x2 boyutlarında olduğunu belirtiyoruz.
  lcd.print("Uv Sensor Projesi"); 

 Serial.begin(9600);

}

void loop() {
 int sensorValue;
 long sum=0;
// sum=analogRead(A0);
 for(int i=0;i<1024;i++)
 {
 sensorValue=analogRead(A0);
 sum=sensorValue+sum;
 delay(2);
 }
  long ortalamaDeger = sum/1024;        // ortalama değer elde ediliyot
  float mVolt=ortalamaDeger*(5000/1023); // milli Volt Değeri  mVolt=deger*5000/1023   ortalamaDeger*(5000/1023) or  ortalamaDeger*4.89 calculate
  float Vsig=mVolt/1000;                 // Volt Değeri        V=mV/1000 
  float IY=Vsig*307;                     // Işık Yoğunluğu     IY=Vsig*307 
  float UI=IY/200;                       // UV İndeksi         UI=IY/200
    Serial.print("UV index is:");
    Serial.print((ortalamaDeger*1000/4.3-83)/21);     // get a detailed calculating expression for UV index in schematic files.
    Serial.print("\tOkunan Değer=");        Serial.print(ortalamaDeger);
    Serial.print("\tmVolt=");             Serial.print(mVolt);
    Serial.print("\tVsig=");              Serial.print(Vsig);
    Serial.print("\tIşık Yoğunluğu=");    Serial.print(IY);
    Serial.print("\tUV İndex=");          Serial.print(UI);
    Serial.print("\n");
 

  //Serial.println(sensorValue);  
   lcd.setCursor(0, 1); // 0. sutun, 1. satıra ekran imlecini ayarla
  lcd.print("IY="); lcd.print(IY,0); lcd.print("  "); lcd.print("UI=");lcd.print(UI,2); 
  // 0. sutun, 1. satır itibari ile sayacı DEC Onlu BIN ikili ikilik tabanda yazdır. 
  delay(1000);
  }
