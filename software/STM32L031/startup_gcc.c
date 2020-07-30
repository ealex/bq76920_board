//*****************************************************************************
//
// startup.c - Boot code for Stellaris.
//
// Copyright (c) 2005,2006 Luminary Micro, Inc.  All rights reserved.
//
// Software License Agreement
//
// Luminary Micro, Inc. (LMI) is supplying this software for use solely and
// exclusively on LMI's Stellaris Family of microcontroller products.
//
// The software is owned by LMI and/or its suppliers, and is protected under
// applicable copyright laws.  All rights are reserved.  Any use in violation
// of the foregoing restrictions may subject the user to criminal sanctions
// under applicable laws, as well as to civil liability for the breach of the
// terms and conditions of this license.
//
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// LMI SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
// CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 852 of the Stellaris Driver Library.
//
//*****************************************************************************

// modified by Martin Thomas - don't blame Luminary if it does
// not work for you.

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
// mthomas: attribute for stack-aligment (see README_mthomas.txt)
#include "stm32l0xx.h"

static void ResetISR(void)             __attribute__((__interrupt__));
static void NmiSR(void)                __attribute__((__interrupt__));
static void HardFaultISR(void)         __attribute__((__interrupt__));
static void SVCallISR(void)            __attribute__((__interrupt__));
static void PendSVISR(void)            __attribute__((__interrupt__));
static void SysTickISR(void)           __attribute__((__interrupt__));
static void IntDefaultHandler(void)    __attribute__((__interrupt__));


//*****************************************************************************
//
// The entry point for the application.
//
//*****************************************************************************
extern int main(void);

//*****************************************************************************
//
// External declaration for the interrupt handler used by the application.
//
//*****************************************************************************
//extern void button_timer6_isr(void)__attribute__((__interrupt__)) ;

//*****************************************************************************
//
// Reserve space for the system stack.
//
//*****************************************************************************
#ifndef STACK_SIZE
#define STACK_SIZE                              256
#endif

// mthomas: added section -> alignment thru linker-script
__attribute__ ((section(".stackarea")))
static unsigned long pulStack[STACK_SIZE];

//*****************************************************************************
//
// The minimal vector table for a Cortex M3.  Note that the proper constructs
// must be placed on this to ensure that it ends up at physical address
// 0x0000.0000.
//
//*****************************************************************************
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((unsigned long)pulStack + sizeof(pulStack)),	/* 0x0000 0000 The initial stack pointer */
    /* CORTEX-M0 system level exceptions */
    ResetISR,                                   /* 0x0000 0004 	The reset handler */
    NmiSR,                                      /* 0x0000 0008 	The NMI handler */
    HardFaultISR,                               /* 0x0000 000C 	The hard fault handler */
    0,                      	      	        /* 0x0000 0010 */
    0,                   				        /* 0x0000 0014 */
    0,                    			            /* 0x0000 0018 */
    0,                                      	/* 0x0000 001C */
    0,                                      	/* 0x0000 0020 */
    0,											/* 0x0000 0024 */
    0,											/* 0x0000 0028	 */
    SVCallISR,                      		  	/* 0x0000 002C	SVCall handler */
    0,                      	   	            /* 0x0000 0030	Debug Monitor */
    0,                                      	/* 0x0000 0034 */
    PendSVISR,                     			  	/* 0x0000 0038	The PendSV handler */
    SysTickISR,	                    		   	/* 0x0000 003C	The SysTick handler */
    
    /* Interrupts */
    IntDefaultHandler,                         	// 0	0x0000 0040	Window Watchdog interrupt
    IntDefaultHandler,                         	// 1	0x0000 0044	PVD through EXTI Line detection interrupt
    IntDefaultHandler,                         	// 2	0x0000 0048	RTC global interrupt through EXTI17/19/20 line and LSE CSS interrupt through EXTI 19 line
    IntDefaultHandler,                         	// 3	0x0000 004C	Flash memory and data EEPROM global interrupt
    IntDefaultHandler,                         	// 4	0x0000 0050	RCC global interrupt
    IntDefaultHandler,                         	// 5	0x0000 0054	EXTI Line0 and 1 interrupts
    IntDefaultHandler,                         	// 6	0x0000 0058	EXTI Line2 and 3 interrupts
    IntDefaultHandler,                         	// 7	0x0000 005C	EXTI Line4 to 15 interrupts
    0,                                      	// 8	0x0000 0060	RESERVED
    IntDefaultHandler,                         	// 9	0x0000 0064	DMA1 Channel1 global interrupt
    IntDefaultHandler,                         	// 10	0x0000 0068	DMA1 Channel2 and 3 interrupts
    IntDefaultHandler,                         	// 11	0x0000 006C	DMA1 DMA1 Channel4 to 7 interrupts
    IntDefaultHandler,                         	// 12	0x0000 0070	ADC and comparator interrupts through EXTI21 and 22
    IntDefaultHandler,                         	// 13	0x0000 0074	LPTIMER1 interrupt through EXTI29
    IntDefaultHandler,                         	// 14	0x0000 0078	USART4/USART5 global interrupt
    IntDefaultHandler,                         	// 15	0x0000 007C	TIMER2 global interrupt
	IntDefaultHandler,                         	// 16	0x0000 0080	TIMER3 global interrupt
	IntDefaultHandler,                         	// 17	0x0000 0084	TIMER6 global interrupt
	IntDefaultHandler,                     		// 18	0x0000 0088	TIMER7 global interrupt
	0,							                // 19 	0x0000 008C RESERVED
    IntDefaultHandler,							// 20 	0x0000 0090	TIMER21 global interrupt
	IntDefaultHandler,							// 21 	0x0000 0094	I2C3 global interrupt
	IntDefaultHandler,							// 22 	0x0000 0098	TIMER22 global interrupt
    IntDefaultHandler,                     		// 23	0x0000 009C	I2C1 global interrupt through EXTI23
    IntDefaultHandler,                      	// 24	0x0000 00A0	I2C2 global interrupt
    IntDefaultHandler,      					// 25	0x0000 00A4	SPI1 global interrupt
    IntDefaultHandler,                      	// 26	0x0000 00A8	SPI2 global interrupt
    IntDefaultHandler,                          // 27	0x0000 00AC	USART1 global interrupt through EXTI25
    IntDefaultHandler,                          // 28	0x0000 00B0	USART2 global interrupt through EXTI26
    IntDefaultHandler                           // 29	0x0000 00B4	LPUART1 global interrupt through EXTI28 + AES global interrupt
};

//*****************************************************************************
//
// The following are constructs created by the linker, indicating where the
// the "data" and "bss" segments reside in memory.  The initializers for the
// for the "data" segment resides immediately following the "text" segment.
//
//*****************************************************************************
extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied main() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void ResetISR(void) {
    volatile unsigned long *pulSrc, *pulDest;

    //
    // Copy the data segment initializers from flash to SRAM.
    //
    pulSrc = &_etext;
    for(pulDest = &_data; pulDest < &_edata; )
    {
        *pulDest++ = *pulSrc++;
    }

    //
    // Zero fill the bss segment.
    //
    for(pulDest = &_bss; pulDest < &_ebss; )
    {
        *pulDest++ = 0;
    }

    //
    // Call the application's entry point.
    //
    main();
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void NmiSR(void) {
    //    // Enter an infinite loop.
    //
    while(1) {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void HardFaultISR(void) {
    //
    // Enter an infinite loop.
    //
    while(1)  {
    }
}

static void SVCallISR(void) {
    //
    // Enter an infinite loop.
    //
    while(1) {
    }
}

static void PendSVISR(void) {
    //
    // Enter an infinite loop.
    //
    while(1) {
    }
}

static void SysTickISR(void) {
    //
    // Enter an infinite loop.
    //
    while(1) {
    }
}


//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void IntDefaultHandler(void) {
    //
    // Go into an infinite loop.
    //
    while(1) {

    }
}
