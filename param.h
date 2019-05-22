#pragma once
//Configura��o dos Pinos
	//Rel�
	constexpr auto PRELE = D0;

	//Bot�es
	constexpr auto BTT1 = D8;
	constexpr auto BTT2 = D7;
	constexpr auto BTT3 = D4;

	//Sensor Biom�trico Digital
	constexpr auto TXFPS = D5;
	constexpr auto RXFPS = D3;

	//Display I2C
	constexpr auto SDADIS = D2;
	constexpr auto SCLDIS = D1;

	//Placa (Matriz de LEDs)
	constexpr auto DINPLA = D6;
	constexpr auto CSPLA = 3;
	constexpr auto CLKPLA = 1;

//Configura��o Display
	//Tamanho
	constexpr auto disp_l = 16;
	constexpr auto disp_a = 2;