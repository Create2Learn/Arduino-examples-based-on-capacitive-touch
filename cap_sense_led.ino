#include <CapacitiveSensor.h>

int led1 = 3;  //change '10' to any desired pin...
long time1 = 0;
long time2 = 0;
int led2 =  9;
int state1 = LOW;
int state2 = LOW;

boolean yes;
boolean yes1;
boolean previous1= false;
boolean previous2 = false;

int debounce = 200;

CapacitiveSensor   cs_5_2 = CapacitiveSensor(5,2); // 1M resistor between pins 5 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_8_12 = CapacitiveSensor(8,12);// 1M resistor between pins 8 & 12, pin 12 is sensor pin, add a wire and or foil if desired
void setup()
{
   cs_5_2.set_CS_AutocaL_Millis(0xFFFFFFFF); //Calibrate the sensor... 
   cs_8_12.set_CS_AutocaL_Millis(0xFFFFFFFF);
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
   Serial.begin(9600);
}

void loop()                    
{
    long total1 =  cs_5_2.capacitiveSensor(30);
    long total2 =  cs_8_12.capacitiveSensor(30);
    
    if (total1 > 60){yes = true;}
    else {yes = false;}    
    
    // to toggle the state of state
    if(yes == true && previous1  == false && millis() - time1>debounce){
      
       if(state1 == LOW){
         state1 = HIGH;
       }
       else 
         state1 = LOW;
         time1 = millis();     
       
    }
    digitalWrite(led1, state1);
    previous1 = yes;
       
    if (total2 > 60){yes1 = true;}
    else {yes1 = false;}    
    
    // to toggle the state of state
    if(yes1 == true && previous2  == false && millis() - time2>debounce){
      
       if(state2 == LOW){
         state2 = HIGH;
       }
       else 
         state2 = LOW;
         time2 = millis();     
      
    }
      digitalWrite(led2, state2);
    previous2 =  yes1;
      Serial.print(millis()-time1);
      Serial.print("\t");
      Serial.print(total1);
      Serial.print("\t");
      Serial.print(millis()-time2);
      Serial.print("\t");
      Serial.println(total2);
      delay(10);
}
