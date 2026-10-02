// Game/Unsorted_10B8ACF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FVector
{
public:
    float X, Y, Z;
};

class Class_10D9FEE0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();

    FVector FUN_10da00f0();
    unsigned FUN_10da0400();
};

class Object_10B8B420
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(unsigned A);

    int Unknown04;
    char Unknown08[0xD8];
    FVector UnknownE0;
};

class Class_10E894C8 : public Class_10D9FEE0
{
public:
    virtual FVector FUN_10b8b450();

    void FUN_10b8b420(Object_10B8B420* Target);

    char Unknown04[0x28];
    Object_10B8B420* Unknown2C;
};

// FUNCTION: 0x10B8B420 ?FUN_10b8b420@Class_10E894C8@@QAEXPAVObject_10B8B420@@@Z
void Class_10E894C8::FUN_10b8b420(Object_10B8B420* Target)
{
    Unknown2C = Target;
    if (Target && Target->Unknown04 == 2)
        Target->Virtual2(FUN_10da0400());
}

// FUNCTION: 0x10B8B450 ?FUN_10b8b450@Class_10E894C8@@UAE?AVFVector@@XZ
FVector Class_10E894C8::FUN_10b8b450()
{
    if (Unknown2C && Unknown2C->Unknown04 == 2)
        return Unknown2C->UnknownE0;
    return FUN_10da00f0();
}
