#include <string.h>


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println("PC와 통신"); //

}

char rxChar = "";
String rxString = "";

void loop() {
  // put your main code here, to run repeatedly:

  // TX test
  //Serial1.println("A");
  //Serial.println("send");


  // RX test
  if (Serial1.available()) {
    while (Serial1.available()) {
      rxChar = (char) Serial1.read(); // 수신 데이터 저장
      rxString += rxChar;
    }
    Serial.println(rxString);
  }
  //delay(1000);

  
  
}
