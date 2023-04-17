
#include <Servo.h>

Servo servos[12];  // create servo object to control a servo
bool isDone = true;
int counter = 0;
String b1;
int angl = 0;
int spid = 0;
int leg = 0;
String command = "0";
String com_rip = "0";
bool latestAngle = true;
void setup() {
for(int i = 0; i < 12; i++){
  servos[i].attach(i+2);  // attaches the servo on pins 2+
}

Serial.begin(9600);
Serial.println("Command list:\nbend_leg angle speed leg_number\npel_rotate angle speed leg_number");
}

void loop() {
//String command = "x";
while (Serial.available() > 0 && isDone == true) {

    command = Serial.readString();
  //byte indoks = command.indexOf(' ');
  byte indoks = command.indexOf(' ');
  byte indoks2 = command.indexOf(' ', indoks + 1);
  byte indoks3 = command.indexOf(' ', indoks + 2);
  byte indoks4 = command.indexOf(' ', indoks + 3);
  b1 = command.substring(0, indoks);
  String b2 = command.substring(indoks, indoks2);
  String b3 = command.substring(indoks2, indoks3);
  String b4 = command.substring(indoks3, indoks4);

  angl = b2.toInt();
  spid = b3.toInt();
  leg = b4.toInt();
  
  isDone=false;
  }
moveLeg(b1, angl, spid, leg);
}

void moveLeg(String commandos, int angle, int speed, int o_leg){
if (isDone==false){
  int curdelay = 15;
  int curang = servos[0].read();
  counter = angle;
  Serial.print(o_leg);
  if(speed > 0 && speed < 6){
  curdelay = 26 - speed*5;
  }
if(commandos=="bend_leg"){
if(angle>0){
  for (int i = angle; i >= 1; i--){
switch(o_leg){
case 1:
  servos[0].write(servos[0].read()+1);
  servos[1].write(servos[1].read()+1);
break;
case 2:
  servos[2].write(servos[2].read()-1);
  servos[3].write(servos[3].read()-1);
break;
case 3:
  servos[4].write(servos[4].read()-1);
  servos[5].write(servos[5].read()-1);
break;
case 4:
  servos[6].write(servos[6].read()+1);
  servos[7].write(servos[7].read()+1);
break;
default:
Serial.println("OLEG");
break;
}
  counter--;
  delay(curdelay);
  if(counter == 0 || counter == 1){
  isDone=true;
  }
}}
if(angle<0){
for (int i = angle*(-1); i >= 1; i--){
switch(o_leg){
case 1:
  servos[0].write(servos[0].read()-1);
  servos[1].write(servos[1].read()-1);
break;
case 2:
  servos[2].write(servos[2].read()+1);
  servos[3].write(servos[3].read()+1);
break;
case 3:
  servos[4].write(servos[4].read()+1);
  servos[5].write(servos[5].read()+1);
break;
case 4:
  servos[6].write(servos[6].read()-1);
  servos[7].write(servos[7].read()-1);
break;
default:
Serial.println("OLEG");
break;
}
  counter++;
  delay(curdelay);
  if(counter == 0 || counter == 1){
  isDone=true;
  }
}}}





if(commandos=="pel_rotate"){
  if(angle>0){
  for (int i = angle; i >= 1; i--){
switch(o_leg){
case 1:
  servos[8].write(servos[8].read()+1);
break;
case 2:
  servos[9].write(servos[9].read()-1);
break;
case 3:
  servos[10].write(servos[10].read()-1);
break;
case 4:
  servos[11].write(servos[11].read()+1);
break;
default:
Serial.println("OLEG");
break;
}
  counter--;
  delay(curdelay);
  if(counter == 0 || counter == 1){
  isDone=true;
  }
}}
if(angle<0){
for (int i = angle*(-1); i >= 1; i--){
switch(o_leg){
case 1:
  servos[8].write(servos[8].read()-1);
break;
case 2:
  servos[9].write(servos[9].read()+1);
break;
case 3:
  servos[10].write(servos[10].read()+1);
break;
case 4:
  servos[11].write(servos[11].read()-1);
break;
default:
Serial.println("OLEG");
break;
}
  counter++;
  delay(curdelay);
  if(counter == 0 || counter == 1){
  isDone=true;
  }
}}
}





}}
