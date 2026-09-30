// Game/Unsorted_109333B0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10932ED0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

class Class_10E49D1C
{
public:
    virtual void Virtual0();
    virtual int FUN_10933630(int A, int B, Struct_10932ED0* C, int D);

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    Struct_10932ED0 Unknown10;
};

class Class_10E49DFC
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual unsigned int FUN_10933960(unsigned int param);

    char Unknown04[0x34];
    unsigned int Unknown38;
};

extern void* DAT_10e49f0c[];

class Class_10E49F0C
{
public:
    void FUN_109341c0();
    void** VTable;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

class Class_10E49EE0 {
public:
    virtual int FUN_109341e0();

    char Unknown04[4];
    int Unknown08;
};

class Class_10E49F38 {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual unsigned int FUN_10934800();

    char Unknown04[0x14];
    unsigned int Unknown18;
    unsigned int Unknown1c;
};

// FUNCTION: 0x10933630 ?FUN_10933630@Class_10E49D1C@@UAEHHHPAUStruct_10932ED0@@H@Z
int Class_10E49D1C::FUN_10933630(int A, int B, Struct_10932ED0* C, int D)
{
    Unknown04 = A;
    Unknown08 = B;
    Unknown10 = *C;
    Unknown0C = D;
    return 0;
}

// FUNCTION: 0x10933960 ?FUN_10933960@Class_10E49DFC@@UAEII@Z
unsigned int Class_10E49DFC::FUN_10933960(unsigned int param)
{
    return Unknown38 / param;
}

// FUNCTION: 0x109341C0 ?FUN_109341c0@Class_10E49F0C@@QAEXXZ
void Class_10E49F0C::FUN_109341c0()
{
    VTable = DAT_10e49f0c;
    Unknown04 = 0;
    Unknown0C = -1;
    Unknown08 = 0;
    Unknown10 = 0;
}

// FUNCTION: 0x109341E0 ?FUN_109341e0@Class_10E49EE0@@UAEHXZ
int Class_10E49EE0::FUN_109341e0()
{
    return ++Unknown08;
}

// FUNCTION: 0x10934800 ?FUN_10934800@Class_10E49F38@@UAEIXZ
unsigned int Class_10E49F38::FUN_10934800()
{
    return Unknown18 / Unknown1c;
}
