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
