// Game/Class_10B062A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Field at 0x448 member call to vtable at 0x10E71638

class Class_10E71638_Member {
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
};

class Class_10B062A0 {
public:
    char Unknown00[0x448];
    Class_10E71638_Member* Field448;
    void FUN_10b062a0();
};

// FUNCTION: 0x10B062A0 ?FUN_10b062a0@Class_10B062A0@@QAEXXZ
void Class_10B062A0::FUN_10b062a0()
{
    Field448->Virtual1();
}
