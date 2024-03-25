#define ledpin 13 //LED는 디지털 핀 13에 연결 됨
int linesensor_data[5] = {0,0,0,0,0}; //읽은 값을 저장할 변수
int linesensor_pin[5] = {2,3,4,5,6}; //int형 배열

void setup() {
  int i;
  pinMode(ledpin, OUTPUT); //디지털 핀 13을 출력으로 설정
for(i=0;i<5;i++)
{
  pinMode(linesensor_pin[i], INPUT); //디지털 linesensor_pin을 입력으로 설정
}
  Serial.begin(9600);
}

void loop() {
int i;

for(i=0;i<5;i++)
{
  linesensor_data[i] = digitalRead(linesensor_pin[i]);//디지털linesensor_pin들로 부터 읽음
}
Serial.print("Input data =");
for(i=0;i<5;i++)
{
 
 
Serial.print(linesensor_data[i]);
Serial.print("  ");
}
Serial.println("  ");
}
