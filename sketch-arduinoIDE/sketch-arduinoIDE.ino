
#include <Servo.h>
#include <Adafruit_VL53L0X.h>
#include <Wire.h>


Servo servos[2];  // create servo object to control a servo
String commss[20];
Adafruit_VL53L0X lox;
bool isDone = true;
bool isReading = false;
bool quingReset = false;
int counter = 0;
int balanced = 0;
int ei = 0;
int tempcalib = 0;
int ei_cur = 1;
int ei_cur_dvach = 0;
int angl = 0;
int spid = 0;
String command = "0";
String com_rip = "0";
bool latestAngle = true;


void setup() {
  lox = Adafruit_VL53L0X();
  servos[0].attach(8);//angle phi
  servos[1].attach(9);//angle tetha
Serial.begin(9600);
Serial.println("begin");
if (!lox.begin()) {Serial.println("Sensor is not connected");
while(1); }
lox.startRangeContinuous();
}


void loop() {
while (Serial.available() > 0 && isDone == true) {



    command = Serial.readString();
	
	doSomething(command);	
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

void doSomething(String com){
  Serial.println("doin ur mom");
  isDone=true;// Начальное фи = 90 тета = 90
  int phi = divide_string(com, 1).toInt();
  int tetha = divide_string(com, 2).toInt();
  int speed = divide_string(com, 3).toInt();
  Serial.println(phi);
  Serial.println(tetha);
  Serial.println(speed);
  int move_phi = servos[0].read() - phi;
  int move_tetha = servos[1].read() - tetha;
  int i, j, k, m = 1;
  if(move_phi < servos[0].read()){ i *=-1; }
  if(move_tetha < servos[1].read()){ j *=-1; }
  while(servos[0].read()!= phi){
  servos[0].write(servos[0].read() + i);
  delay(100/speed);
  Serial.print(phi); Serial.print(" "); Serial.print(servos[0].read()); Serial.println(" ");
  }
  while(servos[1].read()!= tetha){
  servos[1].write(servos[1].read() + j);
  delay(100/speed);
  }
  Serial.print("Range: ");Serial.println(lox.readRange());
  if(phi > 90){ k *=-1; }
  if(tetha > 90){ m *=-1; }
  while(servos[0].read()!= 90){
  servos[0].write(servos[0].read() + i);
  delay(100/speed);
  }
  while(servos[1].read()!= 90){
  servos[1].write(servos[1].read() + j);
  delay(100/speed);
  }
  
  
}
