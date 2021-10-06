//********************************************************************************
// Universidad del Valle de Guatemala
// BE3015: Electrnónica Digital 2
// José David Méndez 19380
// Laboratorio 5
//********************************************************************************

//**********************************************************************************************************************
// Librerías
//**********************************************************************************************************************
#include <Arduino.h>
#include <LiquidCrystal.h> // Librería que contiene la cofiguración completa de la pantalla LCD
//**********************************************************************************************************************
// Defincion de Pines
//**********************************************************************************************************************
#define d4 18
#define d5 5
#define d6 17
#define d7 16
#define en 19
#define rs 21
#define pot1 34
#define pot2 35
// Definición de las varaibles de salida de los leds con sus respectivo numero de pin
#define ledR 33
#define ledV 27
#define ledA 13

// Definción de varaibles para la configuración del PWM
#define pwmChledR 0  // 16 Canales 0-15
#define pwmChledV 1  // 16 Canales 0-15
#define pwmChledA 2  // 16 Canales 0-15
#define freqPWM 50   // Frecuencia en Hz
#define resolucion 8 // 1-16 bits de resolucion

//**********************************************************************************************************************
// Prototipo de Funciones
//**********************************************************************************************************************
void voltaje1(void); // Función para la impresión del voltaje del potenciometro 1
void voltaje2(void); // Función para la impresión del voltaje del potenciometro 2
void UPC(void);      // Función para la impresión del contador en la LCD
void USART(void);    //Función de comunicación USART
void configurarPWM(void);
void funcionamientoLEDS(void);
//**********************************************************************************************************************
// Variables Globales
//**********************************************************************************************************************
LiquidCrystal LCD(rs, en, d4, d5, d6, d7); // Variables definidas en la librería
uint8_t decenas, unidades, decimal;
uint8_t decenas1, unidades1, decimal1;
uint8_t centenas, decenas2, unidades2;
int adcRaw;
int contador = 0;
float voltaje;
//**********************************************************************************************************************
// ISR: Interrupciones
//**********************************************************************************************************************

//**********************************************************************************************************************
// Configuracion
//**********************************************************************************************************************
void setup()
{
  // Velocidad a la que trabaja la comunicación serial
  Serial.begin(115200);
  // Se establece que la LCD utilizada es de 16x2
  LCD.begin(16, 2);
}
//**********************************************************************************************************************
// LOOP
//**********************************************************************************************************************
void loop()
{
  // Llamado de funciones
  voltaje1();
  voltaje2();
  UPC();
  delay(250);
//**********************************************************************************************************************
// Fuinciones
//**********************************************************************************************************************
void voltaje1(void) // Voltaje potenciometro 1
{
  // Conversión de señal ADC a miliVoltios
  voltaje = analogReadMilliVolts(pot1) / 10.0;

  // Operación para obtener unidades y decimales del voltaje del Potenciometro 1
  int vol = voltaje;
  decenas = vol / 100.0;
  vol = vol - decenas * 100.0;
  unidades = vol / 10.0;
  vol = vol - unidades * 10.0;
  decimal = vol;

  // Impresión del voltaje del potenciometro 1 en la LCD con su respectiva posición
  LCD.clear();
  LCD.print("Rojo:");
  LCD.setCursor(1, 0);
  LCD.print(decenas);
  LCD.print('.');
  LCD.print(unidades);
  LCD.print(decimal);
}
void voltaje2(void) // Voltaje potenciometro 2
{
  // Conversión de señal ADC a miliVoltios
  voltajeB = analogReadMilliVolts(pot2) / 10.0;

  // Operación para obtener unidades y decimales del voltaje del Potenciometro 2
  int vol1 = voltajeB;
  decenas1 = vol1 / 100.0;
  vol1 = vol1 - decenas1 * 100.0;
  unidades1 = vol1 / 10.0;
  vol1 = vol1 - unidades1 * 10.0;
  decimal1 = vol1;

  // Impresión del voltaje del potenciometro 2 en la LCD con su respectiva posición
  LCD.setCursor(0, 6);
  LCD.print("Ver:");
  LCD.setCursor(1, 6);
  LCD.print(decenas1);
  LCD.print('.');
  LCD.print(unidades1);
  LCD.print(decimal1);
}
void UPC(void) // Valor contador
{
  // Operación para obtener centenas, decenas y unidades del valor del contador
  int cont = contador;
  centenas = cont / 100.0;
  cont = cont - centenas * 100.0;
  decenas2 = cont / 10.0;
  cont = cont - decenas2 * 10.0;
  unidades2 = cont;

  // Impresión del valor del contador en la pantalla LCD
  LCD.setCursor(0, 11);
  LCD.print("Azul:");
  LCD.setCursor(1, 11);
  LCD.print(centenas);
  LCD.print(decenas2);
  LCD.print(unidades2);
}
