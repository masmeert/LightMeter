#include <constants.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void setup_display()
{
    if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("Failed to initialize SSD1306 display.");
        return;
    }
    display.clearDisplay();
    display.display();
}

void display_values(float EV, float shutter_speed, float aperture)
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(1);

    display.setCursor(0, 0);
    display.println(aperture);
    display.println(shutter_speed, 4);

    display.setTextSize(1);
    display.setCursor(60, 0);
    display.print("ISO: ");
    display.println(ISO);
    display.setCursor(60, 8);
    display.print("EV:");
    display.println(EV);

    display.display();
}