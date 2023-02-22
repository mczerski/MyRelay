/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 17
#endif

// Enable debug prints to serial monitor
//#define MY_DEBUG
#define MY_BAUD_RATE 115200
#define MY_SERIALDEVICE Serial2
//#define MYS_TOOLKIT_DEBUG
//#define MYS_TOOLKIT_SERIAL Serial

#define TEST
#define SKETCH_NAME "Relay"
#define SKETCH_MAJOR_VER "1"
#define SKETCH_MINOR_VER "0"

// Enable and select radio type attached
#define MY_RS485
//#define MY_RS485_DE_PIN PA8
#define MY_RS485_BAUD_RATE 115200
#define MY_RS485_HWSERIAL Serial2
#define MY_TRANSPORT_WAIT_READY_MS 1

#ifdef TEST
#define MY_NODE_ID 40
#define MY_DEBUG_VERBOSE_RS485
#define SKETCH_SUBNAME "Test"
#endif

#include <MySensors.h>
#include <MySensorsToolkit.h>
#include <MySensorsToolkit/Actuator/RelayActuator.h>
#include "BL0942RequestableValue.h"

using namespace mys_toolkit;

#ifdef TEST
#define RELAY1
GPIOSwitch sw1(15, true);
GPIORelay rel1(3, false);
BL0942RequestableValue bl0942(Serial1, 3, Duration(1000));
#endif

#ifdef RELAY1
RelayActuator relay1(0, rel1, sw1);
#endif
#ifdef RELAY2
RelayActuator relay2(1, rel2, sw2);
#endif
#ifdef RELAY3
RelayActuator relay3(2, rel3, sw3);
#endif

/***
 * Relay initialization method
 */
void setup()
{
  ActuatorBase::begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

void presentation() {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo(SKETCH_NAME "-" SKETCH_SUBNAME, SKETCH_MAJOR_VER "." SKETCH_MINOR_VER);

  // Register the LED Dimmable Light with the gateway
  ActuatorBase::present();
}

int prevMillis = 0;
int prevLed = LOW;

void flipLed() {
  if (prevLed == LOW) {
    digitalWrite(LED_BUILTIN, HIGH);
    prevLed = HIGH;
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    prevLed = LOW;
  }
}

/***
 *  Relay main processing loop
 */
void loop()
{
  ActuatorBase::update();
  if (prevMillis + 1000 < millis()) {
    flipLed();
    prevMillis = millis();
  }
}

void receive(const MyMessage &message) {
  ActuatorBase::receive(message);
}
