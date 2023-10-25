#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>

OneWire ds(2);  // Pin de datos del sensor DS18B20
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Dirección del I2C y tamaño del LCD
byte addr[8]; 

void setup() {
  lcd.init();  // Inicializa el LCD
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  Wire.begin();
}

void loop() {
  lcd.setCursor(0, 1);
  
  // Lee la temperatura del sensor DS18B20
  float tempC;
  if (ds.search(addr)) {
    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);  // Inicia la conversión de temperatura
    delay(800);  // Espera a que la conversión termine
    
    ds.reset();
    ds.select(addr);
    ds.write(0xBE);  // Lee el registro de datos
    
    byte data[9];
    for (int i = 0; i < 9; i++) {
      data[i] = ds.read();
    }
    
    int16_t raw = (data[1] << 8) | data[0];
    tempC = (float)raw / 16.0;
  }

  lcd.print(tempC);
  lcd.print(" C");

  delay(400);  // Actualiza la temperatura cada segundo
}
