// Game/Unsorted_10A81FE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C00A60
{
public:
    void FUN_10c00a60(int Count);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E6C1F0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10a823c0(int Value);

    Class_10C00A60 Unknown04;
};

class Class_10E6C104
{
public:
    Class_10E6C104();

    virtual ~Class_10E6C104();

    char Unknown04[4];
};

struct Struct_10A82E20
{
    int Unknown00;
    int Unknown04;
    int Unknown08;

    Struct_10A82E20() : Unknown00(0), Unknown04(0), Unknown08(0) {}
};

class Class_10E6C290 : public Class_10E6C104
{
public:
    Class_10E6C290();

    virtual ~Class_10E6C290();

    Struct_10A82E20 Unknown08;
    int Unknown14;
    int Unknown18;
    Struct_10A82E20 Unknown1C;
};

extern void* DAT_10e6c364[];

class Class_10E6C364 {
public:
    Class_10E6C364();

    void** Unknown00;
    char Unknown04[4];
    int Unknown08;
    int Unknown0c;
    int Unknown10;
};

// FUNCTION: 0x10A823C0 ?FUN_10a823c0@Class_10E6C1F0@@UAEXH@Z
void Class_10E6C1F0::FUN_10a823c0(int Value)
{
    Class_10C00A60* Array = &Unknown04;
    int Index = Array->Unknown00;
    Array->FUN_10c00a60(Index + 1);
    Array->Unknown08[Index] = Value;
}

// FUNCTION: 0x10A82E20 ??0Class_10E6C290@@QAE@XZ
Class_10E6C290::Class_10E6C290() : Unknown14(0), Unknown18(-1)
{
}

// FUNCTION: 0x10A82E50 ??_GClass_10E6C290@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10A82E20's definition in this unit.

// FUNCTION: 0x10A84800 ??0Class_10E6C364@@QAE@XZ
Class_10E6C364::Class_10E6C364()
{
    Unknown00 = DAT_10e6c364;
    Unknown08 = 0;
    Unknown0c = 0;
    Unknown10 = 0;
}
