/*
Start Date: 29.08.2020
Source Web: https://howtomechatronics.com/tutorials/arduino/arduino-ds3231-real-time-clock-tutorial
DS3231 Library Document Web: http://www.rinkydinkelectronics.com/library.php?id=73


*/

/*
* Arduino DS3231 Real Time Clock Module Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
* DS3231 Library made by Henning Karlsen which can be found and downloaded from his website, www.rinkydinkelectronics.com.
*
*/
#include <DS3231.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 

//Define custom name of Buttons
#define DOWN_BUTTON 10
#define UP_BUTTON 9
#define SELECT_BUTTON 8

//Define custom name of Outputs
#define TMR1_OUT 13 
#define TMR2_OUT 14 //A0 pin



  DS3231  rtc(SDA, SCL);
  //Parameters: (rs, enable, d4, d5, d6, d7) 
  LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Creates an LCD object. 

  /****************** Global Variables ********************************/
  enum CursAddr {Home = 0, HOUR_ADR, MINUTES_ADR, SECONDS_ADR, 
                 DAY_ADR, MONTH_ADR, YEAR_ADR, DOW_ADR} CursPlace = Home;
                 
  Time RTCC; //Class Varible contain all .hour .min .sec .date .mon .year .dow

  /********************************************************************/



void setup() { 

  
  CursPlace = Home;

  
  /*****Config Pins and define custom names of pins *****/
  //Inputs
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(SELECT_BUTTON, INPUT_PULLUP);
  
  //Outputs
  pinMode(TMR1_OUT, OUTPUT);
  pinMode(TMR2_OUT, OUTPUT);
  /******************************************************/
  
  rtc.begin(); // Initialize the rtc object
  lcd.begin(20,4); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 

  // Aproximate 8 seconds to upload scatch
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(SUNDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(20, 4, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(29, 8, 2020);   // Set the date to January 1st, 2014

}


void loop() { 

  
  
  //SELECT BUTTON REACTION
  //====================================================
    if (!digitalRead(SELECT_BUTTON)){

      CursPlace = CursPlace + 1;
      while(!digitalRead(SELECT_BUTTON));
      if(CursPlace > DOW_ADR)CursPlace = Home;
      delay(20);
  }

  //UP BUTTON REACTION
  //====================================================
  if (!digitalRead(UP_BUTTON)){

         if(CursPlace == HOUR_ADR){ //Curssor is pointed to Hour
          
          RTCC = rtc.getTime();
          RTCC.hour++; //Incrase Hour
          if(RTCC.hour > 23)RTCC.hour = 0;//Check If Hour is reached 23 and turn back to 0 
          rtc.setTime(RTCC.hour, RTCC.min, RTCC.sec);               
         }
         //-----------------------------------------------------

         if(CursPlace == MINUTES_ADR){ //Curssor is pointed to Minutes
          
          RTCC = rtc.getTime();
          RTCC.min++; //Incrase Minutes
          if(RTCC.min > 59)RTCC.min = 0;//Check If Minutes is reached 59 and turn back to 0 
          rtc.setTime(RTCC.hour, RTCC.min, RTCC.sec);               
         }
         //-----------------------------------------------------

         if(CursPlace == SECONDS_ADR){ //Curssor is pointed to Seconds
          
          RTCC = rtc.getTime();
          rtc.setTime(RTCC.hour, RTCC.min, 0); //Zero seconds               
         }
         //-----------------------------------------------------
    
        if(CursPlace == DOW_ADR){ //Curssor is pointed to Day Of Week

          RTCC = rtc.getTime();
          RTCC.dow++; //Incrase Day Of Week
          if(RTCC.dow > SUNDAY)RTCC.dow = MONDAY;//Check Day If is SunDay turn Back to Monday
          rtc.setDOW(RTCC.dow);//Write to back to DS3231          
         }
         //-----------------------------------------------------

         
       while(!digitalRead(UP_BUTTON));
       delay(20);
  }

  //DOWN BUTTON REACTION
  //===================================================
  if (!digitalRead(DOWN_BUTTON)){

        if(CursPlace == HOUR_ADR){ //Curssor is pointed to Hour
          
          RTCC = rtc.getTime();
          RTCC.hour--; //Decrase Hour
          if(RTCC.hour < 0)RTCC.hour = 23;//Check If Hour is reached 0 and turn back to 23 
          rtc.setTime(RTCC.hour, RTCC.min, RTCC.sec);               
         }
         //-----------------------------------------------------

         if(CursPlace == MINUTES_ADR){ //Curssor is pointed to Minutes
          
          RTCC = rtc.getTime();
          RTCC.min--; //Decrase Minutes
          if(RTCC.min < 0)RTCC.min = 0;//Check If Minutes is reached 0 and turn back to 59 
          rtc.setTime(RTCC.hour, RTCC.min, RTCC.sec);               
         }
         //-----------------------------------------------------

         if(CursPlace == SECONDS_ADR){ //Curssor is pointed to Seconds
          
          RTCC = rtc.getTime();
          rtc.setTime(RTCC.hour, RTCC.min, 0); //Zero seconds               
         }
         //-----------------------------------------------------

        if(CursPlace == DOW_ADR){ //Curssor is pointed to Day Of Week

          RTCC = rtc.getTime();
          RTCC.dow--; //Decrase Day Of Week
          if(RTCC.dow < MONDAY)RTCC.dow = SUNDAY; //Check Day If is Monday turn back to SunDay 
          rtc.setDOW(RTCC.dow);//Write to back to DS3231          
         }
         //------------------------------------------------------
         
       while(!digitalRead(DOWN_BUTTON));
       delay(20);
    
    
   }
 
   lcd.setCursor(0,0);
   lcd.print("Time: ");
   lcd.print(rtc.getTimeStr());
   
   lcd.setCursor(0,1);
   lcd.print("Date: ");
   lcd.print(rtc.getDateStr(FORMAT_SHORT,FORMAT_LITTLEENDIAN,'/'));
  
   lcd.setCursor(0,2);
   lcd.print("Day:  ");
   lcd.print(rtc.getDOWStr(FORMAT_SHORT));
  
   lcd.setCursor(0,3);
   lcd.print("Temp: ");
   lcd.print(rtc.getTemp());
   lcd.print(" C");


   delay(90);
   
       //Turn Off curssor when rotate all parameters
       if(CursPlace == Home){
        lcd.noCursor();
       }
       
       //Place Curssor on the Time
       //--------------------------------------------
       if(CursPlace == HOUR_ADR){
        lcd.setCursor(7,0);
        lcd.cursor();
       }
       if(CursPlace == MINUTES_ADR){
        lcd.setCursor(10,0);
        lcd.cursor();
       }
       if(CursPlace == SECONDS_ADR){
        lcd.setCursor(13,0);
        lcd.cursor();
       }

       //Place Curssor on the Date
       //--------------------------------------------
       if(CursPlace == DAY_ADR){
        lcd.setCursor(7,1);
        lcd.cursor();
       }
       if(CursPlace == MONTH_ADR){
        lcd.setCursor(10,1);
        lcd.cursor();
       }
       if(CursPlace == YEAR_ADR){
        lcd.setCursor(13,1);
        lcd.cursor();
       }

       //Place Curssor on the Day Of Week
       //-------------------------------------------
       if(CursPlace == DOW_ADR){
        lcd.setCursor(6,2);
        lcd.cursor();
       }
       
 
   delay(90);
   lcd.noCursor(); 
}
