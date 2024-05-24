// Pin tanımlamaları
const int motor1Pin1 = 3; // Motor 1'in ileri pin 1'i
const int motor1Pin2 = 2; // Motor 1'in ileri pin 2'si
const int motor2Pin1 = 4; // Motor 2'nin ileri pin 1'i
const int motor2Pin2 = 5; // Motor 2'nin ileri pin 2'si

// Pin tanımlamaları
const int sensorPin1 = A4;    // Sol çizgi sensörü pin
const int onEchoPin = A0;     // Ön ultrasonik sensör trig pin
const int onTrigPin = A1;     // Ön ultrasonik sensör echo pin
const int solEchoPin = A2;    // Sağ ultrasonik sensör trig pin
const int solTrigPin = A3;    // Sağ ultrasonik sensör echo pin

// Siyah ve beyaz arasındaki eşik değerler
const int beyazEsik = 600; // Beyaz olarak kabul edilen eşik değer

void setup() {
  // Pin modlarını ayarlama
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  pinMode(onTrigPin, OUTPUT); 
  pinMode(onEchoPin, INPUT);  

  pinMode(solTrigPin, OUTPUT); 
  pinMode(solEchoPin, INPUT); 
  
  Serial.begin(9600); // Seri iletişim başlat
}

void loop() {
  // Çizgi sensörlerini oku
  int sensor1Durum = digitalRead(sensorPin1); // Sol çizgi sensörünün durumunu oku
  
  // Ultrasonik sensörlerden mesafeleri ölç
  int onMesafe = mesafeOlc(onTrigPin, onEchoPin); // Ön ultrasonik sensörden mesafe ölç
  int solMesafe = mesafeOlc(solTrigPin, solEchoPin); // Sağ ultrasonik sensörden mesafe ölç
  
  // Engelin varlığını kontrol et
  bool onEngelVar = (onMesafe < 10); // Ön sensör için engel kontrolü
  bool solEngelVar = (solMesafe < 10); // Sağ sensör için engel kontrolü
  
  // Sonuçları seri monitöre yazdır
  Serial.print("Sağ Çizgi Sensörü Durumu: ");
  Serial.print(sensor1Durum);
  Serial.print(", Ön Engel: ");
  Serial.print(onEngelVar);
  Serial.print(", Sol Engel: ");
  Serial.print(solEngelVar);
  Serial.println();

  delay(100); // 0.1 saniye bekle

  // Robotun hareketini belirle
    if (onEngelVar && !solEngelVar) {
    ileri();
  } else if (!onEngelVar && solEngelVar) {
    sol();
  }else if(!onEngelVar && !solEngelVar){
    sag();
    delay(500);
    dur();
    delay(500);
  }

  
}


// Mesafe ölçümü fonksiyonu
int mesafeOlc(int trigPin, int echoPin) {
  // Trigger pini için 10 mikro saniye boyunca yüksek sinyal gönder
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Echo pini ile gelen sinyali oku
  unsigned long sure = pulseIn(echoPin, HIGH);

  // Ses hızı 343 m/s olduğu için mesafeyi hesapla
  int mesafe = sure * 0.0343 / 2;
  return mesafe;
}
// Motor ileri fonksiyonu
void ileri() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Motor geri fonksiyonu
void geri() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

// Motor sağa dönme fonksiyonu
void sol() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(300); //  milisaniye boyunca sola dön
  dur(); // Durdur
}

// Motor sağa dönme fonksiyonu
void sag() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  delay(500); // 500 milisaniye boyunca sağa dön
  dur(); // Durdur
}

// Motoru durduran fonksiyon
void dur() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}