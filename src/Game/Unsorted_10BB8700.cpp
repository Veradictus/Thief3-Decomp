// Game/Unsorted_10BB8700.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

class Class_10BB8A60
{
public:
    void FUN_10bb8a60(float Delta);

    char Unknown00[0x258];
    float Unknown258;
};

class Class_10BB8AA0
{
public:
    void FUN_10bb8aa0(float Delta);

    char Unknown00[0x260];
    float Unknown260;
};

class Class_10BB8700_Unknown1C
{
public:
    virtual void Virtual0();
    virtual bool Virtual1();
};

class Class_10BB8700
{
public:
    void FUN_10bb8700();

    char Unknown00[0x14];
    int Unknown14;
    char Unknown18[4];
    Class_10BB8700_Unknown1C** Unknown1C;
};

class Class_10BC9D40;

class Class_10B9CAC0
{
public:
    Class_10BC9D40* FUN_10b9cac0();
};

struct Struct_10B9BCA0
{
    char Unknown00[8];
    Class_10B9CAC0* Unknown08;
};

class Class_10B9BCA0
{
public:
    char Unknown00[0x118];
    Struct_10B9BCA0* Unknown118;
};

class AAIPawn;

Class_10B9BCA0* FUN_10baa660(AAIPawn* Pawn);

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

class Class_10BB8A30
{
public:
    Class_10BC9D40* FUN_10bb8a30();

    char Unknown00[8];
    Class_10c7d570* Unknown08;
};

// FUNCTION: 0x10BB8700 ?FUN_10bb8700@Class_10BB8700@@QAEXXZ
void Class_10BB8700::FUN_10bb8700()
{
    for (int i = 0; i < Unknown14; i++)
    {
        Class_10BB8700_Unknown1C* Item = Unknown1C[i];
        if (Item->Virtual1())
            Item->Virtual0();
    }
}

// FUNCTION: 0x10BB8A30 ?FUN_10bb8a30@Class_10BB8A30@@QAEPAVClass_10BC9D40@@XZ
Class_10BC9D40* Class_10BB8A30::FUN_10bb8a30()
{
    Class_10B9BCA0* Controller = FUN_10baa660((AAIPawn*)Unknown08->FUN_10c7d570());
    if (Controller && Controller->Unknown118 && Controller->Unknown118->Unknown08)
        return Controller->Unknown118->Unknown08->FUN_10b9cac0();
    return 0;
}

// FUNCTION: 0x10BB8A60 ?FUN_10bb8a60@Class_10BB8A60@@QAEXM@Z
void Class_10BB8A60::FUN_10bb8a60(float Delta)
{
    Unknown258 += Delta;
    Unknown258 = (DAT_10eafbdc >= Unknown258) ? 0.0f : Unknown258;
}

// FUNCTION: 0x10BB8AA0 ?FUN_10bb8aa0@Class_10BB8AA0@@QAEXM@Z
void Class_10BB8AA0::FUN_10bb8aa0(float Delta)
{
    Unknown260 += Delta;
    Unknown260 = (DAT_10eafbdc >= Unknown260) ? 0.0f : Unknown260;
}
