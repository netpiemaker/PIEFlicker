//===================================
//           NETPIE PROJECT
//===================================
//          CODENAME: FRISK
//       PROJECT NAME: PIE_FLICKER
//-----------------------------------
//           LED MANCHESTER 
//         DATA COMMUNICATION
//===================================
//   DIRECTOR: CHAVEE ISSARIYAPAT
//===================================
// NARIN BANNASAN / SIRAWIT MOONRINTA
//  NECTEC/NSTDA AND NARIN AVIATION
//===================================

#define IN_PIN 2    //=== PIEFLICKER_SENSOR PIN

int transmission_rate = 10;       //=== HALF PULSE DURATION
int buffertime = 2;               //=== BUFFER TIME FOR ERROR CORRECTIONS

int transmission_phase;           //=== TRANSMISSION PHASE; 0 = START ; 1 = LISTENING ;

unsigned long hightime;           //=== VARIABLES TO STORE GO-HIGH TIME DATA
unsigned long lowtime;            //=== VARIABLES TO STORE GO-LOW TIME DATA

bool listening = false;           //=== LISTENING (RECEIVEING) STATE

void onSignal()                   
{
  if(listening)                   
  {
    if(digitalRead(IN_PIN))
    {
      if(millis() - lowtime >= transmission_rate+buffertime)
      {        
        switch(transmission_phase)
        {
          case 0 :
            hightime = millis();
          break;
      
          case 1 :
            hightime = millis();
            Serial.print("1");
          break;
        }
      }
    }
    else
    {
      if(millis() - hightime >= transmission_rate+buffertime)
      {       
        switch(transmission_phase)
        {
          case 0 :
            lowtime = millis();
            Serial.print("Recieved : ");
            transmission_phase = 1;
          break;
          
          case 1 :
            lowtime = millis();
            Serial.print("0");
          break;
        }
      }
    }
  }
}

void send(int PIN_OUT,String data)  
{
  pinMode(PIN_OUT,OUTPUT); delay(buffertime);
  digitalWrite(PIN_OUT, HIGH ); delay(transmission_rate*5);
  digitalWrite(PIN_OUT, LOW ); delay(buffertime);  
  
  for(int i = 0; i <= data.length(); i++)
  {
    switch(data[i])
    {
      case '0': //SEND 0 : FALLING
        digitalWrite(PIN_OUT, HIGH); delay(transmission_rate);
        digitalWrite(PIN_OUT, LOW); delay(transmission_rate);
      break;
      case '1': //SEND 1 : RISING
        digitalWrite(PIN_OUT, LOW ); delay(transmission_rate);
        digitalWrite(PIN_OUT, HIGH ); delay(transmission_rate);
      break;
    }
  }
  delay(buffertime);  
  digitalWrite(PIN_OUT, LOW );
}

void receive(int timeout)
{
  attachInterrupt(digitalPinToInterrupt(IN_PIN),onSignal,CHANGE);
  
  Serial.print("START -> ");
  listening = true;         //TRIGGER TO RECEIVE DATA
  lowtime = millis();       //SET LOWTIME TO START TIME
  transmission_phase = 0;   //TRANSMISSION PHASE = 1: START PHASE
  
  while(listening)
  {
    if(millis()-lowtime > timeout)
    {
      listening = false;
    }
  }
  detachInterrupt(digitalPinToInterrupt(IN_PIN));
  Serial.println(" : END");
}

void setup() 
{
  Serial.begin(9600);
  Serial.println("");
}

void loop() 
{
  receive(5000);
//  send(8,"1010100110010110101011010101001010101010111101010100");
//  delay(6000);
//  send(8,"0001010101010101010100101010101101010101010100101011");
//  delay(6000);
}

