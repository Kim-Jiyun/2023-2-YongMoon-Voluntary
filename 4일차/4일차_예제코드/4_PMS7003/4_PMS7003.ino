#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX로 먼지센서의 TX와 RX에 각각 연결됨

void setup() {
  
  Serial.begin(115200); // 확인을 위한 디버깅
  
  mySerial.begin(9600); // PC와 아두이노간 시리얼 통신 속도를 9600bps로 설정
}

void loop() {
  static int CheckFirst=0; // 실행여부 체크
  static int pm_add[3][5]={0,}; // 미세먼지 센서에서 읽어온 데이터를 저장
  static int pm_old[3]={0,}; // 이전에 읽어온 미세먼지 데이터를 저장
  int chksum=0,res=0;;
  unsigned char pms[32]={0,}; // 미세먼지 센서에서 읽어온 raw 데이터를 저장
  
  
  if(mySerial.available()>=32){

    for(int j=0; j<32 ; j++){
      pms[j]=mySerial.read();
      if(j<30)
        chksum += pms[j];
    }

    // 함수 종료 조건문
    if(pms[30] != (unsigned char)(chksum>>8)|| pms[31]!= (unsigned char)(chksum) ){
      return res;
    }
    if(pms[0]!=0x42 || pms[1]!=0x4d ){
      return res;
    }

  // 출력문 확인
  Serial.print("Dust raw data debugging :  ");
  Serial.print("1.0ug/m3:");
  Serial.print(pms[10]);
  Serial.print(pms[11]);
  Serial.print("  ");
  Serial.print("2.5ug/m3:");
  Serial.print(pms[12]);
  Serial.print(pms[13]);
  Serial.print("  ");
  Serial.print("2.5ug/m3:");
  Serial.print(pms[14]);
  Serial.println(pms[15]);
  } 
}
