#define USB_PRODUCT "Big Red Button"
#ifndef ARDUINO_USB_MODE
#error This ESP32 SoC has no Native USB interface
#elif ARDUINO_USB_MODE == 1
#warning This sketch should be used when USB is in OTG mode
void setup() {}
void loop() {}
#else

#include "Arduino.h"
#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

const int buttonPin = RX;
int previousButtonState = HIGH;

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  USB.productName("Big Red Button");
  USB.begin();
  delay(1000);  // give me time to bring up serial monitor

  pinMode(buttonPin, INPUT_PULLUP);
  Serial.println("\nESP32 Big Red Return Button\n");
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if ((buttonState != previousButtonState) && buttonState == LOW) {
    Keyboard.write(KEY_RETURN);
    Serial.println("Button Pressed");
  }

  previousButtonState = buttonState;

  delay(50);
}
#endif /* ARDUINO_USB_MODE */