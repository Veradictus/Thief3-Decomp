// Game/Unsorted_10C08F00_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C09A10
{
    char Unknown00[0xC];
    int Unknown0C;
};

Struct_10C09A10* FUN_10b8b660(int A);

class Class_10E97BEC {
public:
    Class_10E97BEC();

    virtual void Virtual0();

    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10E97C18
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual bool FUN_10c0b040();

    char Unknown04[4];
    int Unknown08;
};

class Class_10BAF8E0 {
public:
    void FUN_10baf8e0(int p1);
};

// FUNCTION: 0x10C09A10 ?FUN_10c09a10@@YG_NH@Z
bool __stdcall FUN_10c09a10(int A)
{
    Struct_10C09A10* Obj = FUN_10b8b660(A);
    if (Obj == 0)
        return true;
    return Obj->Unknown0C == 0;
}

// FUNCTION: 0x10C0AD70 ??0Class_10E97BEC@@QAE@XZ
Class_10E97BEC::Class_10E97BEC()
{
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
}

// FUNCTION: 0x10C0B040 ?FUN_10c0b040@Class_10E97C18@@UAE_NXZ
bool Class_10E97C18::FUN_10c0b040()
{
    return Unknown08 < 8;
}

// FUNCTION: 0x10C0BDC0 ?FUN_10c0bdc0@@YGXHPAVClass_10BAF8E0@@@Z
void __stdcall FUN_10c0bdc0(int p1, Class_10BAF8E0* p2)
{
    p2->FUN_10baf8e0(p1);
}
