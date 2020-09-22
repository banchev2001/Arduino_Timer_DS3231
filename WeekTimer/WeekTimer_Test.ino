#include <DS3231.h>
#include <WeekTimer.h>

WeekTimer WT[2][3]; //Declare Array of objects

int8_t  currentHour;
int8_t  currentMinutes;
int16_t currentTime;
int8_t  currDOW;


 
void setup() {

 
  
 Serial.begin(115200);
 Serial.println("       All Timers Settings:");
 Serial.println("==================================");

}
void loop() {

  /******************Initialisation Of Week Timer 1 layer 1*******************/
  WT[0][0].WeekPlan = 0; //All days of week Disable 
  WT[0][0].SetWeekPlanStr("MTWTFSS");//One of posible way to config working days of week

  //Here is second posible way to config Working week days but in more line
//  WT[0][0].EnableWD(MONDAY);
//  WT[0][0].DisableWD(MONDAY);
//  WT[0][0].EnableWD(TUESDAY);
//  WT[0][0].DisableWD(TUESDAY);
//  WT[0][0].EnableWD(WEDNESDAY);
//  WT[0][0].DisableWD(WEDNESDAY);
//  WT[0][0].EnableWD(THURSDAY);
//  WT[0][0].DisableWD(THURSDAY);
//  WT[0][0].EnableWD(FRIDAY);
//  WT[0][0].DisableWD(FRIDAY);
//  WT[0][0].EnableWD(SATURDAY);
//  WT[0][0].DisableWD(SATURDAY);
//  WT[0][0].EnableWD(SUNDAY);
//  WT[0][0].DisableWD(SUNDAY);
  
  //Set timer on and off moment at day with function 
  WT[0][0].SetOnTime(8,20);
  WT[0][0].SetOffTime(9,20);
//  WT[0][0].OnHour = 8;
//  WT[0][0].OnMinutes = 31;
//  WT[0][0].OffHour = 8;
//  WT[0][0].OffMinutes = 30;

  //Here Start Code to prin on Serial Print Settings
  Serial.print("T1L1/");
  Serial.print(WT[0][0].GetWeekPlanStr());
  Serial.print("/ On=");
  Serial.print(WT[0][0].OnHour,DEC);
  Serial.print(":");
  Serial.print(WT[0][0].OnMinutes,DEC);
  Serial.print("/ Off=");
  Serial.print(WT[0][0].OffHour,DEC);
  Serial.print(":");
  Serial.println(WT[0][0].OffMinutes,DEC);
  /***************EOF Initialisation Of Week Timer 1 layer 1******************/

  /******************Initialisation Of Week Timer 1 layer 2*******************/
  WT[0][1].WeekPlan = 0;
  WT[0][1].SetWeekPlanStr("-----SS");//One of posible way to config working days of week
     
  //initial WEEK TIMER OBJECT
  WT[0][1].SetOnTime(12,30);
  WT[0][1].SetOffTime(14,30);
  

  //Here Start Code to prin on Serial Print Settings
  Serial.print("T1L2/");
  Serial.print(WT[0][1].GetWeekPlanStr());
  Serial.print("/ On=");
  Serial.print(WT[0][1].OnHour,DEC);
  Serial.print(":");
  Serial.print(WT[0][1].OnMinutes,DEC);
  Serial.print("/ Off=");
  Serial.print(WT[0][1].OffHour,DEC);
  Serial.print(":");
  Serial.println(WT[0][1].OffMinutes,DEC);
  
  /***************EOF Initialisation Of Week Timer 1 layer 2*******************/

  /******************Initialisation Of Week Timer 1 layer 3*******************/
  WT[0][2].WeekPlan = 0;
  WT[0][2].SetWeekPlanStr("-T-T---");//One of posible way to config working days of week
  
  WT[0][2].SetOnTime(19,30);
  WT[0][2].SetOffTime(22,20);

  //Here Start Code to prin on Serial Print Settings
  Serial.print("T1L3/");
  Serial.print(WT[0][2].GetWeekPlanStr());
  Serial.print("/ On=");
  Serial.print(WT[0][2].OnHour);
  Serial.print(":");
  Serial.print(WT[0][2].OnMinutes);
  Serial.print("/ Off=");
  Serial.print(WT[0][2].OffHour);
  Serial.print(":");
  Serial.println(WT[0][2].OffMinutes);
  /***************EOF Initialisation Of Week Timer 1 layer 3*******************/
    
    for(currDOW = MONDAY; currDOW <= SUNDAY ;currDOW++){
        for (currentHour = 0; currentHour < 24; currentHour++){
              for(currentMinutes = 0; currentMinutes < 60; currentMinutes++){
        
                  if(currDOW == MONDAY)Serial.print("MON");
                  if(currDOW == TUESDAY)Serial.print("TUE");
                  if(currDOW == WEDNESDAY)Serial.print("WED");
                  if(currDOW == THURSDAY)Serial.print("THU");
                  if(currDOW == FRIDAY)Serial.print("FRI");
                  if(currDOW == SATURDAY)Serial.print("SAT");
                  if(currDOW == SUNDAY)Serial.print("SUN");
                  Serial.print(" Time:");
                  Serial.print(currentHour);
                  Serial.print(":");
                  Serial.print(currentMinutes);
                  
                  //Control Timer 1
                  if(WT[0][0].Check(currDOW,currentHour,currentMinutes))Serial.println(" \t\tOut is ON T1 L1");
            
                  //Control Timer 2
                  else if(WT[0][1].Check(currDOW,currentHour,currentMinutes))Serial.println(" \t\tOut is ON T1 L2");

                  //Control Timer 3
                  else if(WT[0][2].Check(currDOW,currentHour,currentMinutes))Serial.println(" \t\tOut is ON T3 L3");
                  
                  
                  else Serial.println(" \tOut is OFF");
                
              }
        }
    }
  

  while(1){
      //UNSTOPUBLE LOOP!
  }
  
  
}
