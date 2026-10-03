// Game/Unsorted_10947530.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_109481D0
{
    int Unknown00;
    int Unknown04;
};

class Class_109481D0
{
public:
    bool FUN_109481d0(int Mask);

    char Unknown00[0xB0];
    Struct_109481D0* UnknownB0;
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

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int Count);

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

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_109475E0
{
public:
    ~Class_109475E0();

    int Unknown00;
    int Unknown04;
    Class_10BFBD70 Unknown08;
    Class_10BFBD70 Unknown14;
};

// FUNCTION: 0x109475E0 ??1Class_109475E0@@QAE@XZ
Class_109475E0::~Class_109475E0()
{
}

// FUNCTION: 0x109481D0 ?FUN_109481d0@Class_109481D0@@QAE_NH@Z
bool Class_109481D0::FUN_109481d0(int Mask)
{
    if (UnknownB0)
    {
        if (UnknownB0->Unknown04 & Mask)
            return true;
    }
    return false;
}
