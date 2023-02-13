
#include <Servo.h>

Servo servos[6];  // create servo object to control a servo
bool isDone = true;
int counter = 0;
int angl = 0;
int spid = 0;
String command = "0";
String com_rip = "0";
bool latestAngle = true;
void setup() {
for(int i = 0; i < 5; i++){
  servos[i].attach(i+2);  // attaches the servo on pin i
}

Serial.begin(9600);
Serial.println("Command list: ");
}

void loop() {
//String command = "x";
while (Serial.available() > 0 && isDone == true) {

    command = Serial.readString();
	//byte indoks = command.indexOf(' ');
	byte indoks = command.indexOf(' ');
	byte indoks2 = command.indexOf(' ', indoks + 1);
	byte indoks3 = command.indexOf(' ', indoks2 + 1);
	String b1 = command.substring(0, indoks);
	String b2 = command.substring(indoks, indoks2);
	String b3 = command.substring(indoks2, indoks3);

	com_rip = b1;
	angl = b2.toInt();
	spid = b3.toInt();
	
	isDone=false;
  }
doSomething(com_rip, angl, spid);
}

void doSomething(String com, int angle, int speed){
if (isDone==false){
	int com_mod = 1;
	//Serial.print("Goin on "); Serial.print(com ); Serial.println(" mode!");
	if(com == "bend_1"){com_mod=0;/*наклон захвата*/}
	else if(com == "bend_2"){com_mod=1;/*наклон локтя*/}
	else if(com == "bend_3"){com_mod=2;/*наклон руки*/}
	else if(com == "base"){com_mod=3;/*поворот руки*/}
	else if(com == "grab"){com_mod=4;/*открытие и закрытие захвата*/}
	else if(com == "grab_rotate"){com_mod=5;/*поворот захвата*/}
	
	int curdelay = 15;
	int curang = servos[com_mod].read();
	if(counter==0){
	if(angle > curang){
	counter = abs(curang - angle);
	}else{counter=curang-angle;}
	if(curang-angle>0){
	latestAngle=false;
	}else if(curang-angle<0){
	latestAngle=true;
	}
	}
	Serial.print(counter);
	if(speed > 0 && speed < 6){
	curdelay = 26 - speed*5;
	}
	switch(latestAngle){
	case true:
	servos[com_mod].write(curang+1);
	Serial.print("Angle written!Angle - ");Serial.print(curang);
	break;
	case false:
	servos[com_mod].write(curang-1);
	Serial.print("-Angle written!Angle - ");Serial.print(curang);
	break;
	}
	
	
	/*switch(com_mod){
	case 0:
	int val = map(val, 0, 1023, 0, 180);
	myservo.write(val);
	break;
	case 1:
	
	break;
	case 2:
	
	break;
	case 3:
	
	break;
	case 4:
	
	break;
	case 5:
	
	break;
	}*/
	counter--;
	if(counter == 0){
	isDone=true;
	}
	delay(curdelay);
}else{Serial.print("fuf");delay(speed*5);return;}

}
