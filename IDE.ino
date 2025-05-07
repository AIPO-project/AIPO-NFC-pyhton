#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

// Definindo o pino de comunicação I2C para o NFC
#define SDA_PIN 2
#define SCL_PIN 3

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(100);
  }

  // Inicializa o módulo NFC
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.println("Não foi possível encontrar o módulo NFC!");
    while (1);
  }

  nfc.SAMConfig();
  Serial.println("Pronto para comando do Python...");
}

void loop() {
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');

    // Se o comando recebido for para ler a TAG NFC
    if (comando.indexOf("ler_nfc") != -1) {
      Serial.println("Lendo TAG NFC...");

      uint8_t success;
      uint8_t uid[7];
      uint8_t uidLength;

      success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 1000);  // timeout de 1s

      if (success) {
        // Monta o UID
        String tagUID = "";
        for (int i = 0; i < uidLength; i++) {
          if (uid[i] < 0x10) tagUID += "0";
          tagUID += String(uid[i], HEX);
        }

        // Constrói e envia JSON
        String resposta = "{\"tag\":\"" + tagUID + "\"}";
        Serial.println(resposta);
      } else {
        Serial.println("{\"erro\":\"Nenhuma TAG detectada\"}");
      }
    }
  }
}

