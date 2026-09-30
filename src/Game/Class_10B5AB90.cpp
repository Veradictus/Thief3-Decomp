// Game/Class_10B5AB90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

extern void FUN_10a58cf0(void);

// Declare as functions to get direct mov instructions
extern void* DAT_10e828b0[];

extern void* DAT_10e7edb8[];

class Class_10B5AB90
{
public:
    void* vtable;
    char Unknown004[0x114];
    void* field118;
    char Unknown11C[0xB4];
    int field1D0;

    Class_10B5AB90* FUN_10b5ab90();
};

// FUNCTION: 0x10B5AB90 ?FUN_10b5ab90@Class_10B5AB90@@QAEPAV1@XZ
Class_10B5AB90* Class_10B5AB90::FUN_10b5ab90()
{
    FUN_10a58cf0();
    this->vtable = (void*)DAT_10e828b0;
    this->field118 = (void*)DAT_10e7edb8;
    this->field1D0 = 0;
    return this;
}
