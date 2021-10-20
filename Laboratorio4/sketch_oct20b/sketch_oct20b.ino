#include <EEPROM.h>
#include <Servo.h>
#include <math.h>

//objetos del servo
Servo servo_vertical;
Servo servo_horizontal;

int pinservo_vertical=12;
int pinservo_horizontal=11;
//lectura del pot
int ver_val;
int hor_val;
/////
int POT_1 = 1;      // potenciometro en entrada analogica A1
int POT_2 = 2;      // potenciometro en entrada analogica A2
///////////////////////////
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


void setup() 
{
  servo_vertical.attach(pinservo_vertical);  // inicializacion de servo vertical
  servo_horizontal.attach(pinservo_horizontal);  // inicializacion de servo vertical
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}
void loop() 
{
a=millis()/1000;
/*Serial.println(a);
delay(1000);*/
b=(int)a%5;
rain_detection = analogRead(rele);


//Bloque de cálculo temperatura
vm=(vcc / 1024)*( analogRead(0) );                //Calcular tensión en la entrada
rntc = rAux / ((vcc/vm)-1);                       //Calcular la resistencia de la NTC
temperaturaK = beta/(log(rntc/r0)+(beta/temp0));  //Calcular la temperatura en Kelvin

//Restar 273 para pasar a grados celsus
float temperaturaC = temperaturaK - 273;
//Serial.println(temperaturaC);
delay(1000); 

////funcionamiento servo vertical
ver_val = analogRead(POT_1);      // valor pin A1
ver_val = map(ver_val, 0, 1023, 0, 180);  // con funcion map convierte rango de 0 a 1023
            // a rango de angulo de 0 a 180
servo_vertical.write(ver_val);       // envia al servo el valor del angulo
delay(15);   
 
////funcionamiento servo horizontal
hor_val = analogRead(POT_2);      // valor pin A2
hor_val = map(hor_val, 0, 1023, 0, 180);  // con funcion map convierte rango de 0 a 1023
            // a rango de angulo de 0 a 180
servo_horizontal.write(hor_val);       // envia al servo el valor del angulo
delay(15);    





//eeprom
if(b==0 && a!=0)
{
  EEPROM.write(address,temperaturaC);
  Serial.println(address);
  Serial.println(EEPROM.get(address,temperaturaC));
  address+=sizeof(float);
  EEPROM.write(address,rain_detection);
  Serial.println(address);
  Serial.println(EEPROM.get(address,rain_detection));
  address+=sizeof(float);
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
