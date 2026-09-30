// Game/Class_10B06290.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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
    virtual void VirtualB() = 0;
};

class Class_10B06290 {
public:
    char Unknown00[0x448];
    Class_10E71638_Member* Field448;
    void FUN_10b06290();
};

// FUNCTION: 0x10B06290 ?FUN_10b06290@Class_10B06290@@QAEXXZ
void Class_10B06290::FUN_10b06290()
{
    Field448->VirtualB();
}
