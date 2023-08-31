#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

#define NUM_DIGITAL_PINS        SOC_GPIO_PIN_COUNT    // GPIO 0..39
#define NUM_ANALOG_INPUTS       16                    // ESP32 has 16 ADC pins
#define EXTERNAL_NUM_INTERRUPTS NUM_DIGITAL_PINS      // All GPIOs

#define analogInputToDigitalPin(p)  (((p)<NUM_ANALOG_INPUTS)?(analogChannelToDigitalPin(p)):-1)
#define digitalPinToInterrupt(p)    (((p)<NUM_DIGITAL_PINS)?(p):NOT_AN_INTERRUPT)
#define digitalPinHasPWM(p)         (p < 34)  // PWM only for GPIO0..33 - NOT GPIO 34,35,36 and 39

static const uint8_t LED_BUILTIN = 13;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility

static const uint8_t TX = 17;
static const uint8_t RX = 16;

static const uint8_t SDA = 23;
static const uint8_t SCL = 22;

static const uint8_t SS    = 2;
static const uint8_t MOSI  = 18;
static const uint8_t MISO  = 19;
static const uint8_t SCK   = 5;


static const uint8_t A0 = 34; 
static const uint8_t A1 = 39;
static const uint8_t A2 = 36;
static const uint8_t A3 = 33;

static const uint8_t D0 = 4; 
static const uint8_t D1 = 16;
static const uint8_t D2 = 17;
static const uint8_t D3 = 22;
static const uint8_t D4 = 23;
static const uint8_t D5 = 5;
static const uint8_t D6 = 18;
static const uint8_t D7 = 19;
static const uint8_t D8 = 33;

// vbat measure
static const uint8_t VBAT = 35;


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
