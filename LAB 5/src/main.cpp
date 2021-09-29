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

#define freq 50
#define resolucion 8
#define LRChannel 1
#define LVChannel 2
#define LAChannel 3

#define LR 4
#define LV 2
#define LA 15

//----------------------------------------------------------------------------------------------------------------------
//Prototipos de funciones
//----------------------------------------------------------------------------------------------------------------------
void LectorVoltajes(void);
void PWMLEDS(V1, V2); 
void configurarPWM(void); 
//---------------------------------------------------------------------------------------------------------------------
//Variables Globales
//----------------------------------------------------------------------------------------------------------------------

//Creación de las variables que reciben el dato analogico del voltaje
int V1 = 0; 
int V2 = 0; 

//Creación de variables de comvierten el dato de Analógico a digital
int LR = 0; 
int LV = 0; 

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

  configurarPWM();
  // Este comando limpia la LCD
  LCD.begin(16, 2);

  pinMode(LR, OUTPUT);
  pinMode(LV, OUTPUT); 
  pinMode(LA, OUTPUT);

  digitalWrite(LR, LOW);
  digitalWrite(LV, LOW);
  digitalWrite(LA, LOW);
  
  analogResolution(resolucion);
   
}


//---------------------------------------------------------------------------------------------------------------------
//Loop principal
//---------------------------------------------------------------------------------------------------------------------
void loop() {
  LectorVoltajes();
  PWMLEDS(V1, V2);
  
  }
//---------------------------------------------------------------------------------------------------------------------
//Lector analogico de voltajes
//---------------------------------------------------------------------------------------------------------------------
void LectorVoltajes(void){
  V1 = analogReadMillivolts(Voltaje1);
  V2 = analogReadMilliVolts(Voltaje2);
  
  V1 = map(V1, 0,1023, 0, 255);
  V2 = map(V2, 0, 1023, 0, 255); 
  }


//----------------------------------------------------------------------------------------------------------------------
//FUNCIÓN PARA CONFIGURAR PWM General
//----------------------------------------------------------------------------------------------------------------------

void configurarPWM(void){
  //Configurando PWM para los leds

  ledcSetup (LRChannel, freq, resolucion); 
  ledcAttachPin(LR, LRChannel);

  ledcSetup (LVChannel, freq, resolucion); 
  ledcAttachPin(LV, LVChannel);

  ledcSetup (LAChannel, freq, resolucion); 
  ledcAttachPin(LA, LAChannel);
}

//---------------------------------------------------------------------------------------------------------------------
//PWM LEDS
//---------------------------------------------------------------------------------------------------------------------
void PWMLEDS(int x, int y){

}
