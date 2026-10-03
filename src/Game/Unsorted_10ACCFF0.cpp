// Game/Unsorted_10ACCFF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E700F0;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10E700F0* Obj);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E67938
{
public:
    virtual void FUN_10c13ea0(int A, int B, int C, int D);
    virtual ~Class_10E67938();
};

class Class_10E70060
{
public:
    virtual float FUN_10ace340(int A, int B, int C) = 0;
};

class Class_10E700F0 : public Class_10E67938, public Class_10E70060
{
public:
    ~Class_10E700F0();

    virtual void FUN_10c13ea0(int A, int B, int C, int D);
    virtual float FUN_10ace340(int A, int B, int C);
};

// FUNCTION: 0x10ACD640 ??1Class_10E700F0@@UAE@XZ
Class_10E700F0::~Class_10E700F0()
{
    DAT_10f46da0->Virtual2(this);
}
