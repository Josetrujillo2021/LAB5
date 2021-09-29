//Universidad Del Valle de Guatemala
//BE3015: Electrónica Digital 2
//José Trujillo
//LAB 5
//Comunicación UART 
//----------------------------------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <LiquidCrystal.h> 
//----------------------------------------------------------------------------------------------------------------------
//Definición de pines
//----------------------------------------------------------------------------------------------------------------------
#define Voltaje1 13
#define Voltaje2 12

#define D4 32
#define D5 33
#define D6 25
#define D7 26

#define RS 27
#define E 14


#define resolucion 8
#define LRChannel 1
#define LVChannel 2
#define LAChannel 3

//----------------------------------------------------------------------------------------------------------------------
//Prototipos de funciones
//----------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
//Variables Globales
//----------------------------------------------------------------------------------------------------------------------

//Creación de las variables que reciben el dato analogico del voltaje
float V1 = 0.0; 
float V2 = 0.0; 

//Creación de variables de comvierten el dato de Analógico a digital
int LR = 0; 
int LV = 0; 

//Generación para las variables de cada uno de los datos mostrados en la LCD 
int decenas1 = 0; 
int unidades1 = 0; 
int decimales1 = 0;

int decenas2 = 0; 
int unidades2 = 0; 
int decimales2 = 0;

int contador = 0; 
LiquidCrystal LCD(RS, E, D4, D5, D6, D7);


//Dutycicle de cada led 
int DutyCicleLR = 0; //dutycicle del led ROJO
int DutyCicleLV = 0; //dutycicle del led VERDE
int DutyCicleLA = 0; //dutycicle del led AZUL

//----------------------------------------------------------------------------------------------------------------------
//ISR  (interrupciones)
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//CONFIGURACIÓN
//----------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200); 
}


//---------------------------------------------------------------------------------------------------------------------
//Loop principal
//---------------------------------------------------------------------------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:
}