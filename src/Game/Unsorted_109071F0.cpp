// Game/Unsorted_109071F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <string.h>

class Class_109081E0
{
public:
    Class_109081E0(const char* In);

    void FUN_10907870(int Length, int Flag);

    char* Unknown00;
};

bool FUN_10907af0(const char* Str, int Max);

// FUNCTION: 0x109081E0 ??0Class_109081E0@@QAE@PBD@Z
Class_109081E0::Class_109081E0(const char* In)
{
    Unknown00 = 0;
    if (In)
    {
        int Length = strlen(In);
        if (Length)
        {
            FUN_10907870(Length, 0);
            strcpy(Unknown00, In);
        }
    }
}

// FUNCTION: 0x10908230 ?FUN_10908230@@YAHPBDH@Z
int FUN_10908230(const char* Str, int Max)
{
    if (Str && Max >= 1 && FUN_10907af0(Str, Max))
        return strlen(Str);
    return 0;
}
