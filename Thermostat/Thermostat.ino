#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "thermodef.h"
#include "setting.h"

const char* ssid = "NETGEAR_IOT";
const char* password = "";

StaticJsonDocument<JSON_OBJECT_SIZE(4)> json_array;

void setup() {
  Serial.begin(115200);  
  pinMode(THERMO,INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");

  Serial.println(WiFi.localIP()); 
  
  ledcSetup(LEDC_CHANNEL_0,LEDC_BASE_FREQ,LEDC_BASE_BIT);
  ledcAttachPin(RLED,LEDC_CHANNEL_0);
  ledcAttachPin(GLED,LEDC_CHANNEL_1);
  ledcAttachPin(BLED,LEDC_CHANNEL_2); 
}

void loop() {
  HTTPClient client;
  if(!client.begin(HOST)){
    Serial.println("Connection failed");
  }

  char json_string[1024];
  
  uint32_t thermoVal0to4096 = analogReadMilliVolts(THERMO);
  double degree = thermoVal2Degree(thermoVal0to4096,12,4.096,5,165);

  json_array["degree"] = degree;
  json_array["degreeType"] = "Celsius";
  json_array["longitude"] = 0;
  json_array["latitude"] = 0;

  serializeJson(json_array, json_string, sizeof(json_string));
  client.addHeader("Content-Type", "application/json");

  int status_code = client.POST((uint8_t *)json_string,strlen(json_string));
  //int status_code = client.GET();
  if(status_code==201){
    Serial.printf("[POST] Send to server (URL:%s)\n",HOST);
    Serial.println(client.getString());
  }else{
    Serial.printf("[POST] Failed to send (URL:%s)\n",HOST);
    Serial.println(json_string);
  }
  
  updateDuty(degree);
  
  ledcWrite(LEDC_CHANNEL_0,rDuty);
  ledcWrite(LEDC_CHANNEL_1,gDuty);
  ledcWrite(LEDC_CHANNEL_2,bDuty);

  delay(60000);
}
