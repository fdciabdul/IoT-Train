# DHT 11 + ST 7789 DISPLAY

make sure if the display didnt have CS pin

disable in user_setup.h


```c

#define ST7789_DRIVER

// Define display dimensions
#define TFT_WIDTH  240
#define TFT_HEIGHT 240

// Define ESP8266 pins connected to display
#define TFT_MOSI 13  // GPIO13 (D7)
#define TFT_SCLK 14  // GPIO14 (D5)
#define TFT_DC   5   // GPIO5  (D1)
#define TFT_RST  16  // GPIO16 (D0)
#define TFT_CS   -1  // CS pin not used (-1 disables it)

// Color byte order - try both if colors appear incorrect
#define TFT_RGB_ORDER TFT_RGB  // Swap to TFT_BGR if colors are reversed

// Optionally enable display inversion
// #define TFT_INVERSION_ON  // Uncomment if display appears negative

// Load the required fonts (comment out ones you don't need to save memory)
#define LOAD_GLCD   // Standard ASCII font
#define LOAD_FONT2  // Small font
#define LOAD_FONT4  // Medium font
#define LOAD_FONT6  // Large font
#define LOAD_FONT7  // 7-segment style font
#define LOAD_FONT8  // Large numeric font
#define LOAD_GFXFF  // FreeFonts

// SPI frequency settings
#define SPI_FREQUENCY  27000000  // Standard SPI speed (reduce if unstable)
#define SPI_READ_FREQUENCY  20000000  // Speed for reading data
#define SPI_TOUCH_FREQUENCY  2500000  // For touch controllers if used

```