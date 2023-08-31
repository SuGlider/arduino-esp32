#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

#define NUM_DIGITAL_PINS        SOC_GPIO_PIN_COUNT    // GPIO 0..39
#define NUM_ANALOG_INPUTS       16                    // ESP32 has 16 ADC pins
#define EXTERNAL_NUM_INTERRUPTS NUM_DIGITAL_PINS      // All GPIOs

#define analogInputToDigitalPin(p)  (((p)<NUM_ANALOG_INPUTS)?(analogChannelToDigitalPin(p)):-1)
#define digitalPinToInterrupt(p)    (((p)<NUM_DIGITAL_PINS)?(p):NOT_AN_INTERRUPT)
#define digitalPinHasPWM(p)         (p < 34)  // PWM only for GPIO0..33 - NOT GPIO 34,35,36 and 39

// I2C OLED Display works with SSD1306 driver
#define OLED_SDA    21
#define OLED_SCL    22
#define OLED_RST    16

// SPI LoRa Radio
#define LORA_SCK    5   // GPIO5 - SX1276 SCK
#define LORA_MISO   19  // GPIO19 - SX1276 MISO
#define LORA_MOSI   27  // GPIO27 - SX1276 MOSI
#define LORA_CS     18  // GPIO18 - SX1276 CS
#define LORA_RST    12  // GPIO14 - SX1276 RST
#define LORA_IRQ    26  // GPIO26 - SX1276 IRQ (interrupt request)

// SD card
#define SD_SCK  14
#define SD_MISO 2
#define SD_MOSI 15
#define SD_CS   13

static const uint8_t LED_BUILTIN =  22;
#define BUILTIN_LED  LED_BUILTIN    // backward compatibility

static const uint8_t KEY_BUILTIN =  0;

static const uint8_t TX =   1;
static const uint8_t RX =   3;

static const uint8_t SDA =  21;
static const uint8_t SCL =  22;

static const uint8_t SS =   18;
static const uint8_t MOSI = 27;
static const uint8_t MISO = 19;
static const uint8_t SCK =  5;

static const uint8_t A0 =   36;
static const uint8_t A1 =   37;
static const uint8_t A2 =   38;
static const uint8_t A3 =   39;
static const uint8_t A4 =   32;
static const uint8_t A5 =   33;
static const uint8_t A6 =   34;
static const uint8_t A7 =   35;
static const uint8_t A10 =  4;
static const uint8_t A11 =  0;
static const uint8_t A12 =  2;
static const uint8_t A13 =  15;
static const uint8_t A14 =  13;
static const uint8_t A15 =  12;
static const uint8_t A16 =  14;
static const uint8_t A17 =  27;
static const uint8_t A18 =  25;
static const uint8_t A19 =  26;

static const uint8_t T0 =   4;
static const uint8_t T1 =   0;
static const uint8_t T2 =   2;
static const uint8_t T3 =   15;
static const uint8_t T4 =   13;
static const uint8_t T5 =   12;
static const uint8_t T6 =   14;
static const uint8_t T7 =   27;
static const uint8_t T8 =   33;
static const uint8_t T9 =   32;

static const uint8_t DAC1 = 25;
static const uint8_t DAC2 = 26;

#endif /* Pins_Arduino_h */
