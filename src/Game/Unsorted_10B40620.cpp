// Game/Unsorted_10B40620.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

    char Unknown04[0x114];
};

class Class_10E7FD18 : public Class_10E67FD0
{
public:
    Class_10E7FD18();

    virtual ~Class_10E7FD18();

    int Unknown118;
    int Unknown11C;
    int Unknown120;
    int Unknown124;
    FArray Unknown128;
    int Unknown134;
};

// FUNCTION: 0x10B40710 ??0Class_10E7FD18@@QAE@XZ
Class_10E7FD18::Class_10E7FD18() : Unknown118(0), Unknown11C(0), Unknown124(-1), Unknown134(0)
{
}

// FUNCTION: 0x10B40760 ??_GClass_10E7FD18@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B40710's definition in this unit.
