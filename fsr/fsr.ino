#define fsrsmall A0
#define fsrbig A1

int fsrsmallreading;
int fsrbigreading;
unsigned long start, ending, duration;
byte timerRunning;
int numsmall=0;
int numbig=0;
int sumsmall=0;
int sumbig=0;
int avgbig=0;
int avgsmall=0;
int threshhold=500;
int resistor=5000;

int fsrPin = 1;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrVoltage;     // the analog reading converted to voltage
unsigned long fsrResistance;  // The voltage converted to resistance, can be very big so make "long"
unsigned long fsrConductance; 
long fsrForce;       // Finally, the resistance converted to force
void setup() {
  Serial.begin(9600);
}
void loop() {
  fsrsmallreading = analogRead(fsrsmall);
  fsrbigreading = analogRead(fsrbig);
  //Serial.println("time since running: "+millis());
//  Serial.print("Small reading = ");
//  Serial.println(fsrsmallreading);
//  Serial.print("Big reading = ");
//  Serial.println(fsrbigreading);
//  Serial.println("__________________");
//
//  Serial.print((pow(1.01,fsrbigreading+.0001))/4000);//big
//  Serial.print(",");
//  Serial.println((pow(1.01,fsrsmallreading+.0001))/1400);//small
//}
//  Serial.print(",");
//  Serial.println(fsrbigreading);

//  if((fsrsmallreading>threshhold || fsrbigreading>threshhold) && timerRunning==0){
//    timerRunning=1;
//    start=millis();
//    sumsmall=sumsmall+fsrsmallreading;
//    numsmall=numsmall+1;
//    numbig=numbig+1;
//    sumbig=sumbig+fsrbigreading;
//  }
//  if((fsrsmallreading<=threshhold && fsrbigreading<=threshhold) && timerRunning==1){
//    timerRunning=0;
//    ending=millis();
//    avgbig=sumbig/numbig;
//    avgsmall=sumsmall/numsmall;
//    duration=ending-start;
//    Serial.print("duration of push: ");
//    Serial.println(duration);
//    Serial.print("average big force: ");
//    Serial.println(avgbig);
//    Serial.print("average small force: ");
//    Serial.println(avgsmall);
//   
//   
//    sumsmall=0;
//    numsmall=0;
//    sumbig=0;
//    numbig=0;
//  }
normalprint();
delay(10);
}
void trys(){
  Serial.println(fsrbigreading*fsrbigreading);
}
void testscale(){
  Serial.print(((1023*resistor)/fsrbigreading)-resistor);
  Serial.print(1024);
  Serial.print(",");
  Serial.println(fsrbigreading);
}
void normalprint(){
    Serial.println(fsrsmallreading);
//    Serial.print(",");
//    Serial.println(fsrbigreading);
}
void newtons() {
  fsrReading = analogRead(fsrPin);  
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);
 
  // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
  fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);
  Serial.print("Voltage reading in mV = ");
  Serial.println(fsrVoltage);  
 
  if (fsrVoltage == 0) {
    Serial.println("No pressure");  
  } else {
    // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
    // so FSR = ((Vcc - V) * R) / V        yay math!
    fsrResistance = 5000 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance *= 10000;                // 10K resistor
    fsrResistance /= fsrVoltage;
    Serial.print("FSR resistance in ohms = ");
    Serial.println(fsrResistance);
 
    fsrConductance = 1000000;           // we measure in micromhos so 
    fsrConductance /= fsrResistance;
    Serial.print("Conductance in microMhos: ");
    Serial.println(fsrConductance);
 
    // Use the two FSR guide graphs to approximate the force
    if (fsrConductance <= 1000) {
      fsrForce = fsrConductance / 80;
      Serial.print("Force in Newtons: ");
      Serial.println(fsrForce);      
    } else {
      fsrForce = fsrConductance - 1000;
      fsrForce /= 30;
      Serial.print("Force in Newtons: ");
      Serial.println(fsrForce);            
    }
  }
  Serial.println("--------------------");
  delay(1000);
}
