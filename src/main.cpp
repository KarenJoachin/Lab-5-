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

#define ledR 23 //ahi va la led roja

#define ledV 2 //ahi va la led verde

#define ledA 4 //para led azul

//-----------------------------------------------------------------------------
//Prototipo de funciones
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//Variabls Globales
//-----------------------------------------------------------------------------
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);
uint8_t decenas, unidades, decimal;
uint8_t decenas2, unidades2, decimal2;
int adcRaw;
float voltaje;
float voltaje2;

String mensaje = "";

int dutycycleR; // para intensidad
int dutycycleV;
int dutycycleA;

int contar = 0;
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

  //Salida de
  pinMode(ledR, OUTPUT);
  pinMode(ledV, OUTPUT);
  pinMode(ledA, OUTPUT);
  // entradas
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
}
//-----------------------------------------------------------------------------
//loop principal
//-----------------------------------------------------------------------------

void loop()
{
  Serial.print(contar);
  //********config UART***********************************************************************
  if (Serial.available() > 0)
  {
    mensaje = Serial.readStringUntil('\n'); // para leer el dato
    Serial.print("Recibi el siguiente mensaje: ");
    Serial.println(mensaje);

    if (mensaje == "pot1")
    {
      Serial.print(voltaje);
      mensaje = "";
    }
    if (mensaje == "pot2")
    {
      Serial.print(voltaje2);
      mensaje = "";
    }
    if (mensaje == "1")
    {
      static unsigned long last_time_intrr1 = 0; //[ultimo tiempo]
      unsigned long time_intrr1 = millis();      //tiempo en tiempo real

      if (time_intrr1 - last_time_intrr1 > 200)
      {
        contar++;

        if (contar > 255)
        {
          contar = 0;
        }
      }
      last_time_intrr1 = time_intrr1; //update del valor de la interrupcion
      digitalWrite(ledA, contar);
      Serial.println("LED SUMA");
      mensaje = "";
    }
    if (mensaje == "2")
    {
      static unsigned long last_time_intrr2 = 0; //[ultimo tiempo]
      unsigned long time_intrr2 = millis();      //tiempo en tiempo real

      if (time_intrr2 - last_time_intrr2 > 200)
      {
        contar--;

        if (contar < 0)
        {
          contar = 255;
        }
      }
      last_time_intrr2 = time_intrr2; //update del valor de la interrupcion

      digitalWrite(ledA, contar);
      Serial.println("LED RESTA");
      mensaje = "";
    }
  }

  //******************************************************************************************

  //para primer potenciometro
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

  //Para leds
  int potvalue = analogRead(pot1);
  int ledValue = map(potvalue, 0, 1023, 0, 255);
  digitalWrite(ledR, ledValue);
  delay(2);
  int potvalue2 = analogRead(pot2);
  int ledValue2 = map(potvalue2, 0, 1023, 0, 255);
  digitalWrite(ledV, ledValue2);
  delay(2);

  //para limpiar LCD
  LCD.clear();
  LCD.print("Rojo:");
  LCD.print("Verde :");
  LCD.print("Azul:");

  LCD.setCursor(0, 1); //para cambiar de fila y columna
  LCD.print(decenas);
  LCD.print(unidades);
  LCD.print('.');
  LCD.print(decimal);
  LCD.print(" ");

  LCD.print(decenas2);
  LCD.print(unidades2);
  LCD.print('.');
  LCD.print(decimal2);
  LCD.print(" ");
  // para el contador con la comunicacion
  LCD.print(contar);

  delay(1000);
}