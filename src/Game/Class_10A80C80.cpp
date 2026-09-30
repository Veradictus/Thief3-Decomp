// Game/Class_10A80C80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Member {
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
    virtual void F2() = 0;
    virtual void F3() = 0;
    virtual void F4() = 0;
};

class Class_10A80C80 {
public:
    char Unknown00[0x10];
    Member* Field10;
    void FUN_10a80c80();
};

// FUNCTION: 0x10A80C80 ?FUN_10a80c80@Class_10A80C80@@QAEXXZ
void Class_10A80C80::FUN_10a80c80()
{
    Field10->F4();
}
