// Game/Unsorted_10ACBF10_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6FFE0;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10E6FFE0* Obj);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E67938
{
public:
    ~Class_10E67938();

    virtual void Virtual0();
};

class Class_10E6FFE0 : public Class_10E67938
{
public:
    ~Class_10E6FFE0();
};

// FUNCTION: 0x10ACBF10 ??1Class_10E6FFE0@@QAE@XZ
Class_10E6FFE0::~Class_10E6FFE0()
{
    DAT_10f46da0->Virtual2(this);
}
