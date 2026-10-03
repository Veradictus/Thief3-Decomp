// Game/Unsorted_10A3AD10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A3B460_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int A);
};

class Class_10E667C4
{
public:
    virtual void FUN_10a3b460(int Message, int Param, int C, int D);

    bool FUN_10a3ad90(int Param);

    Class_10A3B460_Member Unknown04;
    char Unknown08[0x20];
    int Unknown28;
};

// FUNCTION: 0x10A3B460 ?FUN_10a3b460@Class_10E667C4@@UAEXHHHH@Z
void Class_10E667C4::FUN_10a3b460(int Message, int Param, int C, int D)
{
    bool NoTarget = Unknown28 == 0;
    switch (Message)
    {
    case 59:
        FUN_10a3ad90(Param);
        break;
    case 6:
    case 38:
    case 39:
        if (!NoTarget)
            Unknown04.Virtual5(Param);
        break;
    }
}
