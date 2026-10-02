// Game/Unsorted_10A18E90_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10A18F40
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(float A);
};

class Class_10A4DFD0
{
public:
    void FUN_10a4dfd0();
};

Class_10A4DFD0* __stdcall FUN_10a4f900(int A, Object_10A18F40* B, void** C);

class Class_10E5D70C
{
public:
    virtual void Virtual0();
    virtual void FUN_10a18f40(float A);

    void FUN_10a18e90();
    void FUN_10a18f10();

    Object_10A18F40* Unknown04;
    char Unknown08[0x630];
    void* Unknown638[14];
    float Unknown670;
};

// FUNCTION: 0x10A18F10 ?FUN_10a18f10@Class_10E5D70C@@QAEXXZ
void Class_10E5D70C::FUN_10a18f10()
{
    for (int i = 0; i < 14; i++)
        FUN_10a4f900(i, Unknown04, &Unknown638[i])->FUN_10a4dfd0();
}
