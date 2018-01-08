/*
   Timer for Christmass Tree ligths
   Author: Gabriele Tasselli
   Date: 12/2/2017
   Board: Arduino M0Pro with Sunfounder relay module (5V)
*/
#include <RTCZero.h>
int Relay = 6; //Relay control pin
enum LigthStateEnum : bool {ON = true, OFF = false};
LigthStateEnum Lstate;
RTCZero rtc;
void setup() {
  // put your setup code here, to run once:
  pinMode(Relay, OUTPUT);
  LightOFF();
  Serial.begin(38400);
  while (!Serial);
  Serial.println(F("\nChristmass Tree Light Timer"));
  Serial.println(F("\n12/12/2017, FW ver 1.0"));

  Serial.println(F("\nClock need to be set --- enter HH:MM.<cr>"));

  bool inok = false;
  unsigned int hh;
  unsigned int mm;
  do
  {
    char intime[6];
    Serial.readBytesUntil('\n', intime, 6);
    Serial.println();
    //    for (int cc=0; cc<6; cc++)
    //    {
    //      Serial.print("[");Serial.print(cc);Serial.print("]=");Serial.println(String(intime[cc]));
    //    }
    if ((intime[2] == ':') & (intime[5] == '.'))
    {
      String hours = String(intime[0]);
      hours += String(intime[1]);

      String minuts = String(intime[3]);
      minuts += String(intime[4]);

      hh = hours.toInt();
      mm = minuts.toInt();
      //      Serial.print("h_str=");Serial.println(hours);
      //      Serial.print("h_uint=");Serial.println(hh);
      //      Serial.print("m_str=");Serial.println(minuts);
      //      Serial.print("m_uint=");Serial.println(mm);
      if ((hh >= 0) & (hh<24) & (mm >= 0) & (mm < 60)) inok = true;
      else Serial.println(F("Invalid time entered"));
    }

    delay(500);
  } while (!inok);
  rtc.begin();
  rtc.setTime(hh, mm, 0);
  rtc.setDate(1, 1, 17);
  rtc.setAlarmTime(19, 00, 0);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  rtc.attachInterrupt(alarmMatch);
  Serial.println(F("Clock setted"));
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("\nTime="); Serial.print(rtc.getHours()); Serial.print(':'); Serial.print(rtc.getMinutes());
  delay(60000);
}

void alarmMatch()
{
  if (Lstate == ON)
  {
    Serial.println("\nLight turned OFF");
    LightOFF();
    rtc.setAlarmTime(19, 00, 0); //Turn  on at 19:00
    Serial.println(F("\nNext event at 19:00"));
  }
  else
  {
    Serial.println("\nLight turned ON");
    LightON();
    rtc.setAlarmTime(23, 00, 0); //turn off at 23:00
    Serial.println(F("\nNext event at 23:00"));
  }
}

void LightON()
{
  digitalWrite(Relay, LOW);
  Lstate = ON;
}
void LightOFF()
{
  digitalWrite(Relay, HIGH);
  Lstate = OFF;
}

