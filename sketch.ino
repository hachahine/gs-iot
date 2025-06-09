#include <WiFi.h>
#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ThingerESP32.h>

// Credenciais do Thinger.io
#define USERNAME "dskaf"
#define DEVICE_ID "esp32"
#define DEVICE_CREDENTIAL "W-J5E65HN%p@LUx5"

// Wifi
#define SSID "Wokwi-GUEST"
#define SSID_PASSWORD ""

// pinos
#define DHTPIN 13
#define DHTTYPE DHT22
#define DSPIN 15
#define POTPIN 34  // Simula umidade do solo

// instanciando a conexão com o thinger io
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);


// sensores
DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(DSPIN);
DallasTemperature ds18b20(&oneWire);

void setup() {
  Serial.begin(115200);
  Serial.println("=== INICIANDO SISTEMA DE MONITORAMENTO AGRÍCOLA ===");

  dht.begin();
  ds18b20.begin();
  pinMode(POTPIN, INPUT);

  // conectando wifi
  thing.add_wifi(SSID, SSID_PASSWORD);
  Serial.println("Wifi conectado com sucesso!");

  // válidações e captação de dados
  thing["sensores_agricolas"] >> [](pson& out){
    float t_ar = dht.readTemperature();
    float u_ar = dht.readHumidity();
    ds18b20.requestTemperatures();
    float t_solo = ds18b20.getTempCByIndex(0);

    int valorAnalogico = analogRead(POTPIN);
    float umidade_solo = map(valorAnalogico, 0, 4095, 0, 100);

    // Lógica de status
    String estado_geral;

    if (t_solo < 15 && umidade_solo < 30) {
      estado_geral = "Crítico - Solo frio e seco";

    } else if (t_solo >= 15 && t_solo < 25 && umidade_solo >= 30 && umidade_solo <= 70) {
        estado_geral = "Normal";

    } else if ((t_solo >= 25 && t_solo < 35) || (umidade_solo < 30 || umidade_solo > 70)) {
        estado_geral = "Alerta - Verificar solo";

    } else if (t_solo >= 35) {
        estado_geral = "Crítico - Solo muito quente";

    } else {
        estado_geral = "Desconhecido";
}

    out["temperatura_ar"] = t_ar;
    out["umidade_ar"] = u_ar;
    out["temperatura_solo"] = t_solo;
    out["umidade_solo"] = umidade_solo;
    out["status"] = estado_geral;

    Serial.println("--- Dados Enviados ---");
    Serial.printf("T_ar: %.1f°C | U_ar: %.1f%% | T_solo: %.1f°C | U_solo: %.1f%%\n", t_ar, u_ar, t_solo, umidade_solo);
    Serial.println("----------------------");
  };
}

void loop() {
  // mantém a conexão ativa e envia dados pro dashboard
  thing.handle();  
}
