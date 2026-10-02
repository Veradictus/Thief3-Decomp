// Game/Unsorted_10ACA680_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6FEE8;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10E6FEE8* Obj);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E67938
{
public:
    ~Class_10E67938();

    virtual void FUN_10acb0c0(int Code, int A, int B, int C);
};

class Class_10E6FEE8 : public Class_10E67938
{
public:
    ~Class_10E6FEE8();

    virtual void FUN_10acb0c0(int Code, int A, int B, int C);
    void FUN_10acae80(int A, int B, int C);
};

// FUNCTION: 0x10ACA790 ??1Class_10E6FEE8@@QAE@XZ
Class_10E6FEE8::~Class_10E6FEE8()
{
    DAT_10f46da0->Virtual2(this);
}
