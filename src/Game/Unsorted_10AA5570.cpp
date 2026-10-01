// Game/Unsorted_10AA5570.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10AA5570_Array
{
    int* Unknown00;
};

struct Struct_10AA5570_Owner
{
    char Unknown00[0x5C];
    Struct_10AA5570_Array* Unknown5C;
};

class Class_10AA5570
{
public:
    int FUN_10aa5570();

    Struct_10AA5570_Owner* Unknown00;
    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10AA5570 ?FUN_10aa5570@Class_10AA5570@@QAEHXZ
int Class_10AA5570::FUN_10aa5570()
{
    Struct_10AA5570_Array* Array = Unknown00->Unknown5C;
    if (Array == 0)
        return 0;
    return Array->Unknown00[Unknown08];
}
