// Game/Unsorted_10BB5660.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10e9092c
{
public:
    Class_10e9092c(void* p1);

    virtual void Virtual0();

    int Unknown04;
    int Unknown08;
    void* Unknown0C;
};

class Class_10BB48E0;

extern Class_10BB48E0* DAT_10ff6694;

struct Struct_10AA3520
{
    char Unknown00[0xA4];
    void* UnknownA4;
};

extern Struct_10AA3520* DAT_10f35dec;

void FUN_10bb55a0(void* A);

class Class_10BAA3C0;

class Class_10BB67F0
{
public:
    void* Unknown00;

    void* FUN_10bb62a0(void* A, int B, void* C, Class_10BAA3C0* D);
    void* FUN_10bb67f0(int B, void* C, Class_10BAA3C0* D);
};

// FUNCTION: 0x10BB5660 ?FUN_10bb5660@@YAPAVClass_10BB48E0@@XZ
Class_10BB48E0* FUN_10bb5660()
{
    if (DAT_10ff6694 == 0 && DAT_10f35dec != 0 && DAT_10f35dec->UnknownA4 != 0)
        FUN_10bb55a0(DAT_10f35dec->UnknownA4);
    return DAT_10ff6694;
}

// FUNCTION: 0x10BB67F0 ?FUN_10bb67f0@Class_10BB67F0@@QAEPAXHPAXPAVClass_10BAA3C0@@@Z
void* Class_10BB67F0::FUN_10bb67f0(int B, void* C, Class_10BAA3C0* D)
{
    return FUN_10bb62a0(Unknown00, B, C, D);
}

// FUNCTION: 0x10BB74E0 ??0Class_10e9092c@@QAE@PAX@Z
Class_10e9092c::Class_10e9092c(void* p1)
{
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = p1;
}
