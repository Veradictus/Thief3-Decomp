// Game/Unsorted_10ACC0D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330;

class Class_10E70098;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10E70098* Obj);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E67938
{
public:
    virtual ~Class_10E67938();
};

class Class_10E7007C
{
public:
    virtual float FUN_10acc440(int A, int B, Class_1098E330* Obj);
};

class Class_10E70098 : public Class_10E67938, public Class_10E7007C
{
public:
    ~Class_10E70098();
};

// FUNCTION: 0x10ACC3E0 ??1Class_10E70098@@UAE@XZ
Class_10E70098::~Class_10E70098()
{
    DAT_10f46da0->Virtual2(this);
}
