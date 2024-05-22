/*

-BALKAN JUNIOR ROBOTSKA RAKA PROGRAMA 2024
-PROGRAMATA IZRABOTENA OD KRISTIJAN TOLESKI

-KORISTENITE FORMULI MOZE DA GI NAJDETE VO (SLIKA 1)

-VO PREDELOT PARAMETRI SE MESTAT PARAMETRITE NA RAKATA I SERVO MOTORITE
-VO PREDELOT CRTANJE SE CRTAAT LINIITE (PODOLU OBJASNATO KAKO)

-KORISTENA BIBLIOTEKA: https://www.arduino.cc/reference/en/libraries/servo/

-ZA TESTIRANJE KORISTEN E SLEDNIOV SIMULATOR NA ROBOTSKA RAKA: https://balkan-junior-robotska-raka.netlify.app

*/

#include <Servo.h>

// PARAMETRI
float a1 = 11.0; // RASTOJANIE OD SERVO 3 DO PENKALO VO CM //
float b1 = 14.0; // RASTOJANIE OD SERVO 2 DO SERVO 3 VO CM //

float greskaZ = 7; // SLUZI ZA PODESUVANJE NA PENKALOTO (SLIKA 2)

int pocetnaPozicijaZaServo1 = 90; // AGOL NA SERVO 1 PRI VKLUCUVANJE NA PROGRAMATA, I OTKAKO KE SE IZVRSI PROGRAMATA
int pocetnaPozicijaZaServo2 = 90; // AGOL NA SERVO 2 PRI VKLUCUVANJE NA PROGRAMATA, I OTKAKO KE SE IZVRSI PROGRAMATA
int pocetnaPozicijaZaServo3 = 180; // AGOL NA SERVO 3 PRI VKLUCUVANJE NA PROGRAMATA, I OTKAKO KE SE IZVRSI PROGRAMATA

int servo1Pin = 9;
int servo2Pin = 10;
int servo3Pin = 11;

int elevacijaPriKrevanjeNaPenkalo = 4; // OVA KAZUVA KOLKU DA SE KRENE PENKALOTO VO VIS PRI ODENJE DO ODREDENA TOCKA ZA CRTANJE

int brzinaNaDvizenjeNaRaka = 25; // POMALA VREDNOST RAKATA E POBRZA, POGOLEMA POSPORA

int koordinatenOpsegZaX_Oska = 1000; // KOORDINATATA DA BIDE PAREN BROJ, koordinatenOpsegZaX_Oska / koordinatenOpsegZaY_Oska == 2, koordinatenOpsegZaX_Oska >= (a1 + b1) * 2
int koordinatenOpsegZaY_Oska = 500;  // KOORDINATATA DA BIDE PAREN BROJ, koordinatenOpsegZaY_Oska * 2 == koordinatenOpsegZaX_Oska, koordinatenOpsegZaY_Oska >= a1 + b1
//

// PROMENLIVI
Servo servo1, servo2, servo3;

float a2, b2, c;
float alfa1, alfa2, alfa = pocetnaPozicijaZaServo2, beta = pocetnaPozicijaZaServo3, gama = pocetnaPozicijaZaServo1;
float alfaPrethodno, betaPrethodno, gamaPrethodno;

float yMax = a1 + b1;
float xMax = 2 * yMax;

int krajnaVrednost;

int prethodnoX = 0;
int prethodnoY = 0;

int prethodnaGreskaZ;

int prethodnaPozicijaNaServo1 = pocetnaPozicijaZaServo1;
int prethodnaPozicijaNaServo2 = pocetnaPozicijaZaServo2;
int prethodnaPozicijaNaServo3 = pocetnaPozicijaZaServo3;

int krajnaXKordinata;
int krajnaYKordinata;
//

void setup() {
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);

  vratiNaPocetnaPozicija(false);
  delay(3000);

  // CRTANJE

  // LINIJA HORIZONTALNA 3CM 
  //crtajLinija(540, 350, 'l', 28);


  /* BUKVATA A PRAVILNO
   * Serial.println("*****************LINIJA 1*****************");
    greskaZ -= 1;
    crtajLinija(521, 350, 'd', 80); 
    
    Serial.println("*****************LINIJA 2*****************");
    greskaZ += 1;
    crtajLinija(521, 350, 'l', 22); 
    
    Serial.println("*****************LINIJA 3*****************");
    greskaZ -= 1;
    crtajLinija(499, 350, 'd', 80); 
                                     
    Serial.println("*****************LINIJA 4*****************");
    crtajLinija(521, 325, 'l', 22);
   */

  /* A 90 stepeni nadesno
   * greskaZ -= 1;
    crtajLinija(521, 350, 'd', 80); 
    
    Serial.println("*****************LINIJA 2*****************");
    crtajLinija(521, 270, 'l', 22); 
    
    Serial.println("*****************LINIJA 3*****************");
    crtajLinija(521, 350, 'l', 22); 
                                     
    Serial.println("*****************LINIJA 4*****************");
    crtajLinija(510, 350, 'd', 80);
  */

  /* A 90 na levo
     *  greskaZ -= 1;
        crtajLinija(499, 350, 'd', 80); 
        
        Serial.println("*****************LINIJA 2*****************");
        crtajLinija(499, 270, 'r', 22); 
        
        Serial.println("*****************LINIJA 3*****************");
        greskaZ += 1;
        crtajLinija(521, 350, 'l', 22); 
                                         
        Serial.println("*****************LINIJA 4*****************");
        greskaZ -= 1;
        crtajLinija(510, 350, 'd', 80);
     */

  /* A 180 stepeni
     * greskaZ -= 1;
      crtajLinija(521, 350, 'd', 80); 
      
      Serial.println("*****************LINIJA 2*****************");
      crtajLinija(521, 270, 'l', 22); 
      
      Serial.println("*****************LINIJA 3*****************");
      crtajLinija(499, 350, 'd', 80); 
                                       
      Serial.println("*****************LINIJA 4*****************");
      crtajLinija(499, 310, 'r', 22);
     */

  /*  E
 *  greskaZ -= 1;
    crtajLinija(499, 350, 'd', 80); 
    
    Serial.println("*****************LINIJA 2*****************");
    crtajLinija(499, 270, 'r', 22); 
    
    Serial.println("*****************LINIJA 3*****************");
    greskaZ += 1;
    crtajLinija(521, 350, 'l', 22); 
                                     
    Serial.println("*****************LINIJA 4*****************");
    greskaZ -= 1;
    crtajLinija(499, 310, 'r', 22);
 */

  /* M
   * Serial.println("*****************LINIJA 1*****************");
  greskaZ -= 1;
  crtajLinija(521, 350, 'd', 80); 
  
  Serial.println("*****************LINIJA 2*****************");
  greskaZ += 1;
  crtajLinija(521, 350, 'l', 22); 
  
  Serial.println("*****************LINIJA 3*****************");
  greskaZ -= 1;
  crtajLinija(499, 350, 'd', 80); 
                                   
  Serial.println("*****************LINIJA 4*****************");
  crtajLinija(510, 350, 'd', 80); */

  /* Ш
   * Serial.println("*****************LINIJA 1*****************");
    greskaZ -= 1;
    crtajLinija(521, 350, 'd', 80); 
    
    Serial.println("*****************LINIJA 2*****************");
    crtajLinija(521, 270, 'l', 22); 
    
    Serial.println("*****************LINIJA 3*****************");
    crtajLinija(499, 350, 'd', 80); 
                                     
    Serial.println("*****************LINIJA 4*****************");
    crtajLinija(510, 350, 'd', 80);
   */ 

   /*Ш 90 na levo
     * 

      Serial.println("*****************LINIJA 1*****************");
      greskaZ -= 1;
      crtajLinija(521, 350, 'd', 80); 
      
      Serial.println("*****************LINIJA 2*****************");
      crtajLinija(521, 270, 'l', 22); 
      
      Serial.println("*****************LINIJA 3*****************");
      greskaZ += 1;
      crtajLinija(499, 350, 'r', 22);
      
      Serial.println("*****************LINIJA 4*****************");
      crtajLinija(521, 310, 'l', 22); 
     */

  //greskaZ = 3;
  //crtajLinija(540, 350, 'l', 60);
  //greskaZ -= 1;
  //crtajLinija(540, 310, 'l', 60);
  //greskaZ -= 1;
  //crtajLinija(540, 270, 'l', 60);
  //greskaZ = 4;
  //crtajLinija(540, 350, 'd', 80);
  //greskaZ += 2;
  //crtajLinija(525, 400, 'l', 30);

  /*
   * grid
   * 
   */
  
  //greskaZ = 1;
  crtajLinija(538, 350, 'd', 130, 1);
  crtajLinija(510, 350, 'd', 130, 1);
  crtajLinija(478, 350, 'd', 130, 1);
  //greskaZ = 3;
  crtajLinija(538, 350, 'l', 60, 3);

  
  vratiNaPocetnaPozicija(true);
}

void loop() {
}

void servo1Agol(int agol){
  servo1.write(180 - agol);
}
void servo2Agol(int agol){ 
  servo2.write(agol);
}
void servo3Agol(int agol){
  servo3.write(180 - agol);
}

void pridviziServoMotori(int servoAgol1, int servoAgol2, int servoAgol3){
  if(prethodnaPozicijaNaServo1 == servoAgol1 && prethodnaPozicijaNaServo2 == servoAgol2 && prethodnaPozicijaNaServo3 == servoAgol3) return;

  for(int i = 0; i <= 100; i++){
    servo2Agol(prethodnaPozicijaNaServo2 + ((servoAgol2 - prethodnaPozicijaNaServo2) * i / 100.0));
    servo3Agol(prethodnaPozicijaNaServo3 + ((servoAgol3 - prethodnaPozicijaNaServo3) * i / 100.0));
    servo1Agol(prethodnaPozicijaNaServo1 + ((servoAgol1 - prethodnaPozicijaNaServo1) * i / 100.0));

    delay(brzinaNaDvizenjeNaRaka);
  }

  prethodnaPozicijaNaServo1 = servoAgol1;
  prethodnaPozicijaNaServo2 = servoAgol2;
  prethodnaPozicijaNaServo3 = servoAgol3;
}

void vratiNaPocetnaPozicija(bool soElevacija){
  if(soElevacija){
    prethodnaGreskaZ = greskaZ;
    greskaZ += elevacijaPriKrevanjeNaPenkalo;
    prethodnoX = 0;
    prethodnoY = 0;

    odiNaTocka(krajnaXKordinata, krajnaYKordinata);
    greskaZ = prethodnaGreskaZ;
  }

  pridviziServoMotori(pocetnaPozicijaZaServo1, pocetnaPozicijaZaServo2, pocetnaPozicijaZaServo3);
}

void presmetajAgli(float x, float y){
  a2 = greskaZ;
  b2 = y;

  c = sqrt(pow((x - yMax), 2) + y*y + greskaZ*greskaZ);

  alfa1 = acos((a1*a1 - b1*b1 - c*c) / (-2 * b1 * c));
  alfa2 = atan(a2 / b2);
  alfa = alfa1 + alfa2;
  alfa *= 180.0 / M_PI;
  
  beta = acos((c*c - a1*a1 - b1*b1) / (-2 * a1 * b1));
  beta *= 180.0 / M_PI;
  
  gama = atan(abs(yMax - x) / (float)y);
  gama *= 180.0 / M_PI;

  if(x > yMax) gama = 90 + gama;
  else gama = 90 - gama;
}

float MAP(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void odiNaTocka(int x, int y){
  if(x == prethodnoX && y == prethodnoY) return;
  prethodnoX = x;
  prethodnoY = y;

  x = MAP(x, 0, koordinatenOpsegZaX_Oska, 0, xMax);
  y = MAP(y, 0, koordinatenOpsegZaY_Oska, 0, yMax);

  presmetajAgli(x, y);

  pridviziServoMotori(gama, alfa, beta);
}

void crtajLinija(int x, int y, char nasoka, int dolzina, float greska){
  if(x != prethodnoX || y != prethodnoY){
    prethodnaGreskaZ = greskaZ;
    greskaZ += elevacijaPriKrevanjeNaPenkalo;
    odiNaTocka(x, y);
    delay(1500);

    prethodnoX = 0;
    prethodnoY = 0;
    greskaZ = greska;
    odiNaTocka(x, y);
    delay(1500);
  }

  if(nasoka == 'u'){
    krajnaVrednost = y + dolzina;
    krajnaXKordinata = x;
    krajnaYKordinata = krajnaVrednost;

    for(int i = y; i <= krajnaVrednost; i++){
      odiNaTocka(x, i);
    }
  }
  else if(nasoka == 'd'){
    krajnaVrednost = y - dolzina;
    krajnaXKordinata = x;
    krajnaYKordinata = krajnaVrednost;

    for(int i = y; i >= krajnaVrednost; i--){
      odiNaTocka(x, i);
    }
  }
  else if(nasoka == 'l'){
    krajnaVrednost = x - dolzina;
    krajnaXKordinata = krajnaVrednost;
    krajnaYKordinata = y;

    for(int i = x; i >= krajnaVrednost; i--){
      odiNaTocka(i, y);
    }
  }
  else if(nasoka == 'r'){
    krajnaVrednost = x + dolzina;
    krajnaXKordinata = krajnaVrednost;
    krajnaYKordinata = y;

    for(int i = x; i <= krajnaVrednost; i++){
      odiNaTocka(i, y);
    }
  }

  greskaZ = prethodnaGreskaZ;
  delay(1500);
}
