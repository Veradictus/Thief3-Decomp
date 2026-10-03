// Game/Unsorted_10B2BE60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B2BE60
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E7B6BC
{
public:
    virtual void Virtual0();
    virtual bool Virtual1();
    virtual void Virtual2();
    virtual Struct_10B2BE60 FUN_10b2be60();

    char Unknown04[8];
    Struct_10B2BE60 Unknown0C;
    char Unknown18[0x24];
    Struct_10B2BE60 Unknown3C;
};

// FUNCTION: 0x10B2BE60 ?FUN_10b2be60@Class_10E7B6BC@@UAE?AUStruct_10B2BE60@@XZ
Struct_10B2BE60 Class_10E7B6BC::FUN_10b2be60()
{
    if (Virtual1())
        return Unknown0C;
    return Unknown3C;
}
