//BLUETOOTH
//Libreria para controlar el modulo bluetooth
#include <SoftwareSerial.h>
//inicializamos los pines a los que conectamos el bluetooth
SoftwareSerial BT(2,3); // RX, TX


//SIGUELINEAS
// Pines del infrarrojo
int sensorizq = 8;
int sensorder = 9;
int seguirLineas = 0;

//SENSOR PROXIMIDAD
// Pines Proximidad
const int triggerEmisor = 7;
const int echoReceptor = 4;
// ValorUmbral para que pare el coche
const int valorUmbral = 15;
long tiempoEntrada;  // Almacena el tiempo de respuesta del sensor de entrada
float distanciaEntrada;  // Almacena la distancia en cm a la que se encuentra el objeto 

//MODO COLOR
//variables para el destino por color
int color = 3;
int destino = 4;//0 = rojo. 1 = verde. 2 = azul. 4 = sin destino.
int claxon = 0;
int triangulo = 0;



//MOTORES
// Pines Motor A
int ENA = 6;
int IN1 = 13;
int IN2 = 12;

// Pines Motor B
int ENB = 5;
int IN3 = 11;
int IN4 = 10;

int vel = 100;

void setup()
{
 Serial.begin(9600);
  //Bluetooth
  BT.begin(9600); 
  
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode( sensorizq  , INPUT) ;
  pinMode( sensorder  , INPUT) ;
  pinMode(triggerEmisor,OUTPUT); 
  pinMode(echoReceptor,INPUT); 

}

void loop()
{
  
  BT.listen();
  if (BT.available()){
    //Serial.println("BT available");
    switch (BT.read())
    {
     //Serial.println(BT.read());
    //Direccion del coche
    case 'F':
      Adelante();
      break;
    case 'B':
      Atras();
      break;
    case 'L':
     Derecha();
      break;
    case 'R':
    Izquierda();
      
      break;
    case 'S':
      Parar();
      break;

    //velocidad del coche
    case '0':
      vel = 50;
    break;
    case '1':
      vel = 60;
    break;
    case '2':
     vel = 80;
    break;
    case '3':
      vel = 100;
    break;
    case '4':
      vel = 120;
    break;
    case '5':
      vel = 140;
    break;
    case '6':
      vel = 160;
    break;
    case '7':
      vel = 180;
    break;
    case '8':
      vel=220;
    break;
    case '9':
      vel=250;
    break;
    //COCHE FANTASTICO LUCES DE ALANTE
    case 'W':
      Serial.write('W');
      
    break;
    case 'w':
     Serial.write('w');
      
    break; 
    //SEGUIR LINEAS LUCES DE ATRAS
     case 'U':
      seguirLineas = 1;
    break; 
     case 'u':
      seguirLineas = 0;
    break;  
    //CLAXON
    case 'V':
     Serial.write('V');    
    break;
    case 'v':
      Serial.write('v');      
    break;
   
    //COLORES: delante izquierda = rojo. delante derecha = azul. detras izquierda = verde. detras derecha = ninguno.
    case 'G':
      destino = 0;
    break; 
    case 'I':
      destino = 1;
    break; 
    case 'H':
      destino = 2;
    break; 
    case 'J':
      destino = 4;
    break;     
    } 
  } 

  if(seguirLineas == 1){
    Siguelineas();
  }
    
  Distancia();
  ColorDestino();
  
  //Serial.println(); 

}


void Distancia(){
    // Llamamos al método de Ultrasonidos
  Ultrasonidos();

   // Condición de parar
   if(distanciaEntrada<valorUmbral){
   // Serial.print("OBSTACULO -> ");
    Parar();
    Atras();
    delay(700);
    Parar();
    } 
  
}

 void Siguelineas(){
    // Los valores del infrarrojo
  int valor1 = digitalRead(sensorizq) ;
  int valor2 = digitalRead(sensorder) ;
  
   // Las acciones que el coche tomará en función de los valores de los sensores
  if (valor1 == 0 && valor2 == 0)
     Adelante();
  if (valor1 == 0 && valor2 == 1)
    Izquierda();
  if (valor1 == 1 && valor2 == 0)
    Derecha();
  //if (valor1 == 1 && valor2 == 1)   
    // Atras(); 
  
 }
void Atras()
{
  //Serial.println("Atras");
  //Direccion motor A
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  analogWrite (ENA, vel); 
  //Direccion motor B
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  analogWrite (ENB, vel); 
}

void Adelante()
{
   //Serial.println("Adelante");
  //Direccion motor A
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  analogWrite (ENA, vel);  
  //Direccion motor B
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  analogWrite (ENB, vel); 
}

void Derecha()
{
  //Serial.println("Derecha");
   //Direccion motor A
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  analogWrite (ENA, vel); 
  //Direccion motor B
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  analogWrite (ENB, vel);  
}

void Izquierda()
{
  Serial.println("Izquierda");
 //Direccion motor A
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  analogWrite (ENA, vel); 
  //Direccion motor B
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  analogWrite (ENB, vel); 
}

void Parar()
{
  //Serial.println("Parar");
  //Direccion motor A
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
  analogWrite (ENA, 0); 
  //Direccion motor B
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
  analogWrite (ENB, 0); 
}

void Ultrasonidos()
{
     // Se inicializa el sensor de ultrasonidos
    digitalWrite(triggerEmisor,LOW);  
 
    // Comenzamos las mediciones
    // Enviamos una señal ultrasónica
    digitalWrite(triggerEmisor, HIGH);  
    tiempoEntrada=pulseIn(echoReceptor, HIGH); 
    distanciaEntrada= int(0.017*tiempoEntrada); // Cálculo de distancia
}

void ColorDestino(){
  
   if(Serial.available()){      
      color = Serial.read();
      if(color == destino){
          Parar();            
      }
   }
}
  
    
