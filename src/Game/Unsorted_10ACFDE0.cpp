// Game/Unsorted_10ACFDE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E3D0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();

    void FUN_1098e3d0(int A, void* B);
};

class Class_10ACA6A0
{
public:
    void FUN_10aca6a0(Class_1098E3D0** A, int B, int C);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x120];
    Class_10ACA6A0* Unknown120;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

// FUNCTION: 0x10ACFFA0 ?FUN_10acffa0@@YGXPAVClass_1098E3D0@@@Z
void __stdcall FUN_10acffa0(Class_1098E3D0* Obj)
{
    int Value = 0;
    Obj->FUN_1098e3d0(0x800182, &Value);
    DAT_10f3a3d8->Unknown120->FUN_10aca6a0(&Obj, 3, 0);
    if (Obj)
        Obj->Virtual2();
}
