#include <Arduino.h>
#include <ESP_Panel_Library.h>



void setup() {
	analogWrite(5,200);
	Serial.begin(115200);
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

}

void loop() {
	delay(500);
	analogWrite(5,200);
	//Serial.println(millis());
	delay(500);
	analogWrite(5,50);
}
