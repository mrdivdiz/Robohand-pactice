#include <Servo.h>
int first_workfull_pin = 2;
int num_legs = 4;
int def_angle = 90;
Servo pelvic[4];
Servo knee[4];
Servo foot[4];
String commandl[4];
int commandc[4];

void setup() {
 Serial.begin(115200);
 Serial.println("Pls entr 4 comms2run");
 for(int i = 0; i < 12; i++){
  if(i < num_legs){
    pelvic[i].attach(first_workfull_pin+i);
  }
  else if(i < 8){
    knee[i-num_legs].attach(first_workfull_pin+i);
  }
  else {
    foot[i-2*num_legs].attach(first_workfull_pin+i);
  }
    }
}

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

void bend_leg(int leg, int angle, int spd){
  //номер ноги leg, 
  leg-=1;
  if ((((leg == 0 || leg == 3))&&(angle > 0))||(((leg == 1 || leg == 2))&&(angle < 0))) angle = abs(angle);
  else angle = -abs(angle);
  syncro_move(foot[leg], knee[leg], angle, spd);
}

void pel_rotate(int leg, int angle, int spd){
  int curr_angle = pelvic[leg-1].read();
  int target_angle;
  if((angle > 0 && (leg == 1 || leg == 4))||(angle < 0 && (leg == 2 || leg == 3))) target_angle = curr_angle+abs(angle);
  else target_angle = curr_angle-abs(angle);
  if (spd == 10) pelvic[leg-1].write(target_angle);
  else smooth_move(pelvic[leg-1], target_angle, spd);
}

void init_pos() {
  bend_leg(4, 20, 9);
  bend_leg(2, 20, 9);
  pel_rotate(2, -30, 9);
  bend_leg(2, -20, 9);
  bend_leg(1, -10, 9);
  bend_leg(3, -10, 9);
  bend_leg(2, 20, 9);
  bend_leg(4, -40, 9);
  bend_leg(4, 20, 9);
  pel_rotate(4, 30, 9);
  bend_leg(1, 10, 9);
  bend_leg(4, 20, 9);
  bend_leg(2, -20, 9);
  bend_leg(4, -20, 9);
  bend_leg(3, 10, 9);
}

void step_programm() {
  if(pelvic[0].read() == pelvic[1].read()) init_pos();
  bend_leg(1, 40, 9);
  bend_leg(3, -20, 9);
  bend_leg(3, 30, 9);
  pel_rotate(3, 60, 9);
  bend_leg(3, -10, 9);
  bend_leg(1, -40, 9);
  bend_leg(2, 30, 9);
  pel_rotate(2, 60, 9);
  bend_leg(2, -30, 9);
  bend_leg(1, 10, 9);
  pel_mass_rotate(-30, 9);
  bend_leg(1, -10, 9);
  bend_leg(2, 50, 9);
  bend_leg(4, -10, 9);
  bend_leg(1, -10, 9);
  bend_leg(3, -10, 9); 
  pel_rotate(4, 60, 9);
  bend_leg(4, 10, 9);
  bend_leg(3, 10, 9);
  bend_leg(2, -50, 9);
  bend_leg(1, 30, 9);
  pel_rotate(1, 60, 9);
  bend_leg(1, -20, 9);
  pel_mass_rotate(-30, 9);
}

void init_mirror() {
  bend_leg(3, 20, 9);
  bend_leg(1, 20, 9);
  pel_rotate(1, -30, 9);
  bend_leg(1, -20, 9);
  bend_leg(2, -10, 9);
  bend_leg(4, -10, 9);
  bend_leg(1, 20, 9);
  bend_leg(3, -40, 9);
  bend_leg(3, 20, 9);
  pel_rotate(3, 30, 9);
  bend_leg(2, 10, 9);
  bend_leg(3, 20, 9);
  bend_leg(1, -20, 9);
  bend_leg(3, -20, 9);
  bend_leg(4, 10, 9);
}

void mk_spin(int num_spins){
  int leg_1 = 1, leg_2 = 2, leg_3 = 3, leg_4 = 4, rot_ind = 1;
  if (num_spins < 0){
    rot_ind = -1;
    leg_1 = 2;
    leg_2 = 1;
    leg_3 = 4;
    leg_4 = 3;
  }
  for(int i = 0; i < abs(num_spins); i++){
    if(num_spins < 0) init_mirror();
    else init_pos();
    bend_leg(leg_3, 20, 9);
    bend_leg(leg_1, 20, 9);
    pel_rotate(leg_1, 30, 9);
    bend_leg(leg_1, -20, 9);
    bend_leg(leg_3, -20, 9);
    bend_leg(leg_4, -10, 9);
    bend_leg(leg_2, 10, 9);
    bend_leg(leg_1, 40, 9);
    pel_rotate(leg_3, -30, 9);
    bend_leg(leg_1, -40, 9);
    bend_leg(leg_2, -10, 9);
    bend_leg(leg_4, 10, 9);
    pel_spin(-30*rot_ind, 9);
    }
}

void pel_spin(int angle, int spd){
  int j = 1;
  if (angle < 0) j = -1;
for(int i = 0; i < abs(angle); i++){
  for(int leg = 1; leg < num_legs+1; leg++){
    if(leg == 1 || leg ==4) pel_rotate(leg, j, 10);
    if(leg == 2 || leg ==3) pel_rotate(leg, -j, 10);
  }
  delay((10-spd)*10);
  }
}

void loop() {
  if (Serial.available()>0){
    serial_string = Serial.readString();
    for(int i = 0; i < 4; i++){
      if(commandl[i] == null){
    commandl[i] = divide_string(serial_string, 1);
    commandc[i] = divide_string(serial_string, 2);
    break;
              }
           }
    }
    runCom();
    if(commandl[3]!=null){Serial.println("Running...");}
}

void runCom(){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < commandc[i];j++){
if(commandl[i] == "bend"){
      int leg_num = divide_string(serial_string, 2).toInt();
      int angle = divide_string(serial_string, 3).toInt();
      bend_leg(leg_num, angle, 9);
    }
    else if(commandl[i] == "alldef"){
      for(int i = 0; i < num_legs; i++){
        pelvic[i].write(def_angle);
        knee[i].write(def_angle);
        foott[i].write(def_angle);
      }
    }
      else if(commandl[i] == "step") {
        int steps = divide_string(serial_string, 2).toInt();
        mk_step(steps);
      }
      else if(commandl[i] == "init") {
        init_pos();
      }
    }
    if(commandl[i] == "pel"){
      int leg_num = divide_string(serial_string, 2).toInt();
      int angle = divide_string(serial_string, 3).toInt();
      pel_rotate(leg_num, angle, 9);
    }
    if(commandl[i] == "masspel"){
    int angle = divide_string(serial_string, 2).toInt();
    pel_mass_rotate(angle, 9);
    }
    }
    for(int k = 0; k < 4; k++){
    commandl[k]=null;
    commandc[k]=null;
    }
    Serial.println("Done.");
  }
