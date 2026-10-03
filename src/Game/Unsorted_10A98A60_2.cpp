// Game/Unsorted_10A98A60_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E662C0
{
public:
    virtual ~Class_10E662C0() {}
};

class Class_10E682E0 : public Class_10E662C0
{
public:
    Class_10E682E0(int Value) : Unknown04(Value) {}

    virtual Class_10E682E0* FUN_10a54ce0();

    int Unknown04;
};

class Class_10E5B578
{
public:
    virtual void Virtual0() = 0;
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E5B578* Listener, int B, int C, Class_10E682E0* D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6DC88_Primary
{
public:
    virtual void FUN_10ba38f0();

    char Unknown04[8];
};

class Class_10E6DC88 : public Class_10E6DC88_Primary, public Class_10E5B578
{
public:
    int Unknown10;
};

class Class_10E6CFB8 : public Class_10E6DC88
{
public:
    virtual void Virtual1();
    virtual void FUN_10a98a60();
};

class Class_10E6CFF0 : public Class_10E6DC88
{
public:
    virtual void Virtual1();
    virtual void FUN_10a98b20();
};

class Class_10E6D00C : public Class_10E6DC88
{
public:
    virtual void Virtual1();
    virtual void FUN_10a98b80();
};

// FUNCTION: 0x10A98A60 ?FUN_10a98a60@Class_10E6CFB8@@UAEXXZ
void Class_10E6CFB8::FUN_10a98a60()
{
    Class_10E682E0 Local(0);
    DAT_10f46da0->Virtual1(this, 0x77, -1, &Local);
}

// FUNCTION: 0x10A98B20 ?FUN_10a98b20@Class_10E6CFF0@@UAEXXZ
void Class_10E6CFF0::FUN_10a98b20()
{
    Class_10E682E0 Local(2);
    DAT_10f46da0->Virtual1(this, 0x77, -1, &Local);
}

// FUNCTION: 0x10A98B80 ?FUN_10a98b80@Class_10E6D00C@@UAEXXZ
void Class_10E6D00C::FUN_10a98b80()
{
    Class_10E682E0 Local(3);
    DAT_10f46da0->Virtual1(this, 0x77, -1, &Local);
}
