// Game/Unsorted_10AA28A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A37700 {
public:
    void FUN_10a37700();
};

struct Struct_10AA3520 {
    char Unknown00[0x10];
    Class_10A37700* Unknown10;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10E6D424 {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10aa28a0(int p1, int p2, int p3);
};

// FUNCTION: 0x10AA28A0 ?FUN_10aa28a0@Class_10E6D424@@UAEHHHH@Z
int Class_10E6D424::FUN_10aa28a0(int p1, int p2, int p3)
{
    DAT_10f35dec->Unknown10->FUN_10a37700();
    return 1;
}
