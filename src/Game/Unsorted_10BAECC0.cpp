// Game/Unsorted_10BAECC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A, int B, int C, int D, int E);
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10BAEC40
{
public:
    void FUN_10bae1d0(int Count);

    void Empty()
    {
        FUN_10bae1d0(0);
        if (Unknown04)
        {
            FUN_10905aa0()->Virtual5(Unknown08);
            Unknown08 = 0;
            Unknown04 = 0;
        }
    }

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10BAF8A0
{
public:
    void FUN_10baf8a0();

    char Unknown00[0x28];
    Class_10BAEC40 Unknown28;
};

// FUNCTION: 0x10BAF8A0 ?FUN_10baf8a0@Class_10BAF8A0@@QAEXXZ
void Class_10BAF8A0::FUN_10baf8a0()
{
    Unknown28.Empty();
}
