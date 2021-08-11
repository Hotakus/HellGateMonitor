///******************************************************************
// * @file HellGateMonitor.ino
// * @author Hotakus (...)
// * @email ttowfive@gmail.com
// * @brief ...
// * @version 1.0
// * @date 2021/8/11 20:19
// * @copyright Copyright (c) 2021/8/11
//*******************************************************************/
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <User_Setup.h>
#include <User_Setup_Select.h>
#include <I2C_MPU6886.h>

///* User include files */
//#include "Source/HgmLvgl/HgmLvgl.h"
//
//
//
//using namespace HGM;
//
//extern HgmLvgl* hgmLvgl;
//
//
//#define COMPILE_DATE __DATE__
//#define COMPILE_TIME __TIME__
//
//
//void setup()
//{
//	/* Base init */
//	Serial.begin(115200);
//	Wire1.begin(21, 22);
//
//	Serial.println("Hello HGM!!!");
//
//	/* Hgm LVGL init */
//	hgmLvgl->HgmLvglBegin();
//
//	
//
//}
//
//void loop()
//{
//	Serial.printf("Temp: %f\n", hgmLvgl->hcl->GetTemperature());
//	vTaskDelay(1000);		// use FreeRTOS
//}

#include <iostream>
#include "regex"

using namespace std;

void setup()
{
	/* Base init */
	Serial.begin(115200);
	Wire1.begin(21, 22);

	string str = "Hello 2018, Bye 2017";
	smatch result;
	regex pattern("\\d{4}");	//匹配四个数字

	//迭代器声明
	string::const_iterator iterStart = str.begin();
	string::const_iterator iterEnd = str.end();
	string temp;
	while (regex_search(iterStart, iterEnd, result, pattern))
	{
		
		temp = result[0];
		Serial.printf("%s\n", temp.c_str());
		iterStart = result[0].second;	//更新搜索起始位置,搜索剩下的字符串
	}

}

void loop()
{
	
}
