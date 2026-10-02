// Game/Unsorted_10BB1C40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

int FUN_10bb0b10(int A, int B, int C, const Class_109081E0& Name);

class Class_10E8C7C4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10bb1c40(int A, int B, int C);
};

// FUNCTION: 0x10BB1C40 ?FUN_10bb1c40@Class_10E8C7C4@@UAEHHHH@Z
int Class_10E8C7C4::FUN_10bb1c40(int A, int B, int C)
{
    Class_109081E0 Name("STATE_FLEE");
    return FUN_10bb0b10(A, B, C, Name);
}
