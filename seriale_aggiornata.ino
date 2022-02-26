#include <math.h>

enum newType{AVVIO, INCALIBRAZIONE, FINECALIBRAZIONE, RICEVIMENTO, ESECUZIONE, FINE};

char risposta;
boolean risp;
char cestino;

const int nMAX=100;
int nCaratteri;
int lungVett;
int dati[nMAX];

int millimetriXMax=100;
int millimetriYMax=150;

newType stato;

void car_to_pc();
void bytes_to_pc();
void bytes_from_pc();
void leggi_cestina();
boolean controllaBuffer();

void setup()
{
  Serial.begin(9600);
  stato=AVVIO;
  risp=false;
}

void loop()
{
  while(stato == AVVIO)
  {
    car_to_pc('s');
    risp=controllaBuffer();
    if(risp==true)
    {
      cestino = Serial.read(); 
      stato = INCALIBRAZIONE;
    }  
  }
  
  stato = FINECALIBRAZIONE;
  nCaratteri=8;
  lungVett=2;
  dati[0]=millimetriXMax;
  dati[1]=millimetriYMax;
  bytes_to_pc();
  
  do{
    stato = RICEVIMENTO;
    car_to_pc('i');
    bytes_from_pc();
    bytes_to_pc();    
    stato = ESECUZIONE;
  }while(controllaBuffer()==true);
  stato = FINE;
}

void car_to_pc(char car)
{
  Serial.write(car);
  delay(500);
}

void bytes_to_pc()
{
  Serial.print(nCaratteri);
  car_to_pc(',');
  delay(500);
  for(int i=0;i<lungVett;i++)
  {
    Serial.print(dati[i]);
    delay(500);
    if(i==0)
      car_to_pc(';');
  }
}

void bytes_from_pc()
{
  while(Serial.available()==0)
    delay(50);
  nCaratteri = Serial.read();
  leggi_cestina();
  for(int i=0;i<2;i++)
    dati[i]=Serial.parseInt();
}

void leggi_cestina()
{
  while(Serial.available()==0)
    delay(50);
  cestino = Serial.read();
}

boolean controllaBuffer()
{
  if(Serial.available()==0)
    return false;
  risposta=Serial.read();
  return true;
}
