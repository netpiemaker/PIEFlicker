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
    if(digitalRead(5))
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

void flicker(int pin_out,String data)  
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

void listen()
{
  listening = true;
  attachInterrupt(5,signal,CHANGE);
}

void setup() 
{
  //==== คำสั่งรับ
  Serial.begin(9600);
  listen(); 
}

void loop() 
{
  //==== คำสั่งส่ง
  //delay(10000);
  //flicker(8,"1110100010101110011000010111000110010110001010010010110001011110010101010100101010110001100100010011111100101000110000011110111111000101101011010011011011001001000010110010100101000110010010101001010010101000011101101101011111101000010111001101000011011001010110100101100011100101001010010011110100001001110100001110011000100100100011110101000101011101010110001100100101010001011101011011000010111110");
}
