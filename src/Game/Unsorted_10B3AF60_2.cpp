// Game/Unsorted_10B3AF60_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B3B220_Item
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19(int A);

    char Unknown04[0x100];
    bool Unknown104;
};

class Class_10B3B220_Unknown0B0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual Class_10B3B220_Item* Virtual6();
};

struct Struct_10B53A00
{
    char Unknown00[0xB0];
    Class_10B3B220_Unknown0B0* Unknown0B0;
    char Unknown0B4[0x39C];
    int Unknown450;
};

class Class_10B3B220
{
public:
    void FUN_10b3b220(Struct_10B53A00* P);
};

class Class_10B3C740
{
public:
    int FUN_10b3c0a0(float p1, float* Out1, float* Out2);
    int FUN_10b3c740(float p1);
};

// FUNCTION: 0x10B3B220 ?FUN_10b3b220@Class_10B3B220@@QAEXPAUStruct_10B53A00@@@Z
void Class_10B3B220::FUN_10b3b220(Struct_10B53A00* P)
{
    Class_10B3B220_Item* Item = P->Unknown0B0->Virtual6();
    Item->Virtual19(1);
    if (Item->Unknown104)
        P->Unknown450 |= 2;
}

// FUNCTION: 0x10B3C740 ?FUN_10b3c740@Class_10B3C740@@QAEHM@Z
int Class_10B3C740::FUN_10b3c740(float p1)
{
    float Out;
    return FUN_10b3c0a0(p1, &Out, &p1);
}
