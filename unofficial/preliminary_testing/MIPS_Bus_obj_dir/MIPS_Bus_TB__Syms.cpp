// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "MIPS_Bus_TB__Syms.h"
#include "MIPS_Bus_TB.h"



// FUNCTIONS
MIPS_Bus_TB__Syms::MIPS_Bus_TB__Syms(MIPS_Bus_TB* topp, const char* namep)
    // Setup locals
    : __Vm_namep(namep)
    , __Vm_activity(false)
    , __Vm_didInit(false)
    // Setup submodule names
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
}
