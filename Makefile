.PHONY: HX711

HX711: main.cpp
	g++ -std=c++17 main.cpp   HX711_ADC.cpp gpio.cpp -o HX711


