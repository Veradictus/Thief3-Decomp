// Game/Unsorted_10A665E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    int FUN_1098e330(int A, int* B);
};

class Class_1098E3D0 : public Class_1098E330
{
public:
    void FUN_1098e3d0(int A, void* B);
};

class Class_10992030 : public Class_1098E3D0
{
public:
    char Unknown00[0xB0];
    int UnknownB0;
};

bool FUN_10a37340(Class_10992030* Obj);

class Class_10E5D360
{
public:
    Class_10E5D360(int Value) : Unknown04(Value) {}

    virtual ~Class_10E5D360() {}
    virtual void Virtual1();
    virtual int FUN_10b9caa0(Class_10E5D360* Other);

    int Unknown04;
};

class Class_10E6B488;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E6B488* Obj, int B, int C, Class_10E5D360* D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6B488
{
public:
    Class_10E6B488();

    virtual void Virtual0();
};

bool FUN_10c5d5b0(int p1, int p2);

class Class_10EB7660
{
public:
    Class_10EB7660();

    virtual ~Class_10EB7660();

    int Unknown04;
};

class Class_109E2A80 : public Class_10EB7660
{
};

class Class_10E6B490 : public Class_109E2A80
{
public:
    ~Class_10E6B490();

    int Unknown08;
};

// FUNCTION: 0x10A66B00 ?FUN_10a66b00@@YGXPAVClass_10992030@@@Z
void __stdcall FUN_10a66b00(Class_10992030* Obj)
{
    int Flag = 0;
    Obj->FUN_1098e330(0x80064b, &Flag);
    if (Flag)
    {
        int Value = 1;
        Obj->FUN_1098e3d0(0x40800056, &Value);
        if (Obj->UnknownB0)
            FUN_10a37340(Obj);
    }
}

// FUNCTION: 0x10A66B60 ??0Class_10E6B488@@QAE@XZ
Class_10E6B488::Class_10E6B488()
{
    Class_10E5D360 Local(0x80064b);
    DAT_10f46da0->Virtual1(this, 1, -1, &Local);
}

// FUNCTION: 0x10A66CF0 ??1Class_10E6B490@@UAE@XZ
Class_10E6B490::~Class_10E6B490()
{
    FUN_10c5d5b0((int)this, Unknown08);
}
