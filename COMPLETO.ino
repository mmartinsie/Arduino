//CÓDIGO COMPLETO

//Librerias utilizadas
#include <LiquidCrystal.h>

//DEFINIMOS LAS CONSTANTES

//Constantes LCD
#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD
#define VELOCIDAD 300 // Velocidad a la que se mueve el texto


//PINES 

// Pines del infrarrojo
int sensorizq = 8;
int sensorder = 9;

// Pines Motor A
int ENA = 6;
int IN1 = 13;
int IN2 = 12;

// Pines Motor B
int ENB = 5;
int IN3 = 11;
int IN4 = 10;

// Lo primero is inicializar la librería indicando los pins de la interfaz
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pines sensor color
const int s0 = A1;  
const int s1 = A2;  
const int s2 = A3;  
const int s3 = A4;  
const int out = A5;    


//Inicializamos la velocidad a la que circula
int vel = 10;

//Inicializamos la variable del color que buscamos

//siendo ROJO = 0 AZUL = 1 VERDE = 2
const int destino = 0;

// Valores con los que detectaremos el color
int a = 0;  
int c = 0;  
int b = 0;  

// Textos
String texto_fila = "VERDE VERDE VERDE";


void setup(){
  // Configuración monitor serie
  Serial.begin(9600);

  // Configuramos las filas y las columnas del LCD en este caso 16 columnas y 2 filas
  lcd.begin(COLS, ROWS);
  
  //Configuramos los pines de los motores como salidas
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  
  //Configuramos los pines del sensor siguelineas como entradas
  pinMode( sensorizq  , INPUT) ;
  pinMode( sensorder  , INPUT) ;
  
  //Configuramos los pines s0,s1,s2 y s3 del sensor de color como salidas  
  pinMode(s0,OUTPUT);  
  pinMode(s1,OUTPUT);  
  pinMode(s2,OUTPUT);  
  pinMode(s3,OUTPUT);
	
  pinMode(out,INPUT); //configuramos el pin out del sensor de color como entradas  
  digitalWrite(s0,HIGH);  
  digitalWrite(s1,HIGH); 
	
}


void loop(){
	
}

void Adelante ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 255); //Velocidad motor B
}
void Atras ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 128); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 128); //Velocidad motor B
}
void Derecha ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 200); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 100); //Velocidad motor A
}

void Izquierda ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 50); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 150); //Velocidad motor A
}
void Parar ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 0); //Velocidad motor A
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
  Serial.print(" A ");  
  Serial.print(a, DEC);  
  Serial.print(" B ");  
  Serial.print(b, DEC);  
  Serial.print(" C ");  
  Serial.print(c, DEC);
  Serial.print(" "); 

  // Condiciones de deteccion de color
  if (a>4&& a<13 && b>4 && b<13 && c>20 && c<32) 
  {  
    Serial.print(" Rojo ");  
  
      
  }   
  else if (a>8 && a<20 && b>1 && b<8 && c>5 && c<15)  
  {  
    Serial.print(" Azul ");   
 
     
  }  
  else if (a>15 && a<28 && b>5 && b<15 && c>15 && c<25)  
  {  
    Serial.print(" Verde ");
          
  }  
    
}

void lcd(String texto) { 

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
