#include <Arduino.h>
#include <ESP_Panel_Library.h>
#include <ESP_IOExpander_Library.h>
#pragma region TOUCH
#include <Wire.h>
#include "TouchDrvCSTXXX.hpp"

#ifndef SENSOR_SDA
#define SENSOR_SDA  1
#endif

#ifndef SENSOR_SCL
#define SENSOR_SCL  3
#endif

#ifndef SENSOR_IRQ
#define SENSOR_IRQ  4
#endif

#ifndef SENSOR_RST
#define SENSOR_RST  -1
#endif

TouchDrvCSTXXX touch;
int16_t x[5], y[5];

void scanDevices(void)
{
    byte error, address;
    int nDevices = 0;
    Serial.println("Scanning for I2C devices ...");
    for (address = 0x01; address < 0x7f; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0) {
            Serial.printf("I2C device found at address 0x%02X\n", address);
            nDevices++;
        } else if (error != 2) {
            Serial.printf("Error %d at address 0x%02X\n", error, address);
        }
    }
    if (nDevices == 0) {
        Serial.println("No I2C devices found");
    }
}

#pragma endregion

ESP_Panel *panel = nullptr;
ESP_PanelLcd *lcd = nullptr;
//ESP_PanelTouch *touch = nullptr;
ESP_IOExpander *expander = nullptr;



void setup() {
	analogWrite(5,200);

	//Mostly to kick Serial0 off of it
	pinMode(43,OUTPUT);
	pinMode(44,OUTPUT);

	Serial.begin(115200);
	Serial.setDebugOutput(true);

	/*
	Serial.println("QSPI LCD example start");
	Serial.println("Create QSPI LCD bus");
	ESP_PanelBus_QSPI *panel_bus = new ESP_PanelBus_QSPI(	ESP_PANEL_LCD_SPI_IO_CS,
															ESP_PANEL_LCD_SPI_IO_SCK,
															ESP_PANEL_LCD_SPI_IO_DATA0,
															ESP_PANEL_LCD_SPI_IO_DATA1,
															ESP_PANEL_LCD_SPI_IO_DATA2,
															ESP_PANEL_LCD_SPI_IO_DATA3);
	panel_bus->configQspiFreqHz(ESP_PANEL_LCD_SPI_CLK_HZ);
	panel_bus->begin();
	ESP_PanelLcd *lcd = new ESP_PanelLcd_ST77916(panel_bus,ESP_PANEL_LCD_COLOR_BITS,ESP_PANEL_LCD_IO_RST);
	lcd->init();
	lcd->begin();
	lcd->displayOn();
	lcd->colorBarTest(ESP_PANEL_LCD_WIDTH,ESP_PANEL_LCD_HEIGHT);
	*/
	Serial.println("Start panel");
	panel = new ESP_Panel();
    panel->init();
	panel->begin();
	lcd = panel->getLcd();
	// touch = panel->getTouch();
	// if (touch != nullptr) 
	// {
	// 	touch->attachInterruptCallback(onTouchInterruptCallback, NULL);
	// }
	Serial.println("Doing BGR test");
	lcd->colorBarTest(panel->getLcdWidth(),panel->getLcdHeight());
	expander = panel->getExpander();
	expander->printStatus();
	/*
	expander->pinMode(0, OUTPUT);
    expander->pinMode(1, OUTPUT);
    expander->multiPinMode(IO_EXPANDER_PIN_NUM_2 | IO_EXPANDER_PIN_NUM_3, OUTPUT);

    Serial.println("Set pint 0-3 to output mode:");
    expander->printStatus();

    expander->digitalWrite(0, LOW);
    expander->digitalWrite(1, LOW);
    expander->multiDigitalWrite(IO_EXPANDER_PIN_NUM_2 | IO_EXPANDER_PIN_NUM_3, LOW);

    Serial.println("Set pint 0-3 to low level:");
    expander->printStatus();

    expander->pinMode(0, INPUT);
    expander->pinMode(1, INPUT);
    expander->multiPinMode(IO_EXPANDER_PIN_NUM_2 | IO_EXPANDER_PIN_NUM_3, INPUT);

    Serial.println("Set pint 0-3 to input mode:");
    expander->printStatus();
	*/
	expander->pinMode(6,OUTPUT);
	//Serial.end();

	#pragma region TOUCH SETUP
		uint8_t address = 0xFF;
		Wire.begin(SENSOR_SDA, SENSOR_SCL,400000);
		scanDevices();

		Wire.beginTransmission(CST816_SLAVE_ADDRESS);
		if (Wire.endTransmission() == 0) {
			address = CST816_SLAVE_ADDRESS;
		}
		Wire.beginTransmission(CST226SE_SLAVE_ADDRESS);
		if (Wire.endTransmission() == 0) {
			address = CST226SE_SLAVE_ADDRESS;
		}
		Wire.beginTransmission(CST328_SLAVE_ADDRESS);
		if (Wire.endTransmission() == 0) {
			address = CST328_SLAVE_ADDRESS;
		}
		while (address == 0xFF) {
			Serial.println("Could't find touch chip!"); delay(1000);
		}

		touch.setPins(SENSOR_RST, SENSOR_IRQ);
		touch.begin(Wire, address, SENSOR_SDA, SENSOR_SCL);


		Serial.print("Model :"); Serial.println(touch.getModelName());

	#pragma endregion

}

void loop() {
	/* static bool val = HIGH;
	expander->digitalWrite(6,val);
	val = !val;
	analogWrite(5,200);
	delay(1000); */
	// if (touch != nullptr)
	// {
	// 	ESP_PanelTouchPoint point[1];
    //     int read_touch_result = touch->readPoints(point, 1, -1);
    //     if (read_touch_result > 0) {
    //         for (int i = 0; i < read_touch_result; i++) {
    //             Serial.printf("Touch point(%d): x %d, y %d, strength %d\n", i, point[i].x, point[i].y, point[i].strength);
    //         }
    //     } else if (read_touch_result < 0) {
    //         Serial.println("Read touch point failed");
    //     }
    //     // Delay for a while to avoid reading too frequently if the interrupt is not enabled
    //     if (!touch->isInterruptEnabled()) {
    //         delay(30);
    //     }
	// }
	/*delay(500);
	analogWrite(5,200);
	//Serial.println(millis());
	delay(500);
	analogWrite(5,50);*/
	//int val = 128 + 127*sin(2*PI*millis()/5000);
	//analogWrite(5,val);
	uint8_t touched = touch.getPoint(x, y, touch.getSupportTouchPoint());
    if (touched) {
        for (int i = 0; i < touched; ++i) {
            Serial.print("X[");
            Serial.print(i);
            Serial.print("]:");
            Serial.print(x[i]);
            Serial.print(" ");
            Serial.print(" Y[");
            Serial.print(i);
            Serial.print("]:");
            Serial.print(y[i]);
            Serial.print(" ");
        }
        Serial.println();
    }

    delay(5);
}
