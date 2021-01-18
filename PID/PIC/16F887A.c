#INCLUDE <16F877A.H>
#DEVICE ADC=10
#USE DELAY(CLOCK=4000000)
#FUSES XT,NOWDT
VOID MAIN(){
INT16 valor, control; //Variables para lectura de ADC y señal de Control a modulo CCP
FLOAT a,b,c; //Constantes para parámetros de controlador PID
FLOAT TEMPERATURA_LIMITE; //Referencia de Temperatura
FLOAT rt,eT,iT,dT,yT,uT,iT0,eT0; //Variables de controlador PID
FLOAT max,min; //Variables para anti-windup
min=0.0;
max=1000.0;
iT0=0.0;
eT0=0.0;
a=0.1243; 
b=0.0062;
c=0.6215;
TEMPERATURA_LIMITE=1200.0; //Set Point r(kT)= 120°C
setup_timer_2(t2_div_by_4,249,1); //Configuracion de Timer 2 para establecer frec. PWM a 1kHz
setup_ccp1(ccp_pwm); //Configurar modulo CCP1 en modo PWM
setup_adc_ports(all_analog); //Configurar ADC
setup_adc(adc_clock_internal);
set_adc_channel(0); //Seleccionar Canal 0 para sensor de Temperatura
while(true){
valor=read_adc(); //Leer ADC
yT=5000.0*valor/1024.0; //Escalizar señal de salida y(kT)
rT=TEMPERATURA_LIMITE;
eT=rT-yT; //Calcular senal de error e(kT)
iT=b*eT+iT0; //Calcular termino integrativo i(kT)
dT=c*(eT-eT0); //Calcular termino derivativo d(kT)
uT=iT+a*eT+dT; //Calcular senal de control u(kT)
if (uT>max){ //Anti-windup
uT=max;
}
else {
 if (uT<min){
uT=min;
 }
}
control=uT;
set_pwm1_duty(control); //Transferencia de senal de control al actuador
iT0=iT;
eT0=eT;
delay_ms(100); //Periodo de muestreo T=0.1s
 }
} 
