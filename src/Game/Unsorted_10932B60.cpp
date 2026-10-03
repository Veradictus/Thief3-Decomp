// Game/Unsorted_10932B60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E4A668
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual ~Class_10E4A668();
};

Class_10E4A668* FUN_10955790(int B);

int FUN_10932c50(int A, Class_10E4A668* P);

void FUN_10932d40(int A, int B);

// FUNCTION: 0x10932DC0 ?FUN_10932dc0@@YAXHH@Z
void FUN_10932dc0(int A, int B)
{
    Class_10E4A668* P = FUN_10955790(B);
    if (P)
    {
        FUN_10932d40(A, FUN_10932c50(A, P));
        delete P;
    }
}
