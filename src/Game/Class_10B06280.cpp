// Game/Class_10B06280.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Field at 0x448 member call to vtable at 0x10E71638

class Class_10E71638_Member {
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
    virtual void Virtual2() = 0;
    virtual void Virtual3() = 0;
    virtual void Virtual4() = 0;
    virtual void Virtual5() = 0;
    virtual void Virtual6() = 0;
    virtual void Virtual7() = 0;
    virtual void Virtual8() = 0;
    virtual void Virtual9() = 0;
    virtual void VirtualA() = 0;
};

class Class_10B06280 {
public:
    char Unknown00[0x448];
    Class_10E71638_Member* Field448;
    void FUN_10b06280();
};

// FUNCTION: 0x10B06280 ?FUN_10b06280@Class_10B06280@@QAEXXZ
void Class_10B06280::FUN_10b06280()
{
    Field448->VirtualA();
}
