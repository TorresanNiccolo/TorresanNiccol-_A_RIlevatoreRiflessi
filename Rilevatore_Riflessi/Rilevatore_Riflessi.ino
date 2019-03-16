#include <LiquidCrystal_I2C.h>
#define LED 13                
#define BUTTON 7              
int  val = 0;                 
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
}
 
void loop() {
  lcd.setCursor(0,0);
  lcd.print("Ciao");
  delay(3000);
  lcd.clear();
  delay(10000);
}
