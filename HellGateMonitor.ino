
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <User_Setup.h>
#include <User_Setup_Select.h>

#include <I2C_MPU6886.h>

#include "./Source/HgmControl/HgmControlLogic.h"

using namespace HGM;

HgmControlLogic* hcl = new HgmControlLogic(Wire1);
TFT_eSPI* lcd = new TFT_eSPI(240, 320);

void setup()
{
	Serial.begin(115200);
	
	/* LCD init */
	lcd->begin();
	lcd->fillScreen(TFT_RED);

	Wire1.begin(21, 22);
	hcl->HgmCtlBegin();
	Serial.printf("0x%X\n", hcl->imu->whoAmI());
}

void loop()
{
	Serial.printf("Test\n");
	delay(100);
}
