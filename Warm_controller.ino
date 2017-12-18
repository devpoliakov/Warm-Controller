// Example sketch for interfacing with the DS1302 timekeeping chip.
//
// Copyright (c) 2009, Matt Sparks
// All rights reserved.
//
// http://quadpoint.org/projects/arduino-ds1302
#include <stdio.h>
#include <DS1302.h>

namespace {

// Set the appropriate digital I/O pin connections. These are the pin
// assignments for the Arduino as well for as the DS1302 chip. See the DS1302
// datasheet:
//
//   http://datasheets.maximintegrated.com/en/ds/DS1302.pdf
const int kCePin   = 5;  // Chip Enable
const int kIoPin   = 6;  // Input/Output
const int kSclkPin = 7;  // Serial Clock

int buttonState = 0;
const int ledPin =  13;
const int buttonPin = 2;

// Create a DS1302 object.
DS1302 rtc(kCePin, kIoPin, kSclkPin);

String dayAsString(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Sunday";
    case Time::kMonday: return "Monday";
    case Time::kTuesday: return "Tuesday";
    case Time::kWednesday: return "Wednesday";
    case Time::kThursday: return "Thursday";
    case Time::kFriday: return "Friday";
    case Time::kSaturday: return "Saturday";
  }
  return "(unknown day)";
}

void printTime() {
  // Get the current time and date from the chip.
  Time t = rtc.time();

  // Name the day of the week.
  const String day = dayAsString(t.day);

  // Format the time and date and insert into the temporary buffer.
  char buf[50];
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day.c_str(),
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  // Print the formatted string to serial so we can see the time.
  Serial.println(buf);
}





void printTime_min() {
  // Get the current time and date from the chip.
  Time t = rtc.time();

  // Name the day of the week.
  // Format the time and date and insert into the temporary buffer.
  char buf[50];
  snprintf(buf, sizeof(buf), "%02d:%02d:%02d",
           t.hr, t.min, t.sec);

  // Print the formatted string to serial so we can see the time.
  pinMode(10, OUTPUT);
  pinMode(ledPin, OUTPUT);     
  pinMode(buttonPin, INPUT); 
  
  buttonState = digitalRead(buttonPin);


  if (
    (t.hr == 23 and t.min > 5)
  or ((t.hr == 5 and t.min > 30) 
  or (t.hr == 6 and t.min < 55))
  or (buttonState == HIGH )
  ) {
    digitalWrite(10, HIGH);
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  
if (buttonState == HIGH){
delay(3600000);
}
} else {
    digitalWrite(10, LOW);
    digitalWrite(ledPin, LOW);
  }


  Serial.println(buf);
}

}  // namespace

void setup() {
  Serial.begin(9600);

  // Initialize a new chip by turning off write protection and clearing the
  // clock halt flag. These methods needn't always be called. See the DS1302
  // datasheet for details.
  rtc.writeProtect(false);
  rtc.halt(false);

  // Set a time (time format and sett command)
  // year, months, day, hour (one number), minutes, seconds, kDay
  //Time t(2017, 12, 19, 0, 25, 00, Time::kTuesday);
  //rtc.time(t);
}

// Loop and print the time every second.
void loop() {
  printTime();
  printTime_min();

  delay(1000);
}
