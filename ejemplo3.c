#include <16f876.h>
#fuses xt,nowdt,noput,nobrownout,nolvp,noprotect
#device adc=10
#use delay(clock= 4M)
#include <lcd.c>
#use standard_io(C)
#use standard_io(A)

enum funciones{med,cal,ini};  // asigna un valor a cada elemento  
                               // med=0 , cal = 1  e ini = 2
//programa 1                               
void medir(void){    // algoritmo de funcionamiento del motor por 1 minuto
int i;
    output_high(PIN_C0);
    lcd_gotoxy(3,1);
 for(i=0;i<=30;i++){ //bucle for para contar los 60 segundos
    lcd_putc("\f");
    delay_ms(200);
    lcd_gotoxy(3,1);
    lcd_putc("Refrigerando");
    lcd_gotoxy(5,2);
    lcd_putc("espere");
    delay_ms(1400);
}
    output_low(PIN_C0);
    lcd_putc("\f");
}

//programa 2
void calibrar(void){   // algoritmo de funcionamiento del motor por 2 minutos
int i;
    output_high(PIN_C0);
    lcd_gotoxy(3,1);
for(i=0;i<=60;i++){  //bucle for para contar los 120 segundos
    lcd_putc("\f");
    delay_ms(200);
    lcd_gotoxy(3,1);
    lcd_putc("Refrigerando");
    lcd_gotoxy(5,2);
    lcd_putc("espere");  
    delay_ms(1400);
}
    output_low(PIN_C0);
    lcd_putc("\f");   
}

//programa 3
void inicializar(void){   //algoritmo de funcionamiento del motor por 3 minutos
int i;
    output_high(PIN_C0);
    lcd_gotoxy(3,1);
for(i=0;i<=90;i++){ //bucle for para contar los 180 segundos
    lcd_putc("\f");
    delay_ms(200);
    lcd_gotoxy(3,1);
    lcd_putc("Refrigerando");
    lcd_gotoxy(5,2);
    lcd_putc("espere");
    delay_ms(1400);
}
    output_low(PIN_C0);
    lcd_putc("\f");
}

// programa para asignar un numero de la variable item a los 3 programas anteriores
void run_func(int numfunc){  

switch(numfunc){
case med:
medir();
break;
case cal:
calibrar();
break;
case ini:
inicializar();
break;
}
}

//programa principal
void main(){
float temper, medicion;// variables para sensor de temperatura
char item;  // variables para las funciones de los minutos
char n_menus = 3;
    lcd_init();
  
while(1){                  
    setup_adc (adc_clock_internal);//programa sensor de temperatura
    setup_adc_ports(AN0);
    set_adc_channel (0);
    medicion=read_adc ();
    setup_adc (adc_off);
    temper=medicion*(0.48875);
    lcd_gotoxy(8,1);
    delay_ms(300);
    printf(lcd_putc, "%02.1f",temper);
    lcd_gotoxy(12,1);
    lcd_putc("oC");

if (medicion*(0.48875)>=4){ // si la temperatura es mayor a 4� se enciende el modulo peltier
     output_high(pin_C1) ;
}
if (medicion*(0.48875)<4){ //si la temperatura es menor a 4� se apagar el modulo peltier
    output_low(pin_C1);
}

                             // aqui inicia el programa del menu

                            // detecta boton para cambiar la seleccion para minutos
if (input(PIN_A1)==1){     //   
    item++;                    // aumenta la variable  item
    delay_ms(100);             // retardo antirebotes 
    lcd_putc('\f');
}
if(item >(n_menus-1)){     // si la variable supera  el numero de funciones   
    item=0;                    // inicializa la variable
}

switch(item){ // programa muestra en la pantalla la opcion para seleccionar segun la variable item

case 0:              // case 0 muestra la opcion de 1 minuto
    lcd_gotoxy(3,1);  
    lcd_putc("Temp=");
    lcd_gotoxy(3,2);
    printf(lcd_putc,"Minutos : 1");
    lcd_gotoxy(3,2);
break;

case 1:             //case 1 muestra la opcion de 2 minutos
    lcd_gotoxy(3,1);
    lcd_putc("Temp=");
    lcd_gotoxy(3,2);
    printf(lcd_putc,"Minutos : 2");
    lcd_gotoxy(3,2);
break;

case 2:             //case 2 muestra la opcion de 3 minutos
    lcd_gotoxy(3,1);
    lcd_putc("Temp=");
    lcd_gotoxy(3,2);
    printf(lcd_putc,"Minutos : 3");
    lcd_gotoxy(3,2);
break;
}
if (input(PIN_A2)==1){     //detecta si se presiono boton de seleccion de opcion mostrada en la pantalla
    delay_ms(100);        //retardo antirebotes
    run_func(item);  //inicializa los programas con las funciones asignadas al inicio de todo el programa
                     // (void medir), (void calibrar), (void inicializar)
}
}
}






