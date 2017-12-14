void mqtt_loop(){
  //// MQTT ////
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    //Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(client_id, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(rele1_set_topic);
      
      char buffer[50];
      sprintf(buffer, "{\"client_id\":\"%s\",\"ip\":\"%s\"}", client_id, WiFi.localIP().toString().c_str());
      client.publish(start_state_topic, buffer);
      client.publish(status_topic, "Desarmada");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print(topic);
  
  if (strcmp(topic,rele1_set_topic)==0){//// Rele 1 ////
      char msg[length];
      snprintf(msg, length+1, "%s", payload);
      if (strcmp(msg,on_cmd)==0) { 
        digitalWrite(pinRele1, LOW);   
        client.publish(rele1_state_topic, on_cmd);
      } else {
        digitalWrite(pinRele1, HIGH);   
        client.publish(rele1_state_topic, off_cmd);
      }
  }
}



