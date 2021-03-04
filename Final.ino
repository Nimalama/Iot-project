

#define BLYNK_PRINT Serial


#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
char auth[] = "mB0vMTr4OxbRVO7GMyI3UKFvA9TA_ltA";


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "saibaba";  //Enter your WIFI Name
char pass[] = "12345678";  //Enter your WIFI Password

int buzzer = D2;
int smokeA0 = A0;
#define DHTPIN 2          // D4 pin
// Your threshold value. You might need to change it.
int sensorThres = 190;

// Uncomment whatever type you're using!


#define DHTTYPE DHT22   // DHT 22
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void sendSensor1(){
  int analogSensor = analogRead(smokeA0);

 Serial.print("Pin A0: ");
 Serial.println(analogSensor);
 // Checks if it has reached the threshold value
 if (analogSensor > sensorThres)
 {
   tone(buzzer, 1000, 200);
   Blynk.notify(" Alert: Fire in the Shop");  
 }
 else
 {
   noTone(buzzer);
 }
 delay(100);
}

void setup()
{
  pinMode(buzzer, OUTPUT);
 pinMode(smokeA0, INPUT);
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  Blynk.notify("The station is ready to use.");
  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  sendSensor1();
  Blynk.run();
  timer.run();
}
