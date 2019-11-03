/**
  
 Program: Capstone byke - Taillight controller
 Date: 01/10/19
 Author:
 Modified: Tanner L
 Desc: Taillight Controller - Controls taillight operation based on I2C
       register values
  
 
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16F15324
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

#define OFF 0
#define ON 1
#define TRUE 1
#define LEFTTURN 0
#define RIGHTTURN 1
#define TAILLIGHT 2
#define BRAKELIGHT 5
#define LASERS 3
#define FLASHING 4
#define TEMPERATURE 6

/*
 * -----------------------------------------------------
 * Function: main
 * Date: 01/10/19
 * Author: Tanner L
 * Modified:
 * Desc: Program loop 
 * ------------------------------------------------------
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    TMR0_StartTimer();
    TMR1_StartTimer();
    
    uint16_t picTemperature = 0;
    
    while (TRUE)
    {
        
        picTemperature = ADC_GetConversion(channel_Temp);
        
        EEPROM_Buffer[TEMPERATURE] = picTemperature/10;
                
       // on
        if(EEPROM_Buffer[LEFTTURN])              // LEFT TURN SEQUENCE ON
            {
            if (time == 0)
                {
                LATAbits.LATA4 = OFF;
                LATCbits.LATC5 = OFF;
                LATCbits.LATC4 = ON;
                }
            if (time == 1)
                {
                LATAbits.LATA4 = OFF;
                LATCbits.LATC5 = ON;
                LATCbits.LATC4 = OFF;
                }
            if (time == 2)
                {
                LATAbits.LATA4 = ON;
                LATCbits.LATC5 = OFF;
                LATCbits.LATC4 = OFF;
                }
            }

        
        if(EEPROM_Buffer[RIGHTTURN])              // RIGHT TURN SEQUENCE ON
            {
            if (time == 0)
                {
                LATAbits.LATA2 = OFF;
                LATCbits.LATC0 = OFF;
                LATCbits.LATC1 = ON;
                }
            if (time == 1)
                {
                LATAbits.LATA2 = OFF;
                LATCbits.LATC0 = ON;
                LATCbits.LATC1 = OFF;
                }
            if (time == 2)
                {
                LATAbits.LATA2 = ON;
                LATCbits.LATC0 = OFF;
                LATCbits.LATC1 = OFF;
                }
            }
        
        if(EEPROM_Buffer[BRAKELIGHT])            // BRAKE LIGHT ON
            {
            LATCbits.LATC3 = ON;
            }
        
        if(EEPROM_Buffer[TAILLIGHT])             // TAILLIGHT ON
            {
            if(EEPROM_Buffer[FLASHING])          // TAILLIGHT FLASH OPTION ON
                {
                LATCbits.LATC2 = flashtaillight;
                }
            else
                {
                LATCbits.LATC2 = ON;
                }
            }
        
        if(EEPROM_Buffer[LASERS])               // LASERS ON
            {
            LATAbits.LATA5 = ON;
            }
        
        
        // OFF
        if(!EEPROM_Buffer[LEFTTURN])            // LEFT TURN OFF
            {
            LATAbits.LATA4 = OFF;
            LATCbits.LATC5 = OFF;
            LATCbits.LATC4 = OFF;
            }
        
        if(!EEPROM_Buffer[RIGHTTURN])           // RIGHT TURN OFF
            {
            LATAbits.LATA2 = OFF;
            LATCbits.LATC0 = OFF;
            LATCbits.LATC1 = OFF;
            }
        
        if(!EEPROM_Buffer[TAILLIGHT])           // TAILLIGHT OFF
            {
            LATCbits.LATC2 = OFF;
            }
        
        if(!EEPROM_Buffer[BRAKELIGHT])          // BRAKE LIGHT OFF
            {
            LATCbits.LATC3 = OFF;
            }
        
        if(!EEPROM_Buffer[LASERS])              // LASERS OFF
            {
            LATAbits.LATA5 = OFF;
            }
        

        if((!EEPROM_Buffer[LEFTTURN]) && (!EEPROM_Buffer[RIGHTTURN])) time = 0;
        
    } // END OF WHILE LOOP
    
} // END OF main::
/**
 End of File
*/