// Game/Unsorted_10B15960.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10B2C030
{
public:
    void FUN_10b2c130();
};

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    ~Class_10BFBD70()
    {
        FUN_10bfbd70(0);
        if (Unknown04)
        {
            FUN_10905aa0()->Virtual5(Data);
            Data = 0;
            Unknown04 = 0;
        }
    }

    int Count;
    int Unknown04;
    Class_10B2C030** Data;
};

class Class_10B16930
{
public:
    Class_10BFBD70 FUN_109e6d80(int A);
    void FUN_10b166a0();
};

class Class_109E8FB0
{
public:
    ~Class_109E8FB0();

    char Unknown00[0x220];
};

class Class_10B17140
{
public:
    ~Class_10B17140();
};

class Class_10B177C0 : public Class_109E8FB0
{
public:
    ~Class_10B177C0();

    Class_10B17140 Unknown220;
};

// FUNCTION: 0x10B166A0 ?FUN_10b166a0@Class_10B16930@@QAEXXZ
void Class_10B16930::FUN_10b166a0()
{
    Class_10BFBD70 First = FUN_109e6d80(0x69);
    if (First.Count > 0 && First.Data[0])
        First.Data[0]->FUN_10b2c130();

    Class_10BFBD70 Second = FUN_109e6d80(0x6a);
    if (Second.Count > 0 && Second.Data[0])
        Second.Data[0]->FUN_10b2c130();
}

// FUNCTION: 0x10B177C0 ??1Class_10B177C0@@QAE@XZ
Class_10B177C0::~Class_10B177C0()
{
}
