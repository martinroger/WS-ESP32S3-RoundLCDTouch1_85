#include <Arduino.h>
#include <ESP_Panel_Library.h>
#include <ESP_IOExpander_Library.h>

ESP_Panel *panel = nullptr;
ESP_PanelLcd *lcd = nullptr;
//ESP_PanelTouch *touch = nullptr;
//ESP_IOExpander *expander = nullptr;
ESP_PanelBacklight *backLight = nullptr;

// IRAM_ATTR bool onTouchInterruptCallback(void *user_data)
// {
//     esp_rom_printf("Touch interrupt callback\n");

//     return false;
// }

void setup() {
	
	Serial.begin(115200);
	Serial.setDebugOutput(true);

	Serial.println("Start panel");
	panel = new ESP_Panel();
    panel->init();
	panel->begin();
	lcd = panel->getLcd();
	// touch = panel->getTouch();
	backLight = panel->getBacklight();
	backLight->setBrightness(80);
	Serial.println("Doing BGR test");
	lcd->colorBarTest(panel->getLcdWidth(),panel->getLcdHeight());
	// expander = panel->getExpander();
	// expander->printStatus();
	// touch->attachInterruptCallback(onTouchInterruptCallback, NULL);

}

void loop() {

	delay(5);
}
