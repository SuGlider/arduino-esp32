#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>
#include "soc/soc_caps.h"

#define NUM_DIGITAL_PINS        SOC_GPIO_PIN_COUNT    // GPIO 0..39
#define NUM_ANALOG_INPUTS       16                    // ESP32 has 16 ADC pins
#define EXTERNAL_NUM_INTERRUPTS NUM_DIGITAL_PINS      // All GPIOs

#define analogInputToDigitalPin(p)  (((p)<NUM_ANALOG_INPUTS)?(analogChannelToDigitalPin(p)):-1)
#define digitalPinToInterrupt(p)    (((p)<NUM_DIGITAL_PINS)?(p):NOT_AN_INTERRUPT)
#define digitalPinHasPWM(p)         (p < 34)  // PWM only for GPIO0..33 - NOT GPIO 34,35,36 and 39

// Neopixel
#define PIN_NEOPIXEL 0
// BUILTIN_LED can be used in new Arduino API digitalWrite() like in Blink.ino
static const uint8_t LED_BUILTIN = (PIN_NEOPIXEL + SOC_GPIO_PIN_COUNT);
#define BUILTIN_LED  LED_BUILTIN // backward compatibility
// RGB_BUILTIN and RGB_BRIGHTNESS can be used in new Arduino API neopixelWrite()
#define RGB_BUILTIN LED_BUILTIN
#define RGB_BRIGHTNESS 64

static const uint8_t TX = 8;
static const uint8_t RX = 7;
#define TX1 TX
#define RX1 RX

static const uint8_t SDA = 22;
static const uint8_t SCL = 20;

static const uint8_t SS    = 33;
static const uint8_t MOSI  = 19;
static const uint8_t MISO  = 21;
static const uint8_t SCK   = 5;

// mapping to match other feathers and also in order
static const uint8_t A0 = 26; 
static const uint8_t A1 = 25;
static const uint8_t A2 = 34;
static const uint8_t A3 = 39;
static const uint8_t A4 = 36;
static const uint8_t A5 = 4;
static const uint8_t A6 = 14;
static const uint8_t A7 = 32;
static const uint8_t A8 = 15;
static const uint8_t A9 = 33;
static const uint8_t A10 = 27;
static const uint8_t A11 = 12;
static const uint8_t A12 = 13;
static const uint8_t A13 = 35;

// vbat measure
#define BATT_MONITOR 35

// internal switch
#define BUTTON 38

// Neopixel & I2C power
#define NEOPIXEL_I2C_POWER 2

static const uint8_t T0 = 4;
static const uint8_t T1 = 0;
static const uint8_t T2 = 2;
static const uint8_t T3 = 15;
static const uint8_t T4 = 13;
static const uint8_t T5 = 12;
static const uint8_t T6 = 14;
static const uint8_t T7 = 27;
static const uint8_t T8 = 33;
static const uint8_t T9 = 32;

static const uint8_t DAC1 = 25;
static const uint8_t DAC2 = 26;

#endif /* Pins_Arduino_h */
