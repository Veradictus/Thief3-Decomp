// Game/Unsorted_10AA7B40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10d3ddc0(void* Reader, int* Out);

void FUN_10d3d3b0(void* Reader, int* Out);

class Class_10E6C14C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10aa7ed0(void* Reader, int A, int B);
    virtual void FUN_10aa7f00(void* Stream, int A, int B);

    char Unknown04[4];
    int Unknown08;
    int Unknown0C;
};

void FUN_10d3d990(void* Stream, int* Value);

void FUN_10d3d2d0(void* Stream, int Value);

class Object_10AA7C30
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3(int A, int B);
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual int Virtual10();
};

class Class_10AA7C30
{
public:
    int FUN_10aa7c30();

    char Unknown00[0xC];
    Object_10AA7C30* Unknown0C;
};

class Class_10E6C104
{
public:
    Class_10E6C104();

    virtual ~Class_10E6C104();

    int Unknown04;
};

struct Struct_10AA7D70
{
    Struct_10AA7D70() : Unknown00(0) {}

    int* Unknown00;
};

class Class_10E6D964 : public Class_10E6C104
{
public:
    Class_10E6D964();

    virtual ~Class_10E6D964();

    void* Unknown08;
    void* Unknown0C;
    Struct_10AA7D70 Unknown10;
};

// FUNCTION: 0x10AA7C30 ?FUN_10aa7c30@Class_10AA7C30@@QAEHXZ
int Class_10AA7C30::FUN_10aa7c30()
{
    if (Unknown0C)
    {
        Unknown0C->Virtual3(0x74, 0);
        return Unknown0C->Virtual10();
    }
    return 0;
}

// FUNCTION: 0x10AA7D70 ??0Class_10E6D964@@QAE@XZ
Class_10E6D964::Class_10E6D964() : Unknown08(0), Unknown0C(0)
{
}

// FUNCTION: 0x10AA7D90 ??_GClass_10E6D964@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10AA7D70's definition in this unit.

// FUNCTION: 0x10AA7ED0 ?FUN_10aa7ed0@Class_10E6C14C@@UAEXPAXHH@Z
void Class_10E6C14C::FUN_10aa7ed0(void* Reader, int A, int B)
{
    FUN_10d3ddc0(Reader, &Unknown08);
    FUN_10d3d3b0(Reader, &Unknown0C);
}

// FUNCTION: 0x10AA7F00 ?FUN_10aa7f00@Class_10E6C14C@@UAEXPAXHH@Z
void Class_10E6C14C::FUN_10aa7f00(void* Stream, int A, int B)
{
    FUN_10d3d990(Stream, &Unknown08);
    FUN_10d3d2d0(Stream, Unknown0C);
}
