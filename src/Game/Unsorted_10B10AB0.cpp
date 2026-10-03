// Game/Unsorted_10B10AB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A73EF0_Object
{
public:
    virtual void Virtual0();

    char Unknown04[0x30];
    int Unknown34;
    int Unknown38;
};

class Class_10A73EF0_Table
{
public:
    Class_10A73EF0_Object* FUN_10af33e0(int Handle);

    int Unknown00;
    int Unknown04;
    Class_10A73EF0_Object** Unknown08;
};

Class_10A73EF0_Table* FUN_10af3470();

class Class_10B10B30
{
public:
    void FUN_10b10b30(unsigned short Value);

    unsigned short Unknown00;
    unsigned short Unknown02;
    int Unknown04;
};

// FUNCTION: 0x10B10B30 ?FUN_10b10b30@Class_10B10B30@@QAEXG@Z
void Class_10B10B30::FUN_10b10b30(unsigned short Value)
{
    if (Value == 0)
    {
        Unknown02 = Value;
        return;
    }
    Class_10A73EF0_Object* Obj = FUN_10af3470()->FUN_10af33e0(Value);
    if (Obj->Unknown38 * Obj->Unknown34 <= 4)
        Value |= 0x8000;
    else
        Value &= 0x7fff;
    Unknown02 = Value;
}
