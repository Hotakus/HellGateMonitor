
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <User_Setup.h>
#include <User_Setup_Select.h>
#include <I2C_MPU6886.h>

/* User include files */
#include "./Source/HgmControl/HgmControlLogic.h"
#include "./Source/HgmLvgl/HgmLvgl.h"

using namespace HGM;

HgmControlLogic* hcl = new HgmControlLogic(Wire1);
TFT_eSPI* lcd = new TFT_eSPI(240, 320);


void setup()
{
	/* Base init */
	Serial.begin(115200);
	Wire1.begin(21, 22);

	/* Hgm Control init */
	hcl->HgmControlBegin();
	Serial.printf("0x%X\n", hcl->imu->whoAmI());


	HgmLvgl *hgmLvgl = new HgmLvgl();
	hgmLvgl->HgmLvglBegin();
}

void loop()
{
	hcl->AnalyzeTask();
	vTaskDelay(50);		// use FreeRTOS
}
