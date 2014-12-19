/*

mesura el voltatge d'una bateria mitjansant el sensor de voltatge http://www.dx.com/es/p/diy-electronic-bricks-voltage-detection-sensor-module-for-arduino-board-blue-green-331542#.VH91t48VWRo

--------------------------------------------------------------
  Program:      volt_measure

  Description:  Reads value on analog input A0 and calculates
                the voltage assuming that a voltage divider
                network on the pin divides by 11.
  
  Hardware:     Arduino Uno with voltage divider on A0.
                
  Software:     Developed using Arduino 1.0.5 software
                Should be compatible with Arduino 1.0 +

  Date:         22 May 2013
 
  Author:       W.A. Smith, http://startingelectronics.com
--------------------------------------------------------------
*/

//calibracio de font i sensor
//primer  mesurem amb el tester el voltatge que arriba al sensor entre vcc i gnd i l'actualitzem a la seguent variable
float volRef = 4.93;
//ara mesurem amb el tester el voltatge de la bateria a controlar i l'actualitzem a la seguent variable
float volBat = 3.55;
//finalment mesurem amb el tester el voltatge entre la sortida de senyal del sensor i gnd i l'actualitzem a la seguent variable
float volSen = 0.633;
//ara ja es pot definir la variavle seguent
float factorDivisor = volBat / volSen;



// number of analog samples to take per reading
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

}
