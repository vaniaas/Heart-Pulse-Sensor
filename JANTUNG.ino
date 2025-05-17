#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PulseSensorPlayground.h>

//Konfigurasi
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int PulsePin = A0;
PulseSensorPlayground pulseSensor;

// Menyimpan nilai BPM terakhir
int lastBPM = 0;
// Untuk mengatur kecepatan update LCD        
unsigned long olastDisplay = 0;  

void setup() {
  Serial.begin(9600);

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Letakkan sensor   ");
  lcd.setCursor(0, 1);
  lcd.print("pada nadi leher");

  // Pulse sensor
  pulseSensor.analogInput(PulsePin);
  pulseSensor.setThreshold(550); // Sesuaikan (cek sensor menggunakan serial monitor)
  pulseSensor.begin();
}

void loop() {
  if (pulseSensor.sawStartOfBeat()) {
    int bpm = pulseSensor.getBeatsPerMinute();
    Serial.print("BPM: ");
    Serial.println(bpm);

    if (bpm > 40 && bpm < 180) {
      lastBPM = bpm;
      lastDisplay = millis();  // Menyimpan waktu terakhir tampilan BPM
    }
  }

  // Update tampilan setiap 500 ms
  if (millis() - lastDisplay < 2000 && lastBPM > 0) {
    lcd.setCursor(0, 0);
    lcd.print("Mengukur...     ");
    lcd.setCursor(0, 1);
    lcd.print("BPM: ");
    lcd.print(lastBPM);
    lcd.print("         ");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Letakkan sensor   ");
    lcd.setCursor(0, 1);
    lcd.print("pada nadi leher");
  }

  delay(20);
}
