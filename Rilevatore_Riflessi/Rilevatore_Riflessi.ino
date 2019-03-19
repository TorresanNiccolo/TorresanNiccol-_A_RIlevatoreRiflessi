#include <LiquidCrystal_I2C.h>                
LiquidCrystal_I2C lcd(0x27, 16, 2);

int btn_Inizio = 1;
int btn_PrimoRiflesso = 3;
int btn_SecondoRiflesso = 5;
int ledBlu = 7;
int ledRosso = 9;
int ledVerde = 11;
int buzzer = 12;

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
  pinMode(ledRosso, OUTPUT);
  pinMode(ledVerde, OUTPUT);
}
 
void loop() {   
    
  lcd.setCursor(0,0);

  tempoAccensioneLed = 0;
  tempoBuzzer = 0;
  
  if (digitalRead(btn_Inizio) == HIGH)
  {
    lcd.clear();
    digitalWrite(ledBlu, LOW);
    digitalWrite(ledRosso, LOW);
    digitalWrite(ledVerde, LOW);
    
    lcd.print("Inizia il test!");
    delay(3000);
    primoRiflesso();
    secondoRiflesso();

    if (tempoAccensioneLed < 500 && tempoBuzzer < 500)
    {
      lcd.println("Hai superato il Test!");
      digitalWrite(ledVerde, HIGH);
    }
    else
    {
      lcd.println("Non hai superato il Test, ritenta!");
      digitalWrite(ledRosso, HIGH);
    }
  }
  else
  {
    
  }
}

void primoRiflesso()
{
  lcd.clear();
  delay(random(2000, 8000));
  digitalWrite(ledBlu, HIGH);

  while (digitalRead(btn_PrimoRiflesso) != HIGH)
  {
    tempoAccensioneLed++;
    delay(1);    //il tempo mi aumenta di un millisecondo ogni volta 
  }

  lcd.print(tempoAccensioneLed + " ms");
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
  
  lcd.println(tempoBuzzer + " ms");
  digitalWrite(buzzer, LOW);
}
