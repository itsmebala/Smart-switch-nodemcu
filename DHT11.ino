#include "DHT.h"
#define BLYNK_PRINT Serial #include <ESP8266WiFi.h> #include <BlynkSimpleEsp8266.h> BlynkTimer timer;
WidgetLCD lcd(V5);


#define DHTTYPE DHT11 #define dht_dpin D3
DHT dht(dht_dpin, DHTTYPE);


char auth[] = "351s8kgbKGST-LwqBtwuMOvkhK3olQWu"; char ssid[] = "selva";
char pass[] = "selvabeece";


void checktouchButton(); int relay1State = HIGH;
int touchButton1State = HIGH; int relay2State = HIGH;
int touchButton2State = HIGH;


#define RELAY_PIN_1  12  //D6
#define RELAY_PIN_2 16  //D0
#define Touch_Swnsor_1  15  //D8
#define Touch_Swnsor_2  14  //D5


#define VPIN_BUTTON_1 V12
 
#define VPIN_BUTTON_2 V13



BLYNK_CONNECTED() {
Blynk.syncVirtual (VPIN_BUTTON_1); Blynk.syncVirtual (VPIN_BUTTON_2);
}


BLYNK_WRITE(VPIN_BUTTON_1) {
relay1State = param.asInt(); digitalWrite(RELAY_PIN_1, relay1State);
}


BLYNK_WRITE(VPIN_BUTTON_2) {
relay2State = param.asInt(); digitalWrite(RELAY_PIN_2, relay2State);
} BLYNK_WRITE(V0)
{
int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable analogWrite(D1,pinValue);
Blynk.virtualWrite(V1, pinValue); Serial.print("V0 Slider value is: "); Serial.println(pinValue);
}


void checktouchButton()
{
if (digitalRead(Touch_Swnsor_1) == LOW) {
 
// pushButton1State is used to avoid sequential toggles if (touchButton1State != LOW) {

// Toggle Relay state relay1State = !relay1State;
digitalWrite(RELAY_PIN_1, relay1State);


// Update Button Widget Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
}
touchButton1State = LOW;
} else {
touchButton1State = HIGH;
}


if (digitalRead(Touch_Swnsor_2) == LOW) {
// pushButton2State is used to avoid sequential toggles if (touchButton2State != LOW) {

// Toggle Relay state relay2State = !relay2State;
digitalWrite(RELAY_PIN_2, relay2State);


// Update Button Widget Blynk.virtualWrite(VPIN_BUTTON_2, relay2State);
}
touchButton2State = LOW;
} else {
touchButton2State = HIGH;
}
 

}
void setup()
{
Serial.begin(9600); Blynk.begin(auth, ssid, pass); dht.begin();
lcd.clear();
lcd.print(4, 0, "SMART"); lcd.print(2, 1, "SWITCH BOX");
delay(3000); pinMode(RELAY_PIN_1, OUTPUT);
pinMode(Touch_Swnsor_1, INPUT_PULLUP); digitalWrite(RELAY_PIN_1, relay1State);


pinMode(RELAY_PIN_2, OUTPUT);
pinMode(Touch_Swnsor_2, INPUT_PULLUP); digitalWrite(RELAY_PIN_2, relay2State);

// Setup a function to be called every 100 ms timer.setInterval(500L, checktouchButton);



}


void loop()
{
float h = dht.readHumidity(); float t = dht.readTemperature(); lcd.clear();
 
lcd.print(0, 0, "Humi:");
lcd.print(6, 0, h);
lcd.print(10, 0, " % ");
lcd.print(0, 1, "Temp:");
lcd.print(6, 1, t);
lcd.print(10, 1, " C ");


delay(1000); Blynk.run();
timer.run();
} 
