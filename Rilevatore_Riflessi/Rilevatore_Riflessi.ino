#include <LiquidCrystal_I2C.h>                
LiquidCrystal_I2C lcd(0x27, 16, 2);

int btn_Inizio = 1;
int btn_PrimoRiflesso = 3;
int btn_SecondoRiflesso = 5;
int ledBlu = 7;
int buzzer = 13;
int tempoAccensioneLed = 0;
int tempoBuzzer = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(btn_Inizio, INPUT);
  pinMode(btn_PrimoRiflesso, INPUT);
  pinMode(btn_SecondoRiflesso, INPUT);
  pinMode(ledBlu, OUTPUT);
  pinMode(buzzer, OUTPUT);
}
 
void loop() {
 // lcd.setCursor(0,0);
 // lcd.print("");
 
  if (digitalRead(btn_Inizio) == HIGH)
  {
    primoRiflesso();
    secondoRiflesso();
  }
  else
  {
    
  }
}

void primoRiflesso()
{
  delay(random(2000, 8000));
  digitalWrite(ledBlu, HIGH);

  while (digitalRead(btn_PrimoRiflesso) != HIGH)
  {
    tempoAccensioneLed++;
    delay(1);    //il tempo mi aumenta di un millisecondo ogni volta 
  }

  digitalWrite(ledBlu, LOW);
}

void secondoRiflesso()
{
  delay(random(2000, 8000));
  digitalWrite(buzzer, HIGH);

  while (digitalRead(btn_SecondoRiflesso) != HIGH)
  {
    tempoBuzzer++;
    delay(1);
  }

  digitalWrite(buzzer, LOW);
}
