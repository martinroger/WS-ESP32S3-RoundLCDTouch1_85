#include <Arduino.h>
#include <ESP_Panel_Library.h>
#include <ESP_IOExpander_Library.h>

ESP_Panel *panel = nullptr;
ESP_PanelLcd *lcd = nullptr;
ESP_PanelTouch *touch = nullptr;
ESP_IOExpander *expander = nullptr;

IRAM_ATTR bool onTouchInterruptCallback(void *user_data)
{
    esp_rom_printf("Touch interrupt callback\n");

    return false;
}

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
	touch = panel->getTouch();
	// if (touch != nullptr) 
	// {
	// 	touch->attachInterruptCallback(onTouchInterruptCallback, NULL);
	// }
	Serial.println("Doing BGR test");
	lcd->colorBarTest(panel->getLcdWidth(),panel->getLcdHeight());
	expander = panel->getExpander();
	expander->printStatus();
	touch->attachInterruptCallback(onTouchInterruptCallback, NULL);
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
	//Serial.end();

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
	
}
