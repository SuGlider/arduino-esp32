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

// LED
static const uint8_t LED_BUILTIN = 13;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility

// UART
static const uint8_t TX = 10;
static const uint8_t RX = 9;

// I2C
static const uint8_t SDA = 23;
static const uint8_t SCL = 22;

// SPI
static const uint8_t SS    = 21;
static const uint8_t MOSI  = 18;
static const uint8_t MISO  = 19;
static const uint8_t SCK   = 5;

// Analog Inputs
static const uint8_t A0 = 4; 
static const uint8_t A1 = 25;
static const uint8_t A2 = 26;
static const uint8_t A3 = 27;
static const uint8_t A4 = 32;
static const uint8_t A5 = 33;
static const uint8_t A6 = 34;
static const uint8_t A7 = 35;
static const uint8_t A8 = 38;

// Right side
static const uint8_t T0 = 4;
static const uint8_t T1 = 25;
static const uint8_t T2 = 26;
static const uint8_t T3 = 27;
static const uint8_t T4 = 32;
static const uint8_t T5 = 33;
static const uint8_t T6 = 34;
static const uint8_t T7 = 35;

// Left side
static const uint8_t T8 = 22;
static const uint8_t T9 = 23;
static const uint8_t T10 = 10;
static const uint8_t T11 = 9;
static const uint8_t T12 = 21;
static const uint8_t T13 = 5;
static const uint8_t T14 = 18;
static const uint8_t T15 = 19;

// Module
static const uint8_t T16 = 37;
static const uint8_t T17 = 14;
static const uint8_t T18 = 2;
static const uint8_t T19 = 38;

// DAC
static const uint8_t DAC1 = 25;
static const uint8_t DAC2 = 26;

#endif /* Pins_Arduino_h */
