/*
 * File:   main.c
 * Author: admin
 *
 * Created on November 23, 2020, 12:14 PM
 */

// PIC24FJ128GA010 Configuration Bit Settings

// 'C' source line config statements

// CONFIG2
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary oscillator disabled)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRC              // Oscillator Select (Fast RC Oscillator (FRC))
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = ON              // JTAG Port Enable (JTAG port is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>//Compilation directives
#include "FreeRTOS.h"
#include "task.h"
#include "list.h"


void vTask1(void *pv1); // NB : le type de l?argument et le type retourné (voir cours)
void vTask2(void *pv2);
void delay(void);
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName );
void vTaskDelete(TaskHandle_t xTaskToDelete);

int main(void) {
// create a task based on the vTask1 function of priority 1 using a stack of depth 150
xTaskCreate(vTask1, "Task1", 150, NULL, 1, NULL );
// créer une tâche basée sur la fonction vTask1 de priorité 1 utilisant une pile de profondeur 150
xTaskCreate( vTask2, "Task2", 150, NULL, 1, NULL );
// Lancer le scheduler
vTaskStartScheduler ();
// On atteint ce point si le scheduler s?est arrêté à cause d?un problème ou il a été arrêté explicitement par le code
return (0);
}

void vTask1(void *pv1){ // Blinking PortA
TRISA=0; // Setup PortA as digital Outputs
int i=25;
while(i){
 PORTA=0x00; delay();
 PORTA = 0xFF; delay();i--; }
vTaskDelete(NULL);
}
void vTask2(void *pv2) { // Blinking PortD
TRISD=0;//Setup PortD as digital Outputs
while(1){ // a task is an infinite loop
 _RD1=0; delay();
 _RD1=1; delay();
    
/*PORTD=0x00; delay();
  PORTD = 0xFF; delay();*/ }
}
void delay(void){
unsigned int Compt=0X0FFF ;
while(Compt--) ;
}
void vApplicationIdleHook(void) {
 // Blinking Pin RC1
TRISC=0;
while(1){
 _RC1=0; delay();
 _RC1=1; delay(); }
}
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName ){
 //Que faire en cas de débordement de pile ?
}
