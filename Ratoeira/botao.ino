void verifica_botao(){
  long now = millis();  

  readingBotao1 = digitalRead(pinBotao1);
  if(readingBotao1 != botao1OldState){
      debounceTimeBotao1 = now;
  }
  if(now - debounceTimeBotao1 > 200){
    if(readingBotao1 != botao1State){
      botao1State = readingBotao1;
      // situação do sernsor
      if(botao1State == HIGH){
        client.publish(sensor_topic, off_cmd);
        // ativa o rele
        if(statusRatueira == 1){
          digitalWrite(pinRele1, HIGH);
          client.publish(rele1_state_topic, on_cmd);
          client.publish(status_topic, "Disparada");
          timeRele = now;
          statusRatueira = 2;
        }
      } else {
        client.publish(sensor_topic, on_cmd);
      }
      
      
    }
  }
  botao1OldState = readingBotao1;

  // código para desarmar despois de 30 segundos disparada
  if(statusRatueira == 2 && now - timeRele > 30000){
    digitalWrite(pinRele1, LOW);
    client.publish(rele1_state_topic, off_cmd);
    client.publish(status_topic, "Desarmada");
    botao1State == LOW;
    statusRatueira = 0;
  }

  // código para armar a ratueira 
  if(botao1State == HIGH){
    timeStatusArmada = now;
  }
  if(statusRatueira == 0 && botao1State == LOW && now - timeStatusArmada > 15000){
    statusRatueira = 1;
    client.publish(status_topic, "Armada");
    botao1State == LOW;
  }
}



