//This is first basic code for line follower

#include "pca9685/pca9685.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


#define MAX_POWER 4096
#define PIN_BASE 300
#define HERTZ 50
int fd;

 //define pins in wiringPi system
#define EN_LEFT 0  //left motor connected to PCA9685
#define EN_RIGHT 1  //right motor connected to PCA9685
#define IN1 4  //Left motor IN1 connect to wiringPI -GPIO 23
#define IN2 5  //Left motor IN2 connect to wiringPi -GPIO 24
#define IN3 2  //Right motor IN3 connect to wiringPi -GPIO 27
#define IN4 3  //Right motor IN4 connect to wiringPi -GPIO 22

//define IR tracking sensors wiringPi
#define SENS1 21 // left sensor
#define SENS2 22 
#define SENS3 23 // middle sensor
#define SENS4 24 
#define SENS5 25 // right sensor
char val[5]; //sensor value array


//Speed and delay definition
#define high_speed 3000  
#define mid_speed  2000  
#define low_speed  1000  
#define short_delay 100
#define long_delay 200
#define extra_long_delay 300


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
        return -1;
    }
    
    setup();

    fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);

    if(fd < 0)
    {
        printf("Error in setup\n");
        return fd;
    }

	while (1)
	{
		//read IR sensor 
		val[0]='0'+!digitalRead(SENS1);
		val[1]='0'+!digitalRead(SENS2);
		val[2]='0'+!digitalRead(SENS3);
		val[3]='0'+!digitalRead(SENS4);
		val[4]='0'+!digitalRead(SENS5);
 
 		//based on IR sensor values to take action. 1 is for BLACK and 0 is for WHITE
        //if and else if will compare recived strings and make action  
//---------------------------LEFT------------------------------------------------------------

        if (strcmp("01000",val)==0 || strcmp("11000",val)==0 || strcmp("10000",val)==0)
        {
        //The black line is in the left of the car, need turn left
            printf("%s sharp left\n", val);  
            go_Left(fd, low_speed, low_speed);  //Turn left sharp
            delay(short_delay);
            stop_car(fd);
            delay(short_delay);
        }

        else if (strcmp("11100",val)==0 || strcmp("10100",val)==0)
        {
        //Blac line is in middle-left side, car need ride forward and slight left
            printf("%s slight left\n",val);
            go_Forward(fd,low_speed,high_speed);  //Turn left slightly
            delay(long_delay);
            stop_car(fd);
            delay(short_delay);
        }
    
    //-------------------------------------FORWARD-------------------------------------------

        else if (strcmp("11110",val)==0 || strcmp("01100",val)==0 ||
                 strcmp("10010",val)==0 || strcmp("10110",val)==0 || 
                 strcmp("11010",val)==0)
        {
            printf("%s forward left\n",val);
            go_Forward(fd,low_speed,mid_speed);  //go forward and slight left
            delay(long_delay);
            stop_car(fd);
            delay(short_delay);
        }

        else if (strcmp("01110",val)==0 || strcmp("01010",val)==0 ||
                 strcmp("00100",val)==0 || strcmp("10101",val)==0 || 
                 strcmp("10011",val)==0 || strcmp("11101",val)==0 || 
                 strcmp("10111",val)==0 || strcmp("11011",val)==0 || 
                 strcmp("11001",val)==0)
        {
            printf("%s forward\n",val);
            go_Forward(fd,mid_speed,mid_speed);  //go forward 
            delay(long_delay);
            stop_car(fd);
            delay(short_delay);
        }

        else if (strcmp("00110",val)==0 || strcmp("01111",val)==0 ||
                 strcmp("01001",val)==0 || strcmp("01011",val)==0 || 
                 strcmp("01101",val)==0)
        {
            printf("%s forward right\n",val);
            go_Forward(fd,mid_speed,low_speed);  //go forward and slight right
            delay(long_delay);
            stop_car(fd);
            delay(short_delay);
        }

    //------------------------------RIGHT-------------------------------------------------------
        else if (strcmp("00001",val)==0 || strcmp("00010",val)==0 ||
                 strcmp("00011",val)==0)
        {
            printf("%s sharp right\n",val);
            go_Right(fd,low_speed,low_speed);  //Turn right sharply
            delay(short_delay);
            stop_car(fd);
            delay(short_delay);
        }  

        else if (strcmp("00111",val)==0 || strcmp("00101",val)==0)
        {
            printf("%s slight right\n",val);
            go_Forward(fd,high_speed,low_speed);  //Turn right slightly
            delay(long_delay);
            stop_car(fd);
            delay(short_delay);
        }
    //--------------------------GO BACK-----------------------------------------------------------

        else if (strcmp("00000",val)==0)
        {
        //No black line is under sensors, Car slowly going backwards
            printf("%s go slowly backwards\n",val);
            go_Back(fd,low_speed,low_speed);  //go back
            delay(short_delay);
            stop_car(fd);
            delay(short_delay);
        }  

    //--------------------------------STOP CAR---------------------------------------------------

        else if (strcmp("11111",val)==0)
        { 
        //all sensor are on. Car stands horizontal to black line. Stop the car
            printf("%s stop\n",val);
            stop_car(fd);
        }

    }
 
	return 0;
}