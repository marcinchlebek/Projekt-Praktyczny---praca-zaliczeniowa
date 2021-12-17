//This is first basic code for line follower
//TODO ---> add bluetooth handler
//TODO ---> add camera interface


#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <signal.h>


#define MAX_POWER 4096
int fd;

 //define pins in wiringPi system
#define EN_LEFT 0  //left motor connected to PCA9685
#define EN_RIGHT 1  //right motor connected to PCA9685
#define IN1 4  //Left motor IN1 connect to wiringPI -GPIO 23
#define IN2 5  //Left motor IN2 connect to wiringPi -GPIO 24
#define IN3 2  //Right motor IN3 connect to wiringPi -GPIO 27
#define IN4 3  //Right motor IN4 connect to wiringPi -GPIO 22

//define IR tracking sensors wiringPi
#define SENS1 21 
#define SENS2 22 
#define SENS3 23 
#define SENS4 24 
#define SENS5 25 
char val[5]; //sensor value array


//Speed and delay definition
#define high_speed 3000  
#define mid_speed  2000  
#define low_speed  1000  
#define short_delay 100
#define long_delay 200
#define extra_long_delay 300

//TODO ----> make external library for functions f.e. functions.cpp

//<---------------------------------------------------------------->
void setup()
{
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 pinMode(SENS1,INPUT);
 pinMode(SENS2,INPUT);
 pinMode(SENS3,INPUT);
 pinMode(SENS4,INPUT);
 pinMode(SENS5,INPUT);
   
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,LOW);
}

void go_Back(int fd,int l_speed,int r_speed)
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW); 
    pca9685PWMWrite(fd, EN_LEFT, 0, l_speed);
    pca9685PWMWrite(fd, EN_RIGHT, 0, r_speed);
}

void go_Forward(int fd,int l_speed,int r_speed)
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH); 
    pca9685PWMWrite(fd, EN_LEFT, 0, l_speed);
    pca9685PWMWrite(fd, EN_RIGHT, 0, r_speed);
}

void go_Left(int fd,int l_speed,int r_speed)
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH); 
    pca9685PWMWrite(fd, EN_LEFT, 0, l_speed);
    pca9685PWMWrite(fd, EN_RIGHT, 0, r_speed);
}

void go_Right(int fd,int l_speed,int r_speed)
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW); 
    pca9685PWMWrite(fd, EN_LEFT, 0, l_speed);
    pca9685PWMWrite(fd, EN_RIGHT, 0, r_speed);
}

void stop_car(int fd)
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW); 
    pca9685PWMWrite(fd, EN_LEFT, 0, 0);
    pca9685PWMWrite(fd, EN_RIGHT, 0, 0);
}

//<-------------------------------------------------------->

int main(void)
{
    if(wiringPiSetup()==-1)
    {
        std::cout<<"setup wiringPi failed!"<<std::endl;
        std::cout<<"check setup"<<std::endl;
        return -1;
    }

	setup();

	std::cout<<"Setup starts..."<<std::endl;
    std::cout<<"Gpio ok"<<std::endl;


    //Main Loop of Program
	while (true)
	{
		//read IR sensor 
		val[0]='0'+!digitalRead(SENS1);
		val[1]='0'+!digitalRead(SENS2);
		val[2]='0'+!digitalRead(SENS3);
		val[3]='0'+!digitalRead(SENS4);
		val[4]='0'+!digitalRead(SENS5);
 
 		//based on IR sensor values to take action. 1 is for BLACK and 0 is for WHITE
        //if and else if will compare recived strings and make action  
        if (...)
        {
            //The black line is in the left of the car, need turn left 
            go_Left(fd, low_speed, low_speed);  //Turn left
            delay(short_delay);
            stop_car(fd);
            delay(short_delay);
        }

        else if (...)
        {
            go_Forward(fd, low_speed, mid_speed);  //go forward
            delay(long_delay);
            stop_car(fd);
            delay(short_delay);
        }
   
        else if (...)
        {
            go_Right(fd, low_speed, low_speed);  //Turn right 
            delay(short_delay);
            stop_car(fd);
            delay(short_delay);
        }  

        else if (...)
        {
            go_Back(fd, low_speed, mid_speed);  //go back
            delay(long_delay);
            stop_car(fd);
            delay(short_delay);
        }

        else if (strcmp(...)
        { 
          stop_car(fd); // Stop car
        }
    }
 
	return 0;
}