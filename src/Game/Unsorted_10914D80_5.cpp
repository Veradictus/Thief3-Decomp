// Game/Unsorted_10914D80_5.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780;

class Class_109169E0
{
public:
    void FUN_10916c00();
};

class Class_10915210
{
public:
    Class_109169E0* FUN_10915210(const Class_1090A780& Name);
    void FUN_109152c0(const Class_1090A780& Name);
};

// FUNCTION: 0x109152C0 ?FUN_109152c0@Class_10915210@@QAEXABVClass_1090A780@@@Z
void Class_10915210::FUN_109152c0(const Class_1090A780& Name)
{
    Class_109169E0* Obj = FUN_10915210(Name);
    if (Obj)
        Obj->FUN_10916c00();
}
