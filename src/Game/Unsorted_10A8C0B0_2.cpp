// Game/Unsorted_10A8C0B0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* A);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_109081E0
{
public:
    Class_109081E0() : Unknown00(0) {}
    ~Class_109081E0()
    {
        if (Unknown00)
        {
            char* Block = Unknown00 - 4;
            FUN_10905aa0()->Virtual5(Block);
            Unknown00 = 0;
        }
    }

    char* Unknown00;
};

void FUN_10d3ddc0(void* Reader, int* Out);

extern const char DAT_10e47660[];

enum EFindName
{
    FNAME_Find = 0,
    FNAME_Add = 1,
    FNAME_Intrinsic = 2
};

class FName
{
public:
    FName(const char* Name, EFindName FindType);

    unsigned long Value;
};

class Class_10E6C6C4
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
    virtual bool FUN_10a8c0b0(int A, void* Reader);

    FName Unknown04;
};

// FUNCTION: 0x10A8C0B0 ?FUN_10a8c0b0@Class_10E6C6C4@@UAE_NHPAX@Z
bool Class_10E6C6C4::FUN_10a8c0b0(int A, void* Reader)
{
    Class_109081E0 Text;
    FUN_10d3ddc0(Reader, (int*)&Text);
    Unknown04 = FName(Text.Unknown00 ? Text.Unknown00 : DAT_10e47660, FNAME_Intrinsic);
    return true;
}
