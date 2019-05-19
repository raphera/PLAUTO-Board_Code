/*
 Name:		PLAUTO_Board_Code.ino
 Created:	19/05/2019 12:48:49
 Author:	raphera
*/

//Inclusão de Parâmetros
	//Gerais
	#include "param.h"
	
	//Únicos
	#include "param_uni.h"

//Bibliotecas Necessárias
	//Teceiras
	#include "LiquidCrystal_I2C.h"
	#include "FPS_GT511C3.h"

	//Inclusas
	#include "SoftwareSerial.h"

//Criando Objetos de Controle
FPS_GT511C3 fps(RXFPS, TXFPS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
	pinMode(PRELE, OUTPUT);
	digitalWrite(PRELE, HIGH); //Lógica inversa (configuração do IO esp8266)
	Serial.begin(9600);
	Serial.println("Iniciou com sucesso!");
	lcd.init();
	lcd.backlight();
	lcd.setCursor(2, 0);
	lcd.print("PLAUTO@2019");
	lcd.setCursor(1, 1);
	lcd.print("V.01/12/16-B3");

	fps.Open();
	fps.SetLED(true);
	
}

void loop() {
	yield();	
}
