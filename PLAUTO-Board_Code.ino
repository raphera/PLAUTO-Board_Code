/*
 Name:		PLAUTO_Board_Code.ino
 Created:	19/05/2019 12:48:49
 Author:	raphera
 E-mail:	raphaeldefreitas2009@gmail.com
*/

//Variaveis Auxiliares
bool aux = false;

//Inclusao de Parametros
	//Gerais
	#include "param.h"

	//Unicos
	#include "param_uni.h"

//Bibliotecas Necessarias
	//Teceiras
	#include "LiquidCrystal_I2C.h"
	#include "FPS_GT511C3.h"
	#include "LcdBarGraphX.h"

	//Inclusas
	#include "SoftwareSerial.h"
	#include <ESP8266WiFi.h>
	#include <ESP8266mDNS.h>
	#include <WiFiUdp.h>
	#include <ArduinoOTA.h>

//Criando Objetos de Controle
FPS_GT511C3 fps(RXFPS, TXFPS);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LcdBarGraphX lbg(&lcd, 16, 0, 1);

void setup() {
	pinMode(PRELE, OUTPUT);
	digitalWrite(PRELE, HIGH); //Logica inversa (configuracao do IO esp8266)
	Serial.begin(115200);
	Serial.println("Iniciou com sucesso!");
	Serial.print("Frequencia da CPU: " + String(ESP.getCpuFreqMHz()) + "Mhz\n");
	lcd.begin(16, 2);
	lcd.backlight();
	lcd.setCursor(2, 0);
	lcd.print("PLAUTO@2019");
	lcd.setCursor(0, 1);
	lcd.print("V.22/05/2019-B3");

	fps.Open();
	fps.SetLED(true);

	//Inicializacao do Wi-Fi
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("Falha ao conectar Wi-Fi! Reiniciando...");
		delay(5000);
		ESP.restart();
	}
	lcd.setCursor(0, 1);
	lcd.print("               ");

	//OTA.
	ArduinoOTA.onStart([]() {
		String type;
		if (ArduinoOTA.getCommand() == U_FLASH) {
			type = "sketch";
		}
		else { // U_SPIFFS
			type = "filesystem";
		}

		// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
		Serial.println("Iniciando atualizacao " + type);
		});
	ArduinoOTA.onEnd([]() {
		Serial.println("\nEnd");
		lcd.setCursor(0, 0);
		lcd.print("                ");
		lcd.setCursor(0, 0);
		lcd.print("Finalizando...");
		});
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		Serial.printf("Progresso: %u%%\r\n", (progress / (total / 100)));
		lcd.setCursor(0, 0);
		lcd.print("Baixando OTA:");
		lbg.drawValue(progress / (total / 100), 100);
		});
	ArduinoOTA.onError([](ota_error_t error) {
		Serial.printf("Erro[%u]: ", error);
		if (error == OTA_AUTH_ERROR) {
			Serial.println("Falha na Autenticacao");
		}
		else if (error == OTA_BEGIN_ERROR) {
			Serial.println("Falha ao iniciar OTA");
		}
		else if (error == OTA_CONNECT_ERROR) {
			Serial.println("Falha na Conex�o");
		}
		else if (error == OTA_RECEIVE_ERROR) {
			Serial.println("Falha no Recebimento");
		}
		else if (error == OTA_END_ERROR) {
			Serial.println("Falha ao terminar OTA");
		}
		});
	ArduinoOTA.begin();
	Serial.println("OTA Pronto!");
	Serial.print("IP: ");
	Serial.println(WiFi.localIP());
}

void loop() {
	yield();
	ArduinoOTA.handle();
}
