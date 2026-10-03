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

class Class_10E9CB00;

struct Struct_10C64E10
{
    Class_10E9CB00* Unknown00;
    int Unknown04;
};

class Class_10C662F0
{
public:
    void FUN_10c64e10(Class_10E9CB00* A);

    char Unknown00[0x178];
    int Unknown178;
    int Unknown17C;
    Struct_10C64E10* Unknown180;
};

// FUNCTION: 0x10C64E10 ?FUN_10c64e10@Class_10C662F0@@QAEXPAVClass_10E9CB00@@@Z
void Class_10C662F0::FUN_10c64e10(Class_10E9CB00* A)
{
    for (int i = 0; i < Unknown178; i++)
    {
        Struct_10C64E10* Entry = &Unknown180[i];
        if (Entry->Unknown00 == A)
            Entry->Unknown04++;
    }
}

// FUNCTION: 0x10C64E50 ?FUN_10c64e50@@YA?AVClass_10AB5B20@@PAV1@@Z
Class_10AB5B20 FUN_10c64e50(Class_10AB5B20* Other)
{
    return *Other;
}
