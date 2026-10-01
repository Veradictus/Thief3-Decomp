// Game/Unsorted_10A56180.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E67FD0
{
public:
    Class_10E67FD0();

    virtual ~Class_10E67FD0();

    char Unknown04[0xE4];
    int Unknown0E8;
    char Unknown0EC[0x2C];
};

class Class_10E68938 : public Class_10E67FD0
{
public:
    Class_10E68938();

    virtual ~Class_10E68938();

    int Unknown118;
    FArray Unknown11C;
    FArray Unknown128;
    bool Unknown134;
};

// FUNCTION: 0x10A56620 ??0Class_10E68938@@QAE@XZ
Class_10E68938::Class_10E68938() : Unknown118(0), Unknown134(false)
{
    Unknown0E8 = 6;
}

// FUNCTION: 0x10A568A0 ??_GClass_10E68938@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10A56620's definition in this unit.
