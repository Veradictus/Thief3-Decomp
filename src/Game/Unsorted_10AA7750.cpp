// Game/Unsorted_10AA7750.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E6C104
{
public:
    Class_10E6C104();

    virtual ~Class_10E6C104();

    char Unknown04[4];
};

class Class_10E6D940 : public Class_10E6C104
{
public:
    Class_10E6D940();

    virtual ~Class_10E6D940();

    int Unknown08;
    int Unknown0C;
    FArray Unknown10;
};

class Class_10AA78A0_Field0C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
};

class Class_10AA78A0
{
public:
    void FUN_10aa78a0();

    char Unknown00[0xC];
    Class_10AA78A0_Field0C* Unknown0C;
};

// FUNCTION: 0x10AA78A0 ?FUN_10aa78a0@Class_10AA78A0@@QAEXXZ
void Class_10AA78A0::FUN_10aa78a0()
{
    if (Unknown0C)
        Unknown0C->Virtual1();
}

// FUNCTION: 0x10AA79F0 ??0Class_10E6D940@@QAE@XZ
Class_10E6D940::Class_10E6D940() : Unknown08(0), Unknown0C(0)
{
}

// FUNCTION: 0x10AA7A20 ??_GClass_10E6D940@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10AA79F0's definition in this unit.
