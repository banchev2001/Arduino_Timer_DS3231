#include <DS3231.h>
#include <WeekTimer.h>

WeekTimer WT[2]; //Declare Array of objects

int8_t  currentHour;
int8_t  currentMinutes;
int16_t currentTime;
int8_t  currDOW;


 
void setup() {

 
  
 Serial.begin(19200);
 //Serial.println("Hello people!");
  

}
void loop() {

  /******************Initialisation Of Week Timer 1 layer 1*******************/
  WT[0].WeekPlan = 0;
  WT[0].EnableWD(MONDAY);
  WT[0].DisableWD(MONDAY);

  WT[0].EnableWD(TUESDAY);
  //WT[0].DisableWD(TUESDAY);

  WT[0].EnableWD(WEDNESDAY);
  //WT[0].DisableWD(WEDNESDAY);
  
  WT[0].EnableWD(THURSDAY);
  //WT[0].DisableWD(THURSDAY);

  WT[0].EnableWD(FRIDAY);
  WT[0].DisableWD(FRIDAY);

  WT[0].EnableWD(SATURDAY);
  WT[0].DisableWD(SATURDAY);

  WT[0].EnableWD(SUNDAY);
  WT[0].DisableWD(SUNDAY);
  
  
  
  //initial WEEK TIMER OBJECT
  WT[0].OnHour = 8;
  WT[0].OnMinutes = 30;
 
  WT[0].OffHour = 9;
  WT[0].OffMinutes = 20;
  
  Serial.print("T1L1/");
  Serial.println(WT[0].GetWeekPlanStr());
//  Serial.print("/ On=");
//  Serial.print(WT[0].OnHour,DEC);
//  Serial.print(":");
//  Serial.print(WT[0].OnMinutes,DEC);
//  Serial.print("/ Off=");
//  Serial.print(WT[0].OffHour,DEC);
//  Serial.print(":");
//  Serial.println(WT[0].OffMinutes,DEC);
  /***************EOF Initialisation Of Week Timer 1 layer 1******************/

  /******************Initialisation Of Week Timer 1 layer 2*******************/
  WT[1].WeekPlan = 0;
  WT[1].EnableWD(MONDAY);
  //WT[1].DisableWD(MONDAY);

  WT[1].EnableWD(TUESDAY);
  WT[1].DisableWD(TUESDAY);

  WT[1].EnableWD(WEDNESDAY);
  //WT[1].DisableWD(WEDNESDAY);
  
  WT[1].EnableWD(THURSDAY);
  //WT[1].DisableWD(THURSDAY);

  WT[1].EnableWD(FRIDAY);
  WT[1].DisableWD(FRIDAY);

  WT[1].EnableWD(SATURDAY);
  WT[1].DisableWD(SATURDAY);

  WT[1].EnableWD(SUNDAY);
  WT[1].DisableWD(SUNDAY);

  Serial.print("T1L2/");
  Serial.println(WT[1].GetWeekPlanStr());
    
  //initial WEEK TIMER OBJECT
  WT[1].OnHour = 10;
  WT[1].OnMinutes = 30;
 
  WT[1].OffHour = 12;
  WT[1].OffMinutes = 20;

  
//  Serial.print("/ On=");
//  Serial.print(WT[1].OnHour,DEC);
//  Serial.print(":");
//  Serial.print(WT[1].OnMinutes,DEC);
//  Serial.print("/ Off=");
//  Serial.print(WT[1].OffHour,DEC);
//  Serial.print(":");
//  Serial.println(WT[1].OffMinutes,DEC);
  
  /***************EOF Initialisation Of Week Timer 1 layer 2*******************/

  /******************Initialisation Of Week Timer 1 layer 3*******************/
  WT[2].WeekPlan = 0;
  WT[2].EnableWD(MONDAY);
  WT[2].DisableWD(MONDAY);

  WT[2].EnableWD(TUESDAY);
  WT[2].DisableWD(TUESDAY);

  WT[2].EnableWD(WEDNESDAY);
  WT[2].DisableWD(WEDNESDAY);
  
  WT[2].EnableWD(THURSDAY);
  WT[2].DisableWD(THURSDAY);

  WT[2].EnableWD(FRIDAY);
  WT[2].DisableWD(FRIDAY);

  WT[2].EnableWD(SATURDAY);
  WT[2].DisableWD(SATURDAY);

  WT[2].EnableWD(SUNDAY);
  WT[2].DisableWD(SUNDAY);
  
//  Serial.print("T1L3/");
//  Serial.println(WT[2].GetWeekPlanStr());
  
  WT[2].OnHour = 19;
  WT[2].OnMinutes = 30;
 
  WT[2].OffHour = 22;
  WT[2].OffMinutes = 20;

  
//  Serial.print("/ On=");
//  Serial.print(WT[2].OnHour);
//  Serial.print(":");
//  Serial.print(WT[2].OnMinutes);
//  Serial.print("/ Off=");
//  Serial.print(WT[2].OffHour);
//  Serial.print(":");
//  Serial.println(WT[2].OffMinutes);
  /***************EOF Initialisation Of Week Timer 1 layer 3*******************/
//    
////    for(currDOW = MONDAY; currDOW <= SUNDAY ;currDOW++){
////        for (currentHour = 0; currentHour < 24; currentHour++){
////              for(currentMinutes = 0; currentMinutes < 60; currentMinutes++){
////        
////                  if(currDOW == MONDAY)Serial.print("MON");
////                  if(currDOW == TUESDAY)Serial.print("TUE");
////                  if(currDOW == WEDNESDAY)Serial.print("WED");
////                  if(currDOW == THURSDAY)Serial.print("THU");
////                  if(currDOW == FRIDAY)Serial.print("FRI");
////                  if(currDOW == SATURDAY)Serial.print("SAT");
////                  if(currDOW == SUNDAY)Serial.print("SUN");
////                  Serial.print(" Time:");
////                  Serial.print(currentHour);
////                  Serial.print(":");
////                  Serial.print(currentMinutes);
////                  
////                  //Control Timer 1
////                  if(WT[0].Check(currDOW,currentHour,currentMinutes))Serial.println(" \t\tOut is ON T1 L1");
////            
////                  //Control Timer 2
////                  else if(WT[1].Check(currDOW,currentHour,currentMinutes))Serial.println(" \t\tOut is ON T1 L2");
////
////                  //Control Timer 3
////                  else if(WT[2].Check(currDOW,currentHour,currentMinutes))Serial.println(" \t\tOut is ON T3 L3");
////                  
////                  
////                  else Serial.println(" \tOut is OFF");
////                
////              }
////        }
////    }
//  
//
  while(1){
//  Serial.println("Loop");
//  delay(1000);
  }
  
  
}
