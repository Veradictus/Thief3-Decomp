// Game/Unsorted_10932FB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_109331D0
{
public:
    virtual void __stdcall Virtual0();
    virtual void __stdcall Virtual1();
    virtual void __stdcall Virtual2();
};

class Class_10E49D44
{
public:
    ~Class_10E49D44();

    virtual int FUN_10932fa0();

    void FUN_10932f40();

    int Unknown04;
    Object_109331D0* Unknown08;
};

// FUNCTION: 0x109331D0 ??1Class_10E49D44@@QAE@XZ
Class_10E49D44::~Class_10E49D44()
{
    FUN_10932f40();
    if (Unknown08)
    {
        Unknown08->Virtual2();
        Unknown08 = 0;
    }
}
