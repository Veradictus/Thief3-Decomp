// Game/Class_10C63A50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C63A50Unknown08
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3(int A, int B);
};

class Class_10C63A50
{
public:
    void FUN_10c63a50(int A, int B);

    char Unknown00[8];
    Class_10C63A50Unknown08* Unknown08;
    char Unknown0C[0x20];
    int Unknown2C;
};

// FUNCTION: 0x10C63A50 ?FUN_10c63a50@Class_10C63A50@@QAEXHH@Z
void Class_10C63A50::FUN_10c63a50(int A, int B)
{
    Unknown08->Virtual3(A, B);
    Unknown2C = 0;
}
