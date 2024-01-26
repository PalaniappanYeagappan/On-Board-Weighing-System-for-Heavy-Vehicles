#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>

WidgetLCD lcd(V2);

char auth[] = &quot;s6EDZ388YrMh-_W_pZQlDLQmYgmziInp&quot;;

// WiFi credentials.
// Set password to &quot;&quot; for open networks.
char ssid[] = "DESKTOP-KL7J4MU 8661";
char pass[] = "1l8891<C";

SimpleTimer timer;

String myString; // complete message from Arduino, which consists of sensors data
char rdata; // received characters
String weight;
int firstVal;

// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means that you define how often to send data to Blynk App.
void myTimerEvent()
{
  Blynk.virtualWrite(V1, millis() / 1000);
}

void setup()
{
  Serial.begin(9600);
  
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L,sensorvalue1);
}

void loop()
{
  if (Serial.available() == 0 )
  {
    Blynk.run();
    timer.run(); // Initiates BlynkTimer
  }
  
  if (Serial.available() &gt; 0 )
  {
    rdata = Serial.read();
    myString = myString+ rdata;
    // Serial.print(rdata);
    if( rdata == &#39;\n&#39;)
    {
      Serial.println(myString);
      weight = getValue(myString, ',', 0);
      myString = &quot;&quot;;
    }
  }
}

void sensorvalue1()
{
  lcd.clear();
  lcd.print(0,0,weight);
  lcd.print(0,1,"ON-BOARD WEIGHING SYSTEM");
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  
  for (int i = 0; i <= maxIndex && found <= index; i++) 
  {
    if (data.charAt(i) == separator || i == maxIndex) 
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
