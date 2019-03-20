#include <LiquidCrystal_I2C.h>                
LiquidCrystal_I2C lcd(0x27, 16, 2);

//VARIABILI IN INPUT OVVERO I 3 BOTTONI PRESENTI
int btn_Inizio          = 1;
int btn_PrimoRiflesso   = 3;
int btn_SecondoRiflesso = 5;

//VARIABILI IN OUTPIUT, OVVERO I LED BLU, ROSSO, VERDE E IL BUZZER
int ledBlu              = 7;
int ledRosso            = 9;
int ledVerde            = 11;
int buzzer              = 12;

//VARIABILI PER I TEMPI SULLE QUALI SI STABILIRA' IL RISULTATO
int tempoAccensioneLed = 0;
int tempoBuzzer = 0;
String s = " ms"; //STRINGA CREATA PER EVITARE ERRORI POI NEL DISPLAY

void setup() {
  lcd.init();
  lcd.backlight();
  
  //STABLISCO QUALE SEGNALE E' IN ENTRATA E QUALE E' IN USCITA
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
  
  if (digitalRead(btn_Inizio) == HIGH)
  {    
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRosso, LOW);
    
    lcd.print("Inizia il Test!");
    delay(2000);
    lcd.clear();    
      
    tempoAccensioneLed = 0;
    tempoBuzzer = 0;
    
    primoRiflesso();
    secondoRiflesso();

    //IF DI CONTROLLO CHE VERIFICA SE L'UTENTE HA SUPERATO O MENO IL TEST
    if (tempoAccensioneLed < 500 && tempoBuzzer < 500)
    {
      lcd.clear();
      lcd.print("Test superato!");
      digitalWrite(ledVerde, HIGH);
    }
    else
    {
      lcd.clear();
      lcd.print("Ritenta!");
      digitalWrite(ledRosso, HIGH);     
    }
  }
  else
  {
  }
}

//CICLO PER IL PRIMO RIFLESSO (LED BLU)
void primoRiflesso()
{
  delay(random(2000, 8000));                              //GENERO UN NUMERO RANDOM IN MILLISECONDI DOVE IN QUEL PRECISO TEMPO IL LED SI ACCENDERA'
  digitalWrite(ledBlu, HIGH);

  while (digitalRead(btn_PrimoRiflesso) != HIGH)          //CICLO DOVE IL TEMPO AUMENTA FINO A CHE L'UTENTE NON PREME IL SECONDO BOTTONE
  {
    tempoAccensioneLed++;
    delay(1);                                            //IL TEMPO AUMENTA DI UN MILLISECONDO OGNI CICLO 
  }

  lcd.print(tempoAccensioneLed + s);                     //SCRIVO SUL DISPLAY IL CONTENUTO DELLA VARIABIL"tempoAccensioneLed"
  digitalWrite(ledBlu, LOW);
}

//CICLO PER IL SECONDO RIFLESSO (BUZZER)
void secondoRiflesso()
{
  delay(random(2000, 8000));                             //GENERO UN NUMERO RANDOM IN MILLISECONDI DOVE IN QUEL PRECISO TEMPO IL LED SI ACCENDERA'
  digitalWrite(buzzer, HIGH);

  while (digitalRead(btn_SecondoRiflesso) != HIGH)       //CICLO DOVE IL TEMPO AUMENTA FINO A CHE L'UTENTE NON PREME IL TERZO BOTTONE
  {
    tempoBuzzer++;
    delay(1);                                            //IL TEMPO AUMENTA DI UN MILLISECONDO OGNI CICLO
  }
  digitalWrite(buzzer, LOW);
  lcd.setCursor(0, 1);
  lcd.print(tempoBuzzer + s);                            //SCRIVO SUL DISPLAY IL CONTENUTO DELLA VARIABILE "tempoBuzzer"
  delay(2000);
}
