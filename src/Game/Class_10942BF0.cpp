// Game/Class_10942BF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10942BF0
{
public:
    char Unknown000[0x158];
    int field158;

    int FUN_10942bf0(int param);
};

// FUNCTION: 0x10942BF0 ?FUN_10942bf0@Class_10942BF0@@QAEHH@Z
int Class_10942BF0::FUN_10942bf0(int param)
{
    if (param == 0) {
        int eax = this->field158;
        eax >>= 0x13;
        eax &= 0x1fff;
        return eax;
    } else {
        int eax = this->field158;
        eax &= 0x7ffff;
        return eax;
    }
}
