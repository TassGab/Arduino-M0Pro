int Relay=6; //Relay pin
bool toggle;
void setup() {
  // put your setup code here, to run once:
pinMode(Relay,OUTPUT);
digitalWrite(Relay,LOW);
Serial.begin(38400);
Serial.println("Hello");
toggle=false;
}

void loop() {
  // put your main code here, to run repeatedly:

if(toggle) 
{
   digitalWrite(Relay,HIGH);
  Serial.println("OFf");
  toggle=false;
}
else 
{
  toggle=true;
  Serial.println("ON");
  pinMode(Relay,OUTPUT);
  digitalWrite(Relay,LOW);
}
delay(5000);
}
