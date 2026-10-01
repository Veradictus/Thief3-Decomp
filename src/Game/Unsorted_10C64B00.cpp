// Game/Unsorted_10C64B00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// FUNCTION: 0x10C64E50 ?FUN_10c64e50@@YA?AVClass_10AB5B20@@PAV1@@Z
Class_10AB5B20 FUN_10c64e50(Class_10AB5B20* Other)
{
    return *Other;
}
