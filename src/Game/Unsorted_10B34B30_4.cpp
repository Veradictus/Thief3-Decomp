// Game/Unsorted_10B34B30_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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
    Class_109081E0(const char* In);
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

bool FUN_1094c430(const Class_109081E0& A, const Class_109081E0& B) throw();

extern const char DAT_10e795b0[];

class Class_10E7C178
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
    virtual int FUN_10b34b30();

    Class_109081E0 Unknown04;
};

// FUNCTION: 0x10B34B30 ?FUN_10b34b30@Class_10E7C178@@UAEHXZ
int Class_10E7C178::FUN_10b34b30()
{
    return FUN_1094c430(Unknown04, Class_109081E0(DAT_10e795b0));
}
