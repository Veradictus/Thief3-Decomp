// Game/Unsorted_10AA80D0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef struct _iobuf FILE;

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

Class_109081E0 FUN_10a83850(FILE* File, int Param);

class Class_10E6C170
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual int FUN_10aa80d0(FILE* File, int Param);

    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10AA80D0 ?FUN_10aa80d0@Class_10E6C170@@UAEHPAU_iobuf@@H@Z
int Class_10E6C170::FUN_10aa80d0(FILE* File, int Param)
{
    FUN_10a83850(File, Param);
    return 1;
}
