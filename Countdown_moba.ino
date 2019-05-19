#include <MobaTools.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

//LCD initialisieren
LiquidCrystal_I2C lcd(0x27, 20, 4);

//Pinlänge
const byte PINLENGTH = 4;

// Zwischenspeicher für Eingaben
char keyBuffer[PINLENGTH+1] = {'-','-','-','-'};

//Hier wird die größe des Keypads definiert
const byte COLS = 4; //4 Spalten
const byte ROWS = 4; //4 Zeilen
char hexaKeys[ROWS][COLS]={
{'D','#','0','*'},
{'C','9','8','7'},
{'B','6','5','4'},
{'A','3','2','1'}
};
byte colPins[COLS] = {2,3,4,5}; //Definition der Pins für die 3 Spalten
byte rowPins[ROWS] = {6,7,8,9}; //Definition der Pins für die 4 Zeilen

char Taste; //Taste ist die Variable für die jeweils gedrückte Taste.
Keypad Tastenfeld = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //Das Keypad kann absofort mit "Tastenfeld" angesprochen werden

//Definition der 4 Timer
EggTimer timer1, timer2, timer3, timer4;

//Definition der einzelnen Variablen
int h1=0, h2=0, m1=0, m2=0,s1=0, s2=0, RC=0;//Die Ziffern und Zeichen des Keypads werden eingegeben:
char appversion="1.0";
long lastSecond;

//Definition der Pins
int Pin1 = 10;
int Pin2 = 11;
int Pin3 = 12;
int Pin4 = 13;
long zeittodo;
int min1 = 0;
int min2 = 0;
int hour1 = 0;
int hour2 = 0;
int ME = 0;
long minu;
long hou;
long time1;
int onoff=1;
char o;
char n;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); //Öffnet den seriellen Port und legt die Baud Rate (9600) für die serielle Übertragung fest.
pinMode(Pin1, OUTPUT);
pinMode(Pin2, OUTPUT);
pinMode(Pin3, OUTPUT);
pinMode(Pin4, OUTPUT);
lcd.begin();
lcd.backlight();
}



void loop() {
  //Willkommenstext
  lcd.clear();
lcd.setCursor(0,0);
lcd.print("Stromiuno Vers. ");
lcd.print("1.0");
lcd.setCursor(0,2);
lcd.print("CR nobbie - 2019");
Anfang:
// Testen ob Timer abgelaufen sind
if (timer1.getTime()==false) {
  digitalWrite(Pin1, HIGH);
} else {
  digitalWrite(Pin1, LOW);
}
if (timer2.getTime()==false) {
  digitalWrite(Pin2, HIGH);
} else {
  digitalWrite(Pin2, LOW);
}
if (timer3.getTime()==false) {
  digitalWrite(Pin3, HIGH);
} else {
  digitalWrite(Pin3, LOW);
}
if (timer4.getTime()==false) {
  digitalWrite(Pin4, HIGH);
} else {
  digitalWrite(Pin4, LOW);
}
char Taste = Tastenfeld.getKey();
   
if (Taste) //Wenn eine Taste gedrückt wurde
// Jetzt werden die einzelnen Eingaben verarbeitet

{

Serial.println(Taste);
   if (Taste=='*') // Wenn die "*" Taste gedrückt wurde... ### Auswahl der Steckdose
   {
   Serial.println("Bitte die Steckdose auswählen");
   ME = 0;
   lcd.clear();
   lcd.setCursor(0,1);
   lcd.print("Bitte eine Steckdose waehlen");
   h1=0; h2=0; m1=0;m2=0;
   RC=0; // Zugang zur ersten Zeicheneingabe freischalten
   
   goto Anfang; //An dieser Stelle springt der Sketch zur Eingabe der Taste zurück, damit das Zeichen "*" nicht im folgenden Abschlitt als Codeeingabe gewertet wird.
   }
   else if ((int(Taste) >= 48) && (int(Taste) <= 57)){
   Serial.println("Es wurde eine Zahl eingegeben");
   Serial.print("ASCII-Wert: ");
   Serial.println(Taste);
   Taste = Taste - 48;
   Serial.print("umgerechnet: ");
   Serial.println(Taste);
//   
    if (RC==0) {
            if ((Taste >= 1) && (Taste <=4)) {
      RC=Taste;
      Serial.println("RC wurde belegt, alles auf Anfang");
      } else {
        Serial.println("Bitte eine Steckdose zwischen 1 und 4 wählen");
           lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Steckdose zwischen 1-4");
            goto Anfang;
      }
   Serial.println("Steckdose wurde ausgewählt");
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Steckdose ");
   lcd.print(RC);
   lcd.print(" gewaehlt");
   lcd.setCursor(0,1);
   lcd.print("Bitte Zeit eingeben:");
   lcd.setCursor(0,2);
   lcd.print("_ _ : _ _");
      goto Anfang;
    }
    if (h1==0) {
      hour1 = Taste;
      h1=1;
   Serial.println("Stunde 1 wurde ausgewählt");
   Serial.println(hour1);
   lcd.setCursor(0,2);
   lcd.print(hour1);
   lcd.print(" _ : _ _");
      goto Anfang;
    }
    if (h2==0) {
      hour2 = Taste;
      h2=1;
   Serial.println("Stunde 2 wurde ausgewählt");
   Serial.println(hour2);
   lcd.setCursor(0,2);
   lcd.print(hour1);
   lcd.print(" ");   
   lcd.print(hour2);
   lcd.print(" : _ _");
      goto Anfang;
    }
    if (m1==0) {
      min1 = Taste;
      m1=1;
   Serial.println("Minute 1 wurde ausgewählt");
   Serial.println(min1);
   lcd.setCursor(0,2);
   lcd.print(hour1);
   lcd.print(" ");   
   lcd.print(hour2);
   lcd.print(" : ");
   lcd.print(min1);
   lcd.print(" _");
      goto Anfang;
    }
    if (m2==0) {
      min2 = Taste;
      m2=1;
   Serial.println("Minute 2 wurde ausgewählt");
   Serial.println(min2);
   lcd.setCursor(0,2);
   lcd.print(hour1);
   lcd.print(" ");   
   lcd.print(hour2);
   lcd.print(" : ");
   lcd.print(min1);
   lcd.print(" ");
   lcd.print(min2);
      goto Anfang;
    }
   }
        if (Taste=='D') // Wenn die "#" Taste gedrückt wurde... Zeit checken, Countdown starten
        {
              timer1.setTime(0);
        timer2.setTime(0);
        timer3.setTime(0);
        timer4.setTime(0);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Alle Steckdosen aus");
        goto Anfang;
}
if (Taste=='A') // Wenn die "A" Taste gedrückt wurde... Zeit checken, Countdown starten
        {
//          if (RC==0) {
//            
//            Serial.println("Bitte zuerst eine Steckdose wählen");
//                lcd.clear();
//                lcd.setCursor(0,0);
//                 lcd.print("Steckdose ");
//          }
          ME=1;
          goto Anfang;
        }
        if (Taste=='B') // Wenn die "B" Taste gedrückt wurde... Zeit checken, Countdown starten
        {

        }
        if (Taste=='C') // Wenn die "C" Taste gedrückt wurde... Zeit checken, Countdown starten
        {

        }
      if (Taste=='#') // Wenn die "#" Taste gedrückt wurde... Zeit checken, Countdown starten
   {
   
   Serial.println("Zeit wird geprüft");
   if ((!h1==0) && (!h2==0) && (!m1==0) && (!m2==0)) {
       long MG=((min1*10)+min2);
   Serial.println("MG:");
   Serial.println(MG);
   long HG=((hour1*10)+hour2)*60;
   Serial.println("HG:");
   Serial.println(HG);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Steckdose ");
   lcd.print(RC);
   lcd.print(" gestartet");
   lcd.setCursor(0,2);
   lcd.print("Dauer:");
   lcd.setCursor(0,3);
   lcd.print(hour1);
   lcd.print(" ");   
   lcd.print(hour2);
   lcd.print(" : ");
   lcd.print(min1);
   lcd.print(" ");
   lcd.print(min2);
   ME = 1;
long TG = (HG + MG);
TG = TG  * 60000;

   Serial.println(TG);
    zeittodo = TG;
   Serial.println(zeittodo);
     
    switch (RC) {
      case 1:
        //Steckdose 1
        timer1.setTime(zeittodo);
   Serial.print("Steckdose ");
   Serial.print(RC);
   Serial.print("wurde mit ");
   Serial.println(zeittodo);
   Serial.println("gestartet");
       RC=0;
        break;
      case 2:
        //Steckdose 2
        timer2.setTime(zeittodo);
   Serial.print("Steckdose ");
   Serial.print(RC);
   Serial.print("wurde mit ");
   Serial.println(zeittodo);
   Serial.println("gestartet");
       RC=0;
        break;
      case 3:
        //Steckdose 3
        timer3.setTime(zeittodo);
   Serial.print("Steckdose ");
   Serial.print(RC);
   Serial.print("wurde mit ");
   Serial.println(zeittodo);
   Serial.println("gestartet");
       RC=0;
        break;
      case 4:
        //Steckdose 4
        timer4.setTime(zeittodo);
   Serial.print("Steckdose ");
   Serial.print(RC);
   Serial.print("wurde mit ");
   Serial.println(zeittodo);
   Serial.println("gestartet");
       RC=0;
        break;
      
    }
    RC=0;
   }
   else if (!RC==0){
        switch (RC) {
      case 1:
        //Steckdose 1
        timer1.setTime(0);
        break;
      case 2:
        //Steckdose 2
        timer2.setTime(0);
        break;
      case 3:
        //Steckdose 3
        timer3.setTime(0);
        break;
      case 4:
        //Steckdose 4
        timer4.setTime(0);
        break;
      default:
        timer1.setTime(0);
        timer2.setTime(0);
        timer3.setTime(0);
        timer4.setTime(0);
   Serial.println("Alle Timer gestoppt!");
        
      
    }
   }
   goto Anfang; //An dieser Stelle springt der Sketch zur Eingabe der Taste zurück, damit das Zeichen "*" nicht im folgenden Abschlitt als Codeeingabe gewertet wird.
   }
   
   Serial.println(timer1.getTime());
   Serial.println(timer2.getTime());
   Serial.println(timer3.getTime());
   Serial.println(timer4.getTime());
   
}
  // put your main code here, to run repeatedly:
// timer.setTime(1000) // 1 Sekunde, Timer startet
// timer.running() == false // Timer läuft nicht 
// timer.getTime() // Restlaufzeit

//Countdown darstellen
if(ME==1) {
  

    
   
   if (millis() >= lastSecond + 1000) {
    
    if (onoff==1) {
      onoff=0;
    } else {
      onoff=1;
    }
lcd.clear();
//                                                                    Steckdose 1
   lcd.setCursor(0,0);
   lcd.print("Steckdose 1: ");
    time1 = timer1.getTime();
    minu = (time1/60000) % 60;
    hou = (time1/3600000);
   if (hou < 10) {
    lcd.print("0");
   }
   lcd.print(hou);
   lcd.print(":");
   if (minu < 10) {
    lcd.print("0");
   }
   lcd.print(minu);   
   if (timer1.running()==true) {
    if (onoff==1) {
      lcd.print(" #");
    }else {
      lcd.print("# ");
    }
   }
//                                                                    Steckdose 2
   lcd.setCursor(0,1);
   lcd.print("Steckdose 2: ");
    time1 = timer2.getTime();
    minu = (time1/60000) % 60;
    hou = (time1/3600000);
   if (hou < 10) {
    lcd.print("0");
   }
   lcd.print(hou);
   lcd.print(":");
   if (minu < 10) {
    lcd.print("0");
   }
   lcd.print(minu);   
    if (timer2.running()==true) {
    if (onoff==1) {
      lcd.print("# ");
    }else {
      lcd.print(" #");
    }
   }
//                                                                    Steckdose 3
   lcd.setCursor(0,2);
   lcd.print("Steckdose 3: ");
    time1 = timer3.getTime();
    minu = (time1/60000) % 60;
    hou = (time1/3600000);
   if (hou < 10) {
    lcd.print("0");
   }
   lcd.print(hou);
   lcd.print(":");
   if (minu < 10) {
    lcd.print("0");
   }
   lcd.print(minu);
   if (timer3.running()==true) {
    if (onoff==1) {
      lcd.print(" #");
    }else {
      lcd.print("# ");
    }
   }
//                                                                    Steckdose 4
   lcd.setCursor(0,3);
   lcd.print("Steckdose 4: ");
    time1 = timer4.getTime();
    minu = (time1/60000) % 60;
    hou = (time1/3600000);
   if (hou < 10) {
    lcd.print("0");
   }
   lcd.print(hou);
   lcd.print(":");
   if (minu < 10) {
    lcd.print("0");
   }
   lcd.print(minu);  
   if (timer4.running()==true) {
    if (onoff==1) {
      lcd.print("# ");
    }else {
      lcd.print(" #");
    }
   }
   lastSecond = millis();
  }
}
goto Anfang;
}


 

