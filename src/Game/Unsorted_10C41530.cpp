// Game/Unsorted_10C41530.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10AB5B20
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
};

class Class_10AB5B20
{
public:
    Class_10AB5B20(const Class_10AB5B20& Other)
    {
        Unknown00 = Other.Unknown00;
        if (Unknown00)
            Unknown00->Virtual1();
    }
    ~Class_10AB5B20();

    Object_10AB5B20* Unknown00;
};

struct Struct_10C41530
{
    Class_10AB5B20 Unknown00;
    char Unknown04[8];
};

class Class_10C41530
{
public:
    Class_10AB5B20 FUN_10c41530(int Index);

    char Unknown00[0xC0];
    Struct_10C41530* UnknownC0;
};

struct Struct_10C423F0
{
};

class Class_10C423F0
{
public:
    void FUN_10c423f0();
    void FUN_10c415d0();

    char Unknown00[0x18];
    Struct_10C423F0* Unknown18;
};

// FUNCTION: 0x10C41530 ?FUN_10c41530@Class_10C41530@@QAE?AVClass_10AB5B20@@H@Z
Class_10AB5B20 Class_10C41530::FUN_10c41530(int Index)
{
    return UnknownC0[Index].Unknown00;
}

// FUNCTION: 0x10C423F0 ?FUN_10c423f0@Class_10C423F0@@QAEXXZ
void Class_10C423F0::FUN_10c423f0()
{
    FUN_10c415d0();
    delete Unknown18;
    Unknown18 = 0;
}
