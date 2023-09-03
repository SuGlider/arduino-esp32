#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>
#include "soc/soc_caps.h"

#define NUM_DIGITAL_PINS        SOC_GPIO_PIN_COUNT    // GPIO 0..21 - not all are available
#define NUM_ANALOG_INPUTS       6                     // GPIO 0..5
#define EXTERNAL_NUM_INTERRUPTS NUM_DIGITAL_PINS      // All GPIOs

#define analogInputToDigitalPin(p)  (((p)<NUM_ANALOG_INPUTS)?(analogChannelToDigitalPin(p)):-1)
#define digitalPinToInterrupt(p)    (((p)<NUM_DIGITAL_PINS)?(p):NOT_AN_INTERRUPT)
#define digitalPinHasPWM(p)         (p < EXTERNAL_NUM_INTERRUPTS)

static const uint8_t TX = 21;
static const uint8_t RX = 20;

static const uint8_t TX1 = 0;
static const uint8_t RX1 = 1;

static const uint8_t SDA = 5;
static const uint8_t SCL = 6;

static const uint8_t SS    = 20;
static const uint8_t MOSI  = 10;
static const uint8_t MISO  = 9;
static const uint8_t SCK   = 8;

static const uint8_t A0 = 2;
static const uint8_t A1 = 3;
static const uint8_t A2 = 4;
static const uint8_t A3 = 5;

static const uint8_t D0 = 2;
static const uint8_t D1 = 3;
static const uint8_t D2 = 4;
static const uint8_t D3 = 5;
static const uint8_t D4 = 6;
static const uint8_t D5 = 7;
static const uint8_t D6 = 21;
static const uint8_t D7 = 20;
static const uint8_t D8 = 8;
static const uint8_t D9 = 9;
static const uint8_t D10 = 10;

static const uint8_t GPIO_IIC_DATA   = 5;
static const uint8_t GPIO_IIC_CLOCK  = 6;
static const uint8_t GPIO_PWRKEY     = 7;
static const uint8_t GPIO_GSM_ENABLE = 10;
static const uint8_t GPIO_TPS_ENABLE = 4;
static const uint8_t GPIO_INT1       = 3;
static const uint8_t GPIO_ANALOG_IN  = 2;
static const uint8_t GPIO_SOS        = 9;
static const uint8_t GPIO_CHG_IN     = 4;
static const uint8_t GPIO_LED_SIGNAL = 8;


#endif /* Pins_Arduino_h */
