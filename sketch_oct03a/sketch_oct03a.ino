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
void configurarPWM(void); 
void Contador(void);
//---------------------------------------------------------------------------------------------------------------------
//Variables Globales
//----------------------------------------------------------------------------------------------------------------------

//Creación de las variables que reciben el dato analogico del voltaje
int V1 = 0; 
int V2 = 0; 


int contador = 0; 
LiquidCrystal LCD(RS, E, D4, D5, D6, D7);


//Dutycicle de cada led 
int DutyCicleLR = 0; //dutycicle del led ROJO
int DutyCicleLV = 0; //dutycicle del led VERDE
int DutyCicleLA = 0; //dutycicle del led AZUL

String Mensaje = ""; 

//Variables de tiempo
int sampleTime1 = 250;
long LastTime; 

int sampleTime2= 500; 
long LastTime2; 
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
  
  //analogResolution(resolucion);

  LastTime=millis();
  LastTime2 = millis(); 
   
}


//---------------------------------------------------------------------------------------------------------------------
//Loop principal
//---------------------------------------------------------------------------------------------------------------------
void loop() {
  if (millis() - LastTime2 >= sampleTime2){
    LectorVoltajes();
    LastTime2 = millis();
  }

  Contador(); 

  if (millis() - LastTime >= sampleTime1){
    LCD.clear(); //limpia la LCD
    LCD.print("Rojo:"); //IMPRIMER EN LA LCD
    LCD.print(" "); 

    LCD.print("Verde:");
    LCD.print(" ");

    LCD.print("Azul:");
    LCD.setCursor(1, 1);
    
    LCD.print(V1);
    LCD.print(" ");

    LCD.print(V2);
    LCD.print(" ");

    LCD.print(contador);
    LastTime= millis(); 
  } 



  }
//---------------------------------------------------------------------------------------------------------------------
//Lector analogico de voltajes
//---------------------------------------------------------------------------------------------------------------------
void LectorVoltajes(void){
  V1 = analogReadMilliVolts(Voltaje1);
  V2 = analogReadMilliVolts(Voltaje2);
  
  V1 = map(V1, 0,3300, 0, 255);
  V2 = map(V2, 0, 3300, 0, 255); 

  ledcWrite(LRChannel, V1);
  ledcWrite(LVChannel, V2);

  //Comunicación con el monitor 
  Serial.print("Pot1: ");
  Serial.print(V1);
  Serial.print('\n');
  Serial.print("Pot2: ");  
  Serial.println(V2);
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

//----------------------------------------------------------------------------------------------------------------------
//FUNCIÓN PARA CONTADOR
//----------------------------------------------------------------------------------------------------------------------4
void Contador(void){
  //si mi entrada es un + entonces mi contador aumenta una unidad
 if(Mensaje =="+"){
    Serial.print("Recibi el siguiente mensaje: ");
    Serial.println(Mensaje);
    Mensaje="";
    if (contador<255){
      contador++;
    }

    else if (contador>=255){
      contador= 0; 
    }
    //ese mismo valor va al dutycicle del led
    ledcWrite(LAChannel, contador); 
    Serial.print("Contador: ");
    Serial.print(contador);
 }
//si mi entrada es un + entonces mi contador disminuye una unidad
 if (Mensaje == "-"){
    Serial.print("Recibi el siguiente mensaje: ");
    Serial.println(Mensaje);
    Mensaje=""; 
    if (contador>0){
      contador--;
    }

    else if (contador<=0){
      contador= 255; 
    }
    //ese mismo valor va al dutycicle del led
    ledcWrite(LAChannel, contador); 

    Serial.print("Contador: ");
    Serial.print(contador);
 }
}
