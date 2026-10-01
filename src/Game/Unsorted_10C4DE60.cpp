// Game/Unsorted_10C4DE60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Elem_10C4DE60
{
    char Unknown00[0x48];
};

struct Struct_10C4DE60
{
    char Unknown00[0xC];
    Elem_10C4DE60* Unknown0c;
};

class Class_10C4DE60
{
public:
    Elem_10C4DE60* FUN_10c4de60(int p1, int p2);

    char Unknown00[0x10];
    Struct_10C4DE60* Unknown10;
};

// FUNCTION: 0x10C4DE60 ?FUN_10c4de60@Class_10C4DE60@@QAEPAUElem_10C4DE60@@HH@Z
Elem_10C4DE60* Class_10C4DE60::FUN_10c4de60(int p1, int p2)
{
    return &Unknown10[p1].Unknown0c[p2];
}
