// Game/Unsorted_10A03A30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AF8250
{
public:
    Class_10AF8250(const Class_10AF8250& Other);
    ~Class_10AF8250();

    char Unknown00[0xC];
};

class Class_10A05FE0
{
public:
    Class_10AF8250 FUN_10a05fe0();

    char Unknown00[0x40];
    Class_10AF8250 Unknown40;
};

class GlobalClass_10A07CA0 {
public:
    void FUN_10a078b0();
};

extern GlobalClass_10A07CA0 DAT_10f397e4;

void FUN_10a082c0();

class Allocator_10FFA700;

extern Allocator_10FFA700* DAT_10ffa700;

class Class_10A0A3C0_Member {
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
};

class Class_10A0A3C0 {
public:
    char Unknown00[0x3c];
    Class_10A0A3C0_Member* Field3c;
    void FUN_10a0a3c0();
};

class Class_10A0A3D0_Member {
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

class Class_10A0A3D0 {
public:
    char Unknown00[0x3c];
    Class_10A0A3D0_Member* Field3c;
    void FUN_10a0a3d0();
};

class Class_10A0A520
{
public:
    char Unknown00[0x4c];
    int Field4c;
    int FUN_10a0a520();
};

void FUN_10a0bed0();

extern void* DAT_10f352d8;

class SomeObject {
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
    virtual void F2() = 0;
    virtual void F3() = 0;
    virtual void F4() = 0;
    virtual void F5() = 0;
    virtual void F6() = 0;
};

extern int DAT_10f39870;

extern int DAT_10f39874;

void FUN_10a123c0();

class InnerObject {
public:
    int Field00;
    int Field04;
};

class Class_10A12DC0 {
public:
    int FUN_10a12dc0();
    char Unknown00[0x40];
    InnerObject* Field40;
};

extern void* DAT_10e5d478[];

class Class_10A12F50
{
public:
    void* Field00;
    void FUN_10a12f50();
};

// FUNCTION: 0x10A0FFC0 ?FUN_10a0ffc0@@YAHXZ
int FUN_10a0ffc0()
{
    return DAT_10f39870;
}

// FUNCTION: 0x10A11EB0 ?FUN_10a11eb0@@YAHXZ
int FUN_10a11eb0()
{
    return DAT_10f39874;
}

// FUNCTION: 0x10A12AE0 ?FUN_10a12ae0@@YAXXZ
void FUN_10a12ae0()
{
    FUN_10a123c0();
}

// FUNCTION: 0x10A12DC0 ?FUN_10a12dc0@Class_10A12DC0@@QAEHXZ
int Class_10A12DC0::FUN_10a12dc0()
{
    return Field40->Field04;
}

// FUNCTION: 0x10A12F50 ?FUN_10a12f50@Class_10A12F50@@QAEXXZ
void Class_10A12F50::FUN_10a12f50()
{
    Field00 = (void*)DAT_10e5d478;
}
