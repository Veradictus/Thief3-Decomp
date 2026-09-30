// Game/Class_1098E330.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
    FName FUN_10992700();
};

// FUNCTION: 0x10992700 ?FUN_10992700@Class_1098E330@@QAE?AVFName@@XZ
FName Class_1098E330::FUN_10992700()
{
    int Value = 0;
    FUN_1098e330(0x100004f, &Value);
    return FName((EName)Value);
}
