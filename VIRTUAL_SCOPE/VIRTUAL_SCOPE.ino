int analogRef = 1024;
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  Serial.println(digitalRead(5));
  //Serial.println(analogRead(0));
  //Serial.println(analogRef);
}
