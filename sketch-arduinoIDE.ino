
#include <Servo.h>

Servo servos[6];  // create servo object to control a servo
String commss[20];
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
for(int i = 0; i < 5; i++){
  servos[i].attach(i+2);  // attaches the servo on pin i
}

Serial.begin(9600);
Serial.println("Waiting for the default pos.\n");

}

void loop() {
Serial.print(balanced);Serial.print(" ");Serial.println(tempcalib);
tempcalib=0;
switch(balanced){
case 0:
if(servos[0].read() != 85){
tempcalib = servos[0].read();
if(servos[0].read() > 85){
servos[0].write(tempcalib-1);
}else if(servos[0].read() < 85){
servos[0].write(tempcalib+1);
}
delay(10);
}if(servos[0].read() == 85){balanced=1;}
break;
case 1:
if(servos[1].read() != 110){
tempcalib = servos[1].read();
if(servos[1].read() > 110){
servos[1].write(tempcalib-1);
}else if(servos[1].read() < 110){
servos[1].write(tempcalib+1);
}
delay(10);
}if(servos[1].read() == 110){balanced=2;}
break;
case 2:
if(servos[2].read() != 55){
tempcalib = servos[2].read();
if(servos[2].read() > 55){
servos[2].write(tempcalib-1);
}else if(servos[2].read() < 55){
servos[2].write(tempcalib+1);
}
delay(10);
}if(servos[2].read() == 55){balanced=3;}
break;
case 3:
if(servos[3].read() != 15){
tempcalib = servos[3].read();
if(servos[3].read() > 15){
servos[3].write(tempcalib-1);
}else if(servos[3].read() < 15){
servos[3].write(tempcalib+1);
}
delay(10);
}if(servos[3].read() == 15){balanced=4;}
break;
case 4:
if(servos[4].read() != 0){
tempcalib = servos[4].read();
if(servos[4].read() > 0){
servos[4].write(tempcalib-1);
}else if(servos[4].read() < 0){
servos[4].write(tempcalib+1);
}
delay(10);
}if(servos[4].read() == 0){balanced=5;}
break;
case 5:
if(servos[5].read() != 125){
tempcalib = servos[5].read();
if(servos[5].read() > 125){
servos[5].write(tempcalib-1);
}else if(servos[5].read() < 125){
servos[5].write(tempcalib+1);
}
delay(10);
}if(servos[5].read() == 125){balanced=6;}//DONE
break;


default:

break;
}

//String command = "x";
while (Serial.available() > 0 && isDone == true) {

    command = Serial.readString();
	if(command=="start"){ isReading=true;ei_cur=0;quingReset=false;Serial.print("Now you can write commands");Serial.print("\n");}
	if(command=="end"){ isReading=false;ei_cur=0;quingReset=true;Serial.print("Manipulating now");Serial.print("\n");}
	if(command=="calibrate"){ balanced=0;Serial.print("Calibrate now");Serial.print("\n");}
	if(command!="start" && command !="end"){
			if(isReading==false){
			Serial.print("Didn\'t I do it for you?");
			Serial.print("\n");
			}
			if(isReading==true){
			commss[ei] = command;
			ei++;
			if(ei >= 20){
			isReading==false;
			ei_cur=0;
			quingReset=true;
			}
			}
		}
 	 }
	if(isDone&&isReading==false&&quingReset==true){
	
		if(ei_cur<ei){
		isDone=false;
			byte indoks = commss[ei_cur].indexOf(' ');
			byte indoks2 = commss[ei_cur].indexOf(' ', indoks + 1);
			byte indoks3 = commss[ei_cur].indexOf(' ', indoks2 + 1);
			String b1 = commss[ei_cur].substring(0, indoks);
			String b2 = commss[ei_cur].substring(indoks, indoks2);
			String b3 = commss[ei_cur].substring(indoks2, indoks3);
			Serial.print("GAY SHIT");
			com_rip = b1;
			angl = b2.toInt();
			spid = b3.toInt();
	
			isDone=false;
			
		}
		ei_cur++;
		if(ei_cur>=ei){quingReset=false;}
	}	
	doSomething(com_rip, angl, spid);	
}

void doSomething(String com, int angle, int speed){
if (isDone==false&&isReading==false){
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
}else{/*Serial.print(ei);*/delay(50);return;}

}
