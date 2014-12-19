#include <virtuabotixRTC.h>

/*

mesura el VOLTATGE d'una bateria mitjansant el sensor de voltatge http://www.dx.com/es/p/diy-electronic-bricks-voltage-detection-sensor-module-for-arduino-board-blue-green-331542#.VH91t48VWRo
mesura tb la INTENSITAT que circula de la bateria cap al consum mitjansant el sensor basat en l'efecte hall http://www.dx.com/es/p/acs712-20a-current-sensor-module-blue-206999#.VH91zY8VWRo
controla el TEMPS i el mostra a cada mesura. 

extret a partir de les segurnts fonts:
--------------------------------------------------------------
  Program:      volt_measure

  Description:  Reads value on analog input A0 and calculates
                the voltage assuming that a voltage divider
                network on the pin divides by 11.                // modificat per un calibratge rapid
  
  Hardware:     Arduino Uno with voltage divider on A0.
                
  Software:     Developed using Arduino 1.0.5 software
                Should be compatible with Arduino 1.0 +

  Date:         22 May 2013
 
  Author:       W.A. Smith, http://startingelectronics.com
--------------------------------------------------------------
i
--------------------------------------------------------------
http://www.lucadentella.it/en/2011/11/29/sensore-di-corrente-con-arduino/
--------------------------------------------------------------
i
--------------------------------------------------------------
https://www.virtuabotix.com/virtuabotix-ds1302-real-time-clock-module-pin-out-coding-guide/
--------------------------------------------------------------

*/



/////////////////////////////////////////
//calibracio de font i sensor de voltatge
//primer  mesurem amb el tester el voltatge que arriba al sensor entre vcc i gnd i l'actualitzem a la seguent variable
float volRef = 4.93;
//ara mesurem amb el tester el voltatge de la bateria a controlar i l'actualitzem a la seguent variable
float volBat = 3.55;
//finalment mesurem amb el tester el voltatge entre la sortida de senyal del sensor i gnd i l'actualitzem a la seguent variable
float volSen = 0.633;
//ara ja es pot definir la variavle seguent
float factorDivisor = volBat / volSen;


////////////////////////////////////
//calibracio del sensor d'intensitat
//la formula per passar de la lectura del sensor a Ampers es la seguent: 
//
//    A = (((5V/1023)*units)-2.5V)/(sensibilitat del sensor) = ((0.0049*units)-2.5)/senSen = ((0.0049/senSen)*units)-(2.5/senSen)
//
//la sensivilitat del sensor ve donada al datasheet : 
//    ACS712ELCTR-05B-T    -->     185 mV/A
//    ACS712ELCTR-20A-T    -->     100 mV/A
//    ACS712ELCTR-30A-T    -->      66 mV/A
float senSen = 0.185;


/////////////////////////////////////////
// Creation of the Real Time Clock Object
//   SCLK -> 6,   I/O -> 7,   CE -> 8
virtuabotixRTC myRTC(6, 7, 8);


///////////////////////////////////////////////////////
// number of analog samples to take per voltage reading
#define NUM_SAMPLES 10
int sum = 0;                    // sum of samples taken
unsigned char sample_count = 0; // current sample number
float voltage = 0.0;            // calculated voltage





void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);


}




void loop() {
  // put your main code here, to run repeatedly:
  
  
  /////////////////////////////////////////////////////////////////////////////////////////
  // This allows for the update of variables for time or accessing the individual elements.                //|
  myRTC.updateTime();
  
  
  //////////////////
  //ara el VOLTATGE
  // take a number of analog samples and add them up
    while (sample_count < NUM_SAMPLES) {
        sum += analogRead(A0);
        sample_count++;
        delay(10);
    }
    // calculate the voltage
    // use 5.0 for a 5.0V ADC reference voltage
    // 5.015V is the calibrated reference voltage
    voltage = ((float)sum / (float)NUM_SAMPLES * volRef) / 1024.0;
    // send voltage for display on Serial Monitor
    // voltage multiplied by 11 when using voltage divider that
    // divides by 11. 11.132 is the calibrated voltage divide
    // value
//    Serial.println(factorDivisor);
    Serial.print(voltage * factorDivisor);
    Serial.println (" V");
    sample_count = 0;
    sum = 0;



///////////////////////////  INICI TRAM EN OBRES !! PRECAUCIO    //////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////
// ara la INTENSITAT
  float average = 0.0;
  for(int i = 0; i < 1000; i++) {
    
//    A = (((5V/1023)*units)-2.5V)/(sensibilitat del sensor) = ((0.0049*units)-2.5)/senSen = ((0.0049/senSen)*units)-(2.5/senSen)
//
  average = average + (.038 * analogRead(A1) - 19.28) / 1000;
//  average = average + (.0264 * analogRead(A1) - 13.38) / 1000;
//  average = average + (.0264 * analogRead(A1) - 13.51) / 1000;
//  average = average + (((5/1023) * analogRead(A1))/senSen - (2.5/senSen)) / 1000;
//  average = average + ((((5/1024) * analogRead(A1)) - 2.5)/senSen) / 1000;

    delay(1);
  }
  Serial.print(average);  
  Serial.println (" A");


/* // debugging
  Serial.print((5/1023)/senSen);  
  Serial.println (" 5/1023 /senSen");
  Serial.print(2.5/senSen);  
  Serial.println (" senSen");
  Serial.print(analogRead(A1));  
  Serial.println (" analogRead(A1)");
*/


//////////////////////////////////////////////
// Start printing RTC elements as individuals                                                            //|   

//  Serial.print("Current Date / Time: ");                                                                 //|
  switch (myRTC.dayofweek)                  // Esto pone nombre del dia
  {
    case 1:
    Serial.print(" Lunes"); break;
    case 2:
    Serial.print(" Martes"); break;
    case 3:
    Serial.print(" Miercoles"); break;
    case 4:
    Serial.print(" Jueves"); break;
    case 5:
    Serial.print(" Viernes"); break;
    case 6:
    Serial.print(" Sabado"); break;
    case 7:
    Serial.print(" Domingo"); break;
  }
  Serial.print("  ");                                                                                    //| 
  Serial.print(myRTC.dayofmonth);                                                                        //| 
  Serial.print("/");                                                                                     //| 
  Serial.print(myRTC.month);                                                                             //| 
  Serial.print("/");                                                                                     //| 
  Serial.print(myRTC.year);                                                                              //| 
  Serial.print("  ");                                                                                    //| 
  Serial.print(myRTC.hours);                                                                             //| 
  Serial.print(":");                                                                                     //| 
  Serial.print(myRTC.minutes);                                                                           //| 
  Serial.print(":");                                                                                     //| 
  Serial.println(myRTC.seconds);    
  
  
///////////////////////////  FINAL TRAM EN OBRES !!  //////////////////////////////////////////////////////////////////////////////////////////////////////////

  Serial.println (" ");

}


