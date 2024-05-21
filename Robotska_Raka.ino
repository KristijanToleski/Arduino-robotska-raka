#include <Servo.h>

float a1 = 11.0;
float b1 = 15.0;

float greskaZ = 3.5;

int pocetnaPozicijaZaServo1 = 90;
int pocetnaPozicijaZaServo2 = 90;
int pocetnaPozicijaZaServo3 = 180;

int servo1Pin = 9;
int servo2Pin = 10;
int servo3Pin = 11;

int elevacijaPriKrevanjeNaPenkalo = 4;

int brzinaNaDvizenjeNaRaka = 25;

int koordinatenOpsegZaX_Oska = 1000;
int koordinatenOpsegZaY_Oska = 500;


Servo servo1, servo2, servo3;

float a2, b2, c;
float alfa1, alfa2, alfa = pocetnaPozicijaZaServo2, beta = pocetnaPozicijaZaServo3, gama = pocetnaPozicijaZaServo1;

float yMax = a1 + b1;
float xMax = 2 * yMax;

int krajnaVrednost;

int prethodnoX = 0, prethodnoY = 0;

int prethodnaGreskaZ;

int prethodnaPozicijaNaServo1 = pocetnaPozicijaZaServo1;
int prethodnaPozicijaNaServo2 = pocetnaPozicijaZaServo2;
int prethodnaPozicijaNaServo3 = pocetnaPozicijaZaServo3;

int krajnaXKordinata, krajnaYKordinata;

void setup() {
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);

  vratiNaPocetnaPozicija(false);
  delay(3000);

  // CRTANJE



  //

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

  for(int i = 1; i <= 100; i++){
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
    odiNaTocka(krajnaXKordinata, krajnaYKordinata);
    greskaZ = prethodnaGreskaZ;

    return;
  }

  pridviziServoMotori(pocetnaPozicijaZaServo1, pocetnaPozicijaZaServo2, pocetnaPozicijaZaServo3);
}

void presmetajAgli(int x, int y){
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

void odiNaTocka(int x, int y){
  if(x == prethodnoX && y == prethodnoY) return;
  prethodnoX = x;
  prethodnoY = y;

  x = map(x, 0, koordinatenOpsegZaX_Oska, 0, xMax);
  y = map(y, 0, koordinatenOpsegZaY_Oska, 0, yMax);

  presmetajAgli(x, y);

  pridviziServoMotori(gama, alfa, beta);
}

void crtajLinija(int x, int y, char nasoka, int dolzina){
  if(x != prethodnoX || y != prethodnoY){
    prethodnaGreskaZ = greskaZ;
    greskaZ += elevacijaPriKrevanjeNaPenkalo;
    odiNaTocka(x, y);
    delay(500);

    prethodnoX = 0;
    prethodnoY = 0;
    greskaZ = prethodnaGreskaZ;
    odiNaTocka(x, y);
    delay(500);
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

  delay(1500);
}










