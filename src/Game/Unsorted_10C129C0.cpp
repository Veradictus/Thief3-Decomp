// Game/Unsorted_10C129C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10d3ddc0(void* Reader, int* Out);

class Class_10E8C4A4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4(int* A);
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual bool FUN_10c129c0(int A, void* Reader);

    char Unknown04[4];
    int Unknown08;
    int Unknown0C;
};

// FUNCTION: 0x10C129C0 ?FUN_10c129c0@Class_10E8C4A4@@UAE_NHPAX@Z
bool Class_10E8C4A4::FUN_10c129c0(int A, void* Reader)
{
    FUN_10d3ddc0(Reader, &Unknown0C);
    Virtual4(&Unknown0C);
    return true;
}
