#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <SD.h>
#include <time.h>
#include <Keypad.h>

typedef struct chip_context {
  u8 memory[Kilobytes(4)];
  u8 V[16];
  u16 stack[16];

  //registers
  u16 I;
  u16 PC;
  u8 SP;
  u8 delay;
  u8 sound;

  
}chip_context;

const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
  {'1', '2', '3', 'c'},
  {'4', '5', '6', 'd'},
  {'7', '8', '9', 'e'},
  {'a', '0', 'b', 'f'}
};

byte rowPins[rows] = {2, 4, 5, 6};
byte colPins[cols] = {7, 8, 9, 10};

Keypad keypad = Keypad( makeKeymap(keys), rowpins, colsPins, rows, cols);


// Display pins (see back of board)
#define TFT_CS   0
#define TFT_DC   45
#define TFT_RST  1
#define TFT_SCLK 46
#define TFT_MOSI 3
#define TFT_MISO -1 // unused
const int buzzerPin = 48;
const int chipSelecct = 40;

File root;

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // put your setup code here, to run once:
  SPI.begin(TFT_SCLK, TFT_MISO, TFT_MOSI);
  tft.init(240, 320);
  tft.setRotation(1); // 320x240 landscape
  tft.fillScreen(ST77XX_BLACK);

  if (!begin(40)) {
    tft.setCursor(0, 120);
    tft.print("initFail");
  }
  int k = 0;
  romFile = SD.open("2-ibm-logo.ch8");
  if (romFile) {
    while (romFile.available()) {
      memory[0x200 + k] = romFile.read();
      k++;
    }
    romFile.close();
  }
  else {
    tft.print("file not found");
  }
}

void loop() {
  
}
