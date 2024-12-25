#include <Arduino.h>
#include <GyverOLED.h>

#define lunghezza_password 8
char Master[lunghezza_password] = "1234567";   //password di accesso
char password[lunghezza_password];

int conta_caratteri = 0;

GyverOLED<SSH1106_128x64> oled;

const byte ROWS = 4;
const byte COLS = 4;

char keymap[ROWS][COLS] = {
                          {'1', '2', '3', 'A'},
                          {'4', '5', '6', 'B'},
                          {'7', '8', '9', 'C'},
                          {'*', '0', '#', 'D'}
                        };

byte rowPins[ROWS] = {19, 18, 17, 16};
byte colPins[COLS] = {27, 26, 21, 20};



const int controlPin = 12;


char getKey(){

char key = '\0';

 for(int c = 0; c < COLS; c++)  
 {  digitalWrite(colPins[c], LOW); //Metto bassa una delle colonne - sono pin di output
    for(int r = 0; r < ROWS; r++){      // Scorro tutte le righe
     if(digitalRead(rowPins[r]) == LOW)  // rilevo tensione bassa solo se il tasto in posizione r,c è stato premuto 
     key = keymap[r][c];                 // Memorizzo quale sia il tasto premuto
    }
    digitalWrite(colPins[c], HIGH);
 }

return key;
}

void hello() {
  oled.clear(); 
  oled.rect(0,0,127,63,OLED_STROKE);
  oled.setCursorXY(28, 13);   
  oled.print("IIS Aosta AQ!");
  oled.setCursorXY(28, 26); 
  oled.println("Elettronica");
  oled.setCursorXY(28, 40); 
  oled.println("2025");
  oled.update(); 
  }
  
  void messaggio_orientamento_20024() {
  oled.clear(); 
  oled.roundRect(0,0,127,63,OLED_STROKE);
  //oled.rect(0,0,127,63,OLED_STROKE);
  oled.setCursorXY(28, 13);   
  oled.print("Benvenuti! ");
  oled.setCursorXY(28, 26); 
  oled.println("Orientamento ");
  oled.setCursorXY(28, 40); 
  oled.println("2025");
  oled.update(); 
  }
  
  void messaggio_utente() {
  oled.clear(); 
  oled.roundRect(0,0,127,63,OLED_STROKE);
  //oled.rect(0,0,127,63,OLED_STROKE);
  oled.setCursorXY(28, 13);   
  oled.print("Inserire  ");
  oled.setCursorXY(28, 26); 
  oled.println("la password ");
  oled.setCursorXY(28, 40); 
  oled.println("di sblocco");
  oled.update(); 

  }




void setup() {


 for (int column = 0; column < COLS; column++)
 {
   pinMode(colPins[column],OUTPUT);     // Setta i pin delle colonne come output
   digitalWrite(colPins[column],HIGH);  // Imposta le colonne a livello HIGH 
  }

 for (int row = 0; row < ROWS; row++)
 {
  pinMode(rowPins[row],INPUT);       // Imposta i pin di riga come input
  // Abilita sui pin di riga i resistori di pull up - aggiunte esternamente 
 }

 

  Serial.begin(9600);
  oled.init();  
  oled.clear();   
  oled.update(); 
  hello();
  delay(4000);
  messaggio_orientamento_20024();
  delay(4000);
  pinMode(controlPin, OUTPUT);
  digitalWrite(controlPin, HIGH); //disattivo il relè
  messaggio_utente();
  delay(4000);




}

void loop() {   

   char key = getKey();

   if( key != '\0') 
   {oled.clear(); 
    oled.roundRect(0,0,127,63,OLED_STROKE);
    
    oled.setCursorXY(18, 13);
    oled.print("Hai premuto: ");
   oled.setCursorXY(18, 33);
   oled.println(key);
   oled.update();
  }

}
