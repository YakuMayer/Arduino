#include <SoftwareSerial.h>

// Создать объект программного последовательного порта для связи с SIM900
// Tx и Rx SIM900 подключены к выводам 7 и 8 Arduino
SoftwareSerial mySerial(7, 8);
String code = "";
String command = "";
int cp1 = 0;
int cp2 = 0;
void SIM900power()
{
  pinMode(9, OUTPUT);
  digitalWrite(9,LOW);
  delay(1000);
  digitalWrite(9,HIGH);
  delay(2000);
  digitalWrite(9,LOW);
  delay(3000);
}

void setup() {
//  pinMode(7,INPUT);
//  pinMode(8,OUTPUT);
  
  Serial.println("SimPower");
  SIM900power();

  Serial.begin(9600);         // включаем hardware-порт
  mySerial.begin(9600);  // включаем software-порт
  
  Serial.println("Star OK");
  // put your setup code here, to run once:
  Serial.println("AT");
  Serial.println("AT+CMGF=1");
  Serial.println("AT+CNMI=1,2,0,0,0");

}


void loop() {
    if (mySerial.available()) {
        char c = mySerial.read();  // читаем из software-порта
        //Serial.print(int(c));                   // пишем в hardware-порт
        //Serial.print(c);
        if (cp1 == 1) {code = code+c;}
        if (c == 34) {
          cp1++;}
        if (c == 34 && cp1 == 2) {
          code = code + "\n";
          cp1++;
          }
        if (cp2 == 1) {command = command+c;}  
        if (c == 10){
          cp2++;}
        if (c == 10 && cp2 == 2){
          command = command+"\n";
          Serial.println(code);
          Serial.println(command);
          cp1 = 0;
          cp2 = 0;}
        
    }
    if (Serial.available()) {
        char c = Serial.read();      // читаем из hardware-порта
        mySerial.write(c);
//         if(c.indexOf("test") != -1){
//          Serial.println("Password OK");
//        }
//          char *str;

//  char sz[] = Serial.read();
//  char *p = sz;
//  while ((str = strtok_r(p, "\r", &p)) != NULL) 
//    {
//     if (str == "test"){
//      Serial.println("Password OK");
//     }
//     else{
//      Serial.println("Хуй там плавал");
//     }
//    }
    }
}
