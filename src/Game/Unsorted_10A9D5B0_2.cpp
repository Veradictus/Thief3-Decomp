// Game/Unsorted_10A9D5B0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

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

class Class_10A03530
{
public:
    void FUN_10a03530(int Value);
};

// A growable array of pointers: a count, the capacity in bytes and the items.
class Class_10BFBD70
{
public:
    Class_10BFBD70() : Unknown00(0), Unknown04(0), Unknown08(0) {}
    ~Class_10BFBD70()
    {
        FUN_10bfbd70(0);
        if (Unknown04)
        {
            FUN_10905aa0()->Virtual5(Unknown08);
            Unknown08 = 0;
            Unknown04 = 0;
        }
    }

    void FUN_10bfbd70(int Count);

    int Unknown00;
    int Unknown04;
    Class_10A03530** Unknown08;
};

// The object FUN_10a030c0 returns: FUN_10a04080 collects its items whose
// Unknown04 matches an id, creating one when asked and none is found.
class Class_10A04080
{
public:
    void FUN_10a04080(int Id, Class_10BFBD70& Found, bool Create);
};

void* FUN_10a030c0();

// FUNCTION: 0x10A9D5B0 ?FUN_10a9d5b0@@YGXHH@Z
void __stdcall FUN_10a9d5b0(int Id, int Value)
{
    if (!Id)
        return;
    Class_10BFBD70 Found;
    ((Class_10A04080*)FUN_10a030c0())->FUN_10a04080(Id, Found, true);
    for (int i = 0; i < Found.Unknown00; i++)
        Found.Unknown08[i]->FUN_10a03530(Value);
}
