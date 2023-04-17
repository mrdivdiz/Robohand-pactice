
#include <Servo.h>

//Servo servos[12];  // create servo object to control a servo
Servo pelvic[4];
Servo foot[4];
Servo knee[4];
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

  if(commandos=="init"){
init_pos();
  }
  if(commandos=="step"){
step(angle);
  }
}}

void syncro_move (Servo servo1, Servo servo2, int angle, int spd){
  int curr_angle = servo1.read();
  int tgt_angle = curr_angle + angle;
  for(int i = 0; i < abs(angle); i++){
      if(curr_angle < tgt_angle){
          servo1.write(curr_angle+i);
          servo2.write(curr_angle+i);
        }
      else {
          servo1.write(curr_angle-i);
          servo2.write(curr_angle-i);
        }
    delay((10-spd)*10);
  }
}

String divide_string(String str_in, int part){
  String out, str=str_in;
  byte div_ind = str.indexOf(' ');
  for(int i=0; i<part; i++){
    out = str.substring(0, div_ind);
    str = str.substring(div_ind+1);
    div_ind = str.indexOf(' ');
  }
  return out;
}

void smooth_move(Servo servo, int angle, int spd){
int curr_angle = servo.read();
int diff = curr_angle-angle;
for(int i = 0; i < abs(diff); i++){
  if(curr_angle < angle) servo.write(curr_angle+i);
  else servo.write(curr_angle-i);
  delay((10-spd)*10);
  }
}

void pel_rotate(int leg, int angle, int spd){
  int curr_angle = pelvic[leg-1].read();
  int target_angle;
  if((angle > 0 && (leg == 1 || leg == 4))||(angle < 0 && (leg == 2 || leg == 3))) target_angle = curr_angle+abs(angle);
  else target_angle = curr_angle-abs(angle);
  if (spd == 10) pelvic[leg-1].write(target_angle);
  else smooth_move(pelvic[leg-1], target_angle, spd);
}

void bend_leg(int leg, int angle, int spd){
  //номер ноги leg, 
  leg-=1;
  if ((((leg == 0 || leg == 3))&&(angle > 0))||(((leg == 1 || leg == 2))&&(angle < 0))) angle = abs(angle);
  else angle = -abs(angle);
  syncro_move(foot[leg], knee[leg], angle, spd);
}

void pel_mass_rotate(int angle, int spd){
  int j = 1;
  if (angle < 0) j = -1;
for(int i = 0; i < abs(angle); i++){
  for(int leg = 1; leg < num_legs+1; leg++){
    pel_rotate(leg, j, 10);
  }
  delay((10-spd)*10);
  }
}

void init_pos(){
  Serial.println("Calibration...");
  bend_leg(4,30,1);
  pel_rotate(2,-30,1);
  bend_leg(1,-10,1);
  bend_leg(3,-10,1);
  bend_leg(2,20,1);
  bend_leg(4,-50,1);
  bend_leg(4,20,1);
  pel_rotate(4,30,1);
  bend_leg(1,10,1);
  bend_leg(4,20,1);
  bend_leg(2,-20,1);
  bend_leg(4,-20,1);
  bend_leg(3,10,1);
  Serial.println("Done!");

}

void step(int npos){

if(spid==null||spid==0){spid=1;}
for(int i = 0; i < n; i++){
  if(pelvic[0].read==pelvic[1].read){
init_pos();
}
bend_leg(1,40,spid);
bend_leg(3,-40,spid);
bend_leg(3,50,spid);
pel_rotate(3,60,spid);
bend_leg(3,-10,spid);
bend_leg(1,-40,spid);
bend_leg(2,30,spid);
pel_rotate(2,60,spid);
bend_leg(2,-30,spid);
bend_leg(1,10,spid);
for(int j = 0; j < 30; j++){
pel_rotate(1,-1,spid);
pel_rotate(2,-1,spid);
pel_rotate(3,-1,spid);
pel_rotate(4,-1,spid);
}
bend_leg(1,-10,spid);
bend_leg(2,50,spid);
bend_leg(4,-10,spid);
bend_leg(1,-10,spid);
bend_leg(3,-10,spid);
pel_rotate(4,60,spid);
bend_leg(1,10,spid);
bend_leg(3,10,spid);
bend_leg(2,-40,spid);
bend_leg(1,30,spid);
pel_rotate(1,60,spid);
bend_leg(1,-30,spid);
for(int k = 0; k < 30; j++){
pel_rotate(1,-1,spid);
pel_rotate(2,-1,spid);
pel_rotate(3,-1,spid);
pel_rotate(4,-1,spid);
}

}
}
}
