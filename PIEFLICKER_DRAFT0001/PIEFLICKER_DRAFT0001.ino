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
int buffertime = 5;

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
  delay(rate*5);
}

void setup() 
{
}

void loop() 
{
  delay(5000);
  frisk(8,"10101010101001011010110");
}
