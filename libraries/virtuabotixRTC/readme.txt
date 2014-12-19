

https://www.virtuabotix.com/virtuabotix-ds1302-real-time-clock-module-pin-out-coding-guide/






Virtuabotix DS1302 Real Time Clock Module Pin-out and coding guide

    Posted on January 21, 2014
    by T. Murphy
    in guides, News

Virtuabotix DS1302 Battery Backed RTC Module for the Arduino and Versalino in handThe DS1302 trickle-charge timekeeping chip contains a real-time clock/calendar and 31 bytes of static RAM.  It communicates with a microprocessor via a simple serial interface.  The Real Time Clock / Calendar provides Seconds, Minutes, Hours, Day, Date, Month, and Year information.  Only three wires are required to communicate with the Real Time Clock / RAM: CE, I/O (data line), and SCLK (serial clock). Data can be transferred to and from the clock/RAM 1 byte at a time or in a burst of up to 31 bytes. The DS1302 is designed to operate on very low power and retain data and clock information on less than 1μW.  The DS1302 Real Time Clock has dual power pins, one for primary and another for backup.  in this example the Priamry power will be provided by the Arduino, and the back up by a CR2032 battery.

The 31 bytes of RAM is formatted as shown in the table below.  Notice that the numeric positions have their own bits to fill.  Specifically the 0-9 value of the ‘ones’ place have 4 bits, and the 0-9 value of the ‘tens’ place has 3 bits for the byte filled with the seconds value.  These values are combined to create the entire byte.

    Virtuabotix DS1302 Battery Backed RTC Module for the Arduino and Versalino Main
    Virtuabotix DS1302 Real Time Clock (RTC) Module for the Arduino and Versalino
    $5.95
    Add to cart


Virtuabotix DS1302 Real Time Clock Schematic:


DS1302 RTC Real Time Clock

 Here you can see the wiring diagram for the DS1302 Real Time Clock.  Vcc2 is set to accept the primary power, this is typically 3.3V, but can use 5V.  It is recommended that more than 7V is applied, as this can damage the unit.  VCC1 is set aside for the backup power, provided by the 3.3V CR2032 Coin Battery.  The quartz crystal is placed between the #2 and #3 pins.  Pin #5-7 are set aside for the data communication between the module and the micro controller.  In previous versions of the module, and DS1302, there is a pin labeled as ‘RESET’, this is the same pin as “CE”.  The pins serve the same function, simply relabeled in this version.  The library will allow for the communication pins to be connected to any type of pin on the Arduino or Versilino boards.  This means that they can be connected to the PWM, DIGITAL, COMMUNICATION, or ANALOG pins and work.  Below you can see the wiring diagram for connecting to the Arduino Mega 2560.
 
Pinout/Procedure:

Once connected to the micro controller, and import the library you can start using the module.  Below are a few examples of how to wire the RTC to your project on different platforms.

Virtuabotix DS1302 Battery Backed RTC Module for the Arduino and Versalino connected to Arduino Mega

If you choose to run the library on the Versalino it would probably be easiest to add an #include , and change the pin calls to virtuabotixRTC myRTC(BUSA.D1, BUSA.P1, BUSA.D2); instead of virtuabotixRTC myRTC(6, 7, 8);

Virtuabotix DS1302 Real Time Clock Battery Backed RTC Module for the Arduino and Versalino wiring diagram main






Code:

Click here to download the virtuabotixRTC Library and install it before you run the code examples below. If you need help installing the library you can find the instructions at the beginning of the Versalino Quickstart guide.

The library provided by Virtuabotix, LLC provides users with the ability to use the RTC Module in a plug and play fashion.  Once the library in imported, simply create the object and define the pins needed for communication, and set the time.  At that point all functions within the library are active.  While these are primarily background functions that keep the time current, the single function that the user needs is updateTime().  This function allows for the user to access any of the elements within the time.  This library comes with two examples: one that will simply print the current date and time, and one that will verify that the RTC is tracking time changes by illuminating LEDs to verify a good, or bad, RTC. 

*NOTE: Users should be reminded that the time to process code between printout statements can accumulate over time.  This is especially noticed when printing out the data at different points within the main program.  When code is executed this way it appears that the time is drifting, be assured that it is most likely not drifting, just the time between calls adding up over time. 





#include //|

// Creation of the Real Time Clock Object
//SCLK -> 6, I/O -> 7, CE -> 8
virtuabotixRTC myRTC(6, 7, 8);

void setup() {
Serial.begin(9600);

// Set the current date, and time in the following format:
// seconds, minutes, hours, day of the week, day of the month, month, year
myRTC.setDS1302Time(00, 59, 23, 6, 10, 1, 2014);
}

void loop() {
// This allows for the update of variables for time or accessing the individual elements.
myRTC.updateTime();

// Start printing elements as individuals
Serial.print("Current Date / Time: ");
Serial.print(myRTC.dayofmonth);
Serial.print("/");
Serial.print(myRTC.month);
Serial.print("/");
Serial.print(myRTC.year);
Serial.print(" ");
Serial.print(myRTC.hours);
Serial.print(":");
Serial.print(myRTC.minutes);
Serial.print(":");
Serial.println(myRTC.seconds);

// Delay so the program doesn't print non-stop
delay( 5000);
}







Real Time Clock Project ideas:

This Real Time Clock (RTC) Module could be used for a plethora of projects.  The RTC can be interfaced to the micro controllers in order to control timed events.  This is especially helpful when timing is critical to the project.

