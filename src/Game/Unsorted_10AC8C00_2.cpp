// Game/Unsorted_10AC8C00_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10990E20;

class Class_10E6FC80;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E6FC80* Obj, int A, int B, int C);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E67938
{
public:
    Class_10E67938();
    ~Class_10E67938();

    virtual void FUN_10ac8e80(int Type, Class_10990E20* Source, int C, int D);
};

class Class_10E6FC80 : public Class_10E67938
{
public:
    Class_10E6FC80();

    virtual void FUN_10ac8e80(int Type, Class_10990E20* Source, int C, int D);
};

// FUNCTION: 0x10AC8E20 ??0Class_10E6FC80@@QAE@XZ
Class_10E6FC80::Class_10E6FC80()
{
    DAT_10f46da0->Virtual1(this, 0x3d, -1, -1);
}
