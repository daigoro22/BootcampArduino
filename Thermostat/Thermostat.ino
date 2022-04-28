#include <HTTPClient.h>
#include <ArduinoJson.h>

#define THERMO 34

const char* ssid = "NETGEAR_IOT";
const char* password = "";

const char* host = "https://754d-153-156-28-29.jp.ngrok.io/api/v1/temperature";

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
}

double thermoVal2Degree(uint32_t thermoVal,uint8_t bits,float thermoRefVolt,float actRefVolt,uint16_t degRange){
  return (degRange * thermoVal) / (1<<bits) * (thermoRefVolt/actRefVolt);
}

void loop() {
  delay(60000);
    
  HTTPClient client;
  if(!client.begin(host)){
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
    Serial.printf("[POST] Send to server (URL:%s)\n",host);
    Serial.println(client.getString());
  }else{
    Serial.printf("[POST] Failed to send (URL:%s)\n",host);
    Serial.println(json_string);
  }
}
