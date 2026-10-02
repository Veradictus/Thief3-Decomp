// Game/Unsorted_10A2FCD0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

bool FUN_1090f010(const int* A, const int* B);

class Class_10E663A0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a2fcd0(Class_10E663A0* Other);
    virtual void Virtual3();
    virtual const int* Virtual4();
};

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10A30530
{
public:
    ~Class_10A30530()
    {
        FUN_10a30530(0);
        if (Unknown04)
        {
            FUN_10905aa0()->Virtual5(Unknown08);
            Unknown08 = 0;
            Unknown04 = 0;
        }
    }

    void FUN_10a30530(int Count);

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10A30690
{
public:
    ~Class_10A30690();

    int Unknown00;
    Class_10A30530 Unknown04;
};

// FUNCTION: 0x10A2FCD0 ?FUN_10a2fcd0@Class_10E663A0@@UAEHPAV1@@Z
int Class_10E663A0::FUN_10a2fcd0(Class_10E663A0* Other)
{
    return FUN_1090f010(Other->Virtual4(), Virtual4());
}

// FUNCTION: 0x10A30690 ??1Class_10A30690@@QAE@XZ
Class_10A30690::~Class_10A30690()
{
}
