# 스마트팜 모듈, 센서 설명 및 예제 코드
스마트팜에 사용되는 모듈과 센서에 대한 설명 및 주로 사용되는 함수와 예제 코드에 대한 문서입니다.
# 1. 물품 종류
## 1.1. 센서 종류
- **수분 센서**
- **온습도 센서**
- **조도 센서**
## 1.2. 모듈 종류
- **블루투스 모듈**
- **쿨링 팬**
- **워터 펌프**
- **5 x 5 RGB LED**
- **LCD (액정 디스플레이) 모듈**
# 2. 센서 설명
## 2.1. 수분 센서
*참고: 에듀이노 토양 탐침 수분센서 <https://eduino.kr/product/detail.html?product_no=4742&cate_no=27&display_group=1>*

토양의 수분을 측정합니다.

**사용 방법 및 주요 함수**

> 아두이노의 아날로그 핀에 꽂은 후 analogRead() 함수를 사용해 수분을 측정함

**예제 코드**
```
void setup() {
  Serial.begin(9600); // open serial port, set the baud rate as 9600 bps
}
void loop() {
  int val;
  val = analogRead(0); //connect sensor to Analog 0
  Serial.println(val); //print the value to serial port
  delay(100);
}
```
## 2.2. 온습도 센서
*참고: 에듀이노 고정밀 온습도센서 <https://www.eduino.kr/product/detail.html?product_no=285&cate_no=27>*

현재 환경의 온도와 습도를 측정합니다.

**라이브러리 필요**
- DHT SENSOR LIBRARY


**사용 방법 및 주요 함수**
  
> DHT 이름(핀번호, 온습도 센서 종류 - 우리는 DHT22 사용) - dht 객체 생성
>
> readHumidity() - 습도를 측정 후 실수 값을 반환함
>
> readTemprateure() - 온도를 측정 후 실수 값을 반환함
>
> 디지털 핀을 사용

**예제 코드**
```
#include "DHT.h"
 
#define DHTPIN 2        // SDA 핀의 설정
#define DHTTYPE DHT22   // DHT22 (AM2302) 센서종류 설정
 
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
  Serial.begin(9600); 
  dht.begin();
}
 
void loop() {
  // 센서의 온도와 습도를 읽어온다.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  if (isnan(t) || isnan(h)) {
    //값 읽기 실패시 시리얼 모니터 출력
    Serial.println("Failed to read from DHT");
  } else {
    //온도, 습도 표시 시리얼 모니터 출력
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }
  delay(2000);
}
```
## 2.3. 조도 센서
*참고: 에듀이노 cds 조도 센서 모듈 <https://eduino.kr/product/detail.html?product_no=234&cate_no=27&display_group=1>*

현재 환경의 광도를 측정합니다.

**사용 방법 및 주요 함수**

> 아두이노의 아날로그 핀에 꽂은 후 analogRead() 함수를 사용해 수분을 측정함

**예제 코드**
```
int CDS = A1;   // 조도 센서 모듈 연결한 핀
int LED = 3;    // LED 연결한 핀
 
void setup() {
  Serial.begin(9600);
  pinMode(CDS, INPUT);  // 조도 센서를 입력 핀으로 설정
  pinMode(LED,OUTPUT);  // LED를 출력 핀으로 설정
}
 
void loop() {
  CDS = analogRead(A1);    // 조도 센서의 측정 값을 val에 저장
  Serial.print("CDS_Sensor: ");
  Serial.println(CDS);         // 시리얼 모니터에 조도 센서의 측정 값 출력
 
  if(CDS > 100) {               // 측정 값이 500 초과이면
    digitalWrite(LED, HIGH);    // LED 켜기
    Serial.println("LED ON");   // 시리얼 모니터에 출력
  }
  
  else {                        // 측정 값이 500 이하이면
    digitalWrite(LED, LOW);     // LED 끄기
    Serial.println("LED OFF");  // 시리얼 모니터에 출력
  }
 
  delay(200);                   // 0.2초 쉬고 반복(1000ms = 1s)
}
```
# 3. 모듈 설명
## 3.1. 블루투스 모듈
*참고: 블루투스 HC-06 모듈 <https://eduino.kr/product/detail.html?product_no=27&cate_no=55&display_group=1>*

블루투스 통신을 가능하게 해주는 모듈입니다.

App Inventor의 블루투스 기능을 이용해 핸드폰으로 스마트팜을 관리할 수 있도록 해줍니다.

**사용 방법 및 주요 함수**

> **아두이노 보드마다 사용방법이 다름**
>
> 이번 프로젝트에서는 MEGA 2560 보드를 사용할 예정
>
> 시리얼 통신의 방법 중 하나인 RXD와 TXD를 이용
>
> 블루투스에는 각각 RX, TX, GND 핀이 있는데, RX는 아두이노의 TX, TX는 RX로 연결하면 된다.
>
> 이때 RX, TX의 핀은 메가에서 각각 3가지로 종류에 따라 코딩할 때 사용할 시리얼의 이름이 달라진다.
>
> Serial1 == 18 19번핀, Serial2 == 16 17번핀, Serial3 == 14 15번핀
>
> Serial1.available()을 통해 Serial1의 수신값이 존재하는지를 확인한다.
> 
> Serial1.read() 또는 .readStringUntil()을 사용해 값을 읽어들인다.

**예제 코드**
```
#include <SoftwareSerial.h>

void setup() {
 Serial.begin(9600);
 Serial1.begin(9600);         //Serial1 == 18 19번핀, Serial2 == 16 17번핀, Serial3 == 14 15번핀
 Serial.println("HELLO!");
}

void loop() {
  if (Serial1.available()) {
    Serial.write(Serial1.read());
  }
  if (Serial.available()) {
    Serial1.write(Serial.read());
  }
}
```
## 3.2. 쿨링 팬
*참고: 5V 쿨링 팬 모듈 <https://m.eduino.kr/product/detail.html?product_no=1260&cate_no=55&display_group=1>*

환기를 위해 설치하는 쿨링 팬입니다. 추가적으로 릴레이 모듈을 사용해야 합니다.

**사용 방법 및 주요 함수**

> 참고의 사이트의 도안을 통해 릴레이 모듈과 쿨링 팬, 아두이노 보드를 정확히 연결해야 한다.
>
> 릴레이 모듈의 SIG 핀은 아두이노의 디지털 핀에 연결해야 한다.
>
> 연결된 핀의 번호를 이용해 digitalWrite()함수를 사용해 팬을 가동한다.

**예제 코드**
```
int Relaypin = 12;
int Switch = 9;
 
void setup()
{
  pinMode(Relaypin,OUTPUT);          //릴레이를 출력으로 설정
  pinMode(Switch,INPUT_PULLUP);      //스위치를 입력으로 설정
}
 
void loop()
{
  if(digitalRead(Switch)==LOW)        //스위치를 누르면
  {
    digitalWrite(Relaypin,HIGH);      //1채널 릴레이 ON
    delay(100);
  }
```
## 3.3. 워터 펌프
*참고: 워터펌프 3 ~ 5V <https://www.eduino.kr/product/detail.html?product_no=984&cate_no=55&display_group=1>*

물을 끌어오는 펌프입니다. 실리콘튜브와 함께 사용합니다.

**사용 방법 및 주요 함수**

> 펌프가 많이 약함;;
>
> 모터 드라이버를 이용해야 쉽게 사용할 수 있다. (2채널 모터 드라이버 사용)

**예제 코드**
```
int AA = 10;  // AA를 연결한 디지털 핀
int AB = 6;   // AB를 연결한 디지털 핀
 
void setup()
{
  pinMode(AA, OUTPUT);  // AA를 출력 핀으로 설정
  pinMode(AB, OUTPUT);  // AB를 출력 핀으로 설정
}
 
void loop()
{
  digitalWrite(AA, HIGH);  // 정방향으로 모터 회전
  digitalWrite(AB, LOW);
  delay(5000);  // 5초동안 상태 유지(1000ms = 5s)
 
  digitalWrite(AA, LOW);  // 모터 정지
  digitalWrite(AB, LOW);
  delay(5000);  // 5초동안 상태 유지(1000ms = 5s)
}
```
## 3.4. 5 x 5 RGB LED
*참고: 네오픽셀 5x5 RGB LED <https://www.eduino.kr/product/detail.html?product_no=609&cate_no=55&display_group=1>*

RGB를 지원하는 5 x 5 LED입니다.

**사용 방법 및 주요 함수**

> Adafruit NeoPixel Library가 필요하다.
>
> 멤버 함수는 이곳에서 확인하면 된다; <https://adafruit.github.io/Adafruit_NeoPixel/html/class_adafruit___neo_pixel.html>
>
> 먼저 1번 ~ 25번 LED가 어디가 켜지는지 확인하자.
>
> 회로는 LED와 비슷하게 연결할 수 있다.

**예제 코드**
```
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel RGB_LED = Adafruit_NeoPixel(25, 13, NEO_GRB);  // 픽셀수 : 25, 핀번호 : 13으로 지정해줍니다.
 
void setup() {
  RGB_LED.begin();            // RGB_LED 불러옵니다.
  RGB_LED.setBrightness(100); // RGB_LED 밝기조절
  RGB_LED.clear();            // RGB_LED 초기화합니다.
}
 
void loop() {
  RGB_LED.setPixelColor(2, 255, 0, 50);   // 2번 네오픽셀에 색상을 출력합니다.
  RGB_LED.show();
  RGB_LED.setPixelColor(3, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(5, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(6, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(7, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(8, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(10, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(11, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(12, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(13, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(15, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(16, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(17, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(18, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(22, 255, 0, 50);
  RGB_LED.show();
  RGB_LED.setPixelColor(23, 255, 0, 50);
  RGB_LED.show();
}
```

## 3.4. LCD (액정 디스플레이) 모듈
*참고: <https://www.eduino.kr/product/detail.html?product_no=105&cate_no=55&display_group=1>*

16 x 2, 32칸만큼 문자를 출력할 수 있는 액정 디스플레이 모듈입니다.

**사용 방법 및 주요 함수**

> LiquidCrystal 라이브러리가 필요하다.
>
> 뒤에 있는 저항 조절기를 통해 디스플레이의 밝기를 조절할 수 있다.
>
> 한글 지원은 안됀다.
>
> 직접 글자를 제작할 수 있지만 등록가능한 글자는 8가지 밖에 만들 수 없다.

**예제 코드**
```
#include <Wire.h>                        // i2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h>        // LCD 1602 I2C용 라이브러리
 
LiquidCrystal_I2C lcd(0x27,16,2);     // 접근주소: 0x3F or 0x27
 
byte pac_man1[8] = {     // 팩맨 출력 입벌림, 얼굴방향 오른쪽
  0b01110,
  0b11011,
  0b11110,
  0b11100,
  0b11100,
  0b11110,
  0b11111,
  0b01110,
};
byte pac_man2[8] = {     // 팩맨 출력 입닫음, 얼굴방향 오른쪽
  0b01110,
  0b11011,
  0b11111,
  0b11111,
  0b11100,
  0b11111,
  0b11111,
  0b01110,
};
 
byte pac_man3[8] = {     // 팩맨 출력 입벌림,  얼굴방향 왼쪽
  0b01110,
  0b11011,
  0b01111,
  0b00111,
  0b00111,
  0b01111,
  0b11111,
  0b01110,
};
byte pac_man4[8] = {     // 팩맨 출력 입닫음,  얼굴방향 왼쪽
  0b01110,
  0b11011,
  0b11111,
  0b11111,
  0b00111,
  0b11111,
  0b11111,
  0b01110,
};
 
void setup()
{
  lcd.init();                      // LCD 초기화
  lcd.backlight();                // 백라이트 켜기
  lcd.createChar(1, pac_man1);    // 팩맨 얼굴1
  lcd.createChar(2, pac_man2);    // 팩맨 얼굴2
  lcd.createChar(3, pac_man3);    // 팩맨 얼굴3
  lcd.createChar(4, pac_man4);    // 팩맨 얼굴4
  
}
void loop(){
  for(int first_line=0; first_line<16; first_line++){     // 첫번째 줄
    if(first_line == 0){        // 프로그램 처음 실행 시
      
      lcd.setCursor(0, 0);  // 커서 위치 0,0    첫번째 줄
      lcd.write(byte(1));       // 팩맨 얼굴 출력
 
      lcd.setCursor(1, 0);    // 커서 위치 1,0    첫번째 줄
      lcd.print("Hello, Eduino!!");// Hello, Eduino!! 출력        
            
      lcd.setCursor(0, 1);    // 커서 위치 0,1    두번째 줄
      lcd.print("Have a nice day!");  // Have a nice day! 출력
    }
    else {
      for(int blank = 0; blank < first_line; blank++){  // 팩맨이 지나온 길을 빈칸으로 만들기
        lcd.setCursor(blank, 0);  // 빈칸
        lcd.print(" ");
      }
      int place = first_line;  // fisrt_line 변화를 막기 위해 place 변수 만듦
      lcd.setCursor(place++, 0);  // 팩맨 한칸씩 이동
      if(place % 2 == 1)
        lcd.write(byte(1));     // 팩맨 1
      else 
        lcd.write(byte(2));     // 팩맨 2    
    }
    delay(500);
  }
  for(int second_line = 15; second_line >= 0; second_line --){      // 팩맨 오른쪽부터 시작
    if(second_line == 15){    // for문 맨 처음 시작 시
      for(int blank = 0; blank < 16; blank++){  // 첫번째 줄 모두 다 빈칸으로 만들기
        lcd.setCursor(blank, 0);  // 빈칸
        lcd.print(" ");
      }
      lcd.setCursor(15, 1); // 맨 오른쪽에 팩맨 위치
      lcd.write(byte(3));      
    }
    else {
      for(int blank = 15; blank >= second_line; blank--){ // 팩맨이 지나온 길 빈칸으로
        lcd.setCursor(blank, 1);  // 빈칸
        lcd.print(" ");
      }
      int place = second_line;   // second_line 변화를 막기 위해 place 변수 만듦
      lcd.setCursor(place++, 1);  // 팩맨 한칸씩 이동
      if(place % 2 == 0)
        lcd.write(byte(3)); // 팩맨3
      else 
        lcd.write(byte(4));     // 팩맨4
    }
    delay(500);
  }
}
```
# 4. 앱 개발
앱에서는 블루투스 통신과 더불어 직접 디자인을 해야하므로

MIT에서 제작한 앱 제작 웹사이트인 MIT App Inventor를 사용할 것이다. (안드로이드, 아이폰 모두 호환됨)

다음의 사이트를 방문해 왼쪽 위의 Create Apps! 버튼을 눌러 앱을 제작해보자.

<https://appinventor.mit.edu/>

## 4.1. 사용법

구글에 로그인을 한 후 새 프로제트를 제작할 수 있다.

새 프로젝트를 만들면 제작 화면이 뜬다.

왼쪽은 Palette로 UI(버튼, 사진 등)나 요소(블루투스, 시간, 등)을 추가 할 수 있다.

가운데는 Viewer로 현재 제작중인 앱의 모습을 확인 할 수 있다.

오른쪽은 All Compoments와 Expertise로 어떤 Component(객체 비슷한거)를 추가했는지와 Component 관리, Component의 속성에 대한 편집을 할 수 있다.

앱 디자인은 딱히 설명할 건 없고 직접 여러 버튼 눌러보면서 테스트하거나 인터넷 검색해보면 잘 나와있다. 이쁘게 만들어보자.

마지막으로 오른쪽 위에 Designer와 Blocks가 있는 버튼이 있는데, Blocks버튼을 누르면 스크래치 비슷한 제작 화면을 넘어가게 된다.

Blocks에서는 블럭 코딩을 통해 앱 기능을 구성할 수 있다. 스크래치와 비슷해서 배우기 쉬우니 직접 해보면서 익히길 바란다.

**단, 블루투스 통신 관련 코드는 까다로우니 아래 링크에서 프로젝트 파일 Yunheok_Smartfarm.aia를 받아 참고하면 된다. 이외에도 블루투스 관련 Component를 넣어야 한다.**

<https://drive.google.com/file/d/100BV83oa5OIaIOZzSGntIrogKpahS99w/view?usp=drive_link>

# 5. 예시 자료
전에 직접 제작했던 스마트팜 코드이다.

제작할 때 느꼈던 점으로 코드 짜는데에는 크게 까다로운건 없었고 if-else if문만 잘 이용해도 쉽게 제작할 수 있었다. (그러니까 직접 짜보자)
```
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
```
*윤혁*
