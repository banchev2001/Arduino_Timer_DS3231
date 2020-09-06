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

//Define constant for logic control
#define ON 1
#define OFF 0

  DS3231  rtc(SDA, SCL);
  //Parameters: (rs, enable, d4, d5, d6, d7) 
  LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Creates an LCD object. 

  /****************** Global Variables ********************************/
  enum CursAddr {Home = 0, HOUR_ADR, MINUTES_ADR, SECONDS_ADR, 
                 DAY_ADR, MONTH_ADR, YEAR_ADR, DOW_ADR} CursPlace = Home;
  enum
  //Flag bits used by program
  struct{ 
    char CursorState :1; //flag bit used for control Cursor ON - OFF state
  }FlagBits;
 
  //here is some variable for curssor blink
  int CursorDelayCnt = 0;
    
  Time RTCC; //Create object RTCC wich is Time class contain all .hour .min .sec .date .mon .year .dow
  /********************************************************************/

/*************************************************************************************/
/*                                 Custom Function START                             */
/*************************************************************************************/

void MainDisplay(){


   if (CursPlace == Home) RTCC = rtc.getTime();
   
   lcd.setCursor(0,0);
   lcd.print("Time: ");
   if (RTCC.hour < 10) lcd.print("0");
   lcd.print(RTCC.hour); lcd.print(":");
   if (RTCC.min < 10) lcd.print("0"); 
   lcd.print(RTCC.min);  lcd.print(":");
   if (RTCC.sec < 10) lcd.print("0"); 
   lcd.print(RTCC.sec);

   
   lcd.setCursor(0,1);
   lcd.print("Date: ");
   if (RTCC.date < 10)lcd.print("0");
   lcd.print(RTCC.date); lcd.print("/"); 
   if (RTCC.mon < 10) lcd.print("0");
   lcd.print(RTCC.mon);  lcd.print("/"); 
   lcd.print(RTCC.year);
   
   //lcd.print(rtc.getDateStr(FORMAT_SHORT,FORMAT_LITTLEENDIAN,'/'));
  
   lcd.setCursor(0,2);
   lcd.print("Day:  ");
   lcd.print(rtc.getDOWStr(FORMAT_SHORT));
  
   lcd.setCursor(0,3);
   lcd.print("Temp: ");
   lcd.print(rtc.getTemp());
   lcd.print(" C");
  
}
/*************************************************************************************/
/*                                 Custom Function END                             */
/*************************************************************************************/


void setup() { 

  
  CursPlace = Home; //Set Cursor in home position
  
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
  //===========================================================================================================
    if (!digitalRead(SELECT_BUTTON)){
      
      CursPlace = CursPlace + 1;
      while(!digitalRead(SELECT_BUTTON));
       
        if(CursPlace > DOW_ADR){ //Write all RTCC Data and send it to DS3231
            CursPlace = Home;
            rtc.setTime(RTCC.hour, RTCC.min, RTCC.sec); 
            rtc.setDate(RTCC.date, RTCC.mon, RTCC.year);
            rtc.setDOW(RTCC.dow);              
        }
      
      delay(20);
  }

  //UP BUTTON REACTION
  //===========================================================================================================
  if (!digitalRead(UP_BUTTON)){
    
         
         
         if(CursPlace == YEAR_ADR){//Curssor is pointed on the Month
         RTCC.year++;//Incrase day of month
         if(RTCC.year > 2099)RTCC.year = 2000; 
         }
         //-----------------------------------------------------
         if(CursPlace == MONTH_ADR){//Curssor is pointed on the Month
         RTCC.mon++;//Incrase day of month
         if(RTCC.mon > 12)RTCC.mon = 0; //HERE WE NEED MORE VERIFICATIONS!!!
         }
         //-----------------------------------------------------
         if(CursPlace == DAY_ADR){//Curssor is pointed on the Day
         RTCC.date++;//Incrase day of month
         if(RTCC.date > 31)RTCC.date = 0; //HERE WE NEED MORE VERIFICATIONS!!!
         }
         //-----------------------------------------------------
          if(CursPlace == HOUR_ADR){ //Curssor is pointed to Hour
          RTCC.hour++; //Incrase Hour
          if(RTCC.hour > 23)RTCC.hour = 0;//Check If Hour is reached 23 and turn back to 0 
          //rtc.setTime(RTCC.hour, RTCC.min, RTCC.sec);               
         }
         //-----------------------------------------------------

         if(CursPlace == MINUTES_ADR){ //Curssor is pointed to Minutes
          RTCC.min++; //Incrase Minutes
          if(RTCC.min > 59)RTCC.min = 0;//Check If Minutes is reached 59 and turn back to 0 
          //rtc.setTime(RTCC.hour, RTCC.min, RTCC.sec);               
         }
         //-----------------------------------------------------

         if(CursPlace == SECONDS_ADR){ //Curssor is pointed to Seconds
          RTCC.sec++; //Incrase Minutes
          if(RTCC.sec > 59)RTCC.sec = 0;//Check If Seconds is reached 59 and turn back to 0 
          //rtc.setTime(RTCC.hour, RTCC.min, 0); //Zero seconds               
         }
         //-----------------------------------------------------
    
        if(CursPlace == DOW_ADR){ //Curssor is pointed to Day Of Week
          RTCC.dow++; //Incrase Day Of Week
          if(RTCC.dow > SUNDAY)RTCC.dow = MONDAY;//Check Day If is SunDay turn Back to Monday
          rtc.setDOW(RTCC.dow);//Write to back to DS3231          
         }
         //-----------------------------------------------------

         
       while(!digitalRead(UP_BUTTON));
       delay(20);
       MainDisplay();
  }

  //DOWN BUTTON REACTION
  //===========================================================================================================
  if (!digitalRead(DOWN_BUTTON)){
    
         if(CursPlace == YEAR_ADR){ //Curssor is pointed to Year
          if(RTCC.year == 2000) RTCC.year = 2099;//Check If Year is reached 2000 and turn back to 2099 
          else RTCC.year--;//Decrase Month
         }
         //-----------------------------------------------------
         if(CursPlace == MONTH_ADR){ //Curssor is pointed to Month
          if(!RTCC.mon) RTCC.mon = 12;//Check If Month is reached 0 and turn back to 12 
          else RTCC.mon--;//Decrase Month
         }//HERE WE NEED MORE VERIFICATIONS!!!
         //-----------------------------------------------------
         if(CursPlace == DAY_ADR){ //Curssor is pointed to Day
          if(!RTCC.date) RTCC.date = 31;//Check If Day is reached 0 and turn back to 31 
          else RTCC.date--;//Decrase Day
         }//HERE WE NEED MORE VERIFICATIONS!!!
         //-----------------------------------------------------
         if(CursPlace == HOUR_ADR){ //Curssor is pointed to Hour
          if(!RTCC.hour) RTCC.hour = 23;//Check If Hour is reached 0 and turn back to 23 
          else RTCC.hour--;//Decrase Hour
         }
         //-----------------------------------------------------
         if(CursPlace == MINUTES_ADR){ //Curssor is pointed to Minutes
          if(!RTCC.min)RTCC.min = 59;//Check If Minutes is reached 0 and turn back to 59 
          else RTCC.min--; //Decrase Minutes            
         }
         //-----------------------------------------------------
         if(CursPlace == SECONDS_ADR){ //Curssor is pointed to Seconds
          if(!RTCC.sec)RTCC.sec = 59;//Check If Seconds is reached 0 and turn back to 59 
          else RTCC.sec--; //Decrase Seconds      
         }
         //-----------------------------------------------------
         if(CursPlace == DOW_ADR){ //Curssor is pointed to Day Of Week
          RTCC.dow--; //Decrase Day Of Week
          if(RTCC.dow < MONDAY)RTCC.dow = SUNDAY; //Check Day If is Monday turn back to SunDay 
          rtc.setDOW(RTCC.dow);//Write to back to DS3231          
         }
         //------------------------------------------------------
         
       while(!digitalRead(DOWN_BUTTON)); //Wait for relase the button
       delay(20);//Debaunce relase
       MainDisplay();
   }
 
  
   

       

  
   
       //Turn Off curssor when rotate all parameters
       if(CursPlace == Home){
        lcd.noBlink();
        MainDisplay(); //Update Main display      
       }
       
       else{
       lcd.blink();
       }
       
       //Place Curssor on the Time
       //--------------------------------------------
       if(CursPlace == HOUR_ADR){
        lcd.setCursor(7,0);
       }
       if(CursPlace == MINUTES_ADR){
        lcd.setCursor(10,0);
       }
       if(CursPlace == SECONDS_ADR){
        lcd.setCursor(13,0);
       }

       //Place Curssor on the Date
       //--------------------------------------------
       if(CursPlace == DAY_ADR){
        lcd.setCursor(7,1);
       }
       if(CursPlace == MONTH_ADR){
        lcd.setCursor(10,1);
       }
       if(CursPlace == YEAR_ADR){
        lcd.setCursor(15,1);
       }

       //Place Curssor on the Day Of Week
       //-------------------------------------------
       if(CursPlace == DOW_ADR){
        lcd.setCursor(6,2);
       }
       
 
   delay(10);
   
}
