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

  Serial.print((pow(1.01,fsrbigreading+.0001))/4000);//big
  Serial.print(",");
  Serial.println((pow(1.01,fsrsmallreading+.0001))/1400);//small
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
delay(10);
}
