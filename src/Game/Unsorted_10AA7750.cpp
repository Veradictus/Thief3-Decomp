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

class Class_10AA7880_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4(void* p1);
};

extern void* DAT_10f46d9c;

class Class_10AA7880
{
public:
    void FUN_10aa7880();

    char Unknown00[0xC];
    Class_10AA7880_Member* Unknown0C;
};

class Object_10AA7810
{
public:
    virtual ~Object_10AA7810();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual int Virtual8();
};

class Class_10AA7810
{
public:
    void FUN_10aa7810(int A, int B);

    char Unknown00[8];
    void* Unknown08;
    Object_10AA7810* Unknown0C;
};

class Object_10AA7850
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int Virtual7();
};

class Class_10AA7850
{
public:
    int FUN_10aa7850();

    char Unknown00[0xc];
    Object_10AA7850* Unknown0C;
};

// FUNCTION: 0x10AA7810 ?FUN_10aa7810@Class_10AA7810@@QAEXHH@Z
void Class_10AA7810::FUN_10aa7810(int A, int B)
{
    if (Unknown08 && Unknown0C && Unknown0C->Virtual8() == B)
    {
        delete Unknown0C;
        Unknown0C = 0;
    }
}

// FUNCTION: 0x10AA7850 ?FUN_10aa7850@Class_10AA7850@@QAEHXZ
int Class_10AA7850::FUN_10aa7850()
{
    if ((Unknown0C->Virtual7() & 2) && !(Unknown0C->Virtual7() & 1))
        return 1;
    return 0;
}

// FUNCTION: 0x10AA7880 ?FUN_10aa7880@Class_10AA7880@@QAEXXZ
void Class_10AA7880::FUN_10aa7880()
{
    if (Unknown0C)
        Unknown0C->Virtual4(DAT_10f46d9c);
}

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
