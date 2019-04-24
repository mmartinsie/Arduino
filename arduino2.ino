//Libreia para el control de la pantalla LCD
#include <LiquidCrystal.h>

//DEFINIMOS LAS CONSTANTES

//Constantes LCD
#define VELOCIDAD 200 // Velocidad a la que se mueve el texto

//Definimos los pines del LCD
int V0 = 9;
int RS = 7;
int E = 8;
int D4 = 10;
int D5 = 11;
int D6 = 12;
int D7 = 13;

// Incializamos la librería indicando los pins de la interfaz
LiquidCrystal lcd(RS,E,D4,D5,D6,D7);

// Destino donde el coche se para 
// ROJO = 0 AZUL = 1 VERDE = 2 NINGUNO DE LOS ANTERIORES = 3
int color = 3;

//pines color
const int s0 = A1;
const int s1 = A2;
const int s2 = A3;
const int s3 = A4;
const int out = A5;

// Textos
String textolcd = "HOLA HOLA HOLA";
String texto_sinColor = "HOLA HOLA HOLA";
String textoAux;

// Valores con los que detectaremos el color
int a = 0;  
int c = 0;  
int b = 0; 

//pines LEDs coche fantástico
int led[] = {2,3,4,5};
int f = 0; //Coche fantastico off


//zumbador
int duracion=1000; //Duración del sonido
const int zumbador = 6; 
int cla = 0; //claxon modo off

void setup() {
  Serial.begin(9600);
  analogWrite(V0,5);
  lcd.begin(16,2);
  lcd.setCursor(1,0);
  lcd.print(textolcd);
  pinMode(s0,OUTPUT);  
  pinMode(s1,OUTPUT);  
  pinMode(s2,OUTPUT);  
  pinMode(s3,OUTPUT);  
  pinMode(out,INPUT);   
  digitalWrite(s0,HIGH);  
  digitalWrite(s1,HIGH);

  for(int i = 0; i<4;i++){
    pinMode(led[i],OUTPUT); 
  }

  
}

void loop() {
   //Llamamos al método de color
  Color(); 
  delay(1000);  
 
  if(Serial.available()){
    char aux = Serial.read();
    if(aux == 'V'){
      cla=1;
    } 

    if(aux == 'v'){
      cla=0;
    } 

    if(aux == 'W'){
      f = 1;
    }

    if(aux == 'w'){
      f = 0;
    }
   
  }
  
  if(cla == 1){
      Claxon();
    }
  if(f == 1){
      Fantastico();
  }
  
}

void Color()  
{    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);   
  a = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);   
  b = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);    
  c = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);


  // Imprimimos por pantalla los valores de color
 /*Serial.print(" A ");  
  Serial.print(a, DEC);  
  Serial.print(" B ");  
  Serial.print(b, DEC);  
  Serial.print(" C ");  
  Serial.print(c, DEC);
  Serial.print(" "); */

  // Condiciones de deteccion de color
  if (a>7 && a<13 && b>7 && b<11 && c>6 && c<10) 
  {  
   //Serial.print(" Verde ");
   textoAux = "VERDE VERDE VERDE";
   color = 2;      
  }
  else if (a>4&& a<10 && b>7 && b<18 && c>8 && c<22)   
  {     
     //Serial.print(" Rojo ");
     textoAux = "ROJO ROJO ROJO";  
     color = 0;        
  }   
  else if (a>10 && a<19 && b>4 && b<8 && c>7 && c<11)  
  {  
   //Serial.print(" Azul ");
    textoAux = "AZUL AZUL AZUL"; 
    color = 1;   
  } else {
    textoAux = texto_sinColor;
    color = 3;  
  }

  if(textoAux != textolcd){
    lcd.clear();
    lcd.setCursor(1,0);
    textolcd = textoAux;
    lcd.print(textolcd); 
    Serial.write(color);
  }
}

void Lcd(String texto_fila) { 

  // Obtenemos el tamaño del texto
  int tam_texto=texto_fila.length();

  // Mostramos entrada texto por la izquierda
  for(int i=tam_texto; i>0 ; i--)
  {
    String texto = texto_fila.substring(i-1);

    // Limpiamos pantalla
    lcd.clear();

    //Situamos el cursor
    lcd.setCursor(0, 0);

    // Escribimos el texto
    lcd.print(texto);

    // Esperamos
    delay(VELOCIDAD);
  }

  // Desplazamos el texto hacia la derecha
  for(int i=1; i<=16;i++)
  {
    // Limpiamos pantalla
    lcd.clear();

    //Situamos el cursor
    lcd.setCursor(i, 0);

    // Escribimos el texto
    lcd.print(texto_fila);

    // Esperamos
    delay(VELOCIDAD);
  }

  // Desplazamos el texto hacia la izquierda en la segunda fila
  for(int i=16;i>=1;i--)
  {
    // Limpiamos pantalla
    lcd.clear();

    //Situamos el cursor
    lcd.setCursor(i, 1);

    // Escribimos el texto
    lcd.print(texto_fila);

    // Esperamos
    delay(VELOCIDAD);
  }

  // Mostramos salida del texto por la izquierda
  for(int i=1; i<=tam_texto ; i++)
  {
    String texto = texto_fila.substring(i-1);

    // Limpiamos pantalla
    lcd.clear();

    //Situamos el cursor
    lcd.setCursor(0, 1);

    // Escribimos el texto
    lcd.print(texto);

    // Esperamos
    delay(VELOCIDAD);
  }
}

void Fantastico(){
   for (int i = 0 ; i < 4 ; i++){
        digitalWrite( led[i] , HIGH);
        delay (500);
        digitalWrite( led[i] , LOW);
        delay (500);
   }      
}

void Claxon(){
    tone(zumbador, 2000, duracion);
}
