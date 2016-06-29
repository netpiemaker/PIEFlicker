int analogRef = 1024;
void setup() 
{
  Serial.begin(19200);
}

void loop() 
{
  Serial.println(digitalRead(2));
  //Serial.println(analogRead(0));
  //Serial.println(analogRef);
}
