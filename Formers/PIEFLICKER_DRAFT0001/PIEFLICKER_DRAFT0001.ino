//===================================
//           NETPIE PROJECT
//===================================
//          CODENAME: FRISK
//          LED MANCHESTER 
//         DATA COMMUNICATION
//===================================
// NARIN BANNASAN / SIRAWIT MOONRINTA
//===================================
//   DIRECTOR: CHAVEE ISSARIYAPAT
//===================================

int rate = 10;
int buffertime = 2;
int transmission_phase = 0;
int hightime;
int lowtime;

bool listening = false;

void signal()
{
  if(listening)
  {
    if(digitalRead(2))
    {
      if(millis() - lowtime >= rate+buffertime)
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
      if(millis() - hightime >= rate+buffertime)
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
      else{}
    }
  }
}

void frisk(int pin_out,String data)  
{
  pinMode(pin_out,OUTPUT);
  delay(rate);
  digitalWrite( pin_out, HIGH );
  delay(rate*10);
  digitalWrite( pin_out, LOW );
  delay(buffertime);  
  
  for(int i = 0; i <= data.length(); i++)
  {
    switch(data[i])
    {
      case '0': //FRISK:FALLING
      digitalWrite(pin_out, HIGH);
      delay(rate);
      digitalWrite(pin_out, LOW);
      delay(rate);
      break;
      
      case '1': //FRISK:RISING
      digitalWrite( pin_out, LOW );
      delay(rate);
      digitalWrite( pin_out, HIGH );
      delay(rate);
      break;
    }
  }
  delay(rate*10);
  digitalWrite( pin_out, HIGH );
  delay(buffertime);  
  digitalWrite( pin_out, LOW );
  delay(buffertime);  
  digitalWrite(pin_out,LOW);
}

void chara()
{
  listening = true;
  attachInterrupt(0,signal,CHANGE);
}
void setup() 
{
  Serial.begin(9600);
  chara();
}

void loop() 
{
  delay(7000);
  //frisk(8,"1011110010010100101000110000101100100111011110100111100110000010001001001011001");
}
