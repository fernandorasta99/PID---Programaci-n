int valor;
int control; //Variables para lectura de ADC y señal de Control a modulo CCP
float kp=0.1243; 
float ki=0.0062;
float kd=0.6215; //Constantes para parámetros de controlador PID
float setpoint=1200.0; //Set Point r(kT)= 120°C  //Referencia de Temperatura
//Variables de controlador PID
float P;
float I;
float D;
float senal;
float error;
float temperatura;
float acomulado=0;
float erroranterior=0; 
int adc=A0;
int salida=3;
int MUESTREO=100;
unsigned long pasado=0;
unsigned long ahora;
void setup() {
pinMode(adc,INPUT);
pinMode(salida,OUTPUT);
}
void control_pid(){
error = setpoint-temperatura;
P=kp*(error); 
I=ki*error+acomulado; 
D=kd*(error-erroranterior); 
senal=P+I+D; 
}
void loop() {
  ahora=millis();                            
    int ACTUAL=ahora-pasado; 
     if(ACTUAL >= MUESTREO) 
     {
valor=analogRead(adc); 
temperatura=5000.0*valor/1023;
control_pid(); 
pasado=ahora;
if (senal>255){ //Anti-windup
senal=255;
}
else {
 if (senal<0){
senal=0;
 }
}
control=senal;
analogWrite(salida,control); 
acomulado=I;
erroranterior=error;
}
}
