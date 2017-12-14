void setup() {
 // Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }

  //// Atuadores Relay ////
  pinMode(pinRele1, OUTPUT);
  digitalWrite(pinRele1, LOW);
 
  //// Botão ////
  pinMode(pinBotao1, INPUT_PULLUP);
  
    
  //// MQTT ////
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop() {
  ArduinoOTA.handle();
  mqtt_loop();
  verifica_botao();
}
