// Game/Unsorted_10A8B0B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10d3d990(void* Stream, int* Value);

void FUN_10d3d2d0(void* Stream, int Value);

class Class_10E6C580
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
    virtual void FUN_10a8b640(int A, void* Stream);

    char Unknown04[4];
    int Unknown08;
    int Unknown0C;
};

extern const char DAT_10e47660[];

enum EFindName
{
    FNAME_Find = 0,
    FNAME_Add = 1
};

class FName
{
public:
    FName(const char* Name, EFindName FindType);

    unsigned long Value;
};

class Class_109022E0
{
public:
    char* Unknown00;
};

class Class_10E6C6C4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int FUN_10a8c080(const Class_109022E0& Name);

    FName Unknown04;
};

extern int DAT_10f3a1dc;

extern void* DAT_10e6c610[];

class Class_1090FD40
{
public:
    void FUN_1090f2c0(int Count);
};

extern Class_1090FD40 DAT_10f3a1e0;

void FUN_10c3fbd0();

struct Class_10E6C610
{
    void* VTable;
};

class Class_10C4CD50
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
    virtual void Virtual8(Class_10E6C610* Event);
};

Class_10C4CD50* FUN_10c4cd50();

class Class_10E6C620
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void FUN_10a8b1e0();
};

// FUNCTION: 0x10A8B1E0 ?FUN_10a8b1e0@Class_10E6C620@@UAEXXZ
void Class_10E6C620::FUN_10a8b1e0()
{
    FUN_10c3fbd0();
    DAT_10f3a1e0.FUN_1090f2c0(0);
    DAT_10f3a1dc = 0;
    Class_10C4CD50* Mgr = FUN_10c4cd50();
    Class_10E6C610 Event;
    Event.VTable = DAT_10e6c610;
    Mgr->Virtual8(&Event);
}

// FUNCTION: 0x10A8B640 ?FUN_10a8b640@Class_10E6C580@@UAEXHPAX@Z
void Class_10E6C580::FUN_10a8b640(int A, void* Stream)
{
    FUN_10d3d2d0(Stream, Unknown08);
    FUN_10d3d990(Stream, &Unknown0C);
}

// FUNCTION: 0x10A8C080 ?FUN_10a8c080@Class_10E6C6C4@@UAEHABVClass_109022E0@@@Z
int Class_10E6C6C4::FUN_10a8c080(const Class_109022E0& Name)
{
    const char* Text = Name.Unknown00 ? Name.Unknown00 : DAT_10e47660;
    Unknown04 = FName(Text, FNAME_Add);
    return 0;
}
