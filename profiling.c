/**
 * @file profiling.c
 * @brief
 * @author Kristoffer Ödmark
 * @version 1.0
 * @date 2016-08-02
 */

#include "profiling.h"
#include "stdint.h"

/*

   Example chibios makefile fixes

   USE_OPT += -finstrument-functions

   NO_INSTRUMENT= $(STARTUPSRC) \
        $(KERNSRC) \
        $(PORTSRC) \
        $(OSALSRC) \
        $(HALSRC) \
        $(PLATFORMSRC) \
        $(BOARDSRC) \
        $(TESTSRC) \
        $(ASMXSRC) \
        modules/profiling.c

    comma:=,
    empty:=
    space:= $(empty) $(empty)
    NO_INSTR_FILES = $(subst $(space),$(comma),$(NO_INSTRUMENT))

    USE_OPT += -finstrument_functions -finstrument-functions-exclude-file-list=$(NO_INSTR_FILES)

*/

void output(void *pointer, uint32_t time){

}

void __attribute__((no_instrument_function)) __cyg_profile_func_enter (void *this_fn,
        void *call_site){

    // output when and where we are going
     //output(this_fn, time);


}
void __attribute__((no_instrument_function)) __cyg_profile_func_exit  (void *this_fn,
        void *call_site){
    //output that we are going back and at which time
    //output(call_site, time);
}

/* semihosting code */
void __attribute__((no_instrument_function)) send_command(int command, void *message)
{
   __asm("mov r0, %[cmd];"
       "mov r1, %[msg];"
       "bkpt #0xAB"
         :
         : [cmd] "r" (command), [msg] "r" (message)
         : "r0", "r1", "memory");
}
void __attribute__((no_instrument_function)) SysTick_Handler(void){
    register int *r0 __asm("r0");

    __asm(  "TST lr, #4\n"
            "ITE EQ\n"
            "MRSEQ r0, MSP\n"
            "MRSNE r0, PSP\n" // stack pointer now in r0
            "ldr r0, [r0, #0x18]\n" // stored pc now in r0
            //"add r0, r0, #6\n" // address to stored pc now in r0
         );
    // now the  pointer is in register 0

    __asm("nop");
    __asm("nop");
    __asm("nop");

    //volatile int pc= *(r0 + 0x18/sizeof(int *));

}

void __attribute__((no_instrument_function))put_char(char c)
{
    __asm (
    "mov r0, #0x03\n"   /* SYS_WRITEC */
    "mov r1, %[msg]\n"
    "bkpt #0xAB\n"
    :
    : [msg] "r" (&c)
    : "r0", "r1"
    );
}
