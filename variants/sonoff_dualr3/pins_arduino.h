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

static const uint8_t BUTTON = 0;
static const uint8_t LED_LINK = 13;
static const uint8_t RELAY_2 = 14;
static const uint8_t RELAY_1 = 27;
static const uint8_t SWITCH_2 = 33;
static const uint8_t SWITCH_1 = 32;

static const uint8_t CSE7761_TX = 25;
static const uint8_t CSE7761_RX = 26;

#endif /* Pins_Arduino_h */
