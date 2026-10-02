// Game/Unsorted_10A69580.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6B620;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10E6B620* Obj);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E67938
{
public:
    ~Class_10E67938();

    virtual void FUN_10a4c470(int Type, int A, int B, int C);
};

class Class_10E6B620 : public Class_10E67938
{
public:
    ~Class_10E6B620();
};

int FUN_10977fa0(int A);

class Class_10E6B614
{
public:
    virtual void FUN_10a695b0(int A, int B, int C, int D);
    virtual void Virtual1();
    virtual void Virtual2(int A);
};

// FUNCTION: 0x10A695B0 ?FUN_10a695b0@Class_10E6B614@@UAEXHHHH@Z
void Class_10E6B614::FUN_10a695b0(int A, int B, int C, int D)
{
    if (A >= 0x24 && A <= 0x25)
    {
        int Value = FUN_10977fa0(B);
        Virtual2(Value);
    }
}

// FUNCTION: 0x10A69740 ??1Class_10E6B620@@QAE@XZ
Class_10E6B620::~Class_10E6B620()
{
    DAT_10f46da0->Virtual2(this);
}
