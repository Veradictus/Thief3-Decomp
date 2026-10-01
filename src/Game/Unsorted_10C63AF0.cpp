// Game/Unsorted_10C63AF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C63CF0_Member {
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
    virtual void F2() = 0;
    virtual void F3() = 0;
    virtual void F4() = 0;
    virtual void F5() = 0;
    virtual void F6() = 0;
    virtual void F7() = 0;
    virtual void F8() = 0;
    virtual void F9() = 0;
    virtual void FA() = 0;
    virtual void FB() = 0;
    virtual void FC() = 0;
    virtual void FD() = 0;
    virtual void FE() = 0;
    virtual void FF() = 0;
    virtual void F10() = 0;
    virtual void F11() = 0;
};

class Class_10C63CF0 {
public:
    char Unknown00[8];
    Class_10C63CF0_Member* Field8;
    void FUN_10c63cf0();
};

class Class_10C63D00_Member {
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
    virtual void F2() = 0;
    virtual void F3() = 0;
    virtual void F4() = 0;
    virtual void F5() = 0;
    virtual void F6() = 0;
    virtual void F7() = 0;
    virtual void F8() = 0;
    virtual void F9() = 0;
    virtual void FA() = 0;
    virtual void FB() = 0;
};

class Class_10C63D00 {
public:
    char Unknown00[8];
    Class_10C63D00_Member* Field8;
    void FUN_10c63d00();
};

class Class_109E3C90
{
public:
    void FUN_109e3c90(int p1);
};

class Class_10C63AF0
{
public:
    void FUN_10c63af0(int p1);

    char Unknown00[0xC];
    Class_109E3C90 Field0C;
};

// FUNCTION: 0x10C63AF0 ?FUN_10c63af0@Class_10C63AF0@@QAEXH@Z
void Class_10C63AF0::FUN_10c63af0(int p1)
{
    Field0C.FUN_109e3c90(p1);
}

// FUNCTION: 0x10C63CF0 ?FUN_10c63cf0@Class_10C63CF0@@QAEXXZ
void Class_10C63CF0::FUN_10c63cf0()
{
    Field8->F11();
}

// FUNCTION: 0x10C63D00 ?FUN_10c63d00@Class_10C63D00@@QAEXXZ
void Class_10C63D00::FUN_10c63d00()
{
    Field8->FB();
}
