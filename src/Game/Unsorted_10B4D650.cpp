// Game/Unsorted_10B4D650.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B396B0
{
public:
    void FUN_10b396b0(int A);
};

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();

    char Unknown04[4];
    int Unknown08;
    int Unknown0C;
};

class Class_10E7EBB0 : public Class_10AA82D0
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int FUN_10b4db40(int A, int B);

    char Unknown10[4];
    int Unknown14;
};

extern float DAT_10f04aa0;

void FUN_10abc090(float p1);

class Class_10E7EA48
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10b4e650(int p1);
};

// FUNCTION: 0x10B4DB40 ?FUN_10b4db40@Class_10E7EBB0@@UAEHHH@Z
int Class_10E7EBB0::FUN_10b4db40(int A, int B)
{
    ((Class_10B396B0*)FUN_10aa82d0())->FUN_10b396b0(B);
    Unknown08 = 0x101;
    Unknown14 = 0;
    return 0x17;
}

// FUNCTION: 0x10B4E650 ?FUN_10b4e650@Class_10E7EA48@@UAEXH@Z
void Class_10E7EA48::FUN_10b4e650(int p1)
{
    FUN_10abc090(DAT_10f04aa0);
}
