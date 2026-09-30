// Game/Class_10B53F70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

extern void FUN_10a51580(void);

extern void* DAT_10e81740[];

extern void* DAT_10e7edb8[];

class Class_10B53F70
{
public:
    void* vtable;
    char Unknown004[0xE4];
    int fieldE8;
    char Unknown0EC[0x2C];
    void* field118;

    Class_10B53F70* FUN_10b53f70();
};

// FUNCTION: 0x10B53F70 ?FUN_10b53f70@Class_10B53F70@@QAEPAV1@XZ
Class_10B53F70* Class_10B53F70::FUN_10b53f70()
{
    FUN_10a51580();
    this->fieldE8 |= 0x10;
    this->vtable = (void*)DAT_10e81740;
    this->field118 = (void*)DAT_10e7edb8;
    return this;
}
