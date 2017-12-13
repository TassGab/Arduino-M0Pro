#include <RTCZero.h>
int Relay = 6; //Relay pin
bool toggle;
RTCZero rtc;
void setup() {
  // put your setup code here, to run once:

  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);
  Serial.begin(38400);
  Serial.println("RTC test");
  rtc.begin();
  rtc.setTime(17, 29, 50);
  rtc.setDate(11, 12, 17);
  rtc.setAlarmTime(17, 30, 0);
  rtc.enableAlarm(rtc.MATCH_SS);
  rtc.attachInterrupt(alarmMatch);
  toggle = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Min=");
  Serial.println(rtc.getMinutes());
  delay(36000);
}

void alarmMatch()
{
  if (toggle)
  {
    digitalWrite(Relay, HIGH);
    Serial.println("OFF");
    toggle = false;
  }
  else
  {
    toggle = true;
    Serial.println("ON");
    pinMode(Relay, OUTPUT);
    digitalWrite(Relay, LOW);
  }
  rtc.setAlarmSeconds(10);
}

