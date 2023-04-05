#include <FirebaseESP32.h>
#include  <WiFi.h>
#include "DHT.h"
#include <HTTPClient.h>
#include <UrlEncode.h>

int t=1;

#define ADC_VREF_mV    3300.0 // in millivolt
#define ADC_RESOLUTION 4096.0
#define PIN_LM35       36
#define PINIR   4  
#define PIRR   5    


#define FIREBASE_HOST "fir-contact-51ee2-default-rtdb.firebaseio.com"
#define WIFI_SSID "Mera wala net" // Change the name of your WIFI
#define WIFI_PASSWORD "12345678" // Change the password of your WIFI
#define FIREBASE_Authorization_key "jmc6YvW1PfKVnHAiJ7j3XGcxzbUonmtzbEhwKTnO"

#define DHTPIN 14    

#define DHTTYPE DHT11 
String phoneNumber = "+918340392013";
String apiKey = "6395251";


DHT dht(DHTPIN, DHTTYPE);

FirebaseData firebaseData;
FirebaseJson json;


void sendMessage(String message){

  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);    
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}


void setup() {

 Serial.begin(115200);
  dht.begin();
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);
  sendMessage("Hello");
   sendMessage(" #Chamber 9 Security Update");
}

void loop() {
  
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  String pre; 
  String gate;
  String motion;
  int IR = digitalRead(PINIR);
  int MOT = digitalRead(PIRR);
  // read the ADC value from the temperature sensor
  int adcVal = analogRead(PIN_LM35);
  // convert the ADC value to voltage in millivolt
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  // convert the voltage to the temperature in °C
  float tempC = milliVolt / 10;
  // convert the °C to °F
  float tempF = tempC * 9 / 5 + 32;
  
  
  
   if (isnan(hum) || isnan(temp)  ){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
   // print the temperature in the Serial Monitor:
  Serial.print("Temperature2: ");
  Serial.print(tempC);   // print the temperature in °C
  Serial.print("°C");
  Serial.print("  ~  "); // separator between °C and °F
  Serial.print(tempF);   // print the temperature in °F
  Serial.println("°F");
  Firebase.setFloat(firebaseData, "/chamber1/Coolantt", tempF);

  
  Serial.print("Temperature1: ");
  Serial.print(temp);
  Serial.print("°C");
  Serial.print(" Humidity: ");
  Serial.print(hum);
  Serial.print("%");
  Serial.println();
   Firebase.setFloat(firebaseData, "/chamber1/VegetableT", temp);
  Firebase.setFloat(firebaseData, "/chamber1/Humidity", hum);
 
  if(tempC==temp){
    Serial.println(" preserve mode is ON");
    pre= "preserve mode are ON";
  }
  else{
    pre= "preserve mode is OFF";
    Serial.println(" preserve mode is OFF");
  }
  Firebase.setString(firebaseData, "/chamber1/Preserved", pre);

  
 if(MOT==1){
    motion=" Motion detected";
    Serial.println("Motion detected");
  }
  else{
    Serial.println("Motion not detected");
    motion="Motion not detected";
 }           
 Firebase.setString(firebaseData, "/chamber1/MotionStatus",motion );
 

  if(IR==1){
    gate=" OPEN";
    Serial.println("gate is OPEND");
  }
  else{
    Serial.println("gate is CLOSED");
    gate="CLOSED";
 }           
 Firebase.setString(firebaseData, "/chamber1/GateStatus", gate);


 if(IR==1){
    sendMessage("Gate is opend");
    sendMessage("Gate of chamber 9 is open ");
    sendMessage("Please close the door ");
    sendMessage("Other than vegitable lose his preservative temperature ");
    t=0;
  }else if(t==0){
    sendMessage("Gate is closed");
    t=1;

  } 
 if(MOT==1){
    sendMessage("Motion detected");
    sendMessage("May be something occur in chamber 9");
    sendMessage("Check the chamber 9");
    t=0;
  }else if(t==0){
    sendMessage("motion is not detected");
    sendMessage("every thing is OK in chamber 9");
    t=1;

  } 
  
 
  
  
   
      
   delay(200);
} 
