/*
 * arduino_pi.cpp
 *
 *  Created on: Nov 4, 2018
 *      Author: raghuravi
 */


#include "wiringPi.h"
#include <wiringSerial.h>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include "arduino_pi.h"
#include <thread>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;
char timeFlag,menuFlag;

/*
 * Raspberry PI UART communication Class.
 *
 * */
/*Class Definition of Raspberry PI UART*/
class raspi_uart
{
private:
	char rx_data[STR_LENGTH];
	int read_char_from_arduino;
	int send_char_to_arduino;
	int serial_fd;

public:
	char write_action_flag;
	int init_arduino_uart(void);
	void write_str_arduino(const char *,int);
	int read_str_arduino(int);
	void write_char_arduino(char,int);
	char read_char_arduino(int);
	void close_arduino_uart(int);
	char * get_rx_data(void);
	void pi_arduino_uart_comm(char);
	int get_serialfd(void);
};

class security{

};

int  raspi_uart::get_serialfd(void){
	return serial_fd;
}

void raspi_uart::pi_arduino_uart_comm(char menu_char_to_ardunio){
	write_char_arduino(menu_char_to_ardunio,serial_fd);
}

char * raspi_uart::get_rx_data(void){
	return &rx_data[0];
}

int raspi_uart::init_arduino_uart(void)
{
	int ret_val=SUCCESS;
	serial_fd= serialOpen (SERIAL_DEVICE, BAUD_RATE);

	if (serial_fd==FAIL)
		cout <<"Arduino Serial device open FAILED"<<endl;
	else
		cout<<"Arduino device open SUCCESS, fd="<<serial_fd<<"\tWaiting for data from Arduino"<<endl;

	return ret_val;
}

int raspi_uart::read_str_arduino(int fd)
{
int num_chars,count=0;

num_chars=serialDataAvail(fd);
if (num_chars==-1)
	return FAIL;
else{
	while(num_chars>=0){
		rx_data[count++]=serialGetchar(fd);
		//cout<<(char)serialGetchar(fd);
		num_chars--;
	}
	}
return count;
}

char raspi_uart::read_char_arduino(int fd)
{
	char dat;
	dat=serialGetchar(fd);
	return dat;
}

void raspi_uart::write_char_arduino(char dat,int fd){
	serialPutchar(fd,dat);
}

void raspi_uart::write_str_arduino(const char *dat,int fd){
	serialPrintf(fd,dat);
}

void raspi_uart::close_arduino_uart(int fd){
serialClose(fd);
}

class arduino_pi_thread_functions
{
public:
	void operator()()
	{
	std::cout<<"\n hello Thread..."<<endl;
	delay(1);
	}
};

int GetRandom(int max){
	srand(time(NULL));
	return rand() % max;
}

raspi_uart obj_pi_arduino_uart;


void WaitForArduinoInit(int id){
do{

}while(1);
}

void menu_function(char menuFlag){


}

void diff_time_secs(int N){
	 	 static time_t start_time=0,end_time=0;
	 	 static int menu_counter=1;
#if DEBUG_ENABLE
	 	 static int display_counter=0;
#endif
	 	 //cout<<"start_time="<<start_time<<" end_time="<<end_time<<" diff time="<<(end_time-start_time)<<" menu_counter= "<<menu_counter<<endl;
	    if (timeFlag==ITS_TRUE){
	    	timeFlag=ITS_FALSE;
	    	start_time= time(NULL);
	    }
	    end_time = time(NULL);

	    if (difftime(end_time,start_time)>N)
		{

#if DEBUG_ENABLE
	   cout<<"display_counter= "<<display_counter++<<endl;
   	if (display_counter%MODULO_VAL==0)
    			cout<<"System started "<<(display_counter * TIME_DIFFERENCE)<<" secs ago "<<endl;
#endif
	    	timeFlag=ITS_TRUE;
	    	switch (menu_counter){

	    	case ARDUINO_DISPLAY_TIME:
	    		menuFlag=ARDUINO_DISPLAY_TIME;
	    		break;

	    	case GET_TEMPARATURE_FROM_ARDUINO:
	    		menuFlag=GET_TEMPARATURE_FROM_ARDUINO;
	    		break;

	    	case GET_SOUND_DATA_FROM_ARDUINO:
	    		menuFlag=GET_SOUND_DATA_FROM_ARDUINO;
	    		break;

	    	case GET_LIGHT_SENSOR_DATA_FROM_ARDUINO:
  		    	menuFlag=GET_LIGHT_SENSOR_DATA_FROM_ARDUINO;
    		break;

	    	case ULTRASONIC_SENSOR_FROM_ARDUINO:
	    		menuFlag=ULTRASONIC_SENSOR_FROM_ARDUINO;
	    	break;

	    	case ARDUINO_ENABLE_LED:
	    		   menuFlag=ARDUINO_ENABLE_LED;
	    	break;

	    	case GET_SENSOR_DATA_FROM_ARDUINO:
	    		   menuFlag=GET_SENSOR_DATA_FROM_ARDUINO;
	      break;

	    	default:
	    		break;
	    	}
	    	menu_counter++;
	    	if (menu_counter>=MAX_MENU_NUM)
	    		menu_counter=1;
		}
}

void menu_function_thread(int id){

auto nowTime=chrono::system_clock::now();
time_t sleepTime;
char *rx_char;

#if IOSTREAM_DISPLAY
tm myLocalTime= *localtime(&sleepTime);
	cout<<"Thread "<<id <<
		  " Sleep Time : "<<
		  ctime(&sleepTime)<<endl;

	cout <<"Month : "<<
			myLocalTime.tm_mon <<endl;

	cout <<"Day : "<<
			myLocalTime.tm_mday <<endl;

	cout <<"Year : "<<
			myLocalTime.tm_year <<endl;

	cout <<"Hours : "<<
			myLocalTime.tm_hour <<endl;

	cout <<"Minutes : "<<
			myLocalTime.tm_min <<endl;

	cout <<"Seconds : "<<
			myLocalTime.tm_sec <<endl;
#endif

while(1){


			if (menuFlag==INITIAL_STATE){
				do{
				cout<<"Waiting for init char from Arduino"<<endl;
				delay(100);
				}while(obj_pi_arduino_uart.read_char_arduino(obj_pi_arduino_uart.get_serialfd())!='A');
				obj_pi_arduino_uart.pi_arduino_uart_comm('P');
				diff_time_secs(10);
				menuFlag=ARDUINO_DISPLAY_TIME;
				timeFlag=ITS_TRUE;
			}

			if (menuFlag==ARDUINO_DISPLAY_TIME){
				obj_pi_arduino_uart.pi_arduino_uart_comm('t');
				delay(1);//wait for the arduino to read the char 't'
				this_thread::sleep_for(chrono::seconds((int)1));
				nowTime=chrono::system_clock::now();
				sleepTime=chrono::system_clock::to_time_t(nowTime);
				//cout<<"current date & time sent="<<ctime(&sleepTime)<<endl;
				serialPrintf(obj_pi_arduino_uart.get_serialfd(),(const char *)ctime(&sleepTime));
				diff_time_secs(TIME_DIFFERENCE);
			}

			if (menuFlag==GET_TEMPARATURE_FROM_ARDUINO){
				obj_pi_arduino_uart.pi_arduino_uart_comm('T');
				delay(1);//wait for the arduino to read the char 'T'
				this_thread::sleep_for(chrono::seconds((int)1));
				diff_time_secs(TIME_DIFFERENCE);
			}

			if (menuFlag==GET_SOUND_DATA_FROM_ARDUINO)
			{
				obj_pi_arduino_uart.pi_arduino_uart_comm('s');
				delay(1);	//wait for the arduino to read the char 's'
				this_thread::sleep_for(chrono::seconds((int)1));
				diff_time_secs(TIME_DIFFERENCE);
			}

			if (menuFlag==GET_LIGHT_SENSOR_DATA_FROM_ARDUINO)
			{
				obj_pi_arduino_uart.pi_arduino_uart_comm('l');
				delay(1);	//wait for the arduino to read the char 'l'
				this_thread::sleep_for(chrono::seconds((int)1));
				diff_time_secs(TIME_DIFFERENCE);
			}

			if (menuFlag==ULTRASONIC_SENSOR_FROM_ARDUINO)
			{
				obj_pi_arduino_uart.pi_arduino_uart_comm('U');
				delay(1);	//wait for the arduino to read the char 'U'
				this_thread::sleep_for(chrono::seconds((int)1));
				diff_time_secs(TIME_DIFFERENCE);
			}

			if (menuFlag==ARDUINO_ENABLE_LED)
			{
				obj_pi_arduino_uart.pi_arduino_uart_comm('e');
				delay(1);	//wait for the arduino to read the char 'e'
				this_thread::sleep_for(chrono::seconds((int)1));
				diff_time_secs(TIME_DIFFERENCE);
			}

			if (menuFlag==SEND_DATA_TO_ARDUINO_16x2_LCD)
			{
				obj_pi_arduino_uart.pi_arduino_uart_comm('a');
				delay(1);	//wait for the arduino to read the char 'a'
				this_thread::sleep_for(chrono::seconds((int)1));
				diff_time_secs(TIME_DIFFERENCE);
			}

			if (menuFlag==GET_SENSOR_DATA_FROM_ARDUINO)
			{
				obj_pi_arduino_uart.pi_arduino_uart_comm('D');
				delay(1);	//wait for the arduino to read the char 'D'
				obj_pi_arduino_uart.read_str_arduino(obj_pi_arduino_uart.get_serialfd());
				rx_char=(char *)obj_pi_arduino_uart.get_rx_data();
				cout<<rx_char<<endl;
				this_thread::sleep_for(chrono::seconds((int)1));
				diff_time_secs(TIME_DIFFERENCE);
			}
	}
}

void response_thread(int id) {
	auto nowTime = chrono::system_clock::now();
	time_t sleepTime;
	cout << "in " <<__func__<< endl;
	this_thread::sleep_for(chrono::seconds((int)1));

}

int main (void)
{
#if 1
timeFlag=ITS_FALSE;
menuFlag=INITIAL_STATE;
int ret_val=SUCCESS;

ret_val=obj_pi_arduino_uart.init_arduino_uart();

	if (ret_val==FAIL)
		return FAIL;

	#if TEST_CODE
		obj_pi_arduino_uart.write_action_flag=1;
		obj_pi_arduino_uart.pi_arduino_uart_comm('a');
	#endif
#if 0
		execute_python_file("animate.py");
	//	SSD1306_Python_Script();

#endif
		//execute_pi_camera("/home/pi/projects/pi_hub/src/pi_camera1.py");
		//execute_python_file("time.py");
		thread th1 (menu_function_thread,1);
		th1.join();
		thread th2(response_thread, 2);
		th2.join();
		return ret_val;
#else
	thread th1 (ExecuteThread,1);
	th1.join();

return 0;

#endif
}

