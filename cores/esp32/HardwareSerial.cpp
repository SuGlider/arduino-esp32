#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "pins_arduino.h"
#include "HardwareSerial.h"
#include "soc/soc_caps.h"

#ifndef SOC_RX0
#if CONFIG_IDF_TARGET_ESP32
#define SOC_RX0 3
#elif CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3
#define SOC_RX0 44
#elif CONFIG_IDF_TARGET_ESP32C3
#define SOC_RX0 20
#endif
#endif

#ifndef SOC_TX0
#if CONFIG_IDF_TARGET_ESP32
#define SOC_TX0 1
#elif CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3
#define SOC_TX0 43
#elif CONFIG_IDF_TARGET_ESP32C3
#define SOC_TX0 21
#endif
#endif

void serialEvent(void) __attribute__((weak));
void serialEvent(void) {}

#if SOC_UART_NUM > 1

#ifndef RX1
#if CONFIG_IDF_TARGET_ESP32
#define RX1 9
#elif CONFIG_IDF_TARGET_ESP32S2 
#define RX1 18
#elif CONFIG_IDF_TARGET_ESP32C3
#define RX1 18
#elif CONFIG_IDF_TARGET_ESP32S3
#define RX1 15
#endif
#endif

#ifndef TX1
#if CONFIG_IDF_TARGET_ESP32
#define TX1 10
#elif CONFIG_IDF_TARGET_ESP32S2
#define TX1 17
#elif CONFIG_IDF_TARGET_ESP32C3
#define TX1 19
#elif CONFIG_IDF_TARGET_ESP32S3
#define TX1 16
#endif
#endif

void serialEvent1(void) __attribute__((weak));
void serialEvent1(void) {}
#endif /* SOC_UART_NUM > 1 */

#if SOC_UART_NUM > 2
#ifndef RX2
#if CONFIG_IDF_TARGET_ESP32
#define RX2 16
#elif CONFIG_IDF_TARGET_ESP32S3
#define RX2 19 
#endif
#endif

#ifndef TX2
#if CONFIG_IDF_TARGET_ESP32
#define TX2 17
#elif CONFIG_IDF_TARGET_ESP32S3
#define TX2 20
#endif
#endif

void serialEvent2(void) __attribute__((weak));
void serialEvent2(void) {}
#endif /* SOC_UART_NUM > 2 */

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL)
#if ARDUINO_USB_CDC_ON_BOOT //Serial used for USB CDC
HardwareSerial Serial0(0);
#elif ARDUINO_HW_CDC_ON_BOOT
HardwareSerial Serial0(0);
#else
HardwareSerial Serial(0);
#endif
#if SOC_UART_NUM > 1
HardwareSerial Serial1(1);
#endif
#if SOC_UART_NUM > 2
HardwareSerial Serial2(2);
#endif

void serialEventRun(void)
{
#if ARDUINO_USB_CDC_ON_BOOT //Serial used for USB CDC
    if(Serial0.available()) serialEvent();
#elif ARDUINO_HW_CDC_ON_BOOT
    if(Serial0.available()) serialEvent();
#else
    if(Serial.available()) serialEvent();
#endif
#if SOC_UART_NUM > 1
    if(Serial1.available()) serialEvent1();
#endif
#if SOC_UART_NUM > 2
    if(Serial2.available()) serialEvent2();
#endif
}
#endif

HardwareSerial::HardwareSerial(int uart_nr) : _uart_nr(uart_nr), _uart(NULL), _rxBufferSize(256) {}

enum { UART_NUM_0, UART_NUM_1, UART_NUM_2 };

void HardwareSerial::begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert, unsigned long timeout_ms, uint8_t rxfifo_full_thrhd)
{
    if(0 > _uart_nr || _uart_nr >= SOC_UART_NUM) {
        log_e("Serial number is invalid, please use numers from 0 to %u", SOC_UART_NUM - 1);
        return;
    }

    // First Time or after end() --> set default Pins
    if (!uartIsDriverInstalled(_uart)) {
        switch (_uart_nr) {
            case UART_NUM_0:
                rxPin = rxPin < 0 ? SOC_RX0 : rxPin;
                txPin = txPin < 0 ? SOC_TX0 : txPin;
            break;
#if SOC_UART_NUM > 1                   // may save some flash bytes...
            case UART_NUM_1:
                rxPin = rxPin < 0 ? RX1 : rxPin;
                txPin = txPin < 0 ? TX1 : txPin;
            break;
#endif
#if SOC_UART_NUM > 2                   // may save some flash bytes...
            case UART_NUM_2:
                rxPin = rxPin < 0 ? RX2 : rxPin;
                txPin = txPin < 0 ? TX2 : txPin;
            break;
#endif
        }
    }

    if(_uart) {
        // in this case it is a begin() over a previous begin() - maybe to change baud rate
        // thus do not disable debug output
        end(false);
    }

    // IDF UART driver keeps Pin setting on restarting. Negative Pin number will keep it unmodified.
    _uart = uartBegin(_uart_nr, baud ? baud : 9600, config, rxPin, txPin, _rxBufferSize, invert, rxfifo_full_thrhd);
    if (!baud) {
        // using baud rate as zero, forces it to try to detect the current baud rate in place
        uartStartDetectBaudrate(_uart);
        time_t startMillis = millis();
        unsigned long detectedBaudRate = 0;
        while(millis() - startMillis < timeout_ms && !(detectedBaudRate = uartDetectBaudrate(_uart))) {
            yield();
        }

        end(false);

        if(detectedBaudRate) {
            delay(100); // Give some time...
            _uart = uartBegin(_uart_nr, detectedBaudRate, config,  rxPin, txPin, _rxBufferSize, invert, rxfifo_full_thrhd);
        } else {
            log_e("Could not detect baudrate. Serial data at the port must be present within the timeout for detection to be possible");
            _uart = NULL;
        }
    }
}

void HardwareSerial::onReceive(void(*function)(void))
{
    uartOnReceive(_uart, function);
}

void HardwareSerial::updateBaudRate(unsigned long baud)
{
	uartSetBaudRate(_uart, baud);
}

void HardwareSerial::end(bool turnOffDebug)
{
    if(turnOffDebug && uartGetDebug() == _uart_nr) {
        uartSetDebug(0);
    }
    delay(10);
    uartEnd(_uart);
    _uart = 0;
}

void HardwareSerial::setDebugOutput(bool en)
{
    if(_uart == 0) {
        return;
    }
    if(en) {
        uartSetDebug(_uart);
    } else {
        if(uartGetDebug() == _uart_nr) {
            uartSetDebug(NULL);
        }
    }
}

int HardwareSerial::available(void)
{
    return uartAvailable(_uart);
}
int HardwareSerial::availableForWrite(void)
{
    return uartAvailableForWrite(_uart);
}

int HardwareSerial::peek(void)
{
    if (available()) {
        return uartPeek(_uart);
    }
    return -1;
}

int HardwareSerial::read(void)
{
    if(available()) {
        return uartRead(_uart);
    }
    return -1;
}

// read characters into buffer
// terminates if size characters have been read, or no further are pending
// returns the number of characters placed in the buffer
// the buffer is NOT null terminated.
size_t HardwareSerial::read(uint8_t *buffer, size_t size)
{
    size_t avail = available();
    if (size < avail) {
        avail = size;
    }
    size_t count = 0;
    while(count < avail) {
        *buffer++ = uartRead(_uart);
        count++;
    }
    return count;
}

void HardwareSerial::flush(void)
{
    uartFlush(_uart);
}

void HardwareSerial::flush(bool txOnly)
{
    uartFlushTxOnly(_uart, txOnly);
}

size_t HardwareSerial::write(uint8_t c)
{
    uartWrite(_uart, c);
    return 1;
}

size_t HardwareSerial::write(const uint8_t *buffer, size_t size)
{
    uartWriteBuf(_uart, buffer, size);
    return size;
}
uint32_t  HardwareSerial::baudRate()

{
	return uartGetBaudRate(_uart);
}
HardwareSerial::operator bool() const
{
    return uartIsDriverInstalled(_uart);
}

void HardwareSerial::setRxInvert(bool invert)
{
    uartSetRxInvert(_uart, invert);
}

// negative Pin value will keep it unmodified
void HardwareSerial::setPins(int8_t rxPin, int8_t txPin)
{
    uartSetPins(_uart, rxPin, txPin, -1, -1);
}

// negative Pin value will keep it unmodified
void HardwareSerial::setAllPins(int8_t rxPin, int8_t txPin, int8_t ctsPin, int8_t rtsPin)
{
    uartSetPins(_uart, rxPin, txPin, ctsPin, rtsPin);
}

// Enables or disables Hardware Flow Control using RTS and/or CTS pins (must use setAllPins() before)
void HardwareSerial::setHwFlowCtrlMode(uint8_t mode, uint8_t threshold)
{
    uartSetHwFlowCtrlMode(_uart, mode, threshold);
}

size_t HardwareSerial::setRxBufferSize(size_t new_size) {

    if (_uart) {
        log_e("RX Buffer can't be resized when Serial is already running.\n");
        return 0;
    }

    if (new_size <= SOC_UART_FIFO_LEN) {
        log_e("RX Buffer must be higher than %d.\n", SOC_UART_FIFO_LEN);
        return 0;
    }

    _rxBufferSize = new_size;
    return _rxBufferSize;
}
