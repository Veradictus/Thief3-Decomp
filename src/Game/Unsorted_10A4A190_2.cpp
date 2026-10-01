// Game/Unsorted_10A4A190_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A4C0B0
{
    char Unknown00[0xC];
    int Unknown0C;
};

class Class_10E5BC00
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
    virtual Struct_10A4C0B0* Virtual10(int A);
    virtual int FUN_10a4c0b0(int A);
};

extern int DAT_10f3a064;

extern bool DAT_10f3a060;

class Class_10E67938 {
public:
    Class_10E67938();

    virtual void FUN_10a4c470(int Type, int A, int B, int C);

    void FUN_10aa6180();
};

// FUNCTION: 0x10A4C0B0 ?FUN_10a4c0b0@Class_10E5BC00@@UAEHH@Z
int Class_10E5BC00::FUN_10a4c0b0(int A)
{
    Struct_10A4C0B0* Info = Virtual10(A);
    if (Info)
        return Info->Unknown0C;
    return 0;
}

// FUNCTION: 0x10A4C1E0 ??0Class_10E67938@@QAE@XZ
Class_10E67938::Class_10E67938()
{
    DAT_10f3a064 = 0;
    DAT_10f3a060 = false;
    FUN_10aa6180();
}
