#include <Adafruit_SSD1306.h>
#include <math.h>

#include <constants.h>
#include <types.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

constexpr uint8_t TEXT_COLOR = SSD1306_WHITE;
constexpr uint8_t LARGE_TEXT_SIZE = 2;
constexpr uint8_t SMALL_TEXT_SIZE = 1;
constexpr uint8_t COLUMN_1_X = 0;
constexpr uint8_t COLUMN_2_X = 75;
constexpr uint8_t ROW_1_Y = 0;
constexpr uint8_t ROW_2_Y = 16;

void setup_display()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("Failed to initialize SSD1306 display.");
        return;
    }
    display.clearDisplay();
    display.display();
}

void display_values(LightMeterSettings &settings, float EV)
{
    display.clearDisplay();
    display.setTextColor(TEXT_COLOR);

    // Display aperture and shutter speed
    display.setTextSize(LARGE_TEXT_SIZE);
    display.setCursor(COLUMN_1_X, ROW_1_Y);
    display.print("f/");
    display.print(settings.aperture, 1);

    display.setCursor(COLUMN_1_X, ROW_2_Y);
    display.print(settings.shutter_speed, 3);
    display.print("s");

    display.setTextSize(SMALL_TEXT_SIZE);
    display.setCursor(COLUMN_2_X, ROW_1_Y);
    display.print("ISO:");
    display.println(FILM_ISO);
    display.setCursor(COLUMN_2_X, ROW_1_Y + 8);
    display.print("EV:");
    display.println(EV, 1);
    display.display();
}
