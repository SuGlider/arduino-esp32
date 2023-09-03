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

static const uint8_t TX = 1;
static const uint8_t RX = 3;

static const uint8_t TXD1 = 14;
static const uint8_t RXD1 = 13;

static const uint8_t TXD2 = 17;
static const uint8_t RXD2 = 16;

static const uint8_t SDA = 32;
static const uint8_t SCL = 33;

static const uint8_t SS   = 5;
static const uint8_t MOSI = 23;
static const uint8_t MISO = -1;
static const uint8_t SCK  = 18;

static const uint8_t G1  = 1;
static const uint8_t G3  = 3;
static const uint8_t G4  = 4;
static const uint8_t G5  = 5;
static const uint8_t G13 = 13;
static const uint8_t G14 = 14;
static const uint8_t G16 = 16;
static const uint8_t G17 = 17;
static const uint8_t G18 = 18;
static const uint8_t G19 = 19;
static const uint8_t G23 = 23;
static const uint8_t G25 = 25;
static const uint8_t G26 = 26;
static const uint8_t G32 = 32;
static const uint8_t G33 = 33;
static const uint8_t G35 = 35;
static const uint8_t G36 = 36;
static const uint8_t G37 = 37;
static const uint8_t G38 = 38;
static const uint8_t G39 = 39;

static const uint8_t DAC1 = 25;
static const uint8_t DAC2 = 26;

static const uint8_t ADC1 = 35;
static const uint8_t ADC2 = 36;

#endif /* Pins_Arduino_h */
