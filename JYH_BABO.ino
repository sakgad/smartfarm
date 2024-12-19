#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27,16, 2); //A4 to SDA, A5 to SCL
Adafruit_NeoPixel RGB_LED = Adafruit_NeoPixel(25, 7, NEO_GRB);
DHT dht(3, DHT22);
 
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  lcd.init();
  lcd.backlight();

  RGB_LED.begin();
  RGB_LED.setBrightness(10);
  RGB_LED.clear();
  RGB_LED.fill((0, 0, 0), 0, 0);
  RGB_LED.show();

  dht.begin();

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);  // AA를 출력 핀으로 설정
  pinMode(5, OUTPUT);
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
    String cmd = Serial1.readStringUntil('/');
    if (cmd == "fan on") {
      digitalWrite(2, HIGH);
    }
    else if (cmd == "fan off") {
      digitalWrite(2, LOW);
    }
    else if (cmd == "jyh babo") {
      jyh_babo();
    }
    else if (cmd == "kirby") {
      kirby();
    }
    else if (cmd == "shiny") {
      RGB_LED.setBrightness(255);
      RGB_LED.fill((255, 255, 255), 0, 0);
      RGB_LED.show();
    }
    else if (cmd == "rainbow") {
      RGB_LED.rainbow();
      RGB_LED.show();
    }
    else if (cmd == "led off") {
      RGB_LED.fill((0, 0, 0), 0, 0);
      RGB_LED.show();
    }
    else if (cmd == "moist") {
      int plant_moist;
      plant_moist = analogRead(0);
      if (plant_moist < 500) {
        Serial1.write("물 충분!");
      }
      else {
        Serial1.write("윤혁아 물줘라");
      }
    }
    else if (cmd == "light") {
      int CDS = analogRead(A1);
      if (CDS > 600) {
        Serial1.write("적당한 불빛");
      }
      else {
        Serial1.write("실명 위기");
      }
    }
    else if (cmd == "temp") {
      float t = dht.readTemperature();
      Serial1.print("Temperature: "); 
      Serial1.print(t);
      Serial1.println(" *C");
    }
    else if (cmd == "humid") {
      float h = dht.readHumidity();
      Serial1.print("Humidity: "); 
      Serial1.print(h);
      Serial1.print(" %\t");
    }
    else if (cmd == "water on") {
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
    }
    else if (cmd == "water off") {
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
    }
    Serial.println(cmd);
  }

  if (Serial.available()) {
    Serial1.write(Serial.read());
    Serial.write("\n");
  }
}