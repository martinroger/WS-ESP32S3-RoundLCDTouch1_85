#include <Arduino.h>
#include <ESP_Panel_Library.h>
#include <ESP_IOExpander_Library.h>

ESP_Panel *panel = nullptr;
ESP_PanelLcd *lcd = nullptr;
ESP_PanelTouch *touch = nullptr;
ESP_IOExpander *expander = nullptr;
ESP_PanelBacklight *backLight = nullptr;

// IRAM_ATTR bool onTouchInterruptCallback(void *user_data)
// {
//     esp_rom_printf("Touch interrupt callback\n");

//     return false;
// }

void setup() {
	// analogWrite(5,200);

	//Mostly to kick Serial0 off of it
	// pinMode(43,OUTPUT);
	// pinMode(44,OUTPUT);

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
	// backLight = panel->getBacklight();
	// backLight->setBrightness(50);
	Serial.println("Doing BGR test");
	lcd->colorBarTest(panel->getLcdWidth(),panel->getLcdHeight());
	expander = panel->getExpander();
	expander->printStatus();
	expander->pinMode(1,OUTPUT);
	pinMode(6,OUTPUT);

	//touch->attachInterruptCallback(onTouchInterruptCallback, NULL);

	// backLight->setBrightness(100);
	
}

void loop() {
	//analogWrite(6,127+127*sin(millis()*2*PI/10000));
	expander->digitalWrite(1,HIGH);
	digitalWrite(6,HIGH);
	delay(1000);
	digitalWrite(6,LOW);
	//expander->printStatus();
	delay(2000);
	expander->digitalWrite(1,LOW);
	digitalWrite(6,HIGH);
	delay(1000);
	digitalWrite(6,LOW);
	//expander->printStatus();
	delay(3000);
}
