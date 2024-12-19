#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <SoftwareSerial.h>
String bluetooth = "0";

LiquidCrystal_I2C lcd(0x27,16, 2); 
Adafruit_NeoPixel RGB_LED = Adafruit_NeoPixel(25, 7, NEO_GRB);
DHT dht(8, DHT22);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  RGB_LED.begin();
  RGB_LED.setBrightness(10);
  RGB_LED.clear();
  RGB_LED.fill((0, 0, 0), 0, 0);
  RGB_LED.show();

  dht.begin();

  lcd.init();
  lcd.backlight();

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(A0, INPUT);

  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

byte j[] = {
  0b00000,
  0b11111,
  0b00010,
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000,
};

byte u[] = {
  0b00000,
  0b01000,
  0b01000,
  0b01000,
  0b11000,
  0b01000,
  0b01000,
  0b01000,
};

byte ng[] = {
  0b01110,
  0b11011,
  0b10001,
  0b11011,
  0b01110,
  0b00000,
  0b00000,
  0b00000,
};

byte y[] = {
  0b00000,
  0b01110,
  0b11011,
  0b10001,
  0b11011,
  0b01110,
  0b00000,
  0b00000,
};

byte oon[] = {
  0b11111,
  0b01010,
  0b00000,
  0b10000,
  0b11111,
  0b00000,
  0b00000,
  0b00000
};

byte h[] = {
  0b00100,
  0b11111,
  0b00000,
  0b01110,
  0b11011,
  0b10001,
  0b11011,
  0b01110,
};

byte yeo[] = {
  0b00000,
  0b01000,
  0b01000,
  0b11000,
  0b01000,
  0b11000,
  0b01000,
  0b01000,
};

byte k[] = {
  0b00000,
  0b11111,
  0b00001,
  0b00001,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};

byte b[] = {
  0b00000,
  0b10001,
  0b10001,
  0b11111,
  0b10001,
  0b11111,
  0b00000,
  0b00000,
};

byte a[] = {
  0b00000,
  0b01000,
  0b01000,
  0b01000,
  0b01100,
  0b01000,
  0b01000,
  0b01000,
};

byte o[] = {
  0b00100,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};

void jyh_babo() {
  lcd.createChar(1, j);
  lcd.createChar(2, u);
  lcd.createChar(3, ng);
  lcd.createChar(4, y);
  lcd.createChar(5, oon);
  lcd.createChar(6, h);
  lcd.createChar(7, yeo);
  lcd.createChar(8, k);
  lcd.createChar(1, j);
  lcd.createChar(2, u);
  lcd.createChar(3, ng);
  lcd.setCursor(0, 0);
  lcd.write(byte(1));
  lcd.setCursor(1, 0);
  lcd.write(byte(2));
  lcd.setCursor(0, 1);
  lcd.write(byte(3));
  lcd.setCursor(2, 0);
  lcd.write(byte(4));
  lcd.setCursor(2, 1);
  lcd.write(byte(5));
  lcd.setCursor(3, 0);
  lcd.write(byte(6));
  lcd.setCursor(4, 0);
  lcd.write(byte(7));
  lcd.setCursor(3, 1);
  lcd.write(byte(8));
  delay(1000);
  lcd.clear();
  lcd.createChar(1, b);
  lcd.createChar(2, a);
  lcd.createChar(3, o);
  lcd.setCursor(5, 0);
  lcd.write(byte(1));
  lcd.setCursor(6, 0);
  lcd.write(byte(2));
  lcd.setCursor(7, 0);
  lcd.write(byte(1));
  lcd.setCursor(7, 1);
  lcd.write(byte(3));
  delay(1000);
  lcd.clear();
}

void kirby() {
  RGB_LED.setBrightness(10);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if(i % 2 != 1) RGB_LED.setPixelColor(5 * i + j, 255, 0, 80);
      else RGB_LED.setPixelColor(5 * (i + 1) - 1 - j, 255, 0, 80);
    }
  }
  RGB_LED.setPixelColor(4, 200, 0, 0);
  RGB_LED.setPixelColor(5, 200, 0, 0);
  RGB_LED.setPixelColor(15, 200, 0, 0);
  RGB_LED.setPixelColor(24, 200, 0, 0);
  RGB_LED.setPixelColor(8, 30, 30, 30);
  RGB_LED.setPixelColor(18, 30, 30, 30);
  RGB_LED.show();
}

void loop() {
  if (Serial1.available()) {
    bluetooth = Serial1.readStringUntil('/');
    Serial.println(bluetooth);
    if (bluetooth == "Temp") {
      float temp =  dht.readTemperature();
      String str_temp = String(temp, 1);
      Serial1.print(str_temp);
    }
    else if (bluetooth == "Humid") { 
      float humid =  dht.readHumidity();
      String str_humid = String(humid, 1);
      Serial1.print(str_humid);
    }
    else if (bluetooth == "Moist") { 
      int moist =  analogRead(0);
      String str_moist = String(moist);
      Serial1.print(str_moist);
    }
    else if (bluetooth == "Light") { 
      int light = analogRead(A1);
      String str_light = String(light);
      Serial1.print(str_light);
    }
    else if (bluetooth == "FanON") { 
      digitalWrite(2, HIGH);
    }
    else if (bluetooth == "FanOFF") { 
      digitalWrite(2, LOW);
    }
    else if (bluetooth == "WpON") { 
      digitalWrite(3, HIGH);
    }
    else if (bluetooth == "WpOFF") { 
      digitalWrite(3, LOW);
    }
    else if (bluetooth.startsWith("Nut")) { 
      String nut = bluetooth.substring(3);
      int int_nut = nut.toInt();
      digitalWrite(5, HIGH);
      delay(int_nut*1000);
      digitalWrite(5, LOW);
    }
    else if (bluetooth == "Auto") { 
      int a = 1;
      while (a == 1) {
        if (Serial1.available()) {
          a = 0;
        }
        else {
          int plant_moist;
          plant_moist = analogRead(0);
          if (plant_moist > 700) {
            digitalWrite(3, HIGH);
            delay(10000);
            digitalWrite(3, LOW);
          }
        }
        delay(1000);
      }
    }
    else if (bluetooth.startsWith("LEDB")) { 
      String ledbr = bluetooth.substring(4);
      int int_ledbr = ledbr.toInt();
      Serial.println(int_ledbr);
      RGB_LED.setBrightness(int_ledbr);
      RGB_LED.show();
    }
    else if (bluetooth.startsWith("LEDQ")) {
      String ledqu = bluetooth.substring(4);
      int int_ledqu = ledqu.toInt();
      Serial.println(int_ledqu);
      for (int i = 24; i >= int_ledqu; i--) {
        RGB_LED.setPixelColor(i, 0, 0, 0);
        RGB_LED.show();
        delay(100);
      }
    }
    else if (bluetooth == "Red") {
      RGB_LED.fill(RGB_LED.Color(255, 0, 0));
      RGB_LED.show();
    }
    else if (bluetooth == "Green") {
      RGB_LED.fill(RGB_LED.Color(0, 255, 0));
      RGB_LED.show();
    }
    else if (bluetooth == "Blue") {
      RGB_LED.fill(RGB_LED.Color(0, 0, 255));
      RGB_LED.show();
    }
    else if (bluetooth == "White") {
      RGB_LED.fill(RGB_LED.Color(255, 255, 255));
      RGB_LED.show();
    }
    else if (bluetooth == "Rainbow") {
      RGB_LED.rainbow();
      RGB_LED.show();
    }
    else if (bluetooth == "Kirby") {
      kirby();
    }
    else if (bluetooth == "Pink") {
      RGB_LED.fill(RGB_LED.Color(255, 0, 255));
      RGB_LED.show();
    }
    else if (bluetooth == "Eyebreaker") {
      RGB_LED.setBrightness(255);
      for (int j = 1; j <= 10; j++) {
        RGB_LED.fill(RGB_LED.Color(255, 0, 0));
        RGB_LED.show();
        delay(100);
        RGB_LED.fill(RGB_LED.Color(0, 0, 255));
        RGB_LED.show();
        delay(100);
      }
      RGB_LED.setBrightness(10);
      RGB_LED.clear();
      RGB_LED.fill((0, 0, 0), 0, 0);
      RGB_LED.show();
    }
    else if (bluetooth == "jyhbabo") {
      jyh_babo();
    }
    else {
      lcd.clear();
      if (bluetooth.length() > 16) {
        for (int k = 0; k <= 15; k++) {
          lcd.setCursor(k, 0);
          lcd.print(bluetooth.charAt(k));
          delay(100);
        }
        for (int t = 0; t <= bluetooth.length() - 17; t++) {
          lcd.setCursor(t, 1);
          lcd.print(bluetooth.charAt(t + 16));
          delay(100);
        }
      }
      else {
          for (int q = 0; q < bluetooth.length() - 1; q++) {
            lcd.setCursor(q, 0);
            lcd.print(bluetooth.charAt(q));
            delay(100);
          }
        }
    }
    delay(1000);
  }
}
