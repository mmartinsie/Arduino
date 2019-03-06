// Sensor luminoso. Se encienden 3 LEDS (azul, verde y rojo) en función de la luminosidad de la sala.
// Usamos resistencias de 220 ohmios para los LEDs y de 10 kOhmios para el sensor de luminosidad.
int sensor = 0; // LDR
int val = 0; // Valor devuelto por el LDR
int nivel = 0;
int led[] = {6,5,3}; // Los LEDS estan conectados en las salidas digitales 6 (azul), 5 (verde) y 3 (rojo) 
void setup() {
 // Establecemos todas las conexiones de los LEDS como salidas
 for (int i=0; i<=2; i++)
 {
 pinMode(led[i],OUTPUT);
 }

 Serial.begin(9600); // Abrimos la comunicación serie
}
void loop(){
 val = analogRead(sensor); // Leemos el sensor de luminosidad
 Serial.println(val); // Y escribimos su valor en el puerto serie
 // Calculamos en que nivel estamos para saber que LEDs deben encenderse. Recordemos que la medida del sensor va de 0 a 1023 y tenemos 3 LEDs. Son 4 niveles el cual el 0 es apagado
 nivel = floor(val/255.75); // Elegimos 4 niveles, donde 1023/4=255.75
 // Hasta el nivel correspondiente, encendemos los LEDS
 if(nivel==0){
  analogWrite(led[0],0);
  analogWrite(led[1],0);
  analogWrite(led[2],0);
 }
 else if(nivel==1){
  analogWrite(led[0],val-255);
  analogWrite(led[1],0);
  analogWrite(led[2],0);
 }
 else if(nivel==2){
  analogWrite(led[0],255);
  analogWrite(led[1],val-510);
  analogWrite(led[2],0);
 }
 else if(nivel==3){
  analogWrite(led[0],255);
  analogWrite(led[1],255);
  analogWrite(led[2],val-765);
 }
}
