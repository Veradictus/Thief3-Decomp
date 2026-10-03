// Game/Unsorted_10A68DB0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6B5C0;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E6B5C0* Obj, int A, int B, int C);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E67938
{
public:
    Class_10E67938();
    ~Class_10E67938();

    virtual void FUN_10a691c0(int Type, int A, int B, int C);
};

class Class_10E6B5C0 : public Class_10E67938
{
public:
    Class_10E6B5C0();

    virtual void FUN_10a691c0(int Type, int A, int B, int C);
};

// FUNCTION: 0x10A690D0 ??0Class_10E6B5C0@@QAE@XZ
Class_10E6B5C0::Class_10E6B5C0()
{
    DAT_10f46da0->Virtual1(this, 0x26, -1, -1);
}
