// Game/Unsorted_10B7AC50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int A, void* B, int C, int* D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10B7AC50
{
public:
    void FUN_10b7ac50();

    void* Unknown00;
    char Unknown04[8];
    int Unknown0C;
    char Unknown10[0x10];
    bool Unknown20;
};

// FUNCTION: 0x10B7AC50 ?FUN_10b7ac50@Class_10B7AC50@@QAEXXZ
void Class_10B7AC50::FUN_10b7ac50()
{
    if (Unknown20)
    {
        int Value = Unknown0C;
        DAT_10f46da0->Virtual5(0x3e, Unknown00, -1, &Value);
    }
}
