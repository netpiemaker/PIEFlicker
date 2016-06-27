int analogRef = 1024;
void setup() 
{
  Serial.begin(2400);
}

void loop() 
{
  Serial.println(digitalRead(2));
  //Serial.println(analogRead(0));
  //Serial.println(analogRef);
}
