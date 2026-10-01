// Game/Unsorted_10A18E50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A18E50
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8(int A, int B, int C, int D);

    void FUN_10a18e50(int A, int B, int C, int D);

    char Unknown04[0x670];
    int Unknown674;
};

// FUNCTION: 0x10A18E50 ?FUN_10a18e50@Class_10A18E50@@QAEXHHHH@Z
void Class_10A18E50::FUN_10a18e50(int A, int B, int C, int D)
{
    if (!A)
        A = Unknown674;
    Virtual8(A, B, C, D);
}
