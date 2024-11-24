# 스마트팜 모듈, 센서 설명 및 예제 코드
스마트팜에 사용되는 모듈과 센서에 대한 설명 및 주로 사용되는 함수와 예제 코드에 대한 문서입니다.
## 센서 종류
- **수분 센서**
- **온습도 센서**
- **조도 센서**
## 모듈 종류
- **블루투스 모듈**
- **쿨링 팬**
- **워터 펌프**
- **5 x 5 RGB LED**
- **LCD 디스플레이 모듈**
---
### 수분 센서
토양의 수분을 측정합니다.
참고: 에듀이노 토양 탐침 수분센서 <https://eduino.kr/product/detail.html?product_no=4742&cate_no=27&display_group=1>
- 주요 함수 
> 없음

> 아두이노의 아날로그 핀에 꽂은 후 analogread() 함수를 사용해 수분을 측정함

**예제 코드**
void setup() {

  Serial.begin(9600); // open serial port, set the baud rate as 9600 bps
  
}

void loop() {

  int val;
  
  val = analogRead(0); //connect sensor to Analog 0
  
  Serial.println(val); //print the value to serial port
  
  delay(100);
  
}

