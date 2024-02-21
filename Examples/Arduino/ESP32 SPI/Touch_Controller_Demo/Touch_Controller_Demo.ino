#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

#include <FT6236.h>

#define I2C_SCL 15
#define I2C_SDA 16

FT6236 ts = FT6236();

#define TS_RESET 13


void setup(void) 
{
  Serial.begin(115200); 
  
  tft.init();
  
  //FT6236 reset pin - drive high
  pinMode(TS_RESET,OUTPUT);
  digitalWrite(TS_RESET,HIGH);
  
  ts.begin(40, I2C_SDA, I2C_SCL);
  tft.fillScreen((0xFFFF));

  ts.debug();
}

void loop() 
{
   static uint16_t color;
  
   if (ts.touched()) 
   {
      // Retrieve a point
      TS_Point p = ts.getPoint();
    
      tft.fillCircle(p.x, p.y, 5, color);
      color += 155;
   } 
   else
   {
     tft.fillCircle(5, 5, 5, color);
     color += 155;
   }

   //Debouncing. To avoid returning the same touch multiple times you can play with this delay.
   delay(50);
}
