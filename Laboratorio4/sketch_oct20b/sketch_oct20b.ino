#include <EEPROM.h>
#include <math.h>
float a;
int b;
int address=0;
int led = 13;
int advertencia= 12;
int valor_advertencia=0;
int rele=15;
int rain_detection=0;


//config temp
//constantes del termistor
float rAux = 10000.0;
float vcc = 5.0;
float beta = 3977.0;
float temp0 = 298.0;
float r0 = 10000.0;


//Variables usadas en el cálculo
float vm = 0.0;
float rntc = 0.0;
float temperaturaK = 0.0;


void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}
void loop() 
{
a=millis()/1000;
/*Serial.println(a);
delay(1000);*/
b=(int)a%5;
rain_detection = analogRead(rele)/ 4;


//Bloque de cálculo temperatura
vm=(vcc / 1024)*( analogRead(0) );                //Calcular tensión en la entrada
rntc = rAux / ((vcc/vm)-1);                       //Calcular la resistencia de la NTC
temperaturaK = beta/(log(rntc/r0)+(beta/temp0));  //Calcular la temperatura en Kelvin

//Restar 273 para pasar a grados celsus
float temperaturaC = temperaturaK - 273;
//Serial.println(temperaturaC);
delay(1000); 


//eeprom
if(b==0 && a!=0)
{
  EEPROM.put(address,rain_detection);
  EEPROM.put(address,rain_detection);
  address ++;
  Serial.println(address,temperaturaC);
  Serial.println(EEPROM.get(address,rain_detection));
  if (address == EEPROM.length())
  {
    //clear EEPROM
    for (int i = 0 ; i < EEPROM.length() ; i++) 
    {
      EEPROM.write(i, 0);
    }
    address = 0;
  } 
  delay(1000);
} 


 /*valor_advertencia =analogRead(advertencia);
 if(valor_relay>1022)
 {
    digitalWrite(led,HIGH);
   delay(100);
   digitalWrite(led,LOW);
 }*/
 
}
