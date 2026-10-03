// Game/Unsorted_10B70AC0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Window
{
public:
    void FUN_10a53560(int A);
};

class Class_10E871C8
{
public:
    virtual void Virtual0();

    void FUN_10b70db0(int A);

    char Unknown04[0x102F0];
    int Unknown102F4;
};

Class_10E871C8* FUN_10b70460();

class Class_10B70F20 : public Window
{
public:
    void FUN_10b70ac0(int A);
    void FUN_10b70f20(int A);
};

// FUNCTION: 0x10B70F20 ?FUN_10b70f20@Class_10B70F20@@QAEXH@Z
void Class_10B70F20::FUN_10b70f20(int A)
{
    FUN_10a53560(A);
    if (FUN_10b70460()->Unknown102F4 > 0)
    {
        FUN_10b70ac0(A);
        FUN_10b70460()->FUN_10b70db0(A);
    }
}
