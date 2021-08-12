///******************************************************************
// * @file HellGateMonitor.ino
// * @author Hotakus (...)
// * @email ttowfive@gmail.com
// * @brief ...
// * @version 1.0
// * @date 2021/8/11 20:19
// * @copyright Copyright (c) 2021/8/11
//*******************************************************************/
//#include <Arduino.h>
//#include <TFT_eSPI.h>
//#include <User_Setup.h>
//#include <User_Setup_Select.h>
//#include <I2C_MPU6886.h>
//
///* User include files */
//#include "Source/HgmLvgl/HgmLvgl.h"
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
//}
//
//void loop()
//{
//	Serial.printf("Temp: %f\n", hgmLvgl->hcl->GetTemperature());
//	vTaskDelay(1000);		// use FreeRTOS
//}

#include "Source/HgmApp/HgmApp.h"

// TODO: TCP Server for projection
// TODO: TCP Client for getting another info
// TODO: Bluetooth for wifi config

#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__
#define COMPILE_SIZE ESP.getSketchSize()

using namespace HgmApplication;


char* ssid = "trisuborn";
char* password = "12345678";
HgmApp* hgmApp;

//
//void setup()
//{
//	/* Base init */
//	Serial.begin(115200);
//	Serial.printf("\n********** Hell Gate Monitor **********\n");
//	Serial.printf("Date     : %s %s\n", COMPILE_DATE, COMPILE_TIME);
//	Serial.printf("ESP-IDF  : %x\n", ESP_IDF_VERSION); 
//	Serial.printf("FreeRTOS : %s\n", tskKERNEL_VERSION_NUMBER);
//	Serial.printf("LVGL     : %d\n", 0);
//	Serial.printf("***************************************\n");
//
//	//hgmApp = new HgmApp(ssid, password);
//	//hgmApp->Begin();
//}
//
//void loop()
//{
//	vTaskDelay(10 * 1000);		// 10 sec
//}

#include "BluetoothSerial.h"


BluetoothSerial SerialBT;

void setup()
{
    Serial.begin(115200);

    /* Base init */
	Serial.printf("\n********** Hell Gate Monitor **********\n");
	Serial.printf("Date     : %s %s\n", COMPILE_DATE, COMPILE_TIME);
	Serial.printf("ESP-IDF  : %x\n", ESP_IDF_VERSION); 
	Serial.printf("FreeRTOS : %s\n", tskKERNEL_VERSION_NUMBER);
	Serial.printf("LVGL     : %d\n", 0);
	Serial.printf("***************************************\n");

    Serial.printf("%d\n", ESP.getFlashChipSize());
    Serial.printf("%d\n", ESP.getHeapSize());
    Serial.printf("%d\n", ESP.getPsramSize());
    Serial.printf("%d\n", ESP.getSketchSize());

	hgmApp = new HgmApp(ssid, password);
	hgmApp->Begin();


    SerialBT.begin("ESP32test"); //蓝牙模块名称
}


uint8_t buf[512];
void loop()
{
    
    memset(buf, 0, 512);
    if (SerialBT.available()) {
        /*String str = SerialBT.readString();
        Serial.println(str.c_str());*/

        int i = 0;
        while (SerialBT.available()) {
            buf[i] = SerialBT.read();
            i++;
        }
        Serial.printf("%s\n", buf);
    }

    vTaskDelay(100);

}