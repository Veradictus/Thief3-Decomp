// Game/Unsorted_10ACE5F0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E70204;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10E70204* Obj);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E67938
{
public:
    ~Class_10E67938();

    virtual void Virtual0(int Code, int A, int B, int C);
};

class Class_10E70204 : public Class_10E67938
{
public:
    ~Class_10E70204();

    virtual void Virtual0(int Code, int A, int B, int C);
};

// FUNCTION: 0x10ACE5F0 ??1Class_10E70204@@QAE@XZ
Class_10E70204::~Class_10E70204()
{
    DAT_10f46da0->Virtual2(this);
}
