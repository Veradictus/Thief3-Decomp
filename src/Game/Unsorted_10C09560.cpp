// Game/Unsorted_10C09560.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C099A0
{
    int Unknown00;
    int Unknown04;
    char Unknown08[0x18];
};

class Class_10C099A0
{
public:
    int FUN_10c099a0(int Value);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    Struct_10C099A0* Unknown0C;
};

struct Struct_10C09A10
{
    char Unknown00[0xC];
    int Unknown0C;
};

Struct_10C09A10* FUN_10b8b660(int A);

// FUNCTION: 0x10C099A0 ?FUN_10c099a0@Class_10C099A0@@QAEHH@Z
int Class_10C099A0::FUN_10c099a0(int Value)
{
    for (int i = 0; i < Unknown04; i++)
    {
        Struct_10C099A0* Item = &Unknown0C[i];
        if (Item->Unknown00 == Value)
            return Item->Unknown04;
    }
    return 0;
}

// FUNCTION: 0x10C099D0 ?FUN_10c099d0@@YG_NH@Z
bool __stdcall FUN_10c099d0(int A)
{
    if (!A)
        return false;
    Struct_10C09A10* Obj = FUN_10b8b660(A);
    if (!Obj)
        return false;
    return Obj->Unknown0C == 2 || Obj->Unknown0C == 3;
}
