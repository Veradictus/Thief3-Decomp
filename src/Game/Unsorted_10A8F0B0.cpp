// Game/Unsorted_10A8F0B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A8F2E0 {
public:
    void FUN_10a8f2e0(int* p1);
};

class Class_10E6C8CC {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10a8f590();

    char Unknown04[0x10];
    int Unknown14;
    char Unknown18[0xc];
    Class_10A8F2E0 Unknown24;
};

// FUNCTION: 0x10A8F590 ?FUN_10a8f590@Class_10E6C8CC@@UAEXXZ
void Class_10E6C8CC::FUN_10a8f590()
{
    Unknown24.FUN_10a8f2e0(&Unknown14);
}
