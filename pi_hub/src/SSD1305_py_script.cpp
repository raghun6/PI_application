/*
 * SSD1305_py_script.cpp
 *
 *  Created on: Dec 6, 2018
 *      Author: raghuravi
 */
#if 1
#include <dlfcn.h>
#include <iostream>
//#include <python3.5/Python.h>
//#include <python3.5/pythonrun.h>
#include <python2.7/Python.h>
#include <python2.7/pythonrun.h>
using namespace std;

void execute_pi_camera(const char *filename){
	dlopen("libpython2.7.so", RTLD_LAZY |RTLD_GLOBAL);

	FILE *fp;
	Py_Initialize();
	fp=fopen(filename,"r+");

	if (fp==NULL)
		cout<<"python file open failed"<<endl;
	else
		cout<<"python file open success"<<endl;

//	PyRun_SimpleFile(fp,"python2.7 pi_camera1.py");
#if 0
	PyRun_SimpleString(/*"from time import sleep\n"
						"from picamera import PiCamera\n"*/
						"camera = PiCamera()\n"
						"camera.start_preview()\n"
						"sleep(5)\n"
						"camera.capture('/home/pi/Desktop/image.jpg')\n"
						"camera.stop_preview()\n");
#else
	//fp = fopen("pi_camera1.py", "r");
	PyRun_SimpleFile(fp,"pi_camera1.py");
#endif
	Py_Finalize();
	fclose(fp);

}

void execute_python_file(const char *filename){
	dlopen("libpython2.7.so", RTLD_LAZY |RTLD_GLOBAL);
	FILE *fp;
	Py_Initialize();
	fp=fopen(filename,"r+");

	if (fp==NULL)
		cout<<"python file open failed"<<endl;
	else
		cout<<"python file open success"<<endl;

	//PyRun_SimpleFile(fp,"python2.7 pi_camera1.py");
	PyRun_SimpleString("from time import time,ctime\n"
						"print 'Today is',ctime(time())\n");
	Py_Finalize();
	fclose(fp);

}

void SSD1306_Python_Script(void){
	dlopen("libpython2.7.so", RTLD_LAZY |RTLD_GLOBAL);
	printf ("in %s @ line %d \n",__func__,__LINE__);
	Py_Initialize();
	printf ("in %s @ line %d \n",__func__,__LINE__);
	PyRun_SimpleString("import time\n"
	"#import Adafruit_GPIO.SPI as SPI\n"
	"import Adafruit_SSD1306\n"
	"from PIL import Image\n"
    "from PIL import ImageDraw\n"
    "from PIL import ImageFont\n"
	"# Raspberry Pi pin configuration:\n"
	"RST = 24\n"
	"# Note the following are only used with SPI:\n"
	"DC = 23\n"
	"SPI_PORT = 0\n"
	"SPI_DEVICE = 0\n"
	"disp = Adafruit_SSD1306.SSD1306_128_64(rst=RST)\n"
	"disp.begin()\n"
	"disp.clear()\n"
	"disp.display()\n"
	"width = disp.width\n"
	"height = disp.height\n"
	"image = Image.new('1', (width, height))\n"
	"draw = ImageDraw.Draw(image)\n"
	"draw.rectangle((0,0,width,height), outline=0, fill=0)\n"
	"padding = 2\n"
	"shape_width = 20\n"
	"top = padding\n"
	"bottom = height-padding\n"
	"x = padding\n"
	"draw.ellipse((x, top , x+shape_width, bottom), outline=255, fill=0)\n"
	"x += shape_width+padding\n"
	"draw.rectangle((x, top, x+shape_width, bottom), outline=255, fill=0)\n"
	"x += shape_width+padding\n"
	"draw.polygon([(x, bottom), (x+shape_width/2, top), (x+shape_width, bottom)], outline=255, fill=0)\n"
	"x += shape_width+padding\n"
	"draw.line((x, bottom, x+shape_width, top), fill=255)\n"
	"draw.line((x, top, x+shape_width, bottom), fill=255)\n"
	"x += shape_width+padding\n"
	"font = ImageFont.load_default()\n"
	"draw.text((x, top),    'Hello',  font=font, fill=255)\n"
	"draw.text((x, top+20), 'Raghu!', font=font, fill=255)\n"
	"disp.image(image)\n"
	"disp.display()\n");
	printf("Executed in main\n");
	//PyRun_SimpleFile(fp,"python2.7 time.py");
	Py_Finalize();


}

#endif
