° 
// Niccolò Torresan 3BI
// Marzo 2018/2019
// RILEVATORE DI RIFLESSI

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//VARIABILI IN INPUT OVVERO I 3 BOTTONI PRESENTI
int btn_Inizio          = 13;
int btn_PrimoRiflesso   = 1;
int btn_SecondoRiflesso = 5;

//VARIABILI IN OUTPUT, OVVERO I LED BLU, ROSSO, VERDE E IL BUZZER
int ledBlu              = 3;
int buzzer              = 7;
int ledRosso            = 9;
int ledVerde            = 11;

//VARIABILI PER I TEMPI SULLE QUALI SI STABILIRA' IL RISULTATO
int tempoAccensioneLed  = 0;
int tempoBuzzer         = 0;

//STRINGHE CREATE PER EVITARE ERRORI DI SCRITTURA NEL DISPLAY
String s = " ms";
String s1 = "TEST 1: ";
String s2 = "TEST 2: ";

//VARIABILE DI TIPO BOOL CHE VERRA' USATA IN SEGUITO PER STABILIRE SE SI HA BARATO OPPURE NO
bool errore = false;

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
  
  if (digitalRead(btn_Inizio) == HIGH)
  {
    lcd.clear();
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRosso, LOW);
    errore = false;

    lcd.print("INIZIA IL TEST!");
    delay(2000);
    lcd.clear();

    tempoAccensioneLed = 0;
    tempoBuzzer = 0;

    primoRiflesso();

    if (errore == true)                                       //IF CHE NEL CASO L'UTENTE ABBIA BARATO NEL PRIMO TEST BLOCCA L'ESECUZIONE DELL'ESAME
    {
      lcd.clear();
      digitalWrite(ledBlu, LOW);
      digitalWrite(ledRosso, HIGH);
      lcd.print("HAI IMBROGLIATO");
      lcd.setCursor(0, 1);
      lcd.print("TEST NON VALIDO!");
    }
    else
    {
      secondoRiflesso();

      if (errore == true)                                     //IF CHE NEL CASO L'UTENTE ABBIA BARATO NEL PRIMO TEST BLOCCA L'ESECUZIONE DELL'ESAME
      {
        lcd.clear();
        digitalWrite(buzzer, LOW);
        digitalWrite(ledRosso, HIGH);
        lcd.print("HAI IMBROGLIATO");
        lcd.setCursor(0, 1);
        lcd.print("TEST NON VALIDO!");
      }
      else
      {
        if (tempoAccensioneLed <= 500 && tempoBuzzer <= 500)  //IF DI CONTROLLO CHE VERIFICA SE L'UTENTE HA PASSATO O MENO IL TEST
        {
          lcd.clear();
          lcd.print("TEST SUPERATO!");
           digitalWrite(ledVerde, HIGH);
        }
        else
        {
          lcd.clear();
          lcd.print("RITENTA!");
          digitalWrite(ledRosso, HIGH);
        }
      }
    }
  }
}

//CICLO PER IL PRIMO RIFLESSO (LED BLU)
void primoRiflesso()
{
  delay(random(1000, 8000));                              //GENERO UN NUMERO RANDOM IN MILLISECONDI DOVE IN QUEL PRECISO TEMPO IL LED SI ACCENDERA'
  digitalWrite(ledBlu, HIGH);
  
  while (digitalRead(btn_PrimoRiflesso) != HIGH)         //CICLO DOVE IL TEMPO AUMENTA FINO A CHE L'UTENTE NON PREME IL SECONDO BOTTONE
 {
    tempoAccensioneLed++;
    delay(1);                                            //IL TEMPO AUMENTA DI UN MILLISECONDO OGNI CICLO
  }
  
  if (tempoAccensioneLed <= 100)                         //IF CHE VERIFICA SE L'UTENTE HA BARATO E IN QUESTO CASO LA VARIABILE "errore" DA FALSO DIVENTA TRUE
  {
    errore = true;
  }
  else
  {
    lcd.print(s1 + tempoAccensioneLed + s);                //SCRIVO SUL DISPLAY IL CONTENUTO DELLA VARIABILE"tempoAccensioneLed"
    digitalWrite(ledBlu, LOW);
  }
}

//CICLO PER IL SECONDO RIFLESSO (BUZZER)
void secondoRiflesso()
{
  errore = false;
  
  delay(random(3000, 8000));                             //GENERO UN NUMERO RANDOM IN MILLISECONDI DOVE IN QUEL PRECISO TEMPO IL LED SI ACCENDERA'
  digitalWrite(buzzer, HIGH);
  
  while (digitalRead(btn_SecondoRiflesso) != HIGH)       //CICLO DOVE IL TEMPO AUMENTA FINO A CHE L'UTENTE NON PREME IL TERZO BOTTONE
  {
    tempoBuzzer++;
    delay(1);                                            //IL TEMPO AUMENTA DI UN MILLISECONDO OGNI CICLO
  }
  
  if (tempoBuzzer <= 100)                                //IF CHE VERIFICA SE L'UTENTE HA BARATO E IN QUESTO CASO LA VARIABILE "errore" DA FALSO DIVENTA TRUE
  {
    errore = true;
  }
  else
  {
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0, 1);                                 //IMPOSTO IL CURSORE PER SCRIVERE NELLA SECONDA RIGA DEL DISPLAY
    lcd.print(s2 + tempoBuzzer + s);                     //SCRIVO SUL DISPLAY IL CONTENUTO DELLA VARIABILE "tempoBuzzer"
    delay(2500);
  }
}
