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
float a1 = 11.5; // RASTOJANIE OD SERVO 3 DO PENKALO VO CM //
float b1 = 15.24; // RASTOJANIE OD SERVO 2 DO SERVO 3 VO CM //

int greskaX = 0; // SLUZI ZA PODESUVANJE NA PENKALOTO (SLIKA 2)
int greskaY = 0; // SLUZI ZA PODESUVANJE NA PENKALOTO (SLIKA 2)
int greskaZ = 0; // SLUZI ZA PODESUVANJE NA PENKALOTO (SLIKA 2)

int pocetnaPozicijaZaServo1 = 90; // AGOL NA SERVO 1 PRI VKLUCUVANJE NA PROGRAMATA, I OTKAKO KE SE IZVRSI PROGRAMATA
int pocetnaPozicijaZaServo2 = 90; // AGOL NA SERVO 2 PRI VKLUCUVANJE NA PROGRAMATA, I OTKAKO KE SE IZVRSI PROGRAMATA
int pocetnaPozicijaZaServo3 = 180; // AGOL NA SERVO 3 PRI VKLUCUVANJE NA PROGRAMATA, I OTKAKO KE SE IZVRSI PROGRAMATA

int servo1Pin = 9;
int servo2Pin = 10;
int servo3Pin = 11;

bool invertirajAgolNaServo1 = true; // AKO AGLITE NA SERVO 1 SE OBRATNI OD (SLIKA 2) TOGAS PARAMETAROT DA E TRUE
bool invertirajAgolNaServo2 = false; // AKO AGLITE NA SERVO 2 SE OBRATNI OD (SLIKA 2) TOGAS PARAMETAROT DA E TRUE
bool invertirajAgolNaServo3 = true; // AKO AGLITE NA SERVO 3 SE OBRATNI OD (SLIKA 2) TOGAS PARAMETAROT DA E TRUE

int elevacijaPriKrevanjeNaPenkalo = 20; // OVA KAZUVA KOLKU DA SE KRENE PENKALOTO VO VIS PRI ODENJE DO ODREDENA TOCKA ZA CRTANJE

int brzinaNaDvizenjeNaRaka = 0; // POMALA VREDNOST RAKATA E POBRZA, POGOLEMA POSPORA

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
  Serial.begin(9600);

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);

  vratiNaPocetnaPozicija(false);
  delay(3000);

  // CRTANJE

  crtajLinija(610, 350, 'l', 100); // ﹉
                                   // 
                                   // 

  crtajLinija(510, 350, 'd', 100); // ┊﹉
                                   // ┊
                                   // ┊

  crtajLinija(510, 250, 'r', 100); // ┊﹉
                                   // ┊
                                   // ┊﹍

  crtajLinija(510, 300, 'r', 100); // ┊﹉
                                   // ┊┄┄
                                   // ┊﹍

  //

  vratiNaPocetnaPozicija(true);
}

void loop() {
}

void servo1Agol(int agol){
  if(invertirajAgolNaServo1) servo1.write(180 - agol);
  else servo1.write(agol);
}
void servo2Agol(int agol){ 
  if(invertirajAgolNaServo2) servo2.write(180 - agol);
  else servo2.write(agol);
}
void servo3Agol(int agol){
  if(invertirajAgolNaServo3) servo3.write(180 - agol);
  else servo3.write(agol);
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

  Serial.print("SERVO 1 AGOL: ");
  Serial.println((int)pocetnaPozicijaZaServo1);
  Serial.flush();

  Serial.print("SERVO 2 AGOL: ");
  Serial.println((int)pocetnaPozicijaZaServo2);
  Serial.flush();

  Serial.print("SERVO 3 AGOL: ");
  Serial.println((int)pocetnaPozicijaZaServo3);
  Serial.flush();

  Serial.println("__________________________________");
  Serial.flush();
}

void presmetajAgli(int x, int y){
  x += greskaX;
  y += greskaY;

  alfaPrethodno = alfa;
  betaPrethodno = beta;
  gamaPrethodno = gama;

  a2 = greskaZ;
  b2 = y;

  c = sqrt(pow((x - yMax), 2) + y*y + greskaZ*greskaZ);
  Serial.println("---------------------------");
  Serial.flush();

  Serial.print("x: ");
  Serial.println(x);
  Serial.flush();

  Serial.print("yMax: ");
  Serial.println(yMax);
  Serial.flush();

  Serial.print("y: ");
  Serial.println(y);
  Serial.flush();

  Serial.print("greskaZ: ");
  Serial.println(greskaZ);
  Serial.flush();

  Serial.println("---------------------------");
  Serial.flush();

  alfa1 = acos((a1*a1 - b1*b1 - c*c) / (-2 * b1 * c));

  beta = acos((c*c - a1*a1 - b1*b1) / (-2 * a1 * b1));

  if(b2 == 0) alfa2 = 90;
  else alfa2 = atan(a2 / b2);

  if(y == 0 && x > yMax) gama = 180;
  else if(y == 0) gama = 0;
  else gama = atan(abs(yMax - x) / (float)y);

  gama *= 180.0 / M_PI;

  if(x > yMax) gama = 90 + gama;
  else gama = 90 - gama;

  alfa = alfa1 + alfa2;

  beta *= 180.0 / M_PI;
  alfa *= 180.0 / M_PI;

  if(c > yMax){
    alfa = alfaPrethodno;
    beta = betaPrethodno;
    gama = gamaPrethodno;
  }
}

void odiNaTocka(int x, int y){
  if(x == prethodnoX && y == prethodnoY) return;
  prethodnoX = x;
  prethodnoY = y;

  int _x = x, _y = y;

  x = map(x, 0, koordinatenOpsegZaX_Oska, 0, xMax);
  y = map(y, 0, koordinatenOpsegZaY_Oska, 0, yMax);

  presmetajAgli(x, y);

  pridviziServoMotori(gama, alfa, beta);

  Serial.print("X: ");
  Serial.println(_x);
  Serial.flush();

  Serial.print("Y: ");
  Serial.println(_y);
  Serial.flush();

  Serial.print("SERVO 1 AGOL: ");
  Serial.println((int)gama);
  Serial.flush();

  Serial.print("SERVO 2 AGOL: ");
  Serial.println((int)alfa);
  Serial.flush();

  Serial.print("SERVO 3 AGOL: ");
  Serial.println((int)beta);
  Serial.flush();

  Serial.print("c: ");
  Serial.println(c, 2);
  Serial.flush();

  Serial.print("b2: ");
  Serial.println(b2, 2);
  Serial.flush();

  Serial.println("__________________________________");
  Serial.flush();
}

void crtajLinija(int x, int y, char nasoka, int dolzina){
  if(x != prethodnoX || y != prethodnoY){
    prethodnaGreskaZ = greskaZ;
    greskaZ += elevacijaPriKrevanjeNaPenkalo;
    odiNaTocka(x, y);

    prethodnoX = 0;
    prethodnoY = 0;
    greskaZ = prethodnaGreskaZ;
    odiNaTocka(x, y);
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

  delay(500);
}












