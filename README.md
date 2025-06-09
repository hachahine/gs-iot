# Harvestime – Sistema de Monitoramento Agrícola Inteligente

O objetivo do projeto é monitorar variáveis ambientais críticas em áreas agrícolas, como **temperatura** e **umidade**, usando **IoT + MQTT + Thinger.io**, visando antecipar riscos e proteger plantações contra eventos extremos como **geadas** e **ondas de calor**.


##  Tecnologias Utilizadas

- **ESP32 (via Wokwi)** – simulação do hardware
- **DHT22** – temperatura e umidade do ar
- **DS18B20** – temperatura do solo
- **Potenciômetro** – simula umidade do solo
- **Thinger.io** – gateway MQTT e dashboard
- **MQTT** – protocolo de comunicação leve
- **C++ / Arduino** – lógica de leitura, envio e status

---

## Funcionamento em Tempo Real

A ESP32, simulada no Wokwi, realiza a leitura contínua dos sensores de temperatura, umidade do ar e umidade do solo. Os dados coletados são enviados em tempo real para o Thinger.io utilizando o protocolo MQTT.

O Thinger.io funciona simultaneamente como gateway MQTT e plataforma de visualização, recebendo os dados e atualizando automaticamente o dashboard do usuário

---

## Links do projeto

- Projeto desenvolvido na Wokwi: [Link projeto](https://wokwi.com/projects/432154312420754433)

- Visualização do dashboard Thinger.io: [Thinger.io](https://console.thinger.io/dashboards/dashboard_esp32?authorization=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJqdGkiOiJEYXNoYm9hcmRfZGFzaGJvYXJkX2VzcDMyIiwic3ZyIjoidXMtZWFzdC5hd3MudGhpbmdlci5pbyIsInVzciI6ImRza2FmIn0.OOar0ILsOBFi6_Xshmq48Av86wsSxYCA8noOtZ9PmDE)
