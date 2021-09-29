//--------------------------------------------------------------------------------
//Universidad del Valle de Guatemala
//BE3015 Electronica Digital 2
//Karen Joachin
//Laboratorio 5 UART
//-----------------------------------------------------------------------------
//Librerias
//-----------------------------------------------------------------------------
#include <Arduino.h>
#include <LiquidCrystal.h>
//-----------------------------------------------------------------------------
//Definiciond de etiquetas
//-----------------------------------------------------------------------------

#define d4 19
#define d5 21
#define d6 5
#define d7 22
#define en 15
#define rs 18

#define pot1 32
#define pot2 13

#define PWMcanalL1 1 // tenemos 16 canales del 0 a 15
#define frecPWM 50   // frecuencia en Hz para todo leds y motor.
#define resolucion 8 //8 bits se puede de 1 a 16 bits ... significa que tengo de 0 a 255 para dutty cicle
#define pinPWMR      //ahi va la led roja

#define PWMcanalL2 2
#define pinPWMV //ahi va la led verde

#define PWMcanalL3 3
#define pinPWMA //para led azul

//-----------------------------------------------------------------------------
//Prototipo de funciones
//-----------------------------------------------------------------------------
void configurarPWMLED(void);
//-----------------------------------------------------------------------------
//Variabls Globales
//-----------------------------------------------------------------------------
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);
uint8_t decenas, unidades, decimal;
uint8_t decenas2, unidades2, decimal2;
int adcRaw;
float voltaje;
float voltaje2;


//-----------------------------------------------------------------------------
//ISR
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//Configuracion
//-----------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  LCD.begin(16, 2);


  configurarPWMLED();
}
//-----------------------------------------------------------------------------
//loop principal
//-----------------------------------------------------------------------------

void loop()
{
  contador;
  //pra primer potenciometro
  voltaje = analogReadMilliVolts(pot1) / 10.0;
  int temp = voltaje;
  decenas = temp / 100.0;
  temp = temp - decenas * 100.0;
  unidades = temp / 10.0;
  temp = temp - unidades * 10.0;
  decimal = temp;

  //para segundo potenciometro
  voltaje2 = analogReadMilliVolts(pot2) / 10.0;
  int temp2 = voltaje2;
  decenas2 = temp2 / 100.0;
  temp2 = temp2 - decenas2 * 100.0;
  unidades2 = temp2 / 10.0;
  temp2 = temp2 - unidades2 * 10.0;
  decimal2 = temp2;

  Serial.print("Rojo: ");
  Serial.print(voltaje);
  Serial.print("\n");

  Serial.print("Verde: ");
  Serial.print(voltaje2);
  Serial.print("\n");

  Serial.print("Azul: ");
  Serial.print(contador);
  Serial.print("\n");


  //para limpiar LCD
  LCD.clear();
  LCD.print("Rojo:");
  LCD.print("Verde :");
  LCD.print("Azul:");

  LCD.setCursor(0, 1); //para cambiar de fila y columna
  LCD.print(decenas);
  LCD.print('.');
  LCD.print(unidades);
  LCD.print(decimal);
  LCD.print(" ");

  LCD.print(decenas2);
  LCD.print('.');
  LCD.print(unidades2);
  LCD.print(decimal2);
  LCD.print(" ");
  // para el contador con la comunicacion
  LCD.print(contador); 

  delay(1000);
}

//-----------------------------------------------------------------------------
//Funcion para configurar pwm de las leds
//-----------------------------------------------------------------------------
void configurarPWMLED(void)
{
  // primero se configura el modulo pwm
  ledcSetup(PWMcanalL1, frecPWM, resolucion);
  ledcSetup(PWMcanalL2, frecPWM, resolucion);
  ledcSetup(PWMcanalL3, frecPWM, resolucion);
  //Para leds. Se conecta el GPIO al canal
  ledcAttachPin(pinPWMR, PWMcanalL1);
  ledcAttachPin(pinPWMV, PWMcanalL2);
  ledcAttachPin(pinPWMA, PWMcanalL3);
}