//Nem sensörü ve Otomatik Sulama
const int Enable_A = 9;
const int inputA1 = 10;
const int inputA2 = 11;
int nemsensor = 5;
int leds = 2;
int ledk = 3;
int sinirDeger = 700;
//**********Yağmur Sensörü
int yagmur = 0;
int sensor = A1;
//*****Duman Sensörü
int esikDegeri = 250; //Gaz eşik değerini belirliyoruz.
int buzzer= 7; //buzzerın takılacağı pin
int deger; //Sensörden okunan değer

//*******Sıcaklık Sensörü
#include <SimpleDHT.h>
int pinDHT11 = 8;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  //******Nem Sensörü ve Otomatik Sulama
  pinMode(Enable_A, OUTPUT);
  pinMode(inputA1, OUTPUT);
  pinMode(inputA2, OUTPUT);
  pinMode(nemsensor, INPUT);
  pinMode(leds, OUTPUT);
  pinMode(ledk, OUTPUT);


  Serial.begin(9600);

  //***********Yağmur Sensörü
  pinMode(sensor, INPUT);

  //*******Duman Sensörü
  pinMode(buzzer, OUTPUT); //Buzzer pinimizi çıkış olarak ayarlıyoruz.

  //*****Sıcaklık Sensörü
  Serial.begin(9600);

}

void loop() {
  //*******Nem Sensörü ve Otomatik Sulama
  int nem = analogRead(nemsensor);
  Serial.print("Toprak Nem Degeri: ");
  Serial.println(nem);

  if (nem > 300) {
    digitalWrite(Enable_A, HIGH);
    digitalWrite(inputA1, HIGH);
    digitalWrite(inputA2, LOW);
    digitalWrite(ledk, HIGH);
    digitalWrite(leds, LOW);
    
  } else {
    digitalWrite(Enable_A, LOW);
    digitalWrite(ledk, LOW);
    digitalWrite(leds, HIGH);
  }
  //Yağmur Sensörü
  yagmur = analogRead(A1);
  Serial.print("Yagmur Sensoru degeri:");
  Serial.println(yagmur);

  if (yagmur > 300) {
    //Serial.println("Yagmur yok!");
    delay(1000);
  }
  else {
    //Serial.println("Yagmur yagiyor!");
    delay(1000);
  }
  //*******Duman Sensörü
  deger = analogRead(A0); //Sensörden analog değer okuyoruz.
  Serial.print("Duman sensoru degeri: ");
  Serial.println(deger);
  if (deger > esikDegeri) { //Sensörden okunan değer eşik değerinden büyükse çalışır.
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
  } else { //Sensörden okunan değer eşik değerinin altındaysa çalışır.
    digitalWrite(buzzer, LOW);
  }
  //****Sıcaklık Sensörü
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("DHT11 HATALİ, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }

  Serial.print("Sicaklik ve Nem Degeri ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" H");//Higrometre

  delay(1500);
  Serial.println("-------------------------------------------------------");
}
