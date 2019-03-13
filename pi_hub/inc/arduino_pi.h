/*
 * arduino_pi.h
 *
 *  Created on: Nov 4, 2018
 *      Author: raghuravi
 */

#ifndef ARDUINO_PI_H_
#define ARDUINO_PI_H_

#include <pthread.h>


#define SUCCESS  0
#define FAIL	-1
#define SERIAL_DEVICE "/dev/ttyACM0"
#define BAUD_RATE	   115200
#define STR_LENGTH	   1024
#define TEST_CODE		0
#define IOSTREAM_DISPLAY	0
#define TIME_DELAY		10000000
#define 	ITS_TRUE 			1
#define 	ITS_FALSE 			0
#define TIME_DIFFERENCE		2
#define DEBUG_ENABLE			1
#define MODULO_VAL			12
void SSD1306_Python_Script(void);
void execute_python_file(const char *filename);
/*
 *
 * */

typedef struct pi_arduino_struct_t{

}pi_arduino_struct;


/*
 * Enum values to be used for Menu in Raspi to be communicated to Arduino
 *
 * */
enum PWD_State
{
	PASSWORD_SUCCESS=0,
	PASSWORD_ENABLED,
	PASSWORD_DISABLED,
	PASSWORD_FAILED=-1
};


 enum WIFI_State
{
	ENABLE_WIFI=0,
	DISABLE_WIFI=-1
};

 enum menu{
	INITIAL_STATE=0,
	ARDUINO_DISPLAY_TIME,
	GET_TEMPARATURE_FROM_ARDUINO,
	GET_SOUND_DATA_FROM_ARDUINO,
	GET_LIGHT_SENSOR_DATA_FROM_ARDUINO,
	ULTRASONIC_SENSOR_FROM_ARDUINO,
   ARDUINO_ENABLE_LED,
   SEND_DATA_TO_ARDUINO_16x2_LCD,
   //PI_GRAPHIC_LCD_DISPLAY,
   //ARDUINO_ENABLE_BLE,
	//ARDUINO_ENABLE_WIFI_MODULE,
	//ARDUINO_SEND_DATA_OVER_WIFI,
	//ARDUINO_GET_PUSH_BUTTON_DATA,
	//ARDUINO_TRIGGER_BUZZER,
	//ARDUINO_ENABLE_RELAY,
	//ARDUINO_ROTARY_ANGLE_SENSOR,
	//ARDUINO_TOUCH_SENSOR,
   GET_SENSOR_DATA_FROM_ARDUINO,
	/********************Add new items above****************/

	MAX_MENU_NUM
};

 void execute_pi_camera(const char *filename);

#endif /* ARDUINO_PI_H_ */
