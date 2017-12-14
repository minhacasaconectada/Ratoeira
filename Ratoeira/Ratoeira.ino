

/*
 * Jonathas Eide Fujii
 * jonathasfujii@gmail.com
 * Criado: 01/01/2017
 * Atualizado: 09/10/2017
 * 
 * Arduino IDE v1.8.0
 */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson
#include <PubSubClient.h> // http://pubsubclient.knolleary.net/


const byte pinLedEsp = 2;

//// WIFI ////
const char* ssid = "";
const char* password = "";
const char* senha_ota = "";

//// MQTT ////
const char* mqtt_server = "192.168.1.16";
const char* mqtt_username = "";
const char* mqtt_password = "";
const char* client_id = "esp01-ratoeira"; // Must be unique on the MQTT network
const char* start_state_topic = "casa/ratoeira/start";
const char* rele1_state_topic = "casa/ratoeira/rele1";
const char* rele1_set_topic = "casa/ratoeira/rele1/set";
const char* sensor_topic = "casa/ratoeira/sensor";
const char* status_topic = "casa/ratoeira/status";

const char* on_cmd = "ON";
const char* off_cmd = "OFF";

WiFiClient espClient;
PubSubClient client(espClient);

//// Atuadores Relay ////
const byte pinRele1 = 2;

//// Botão ////
const int debouncerTime = 200;


const byte pinBotao1 = 0;
byte readingBotao1 = HIGH;
byte botao1State = HIGH;
byte botao1OldState = HIGH;
long debounceTimeBotao1 = 0;
long timeRele = 0;

byte statusRatueira = 0;
long timeStatusArmada = 0;


