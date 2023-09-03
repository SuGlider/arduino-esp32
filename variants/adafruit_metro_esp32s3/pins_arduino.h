#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>
#include "soc/soc_caps.h"

#define USB_VID            0x239A
#define USB_PID            0x8145
#define USB_MANUFACTURER   "Adafruit"
#define USB_PRODUCT        "Metro ESP32-S3"
#define USB_SERIAL         ""   // Empty string for MAC adddress

#define NUM_DIGITAL_PINS        SOC_GPIO_PIN_COUNT    // GPIO 0..48
#define NUM_ANALOG_INPUTS       20                    // GPIO 1..20
#define EXTERNAL_NUM_INTERRUPTS NUM_DIGITAL_PINS      // All GPIOs

#define analogInputToDigitalPin(p)  (((p)<NUM_ANALOG_INPUTS)?(analogChannelToDigitalPin(p)):-1)
#define digitalPinToInterrupt(p)    (((p)<NUM_DIGITAL_PINS)?(p):NOT_AN_INTERRUPT)
#define digitalPinHasPWM(p)         (p < NUM_DIGITAL_PINS)

#define PIN_NEOPIXEL    45
#define NEOPIXEL_PIN    45
// BUILTIN_LED can be used in new Arduino API digitalWrite() like in Blink.ino
static const uint8_t LED_BUILTIN = SOC_GPIO_PIN_COUNT+PIN_NEOPIXEL;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility
// RGB_BUILTIN and RGB_BRIGHTNESS can be used in new Arduino API neopixelWrite()
#define RGB_BUILTIN LED_BUILTIN
#define RGB_BRIGHTNESS 64

#define NEOPIXEL_NUM    1

#define PIN_BUTTON1     0  // BOOT0 switch

static const uint8_t TX = 40;
static const uint8_t RX = 41;
#define TX1 TX
#define RX1 RX

static const uint8_t SDA = 47;
static const uint8_t SCL = 48;

static const uint8_t SS   = 21;
static const uint8_t MOSI = 35;
static const uint8_t SCK  = 36;
static const uint8_t MISO = 37;

static const uint8_t A0 = 14;
static const uint8_t A1 = 15;
static const uint8_t A2 = 16;
static const uint8_t A3 = 17;
static const uint8_t A4 = 18;
static const uint8_t A5 = 1;

static const uint8_t A6 = 40;
static const uint8_t A7 = 41;
static const uint8_t A8 = 2;
static const uint8_t A9 = 3;
static const uint8_t A10 = 4;
static const uint8_t A11 = 5;
static const uint8_t A12 = 6;
static const uint8_t A13 = 7;
static const uint8_t A14 = 8;
static const uint8_t A15 = 9;
static const uint8_t A16 = 10;
static const uint8_t A17 = 11;
static const uint8_t A18 = 12;
static const uint8_t A19 = 13;

static const uint8_t T1 = 1;
static const uint8_t T2 = 2;
static const uint8_t T3 = 3;
static const uint8_t T4 = 4;
static const uint8_t T5 = 5;
static const uint8_t T6 = 6;
static const uint8_t T7 = 7;
static const uint8_t T8 = 8;
static const uint8_t T9 = 9;
static const uint8_t T10 = 10;
static const uint8_t T11 = 11;
static const uint8_t T12 = 12;
static const uint8_t T13 = 13;
static const uint8_t T14 = 14;

#endif /* Pins_Arduino_h */
