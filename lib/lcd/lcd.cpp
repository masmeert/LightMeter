#include <Adafruit_SSD1306.h>
#include <math.h>

#include <constants.h>
#include <computation.h>

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
    display.print("f/");
    display.println(aperture, 1);
    display.print(shutter_speed, 3);
    display.print("s");

    display.setTextSize(1);
    display.setCursor(75, 0);
    display.print("ISO:");
    display.println(FILM_ISO);
    display.setCursor(75, 8);
    display.print("EV:");
    display.println(EV);

    display.display();
}