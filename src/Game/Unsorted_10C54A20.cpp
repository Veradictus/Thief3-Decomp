// Game/Unsorted_10C54A20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <list>

class Object_10AB5B20
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
};

class Class_10AB5B20
{
public:
    Class_10AB5B20()
    {
        Unknown00 = 0;
    }
    Class_10AB5B20(const Class_10AB5B20& Other)
    {
        Unknown00 = Other.Unknown00;
        if (Unknown00)
            Unknown00->Virtual1();
    }
    ~Class_10AB5B20();

    Object_10AB5B20* Unknown00;
};

struct Struct_10C55320
{
    Struct_10C55320* Unknown00;
    Struct_10C55320* Unknown04;
    char Unknown08[0x14];
    Class_10AB5B20 Unknown1C;
};

class Class_10C55320
{
public:
    Class_10AB5B20 FUN_10c55320();

    char Unknown00[0x20];
    Struct_10C55320* Unknown20;
    char Unknown24[0x34];
    Struct_10C55320* Unknown58;
};

struct Entry_10C55360
{
    char Unknown00[0x14];
    Class_10AB5B20 Value;
};

class Class_10C55360
{
public:
    Class_10AB5B20 FUN_10c55360();

    char Unknown00[0x1C];
    std::list<Entry_10C55360> Unknown1C;
    char Unknown28[0x30];
    std::list<Entry_10C55360>::iterator Unknown58;
};

// FUNCTION: 0x10C55320 ?FUN_10c55320@Class_10C55320@@QAE?AVClass_10AB5B20@@XZ
Class_10AB5B20 Class_10C55320::FUN_10c55320()
{
    Unknown58 = Unknown20->Unknown00;
    if (Unknown58 == Unknown20)
        return Class_10AB5B20();
    return Unknown58->Unknown1C;
}

// FUNCTION: 0x10C55360 ?FUN_10c55360@Class_10C55360@@QAE?AVClass_10AB5B20@@XZ
Class_10AB5B20 Class_10C55360::FUN_10c55360()
{
    ++Unknown58;
    if (Unknown58 == Unknown1C.end())
        return Class_10AB5B20();
    return Unknown58->Value;
}
