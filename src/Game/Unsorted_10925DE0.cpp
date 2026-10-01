// Game/Unsorted_10925DE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10925FC0
{
public:
    Class_10AB5B20 FUN_10925fc0(int Index);

    char Unknown00[0xcc];
    Class_10AB5B20* UnknownCC;
};

// FUNCTION: 0x10925FC0 ?FUN_10925fc0@Class_10925FC0@@QAE?AVClass_10AB5B20@@H@Z
Class_10AB5B20 Class_10925FC0::FUN_10925fc0(int Index)
{
    return UnknownCC[Index];
}
