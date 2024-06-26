#include <NewPing.h>

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 180 // Maximum distance (in cm) to ping.

#define Front 0
#define Left  1 
#define Right 2

#define TRIG1 26 // 초음파 센서 1번 Trig 핀 번호
#define ECHO1 27 // 초음파 센서 1번 Echo 핀 번호

#define TRIG2 30 // 초음파 센서 2번 Trig 핀 번호
#define ECHO2 31 // 초음파 센서 2번 Echo 핀 번호

#define TRIG3 34 // 초음파 센서 3번 Trig 핀 번호
#define ECHO3 35 // 초음파 센서 3번 Echo 핀 번호

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
NewPing(TRIG1, ECHO1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
NewPing(TRIG2, ECHO2, MAX_DISTANCE),
NewPing(TRIG3, ECHO3, MAX_DISTANCE)
};

float front_sonar = 0.0;
float left_sonar  = 0.0;
float right_sonar = 0.0;

// 재귀 평균 필터 변수
float alpha = 0.1; // 필터 계수, 0 < alpha < 1
float front_filtered = 0.0;
float left_filtered = 0.0;
float right_filtered = 0.0;

void setup() 
{
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);

  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3, INPUT);
  
  Serial.begin(115200); // 통신속도를 115200으로 정의함
}

void loop() 
{
  // 초음파 센서 측정값 업데이트
  front_sonar = sonar[Front].ping_cm() * 10; // 전방 센서 측정
  left_sonar  = sonar[Left].ping_cm() * 10;  // 좌측 센서 측정
  right_sonar = sonar[Right].ping_cm() * 10; // 우측 센서 측정

  // 0.0 출력이 최대값이므로 보정
  if(front_sonar == 0.0) front_sonar = MAX_DISTANCE * 10; 
  if(left_sonar  == 0.0) left_sonar  = MAX_DISTANCE * 10;
  if(right_sonar == 0.0) right_sonar = MAX_DISTANCE * 10;

  // 재귀 평균 필터 적용
  front_filtered = alpha * front_sonar + (1 - alpha) * front_filtered;
  left_filtered  = alpha * left_sonar  + (1 - alpha) * left_filtered;
  right_filtered = alpha * right_sonar + (1 - alpha) * right_filtered;

  Serial.print("F(재귀평균필터): "); Serial.print(front_filtered); Serial.print(" cm, ");
  Serial.print("F(필터없음): "); Serial.print(front_sonar); Serial.print(" cm | ");

  Serial.print("L(재귀평균필터): "); Serial.print(left_filtered); Serial.print(" cm, ");
  Serial.print("L(필터없음): "); Serial.print(left_sonar); Serial.print(" cm | ");

  Serial.print("R(재귀평균필터): "); Serial.print(right_filtered); Serial.print(" cm, ");
  Serial.print("R(필터없음): "); Serial.print(right_sonar); Serial.println(" cm");

  delay(100); // 데이터 갱신 주기 조절
}
